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

#include "messageprocessor.h" 



bool  MessageProcessor::EnqueFromLib(const peerid_t& peer, const std::string &mesg, epoch_t expiry)
{
   if( outgoing.find(peer) == outgoing.end() ) 
      outgoing.insert( make_pair(peer, std::deque<SerializedMessage> () ) ) ;

   SerializedMessage m;    
   m.mesg = mesg;       // Optimization : Try to use swap data instead of copy 
   m.expiry = expiry; 

   outgoing[peer].push_back(m); 
   return true; 
}






bool MessageProcessor::DequeForApp(const peerid_t& peer, std::string &mesg, epoch_t & expiry)
{
   if( outgoing.find(peer) == outgoing.end() ) 
      return false; 

   if( outgoing[peer].empty() ) 
      return false; 


   // improve execution time by preventing copy creation 
   // for getting front item 
   SerializedMessage& m = outgoing[peer].front(); 
   mesg.swap(m.mesg);
   expiry = m.expiry; 
   outgoing[peer].pop_front(); 
   return true; 
}





bool MessageProcessor::DequeForAppAnyPeer(peerid_t& peer, std::string & mesg, epoch_t & expiry)
{
        // find the non empty peers and send
   for( mesg_queue_t::iterator i = outgoing.begin(); i != outgoing.end(); i++ )
      if( !i->second.empty() )
         return DequeForApp( peer = i->first, mesg, expiry ) ; 

   return false; 
}
