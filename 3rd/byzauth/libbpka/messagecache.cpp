/*
 * Copyright (c) 2007, Rutgers, The State University of New Jersey. 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of  Rutgers, The State University of New Jersey, 
 *       nor the names of its contributors may be used to endorse or promote 
 *       products derived from this software without specific prior written 
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY  Rutgers, The State University of New Jersey 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rutgers, The State University of 
 * New Jersey BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Author:  Vivek Pathak 
 * Wed Mar 21 02:43:10 EDT 2007
 *
 *
 */

#include "messagecache.h" 
#include "logger.h"
#include "configfile.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>



#ifdef DEBUG
std::map< std::string, std::map< std::string, std::set<epoch_t> > > todo, sent, delivered; 
std::map< std::string, std::map< std::string, std::map<epoch_t, std::set<std::string> > > > cachers; 
#endif



#define              TS_UPDATE(x,y)          (x =((x<y)?(y):(x))) 



XLogger& cachelog = * XLogManager::GetLogger("cachelog"); 


void MessageCache::Configure(std::string configfile)
{
   ConfigFile cfg;
   if(!cfg.Init(configfile))
   {
      std::cerr << "Cannot init configfile " << configfile << std::endl;
      ::abort();
   }

   std::string logdir =
      cfg.GetStringValue( "Logging" , "LogDirectory" , "." ) ;


   std::string cachelogfile =
      cfg.GetStringValue( "Logging" , "CacheLogFile" , "messagecache.log" ) ;
   cachelog.SetDestination(
      XLogManager::GetFileLogDestination( logdir + "/" + cachelogfile )
      );

   debugger.Configure(configfile); 
}





bool MessageCache::GetCacheSize(unsigned & messages, unsigned & bytes)
{
   CacheLoader cl(this); 
   messages = nmessages = cache.size(); 
   bytes = nbytes; 
   return true; 
}



MessageCache::CacheLoader::CacheLoader(MessageCache * p) 
   : 
   cache(p) 
{
   cache->CacheIn(); 
}



MessageCache::CacheLoader::~CacheLoader() 
{
   cache->CacheOut(); 
}





MessageCache::MessageCache(epoch_t & _lamport_time, 
                           epoch_t & _causal_time, 
                           epoch_t & _local_time, 
                           const std::string& _persistent, const std::string& _self) 
   :
   self(_self), 
   persistent(_persistent),  
   lamport_time(_lamport_time), 
   causal_time(_causal_time),
   local_time(_local_time),
   stable_read(0),
   debugger(_self)
{
   std::ifstream ifs(persistent.c_str());
   if(!ifs.good())
   {
      LOG( cachelog, "Self=%s No persistent cache image found" , self.c_str()) ; 
      return;
   }
   
   boost::archive::xml_iarchive ia(ifs);
   MessageCache & message_cache = *this; 
   ia >> BOOST_SERIALIZATION_NVP(message_cache);  
   LOG( cachelog, "Self=%s Loaded CacheRecords=%d records from cache data image", self.c_str() , cache.size() ) ; 

   trim_cache(); 
}






bool MessageCache::CacheUsage(std::map<std::string, unsigned>& src, std::map<std::string, unsigned>& dst)
{
   CacheLoader cl(this); 

   update_stable_read_vec(); 
   delete_delivered_messages(); 
   
   src.clear(); 
   dst.clear(); 
   for( cached_mesgmap_t::iterator i = cache.begin(); i != cache.end(); i++ ) 
   {
      if( src.find(i->second.source) == src.end() )
         src[i->second.source] = 0; 
      else
         src[i->second.source]++;
      if( dst.find(i->second.destination) == dst.end() )
         dst[i->second.destination] = 0; 
      else
         dst[i->second.destination]++;
   }
   return true;
}









