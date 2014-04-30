#include "messageprocessor.h" 
#include "byzantineauthenticationadapter.h" 
#include <cstdio>
#include <map>
#include <set>
#include <vector> 
#include <string>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <zlib.h> 


     /**
      * The eager version of the protocol run on top 
      * of the mail trace input 
      */ 


#define  MAX_NAME    1024
#define  MININCOUNT  50
#define  MINOUTCOUNT 20 
#define  TWOWAYCOUNT 2
     /**
      * Program takes in an email trace to simulate the progress of 
      * byzantine fault tolerant authentication on the work load 
      *
      * Format of the email trace file:
      *     timeofmail  sizeofmail  mesgid   fromwho  towho ccwho ... \n
      *
      * Logic 
      * Compute all senders and receivers and make an adapter for each.  
      * Load all the messages into sequence by time. 
      * Execute the work load in a synchronous manner using the 
      * receive call at end of every call 
      */


int linebufsize = 64*1024; 

char * linebuf = new char [linebufsize]; 

unsigned int mintime = 0xffffffff;

struct MessageTrace 
{  
   std::string    from; 
   std::vector<std::string>   to; 
   unsigned       date; 
   unsigned       size; 
}; 

std::set<std::string>  peers; 

std::map<unsigned, MessageTrace>    message_trace; 

std::map<std::string, std::vector<std::string> > trustgroups; 

std::map<std::string, ByzantineAuthenticationAdapter *> peer_map;
std::map<std::string, int> woutcount; 
std::map<std::string, int> outcount; 
std::map<std::string, int> incount; 
std::map<std::pair<std::string,std::string>, int> p2pcount; 


     // counters for calculating theo overhead on number of messages sent by 
     // eager mode protocol 
std::map< std::string, int> from_extra_counter ;
std::map< std::string, int> to_extra_counter ; 
std::map< std::string, int> from_base_counter;
std::map< std::string, int> to_base_counter; 


void transmit_outstanding_messages(FILE * , int);



std::string trim(std::string who) 
{
   char name[MAX_NAME]; 
   strcpy( name, who.c_str() ) ; 
   
   int len = who.size();
   for( int i = 0; i < len; i++ ) 
      if( isupper(name[i]) )
         name[i] = tolower(name[i]) ;
   return name; 
}   




int get_compr_size(const std::string& mesg)
{  
   uLongf destLen = (mesg.size() + 12) + (mesg.size()/4); 
   Bytef *dest = new Bytef[destLen]; 
   const Bytef *source = (Bytef *) mesg.data(); 
   uLong sourceLen = mesg.size(); 
   int ret = 0; 
   if( Z_OK != (ret = compress(dest, &destLen, source, sourceLen)))
   {
      std::cerr << "Error in compress " << ret << std::endl; 
      abort() ; 
   }
   delete [] dest; 
   return destLen*3/2;  // for base 64 encoding 
}





