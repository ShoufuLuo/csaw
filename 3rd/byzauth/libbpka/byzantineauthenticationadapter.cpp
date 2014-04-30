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

#include "proxypeer.h"
#include "rsa.h" 
#include "messageprocessor.h" 
#include "peerfactory.h" 
#include "keyrepository.h" 
#include "self.h"
#include "byzantineauthenticationadapter.h" 
#include "message.h"
#include "authenticationrequest.h"
#include "proofrequest.h"
#include "byzantinefault.h" 
#include "byzantineauthenticationmessage.h"
#include "publickeyinfectionadapter.h" 
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>





ByzantineAuthenticationAdapter* ByzantineAuthenticationAdapter::New(std::string _cfg,
                                                                    int tgs, 
                                                                    epoch_t expiry_interval, 
                                                                    unsigned nmesg_payload,  
                                                                    bool _lazy) 
{
   std::string cfgfile = _cfg; 
   ByzantineAuthenticationAdapter* p = 0; 
   if( _lazy ) 
      p = new PublicKeyInfection(cfgfile, tgs, expiry_interval, nmesg_payload) ; 
   else
      p = new ByzantineAuthenticationAdapter(cfgfile,tgs) ; 
   return p; 
}




void ByzantineAuthenticationAdapter::Delete(ByzantineAuthenticationAdapter *_p)
{
   delete _p; 
}









bool ByzantineAuthenticationAdapter::GetCacheSize(unsigned & messages, unsigned & bytes)
{
   return false; 
}





bool ByzantineAuthenticationAdapter::Recv(const peerid_t& peer, const std::string & mesg)
{
   return (static_cast<Self *>(self))->Recv(peer, mesg); 
}






bool ByzantineAuthenticationAdapter::Send(const peerid_t& peer, std::string & mesg)
{
   epoch_t expiry; 
   return messageprocessor->DequeForApp(peer, mesg, expiry); 
}





bool  ByzantineAuthenticationAdapter::SendMulti(const std::vector<peerid_t>& peers, std::string & mesg, bool) 
{
   assert(0);
   return true; 
}




void ByzantineAuthenticationAdapter::SetTrusted(const peerid_t& pid)
{
   (static_cast<Self *>(self))->_set_trusted(pid);
}





void ByzantineAuthenticationAdapter::SetUntrusted(const peerid_t& pid)
{
   (static_cast<Self *>(self))->_set_untrusted(pid); 
}





void ByzantineAuthenticationAdapter::SetProbationary(const peerid_t& pid)
{
   (static_cast<Self *>(self))->_set_probationary(pid);
}





bool ByzantineAuthenticationAdapter::GetAuthenticatedKey(
   const peerid_t& pid, std::string& pubkey, int & trust_value, bool & unknown)
{
   return (static_cast<Self *>(self))->_get_authentic_key(pid, pubkey, trust_value, unknown); 
}




ByzantineAuthenticationAdapter::ByzantineAuthenticationAdapter(std::string _cfg, int tgs, epoch_t interval) 
   :
   messageprocessor(0), 
   peerfactory(0),
   self(0),
   max_trust_group_size(tgs) , 
   expiry_interval(interval) 
{
   cfgfile = _cfg; 
}






bool ByzantineAuthenticationAdapter::Init(int keybits, 
                                          const peerid_t& _self, 
                                          const std::vector<peerid_t>& _bootstrap, 
                                          std::string _filename, 
                                          epoch_t t
   )
{
   messageprocessor = new  MessageProcessor ; 
   peerfactory = new PeerFactory(messageprocessor); 

   epoch_t epoch = local_time = t; 
   group_t bootstrap; 
   bootstrap.insert(make_pair(_self, epoch)) ; 
   for( std::vector<peerid_t>::const_iterator i = _bootstrap.begin(); i != _bootstrap.end(); i++ ) 
      if( bootstrap.find(*i) == bootstrap.end() ) 
         bootstrap.insert( make_pair( *i, epoch ) ) ; 

        /*
         * make self object for running protocol actions 
         */
   self = (static_cast<PeerFactory *>(peerfactory))->Create( keybits, _self, bootstrap, cfgfile, &local_time, expiry_interval ); 
   Self * ps = static_cast<Self *> (self) ; 
   ps->set_tg_size(max_trust_group_size, (max_trust_group_size/2) < 3 ? 3 : (max_trust_group_size/2)) ; 
   
   
   filename = _filename; 
   
   OnInit(); 

   return true; 
}