bool MessageCache::Save() 
{
   trim_cache(); 

   LOG( cachelog, "Self=%s Started save of cache data to disk", self.c_str() ) ; 
   std::string filename = persistent + ".tmp" ; 
   std::ofstream ofs(filename.c_str());
   if(!ofs.good())
   {
      abort(); 
      return false; 
   }

   boost::archive::xml_oarchive oa(ofs);
   const MessageCache & message_cache = *this; 
   oa << BOOST_SERIALIZATION_NVP(message_cache);

   if(0 == rename( filename.c_str(), persistent.c_str()))
   {
      LOG( cachelog, "Self=%s Done save of cache data to disk", self.c_str() ) ; 
      return true; 
   }
   
   LOG( cachelog, "Self=%s Error saving cache data to disk", self.c_str() ) ; 
   return false;
}










     // the basic thing to do here is to pass all the correct timestamps
     // and send only the messages required
     //!! note that max_num_messages = 0 means unlimited !!
     //----------------------------------------------------------------------

void MessageCache::OutGoingEvent(const std::vector<std::string>& to, std::string& mesg, unsigned int max_num_messages)
{
   CacheLoader cl(this); 
   
   trim_cache(); 

   ltv[self].timestamp = ++lamport_time; 
   ctm[self][self].timestamp = ++causal_time; 


   Envelope e; 

   for( std::vector<std::string>::const_iterator i = to.begin(); i != to.end(); i++ )
      e.dest.insert(*i); 
   

   vector_ets_t cached_cts; //todo get rid of
   epoch_t prevlt = 0; 
   for( cached_mesgmap_t::iterator i = cache.begin(); i != cache.end() ; i++ ) 
   {
      CacheRecord & cr = i->second; 
      std::string & source = cr.source; 

      cached_cts[source].timestamp = MAX(cached_cts[source].timestamp, i->second.causal_time.timestamp); 

      if( max_num_messages && e.messages.size() >= max_num_messages )
         continue; 

      ltv[self].timestamp = ++lamport_time; 
      ctm[self][self].timestamp = ++causal_time; 

      if( i->second.expiry < local_time ) 
      {
         debugger.Expire( i->second.message ) ;
         continue; 
      }

           // decision for sending:
           // do not send if a later causal time at the source is known to the current destination 
           // this is because each older message is received before a newer message, hence this 
           // one must be in the destination's cache already 
      epoch_t mincts = 0; 
      for( std::vector<std::string>::const_iterator j = to.begin() ; j != to.end() ; j++ ) 
      {
         if( j == to.begin() && ctm[*j].find(source) != ctm[*j].end() )
            mincts = ctm[*j][source].timestamp; 

         else if( ctm[*j].find(source) == ctm[*j].end()  )
            continue; 

         else if( mincts > ctm[*j][source].timestamp )
            mincts = ctm[*j][source].timestamp;
      }
      
           // why min of all? 
           // be conservative and send all the messages that might need sending to
           // any peer.  this works because the receiver will take care of eliminating
           // the extra messages based on causal time of message sender 

      if(i->second.causal_time.timestamp > mincts)
         e.messages.push_back(i->second) ; 

      if( e.ctv.find(source) == e.ctv.end() ) 
         e.ctv[source].timestamp = 0; 
      e.ctv[source].timestamp = MAX(e.ctv[source].timestamp, i->second.causal_time.timestamp);

      assert ( prevlt <= i->second.lamport_time.timestamp ) ; 
      prevlt = i->second.lamport_time.timestamp ; 
   }

   ltv[self].timestamp = ++lamport_time; 
   ctm[self][self].timestamp = ++causal_time; 

   e.source = self; 
   e.lt.timestamp = lamport_time; 
   e.ctv = ctm[self]; 
   update_stable_read_vec() ;
   e.sr = srv[self]; 

        // we are hiding some latest timestamps from peer to allow fewer than 
        // max messages.  but we want to share latest for peers that are not part 
        // of the 
   //for(  vector_ets_t::iterator i = ctm[self].begin() ; i != ctm[self].end() ; i++ )
   //   if( e.ctv.find(i->first) == e.ctv.end() && cached_cts.find(i->first) == cached_cts.end() )
   //      e.ctv[i->first] = i->second; 


   std::ostringstream os;
   boost::archive::xml_oarchive oa(os);
   oa << BOOST_SERIALIZATION_NVP(e) ;   
   mesg = os.str(); 

   LOG( cachelog, "Self=%s LocalTime=%llu Sending NumOutMessages=%d messages in outgoing event to NumPeers=%d" , 
        self.c_str(), local_time, e.messages.size(), to.size()) ; 
}











     //
     // Should get the incoming messages and keep the local ones 
     // separete for later call 
     // maintain the timestamps and erase delivered messages
     // avoid delivery of stale messages to self
     //// todo : validate integrity of encrypt
     //------------------------------------------------------------