bool  load_trace(char * filename) 
{
   FILE * fp = fopen(filename, "r");
   if(!fp)
      return false; 

   const char * tb = " \t\n" ; 
   while(fgets(linebuf, linebufsize, fp))
   {
      char * p = 0; 
      MessageTrace curr;  
      for( int tn = 0; 1; tn++)
      {
         if(!tn)
            p = strtok( linebuf , tb )  ; 
         else
            p = strtok( 0, tb ) ; 
         if(!p)   
            break; 
         switch(tn)
         {
            case 0: curr.date = atoi(p); 
               if (mintime > curr.date)
                  mintime = curr.date; 
               break; 

            case 1: curr.size = atoi(p); 
               break; 
            case 2: break; 

            case 3: curr.from = trim(p); 
               peers.insert(curr.from); 
               break; 
            default:
               curr.to.push_back(trim(p));
               peers.insert(trim(p)); 
               break; 
         }
      }
      message_trace.insert(std::make_pair(curr.date, curr)); 
      outcount[ curr.from ] ++ ; 
      for( std::vector<std::string>::iterator i = curr.to.begin() ; i != curr.to.end() ; i++) 
      {
         if( p2pcount.find( std::make_pair(curr.from,*i) ) == p2pcount.end() ) 
            p2pcount[ std::make_pair(curr.from, *i) ] = 0; 
         ++p2pcount[ std::make_pair(curr.from, *i) ] ; 
         ++incount[ *i ] ; 
      }
      woutcount[curr.from] +=  curr.to.size(); 
   }
   return true; 
}
      
            
         
      
int main(int argc, char * argv[]) 
{
   if( argc != 6 && argc != 7) 
   {
      std::cout << "Usage " << argv[0] << " <bsfile> <msgtrace> <tgs> <keysz> <eager interval> [<maxtimetorun>]" << std::endl;  
      return 1; 
   }


   int tgs = atoi(argv[3]); 
   int keysz = atoi(argv[4]) ; 
   int eager_check_interval = atoi(argv[5]) ; 


        // if the max time to run is 0 then just keep going till 
        // end of the trace.  else just quit when the timeout is 
        // reached. 
        // this control is needed to allow the simulation to stop 
        // in reasonable time and not go on and on even though 
        // completion is achieved 
   unsigned int maxtimetorun = 0; 
   if (argc == 7) 
      maxtimetorun = atoi(argv[6]); 
   

        // load trace 
   load_trace( argv[2] ) ; 



        // load trusted group information
   FILE * bfp = fopen( argv[1] , "r" ) ;
   if(!bfp)
   {
      std::cerr << "Could not open file" << std::endl;   
      return 2; 
   }
   while( fgets( linebuf, linebufsize, bfp ) ) 
   {
      char * p = strtok( linebuf, " \t\n" ) ; 
      if(p && peers.find(p) != peers.end())
      {
         std::string self = p; 
         int count = 0; 
         while( (p = strtok( 0, " \t\n" )) &&  peers.find(p) != peers.end() && count < tgs )
         {
                 // ignore trusted peers who do not send or recv messages 
                 // to this one             
            if( p2pcount[ std::make_pair(self, std::string(p)) ] < TWOWAYCOUNT || 
                p2pcount[ std::make_pair(std::string(p), self) ] < TWOWAYCOUNT ) 
               continue; 

            count++; 
            trustgroups[self].push_back(std::string(p)); 
         }

         if(count < 3)  // 4th is self  
            trustgroups.erase(self); 
      }
   }
   std::cout << "loaded trust groups" << std::endl ; 




        // erased peers who have no trust groups
   for( std::set<std::string>::iterator i = peers.begin() ; i != peers.end() ; ) 
   {
      std::set<std::string>::iterator j = i; 
      j++; 
      if( trustgroups.find(*i) == trustgroups.end() )
         peers.erase(*i); 
      i = j; 
   }
   std::cout << "trimmed messages in trace " << peers.size() << " peers left " << std::endl ; 



        // initialize all adapters 
   mkdir( "./peerdata", 0770 ) ; 
   system( "rm -rf peerdata/*" ) ; 

   for( std::set<std::string>::iterator i = peers.begin() ; i != peers.end() ; i++ ) 
   {
      ByzantineAuthenticationAdapter * adapter = 
         ByzantineAuthenticationAdapter::New( "example.conf" ,    // log dir etc. 
                                              tgs,                // trusted group size
                                              0 ,                 // DUMMY expiry interval in seconds
                                              0,                  // DUMMY maximum message payload i.e. how many messages to attach on outgoing
                                              false ) ;           // use eager implementaton 


      std::string filename = *i + ".xml";
      filename = "./peerdata/" + filename;  

      std::vector<std::string> consistent_trust_group; 
      for( std::vector<std::string>::iterator j = trustgroups[*i].begin(); j != trustgroups[*i].end(); j++ ) 
      {
         if( peers.find( *j ) == peers.end() ) 
            continue; 
         else
            consistent_trust_group.push_back(*j) ; 
      }

      peerid_t me = *i; 
      if(!adapter->Init(keysz, me, consistent_trust_group, filename.c_str(), mintime))
         return false; 

      peer_map.insert( std::make_pair( *i, adapter ) ) ; 
      from_extra_counter[*i] = 
         to_extra_counter[*i] = from_base_counter[*i] =  to_base_counter[*i] = 0 ; 
   }


   std::cout << "initialize all adapters" << std::endl ;



        // run the trace
   char filename[1024]; 
   sprintf( filename, "tgs%d.interval%d.data", tgs, eager_check_interval) ; 
   FILE * statfp = fopen( filename, "w" ) ; 
   assert( statfp ) ; 




   int done = 0, max = message_trace.size(); 
   int percent, prevpercent = 0; 
   int prevcheck = message_trace.begin()->second.date; 
   for( std::map<unsigned, MessageTrace>::iterator i = message_trace.begin(); 
        i != message_trace.end() ; i++ ) 
   {
      done++; 
      percent = int( 100.0*done/max ) ; 
      if( percent != prevpercent ) 
      {
         std::cout << percent << " % done " << std::endl;
         prevpercent = percent; 
      }
      std::cout << done << " of " << max << " done\r" << std::flush ; 

           // the sender
      ByzantineAuthenticationAdapter * pfrom = peer_map[i->second.from];
      if(!pfrom)
         continue; 

      pfrom->LocalTime(i->second.date) ;
      from_base_counter[i->second.from]++ ; 

     
      for( std::vector<std::string>::iterator j = i->second.to.begin(); j != i->second.to.end(); j++ ) 
      {
         ByzantineAuthenticationAdapter * pto = peer_map[*j]; 
         if( (!pto) || (!pfrom) )
            continue; 

         to_base_counter[*j] ++ ; 

         std::string pubkey; 
         bool unknown; 
         int trust_value; 
         pfrom->GetAuthenticatedKey(*j, pubkey, trust_value, unknown); 
                 
         std::string mesg;
              // 
              // TODO - can we have a super eager mode, where the 
              // library tells who it wants to send messages to 
              // 
         while( pfrom->Send( *j, mesg ) )
            pto->Recv( i->second.from, mesg ) ; 

              // Keep track of authe changes whenever the status could change 
         unsigned int ntrusted = 0, nknown = 0;
         float completion = pto->GetCompletion(ntrusted, nknown) ;
         fprintf( statfp, "AUTHSTATUS   SENDER=%s  TIME=%lu  BASESENT=%u  OVERHEAD=%u  COMPLETION=%f \n",
                  j->c_str(), (unsigned long) i->second.date,
                  from_extra_counter[*j], from_base_counter[*j], completion) ;

      }


           // send out messages eagerly if it is the time to check 
           // if new emails have arrived 
      if( ((int)i->second.date - prevcheck) > eager_check_interval ) 
      {
         transmit_outstanding_messages(statfp, i->second.date); 
         prevcheck = i->second.date; 
      }


           // break the loop if max time is prescribed and is exceeded 
      if( maxtimetorun > 0 && i->second.date > maxtimetorun )
         break; 

   }



   transmit_outstanding_messages(statfp, prevcheck + eager_check_interval);
 

        // de init all adapters
   for( std::map<std::string, ByzantineAuthenticationAdapter *>::iterator i = peer_map.begin(); 
        i != peer_map.end(); i++ ) 
   {
      if( !i->second )
         continue; 

      i->second->DeInit(); 
      ByzantineAuthenticationAdapter::Delete(i->second); 
   }


   fclose(statfp); 

   return 0;
}

                








