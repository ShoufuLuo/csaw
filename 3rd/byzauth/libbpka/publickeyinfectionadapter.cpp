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

#include "self.h"
#include "publickeyinfectionadapter.h" 
#include "diskmessagecache.h"


static const int INMEMSZ = 8192; 



bool PublicKeyInfection::GetCacheSize(unsigned & messages, unsigned & bytes)
{
   return cache->GetCacheSize(messages, bytes); 
}



bool PublicKeyInfection::Recv(const peerid_t& peer, const std::string & mesg)
{
   (static_cast<Self *>(ByzantineAuthenticationAdapter::self))->MarkLive(peer); 
   cache->InComingEvent ( peer, mesg ) ;
   while(true)
   {
      std::string bmesg; 
      std::string bfrom;
      if(!cache->DeliverLocal( bfrom, bmesg ) )
         break; 
      ByzantineAuthenticationAdapter::Recv(bfrom, bmesg); 
   }  
   return true; 
}





bool  PublicKeyInfection::Send(const peerid_t& peer, std::string & mesg)
{
   throw "not implemented" ; 
}






bool  PublicKeyInfection::SendMulti(const std::vector<peerid_t>& peers, std::string & mesg, bool overload) 
{
   int ninserted = 0; 
   while(true)
   {
      std::string peer; 
      std::string mesg; 
      epoch_t expiry; 
      if(!messageprocessor->DequeForAppAnyPeer(peer, mesg, expiry)) 
      {
              // last chance to restart any hung protocol actions
         (static_cast<Self *>(ByzantineAuthenticationAdapter::self))->check_expired(); 
         if(!messageprocessor->DequeForAppAnyPeer(peer, mesg, expiry)) 
            break; 
      }
      cache->Insert(peer, mesg, expiry); 
      ninserted++;
   }
   cache->OutGoingEvent(peers, mesg, overload ? 0 : max_message_payload); 
   return true; //ninserted != 0; 
}







void  PublicKeyInfection::OnInit()
{
   selfname = (static_cast<Self *>(ByzantineAuthenticationAdapter::self))->GetName(); 
   persistent = ByzantineAuthenticationAdapter::filename + ".cache" ; 
#ifdef LARGE_SIMULATION
   cache = new DiskMessageCache( lamport_time, 
                                 causal_time, 
                                 local_time, 
                                 persistent, 
                                 selfname,
                                 INMEMSZ) ; 
#else
   cache = new MessageCache( lamport_time, 
                             causal_time, 
                             local_time, 
                             persistent, 
                             selfname) ; 
   cache->Configure( cfgfile ) ; 
#endif
}








PublicKeyInfection::PublicKeyInfection(std::string cfg, int tgs, epoch_t _expiry_interval, unsigned nmesg_payload)
   :
   ByzantineAuthenticationAdapter(cfg, tgs, _expiry_interval) ,
   cache(0), lamport_time(0), causal_time(0),  
   max_message_payload(nmesg_payload) 
{
}







PublicKeyInfection::~PublicKeyInfection()
{
   delete cache; 
}