void MessageCache::InComingEvent  (const std::string& from, const std::string& mesg)
{
   CacheLoader cl(this); 

   ltv[self].timestamp = ++lamport_time; 
   ctm[self][self].timestamp = ++causal_time; 

        // get the message envelope 
   Envelope e; 
   std::istringstream ins;
   ins.str(mesg); 
   boost::archive::xml_iarchive ia(ins);
   ia >> BOOST_SERIALIZATION_NVP(e) ;

   LOG( cachelog, "Self=%s LocalTime=%llu Incoming event NumInMessages=%d records from %s with ECT=%llu ELT=%llu  LT=%llu CT=%llu",  
        self.c_str(), local_time, e.messages.size(), from.c_str(), e.ctv[e.source].timestamp, e.lt.timestamp, lamport_time, causal_time ) ; 

        //-----------------------------------------------
        // receive messages
   epoch_t lt = 0; 
   int nlocal = 0, ndirect = 0; 
   for( unsigned int i = 0; i < e.messages.size(); i++ ) 
   {
      e.messages[i].local_time = local_time;

           // sending to oneself - this could happen because infection protocol  
           // doesnt ignore messages going back to source
      if( e.messages[i].source == self ) 
         continue; 

           // we have already sent messages to target with later cts or same (i.e. same message recvd again) =
      if( e.messages[i].causal_time.timestamp <= ctm[self][e.messages[i].source].timestamp )
      {
#ifdef DEBUG
         assert( cachers[e.messages[i].source][e.messages[i].destination][e.messages[i].causal_time.timestamp].size() > 0 ||
                 delivered[e.messages[i].source][e.messages[i].destination].find(e.messages[i].causal_time.timestamp) != 
                 delivered[e.messages[i].source][e.messages[i].destination].end() ) ; 
#endif
         continue; 
      }

           // but - out of order is possible in constrained mode
//            // i am the receiver and already know of later times from the sender
//            // i.e. out of order delivery or repeat
//       else if( e.messages[i].destination == self && 
//                e.messages[i].lamport_time.timestamp <= ltv[e.messages[i].source].timestamp)
//       {
// #ifdef DEBUG
//          assert( delivered[e.messages[i].source][e.messages[i].destination].find(e.messages[i].causal_time.timestamp) != 
//                  delivered[e.messages[i].source][e.messages[i].destination].end() ) ; 
// #endif
//          continue; 
//       }

           // messages should be in correct order else the timestamp update and skips 
           // above will lose messages. assert this.
      assert( e.messages[i].lamport_time.timestamp != 0 ) ; 
      assert( (!lt) || (lt <= e.messages[i].lamport_time.timestamp) ) ; 
           //lt = e.messages[i].lamport_time.timestamp; 


           // !! But if the messages come in wrong time order in the vector, then we have a problem
           // okay so we got a new message from a source - reflect in ts vector
           // and timestamp for partial order
      TS_UPDATE( lamport_time, e.messages[i].lamport_time.timestamp);

      if( ltv.find( e.messages[i].source ) == ltv.end() )
         ltv[e.messages[i].source].timestamp = 0; 
      TS_UPDATE( ltv[e.messages[i].source].timestamp, e.messages[i].lamport_time.timestamp); 

      if( srv.find( e.messages[i].source ) == srv.end() )
         srv[e.messages[i].source].timestamp = 0; 
      TS_UPDATE( srv[e.messages[i].source].timestamp, e.messages[i].stable_read.timestamp); 

      assert( srv[e.messages[i].source].timestamp < lamport_time ) ; 
      
      if( ctm[from].find(e.messages[i].source) == ctm[from].end() )
         ctm[from][e.messages[i].source].timestamp = 0;
      TS_UPDATE( ctm[from][e.messages[i].source].timestamp, e.messages[i].causal_time.timestamp) ; 

      if( ctm[self].find(e.messages[i].source) == ctm[self].end() )
         ctm[self][e.messages[i].source].timestamp = 0;
      TS_UPDATE( ctm[self][e.messages[i].source].timestamp, e.messages[i].causal_time.timestamp) ; 

      ltv[self].timestamp = ++lamport_time; 
      ctm[self][self].timestamp = ++causal_time; 

           // if local deliver else save
      if( e.messages[i].destination == self ) 
      {
         std::pair<epoch_t, CacheRecord> kvp(e.messages[i].lamport_time.timestamp, e.messages[i]) ;
         debugger.Deliver( e.messages[i].message ) ;
         localmesg.insert(kvp) ; 
         nlocal++;
      }

//            // Optimization:  
//            // Coreceiver optimization 
//            // must be delivered to co-receiver so no point in storing
//            // can this be reflected in the timestamps? yes but that may be risky 
//       else if( e.dest.find( e.messages[i].destination ) != e.dest.end() )
//       {
// #if 0
//          TS_UPDATE( ltv[e.messages[i].destination].timestamp, e.messages[i].lamport_time.timestamp); 
// #endif
//          ndirect++;
//       }

      else
      {
         std::pair<epoch_t, CacheRecord> kvp(e.messages[i].lamport_time.timestamp,e.messages[i]) ;
         debugger.Insert( e.messages[i].message ) ;
         cache.insert(kvp); 
#ifdef DEBUG 
         cachers[e.messages[i].source][e.messages[i].destination][e.messages[i].causal_time.timestamp].insert(self); 
#endif
      }


   }
   LOG( cachelog, "Self=%s LocalTime=%llu Cache has CacheSizePeak=%d records after LocalDeliver=%d PeerDeliver=%d", 
        self.c_str(), local_time, cache.size() , nlocal, ndirect) ; 


        //---------------------------------------------------
        // get my stable read timestamp upto date ; get causal 
        // time uptodate for next send etc 
   TS_UPDATE(ltv[from].timestamp, e.lt.timestamp); 
   TS_UPDATE(srv[from].timestamp, e.sr.timestamp);
   for( vector_ets_t::iterator i = e.ctv.begin() ; i != e.ctv.end() ; i++ ) 
      TS_UPDATE( ctm[from][i->first].timestamp , i->second.timestamp ) ; 

   TS_UPDATE(lamport_time, e.lt.timestamp); 
   ltv[self].timestamp = ++lamport_time; 
   ctm[self][self].timestamp = ++causal_time; 

   assert( srv[from].timestamp < lamport_time ) ; 


   trim_cache();

        //---------------------------------------------------
        // delete purgable messages
   update_stable_read_vec();
   delete_delivered_messages(); 
}