void transmit_outstanding_messages(FILE * fp, int timestamp)
{
   typedef std::map<std::string, ByzantineAuthenticationAdapter *>::const_iterator Iterator; 

        // the readers are checking the email 
        // but are unlikely to be synchronizaed.  so the protocol can make at most two handshakes
        // during one unit time when mail clients are booted up and down for checking email 
   for( int protocycles = 0; protocycles < 2; protocycles++ ) 
   {
      int numdid = 0; 
      for( Iterator i = peer_map.begin(); i != peer_map.end() ; i++ ) 
      {
         if( !i->second )
            continue; 

         for( Iterator j = peer_map.begin(); j != peer_map.end() ; j++ ) 
         {        
            if( !j->second )
               continue; 

                 //ByzantineAuthenticationAdapter * pfrom = i->second; 
                 //ByzantineAuthenticationAdapter * pto = j->second;

            bool didsome = false; 
            std::string mesg;
            while( i->second->Send( j->first, mesg ) )
            {
               didsome = true; 
               j->second->Recv( i->first, mesg ) ; 
            }

            if(didsome) 
            {
               from_extra_counter[i->first] ++ ;
               to_extra_counter[j->first] ++ ; 
               numdid++;
            }
         } 
      }
      if(!numdid)
         break;
   }


   for( Iterator i = peer_map.begin(); i != peer_map.end() ; i++ ) 
   {
      if(!i->second)
         continue; 

      unsigned int ntrusted = 0, nknown = 0; 
      float completion = i->second->GetCompletion(ntrusted, nknown) ; 

      fprintf( fp, "AUTHSTATUS   SENDER=%s  TIME=%lu  BASESENT=%u  OVERHEAD=%u  COMPLETION=%f \n", 
               i->first.c_str() , (unsigned long) timestamp, 
               from_extra_counter[i->first], from_base_counter[i->first], completion) ; 
   }
}