bool ByzantineAuthenticationAdapter::Init(std::string _filename, epoch_t t)
{
   if(self)
      return false; 

   filename = _filename; 

   struct stat statbuf ; 
   if( 0 > ::stat(filename.c_str(), &statbuf) )
      return false; 

        // must be a regular file
   if(!S_ISREG( statbuf.st_mode ))
      return false; 

        // others do not have pernssions for file read/write/execute 
   if( (S_IRGRP&statbuf.st_mode) || (S_IWGRP&statbuf.st_mode) ||
       (S_IROTH&statbuf.st_mode) || (S_IWOTH&statbuf.st_mode) ||
       (S_IXGRP&statbuf.st_mode) || (S_IXOTH&statbuf.st_mode) 
      )
      return false;

        // owner has permission
   assert( (statbuf.st_mode&S_IRUSR) && (statbuf.st_mode&S_IWUSR) ) ; 
   

   std::ifstream ifs(filename.c_str());
   if(!ifs.good())
      return false ;

   boost::archive::xml_iarchive ia(ifs);
   ia >> BOOST_SERIALIZATION_NVP(messageprocessor);

   Self * typed_self; 
   ia >> BOOST_SERIALIZATION_NVP(typed_self); 
   self = typed_self; 

   peerfactory = new PeerFactory(messageprocessor);
   (static_cast<PeerFactory *>(peerfactory))->Assign(static_cast<Self*>(self)); 
   
   OnInit(); 
   return true; 
}



bool ByzantineAuthenticationAdapter::DeInit()
{
   std::ofstream ofs(filename.c_str());
   if(!ofs.good())
      return false; 

   if(0 > ::chmod(filename.c_str(), S_IRUSR|S_IWUSR) ) 
      return false; 

   boost::archive::xml_oarchive oa(ofs);
   oa << BOOST_SERIALIZATION_NVP(messageprocessor);

   Self * typed_self = static_cast<Self *>(self);
   oa << BOOST_SERIALIZATION_NVP(typed_self); 

   delete messageprocessor; 
   delete (static_cast<PeerFactory *>(peerfactory)); 
   delete (static_cast<Self *>(self)); 
   fflush(0);
   return true; 
}








bool ByzantineAuthenticationAdapter::Debug()
{
   return (static_cast<Self *>(self))->debug(); 
}






         
void ByzantineAuthenticationAdapter::GetTrusted(group_t& trusted) 
{
   trusted = (static_cast<Self *>(self))->trusted ; 
}





         

void ByzantineAuthenticationAdapter::GetUntrusted(group_t& untrusted) 
{
   untrusted = (static_cast<Self *>(self))->untrusted ; 
}







         
void ByzantineAuthenticationAdapter::GetProbationary(group_t& probationary)
{
   probationary = (static_cast<Self *>(self))->probationary ; 
}






void ByzantineAuthenticationAdapter::MarkNonLive(const peerid_t& peer)
{
   (static_cast<Self *>(self))->PruneNonLive(peer); 
}


double ByzantineAuthenticationAdapter::GetCompletion (unsigned int& ntrusted, unsigned int& nknown)
{
   return (static_cast<Self *>(self))->GetCompletion(ntrusted, nknown); 
}


        /* 
         * sign messages and verify signatures
         */
void ByzantineAuthenticationAdapter::Sign(const char * mesg, std::string & sig)
{
   (static_cast<Self *>(self))->Sign(mesg, sig);
}



bool ByzantineAuthenticationAdapter::Verify(const char * mesg, const char * sig, const char * peer, bool & unknown)
{
   return (static_cast<Self *>(self))->Verify(mesg, sig, peer, unknown);
}



bool ByzantineAuthenticationAdapter::GenerateNewKeyPair(int keybits) 
{
   return (static_cast<Self *>(self))->GenerateNewKeyPair(keybits); 
}



bool ByzantineAuthenticationAdapter::GetAuthenticators(const peerid_t& pid, group_t & authenticators)
{
   return (static_cast<Self *>(self))->GetAuthenticators(pid, authenticators);
}




void ByzantineAuthenticationAdapter::LocalTime(epoch_t t)
{
   local_time = t;
}