void MessageCache::update_stable_read_vec() 
{
   stable_read = lamport_time;
   for( vector_ets_t::iterator i = ltv.begin(); i != ltv.end(); i++ ) 
      stable_read = (stable_read < i->second.timestamp) ? 
         stable_read : i->second.timestamp;
   srv[self].timestamp = stable_read; 
}








void MessageCache::delete_delivered_messages()
{
   CacheLoader cl(this); 
   int npurged = 0; 
   cached_mesgmap_t::iterator i = cache.begin(), j; 
   while( i != cache.end() ) 
   {
      j = i; ++j;  
      
      CacheRecord & cr = i->second; 

           // srv has a problem: if you dont know all the peers then min(lt) may overestimate sr and
           // delete messages undelivered
           //if(srv.find(cr.destination) != srv.end() && cr.lamport_time.timestamp < srv[cr.destination].timestamp)
          
           // destination knows a later timestamp of source i.e. no point in cacheing
           // this message. 
      if( cr.causal_time.timestamp < ctm[cr.destination][cr.source].timestamp ) 
      {
#ifdef DEBUG
         debugger.Trim( cr.message ) ;
#if 0
           // because the single point test gets later time stamp 
           // by increment on receive. this is a quirk of email because multiple identities may be
           // visible for same single bftauth object
         assert( delivered[cr.source][cr.destination].find(cr.causal_time.timestamp) != 
                 delivered[cr.source][cr.destination].end() ) ; 
#endif 
         cachers[cr.source][cr.destination][cr.causal_time.timestamp].erase(self); 
#endif
         cache.erase(i);
         npurged++;
      }

      i = j; 
   }     
   LOG( cachelog, "Self=%s LocalTime=%llu Cache has CacheSizeClean=%d records after Purged=%d ", 
        self.c_str(), local_time, cache.size() , npurged) ;   
}









void MessageCache::trim_cache()
{
   CacheLoader cl(this); 
   int npurged = 0; 
   cached_mesgmap_t::iterator i = cache.begin(), j; 
   while( i != cache.end() ) 
   {
      j = i; ++j;  
      
      CacheRecord & cr = i->second; 
      if(cr.expiry <= local_time) 
      {
#ifdef DEBUG
         debugger.Expire( cr.message ) ;
         cachers[cr.source][cr.destination][cr.causal_time.timestamp].erase(self); 
#endif
         cache.erase(i);
         npurged++;  
      }
      i = j; 
   }     
   LOG( cachelog, "Self=%s LocalTime=%llu Cache has CacheSizeClean=%d records after Expired=%d ", 
        self.c_str(), local_time, cache.size() , npurged) ;   
}









void MessageCache::EraseFrom(const std::string & peer) 
{
   abort(); 
   CacheLoader cl(this); 
   for( cached_mesgmap_t::iterator j, i = cache.begin(); i != cache.end(); i = j)
      if( j++, i->second.source == peer )
         cache.erase(i);
}






void MessageCache::EraseTo(const std::string & peer) 
{
   abort();
   CacheLoader cl(this); 
   for( cached_mesgmap_t::iterator j, i = cache.begin(); i != cache.end(); i = j)
      if( j++, i->second.destination == peer )
         cache.erase(i);
}













bool MessageCache::DeliverLocal(std::string& from, std::string & mesg)
{
   if(localmesg.empty())
      return false; 

   std::multimap<epoch_t, CacheRecord>::iterator i = localmesg.begin(); 
   CacheRecord & cr = i->second; 

   from = cr.source; 
   mesg = cr.message; 

#ifdef DEBUG
   assert(todo[cr.source][cr.destination].find(cr.causal_time.timestamp) != todo[cr.source][cr.destination].end()); 
   todo[cr.source][cr.destination].erase(cr.causal_time.timestamp); 

   assert(delivered[cr.source][cr.destination].find(cr.causal_time.timestamp) == delivered[cr.source][cr.destination].end()) ; 
   delivered[cr.source][cr.destination].insert(cr.causal_time.timestamp); 
#endif

   localmesg.erase(i); 

   ltv[self].timestamp = ++lamport_time; 
   ctm[self][self].timestamp = ++causal_time; 


   return true; 
}







bool MessageCache::Insert(const std::string & peer, const std::string & mesg, epoch_t  expiry) 
{
   ltv[self].timestamp = ++lamport_time; 
   ctm[self][self].timestamp = ++causal_time; 

   CacheRecord cr; 
   cr.local_time = local_time; 
   cr.expiry = expiry ; 
   cr.lamport_time.timestamp = lamport_time; 
   cr.causal_time.timestamp = causal_time; 
   cr.stable_read.timestamp = stable_read; 
   cr.source = self; 
   cr.destination = peer; 
   cr.message = mesg; 

#ifdef DEBUG
   assert( sent[cr.source][cr.destination].find(causal_time) == sent[cr.source][cr.destination].end() );
   sent[cr.source][cr.destination].insert(causal_time); 
   todo[cr.source][cr.destination].insert(causal_time); 
   if( cr.destination != self ) 
      cachers[cr.source][cr.destination][causal_time].insert(self); 
#endif

   if( cr.destination == self ) 
   {
      std::pair<epoch_t, CacheRecord> kvp(cr.lamport_time.timestamp, cr) ;
      localmesg.insert(kvp) ; 
   }
   else
   {
      CacheLoader cl(this); 
      std::pair<epoch_t, CacheRecord> kvp(cr.lamport_time.timestamp, cr) ;
      debugger.Insert( mesg ) ; 
      cache.insert(kvp); 
   }
   return true; 
}

