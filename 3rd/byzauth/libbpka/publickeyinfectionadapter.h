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

#ifndef __PUBLIC_KEY_INFECTION_ADAPTER_H__ 
#define __PUBLIC_KEY_INFECTION_ADAPTER_H__ 

#include <string>
#include "byzantineauthenticationadapter.h" 
#include "messageprocessor.h" 
#include "messagecache.h" 


class PublicKeyInfection : public ByzantineAuthenticationAdapter
{
   friend class ByzantineAuthenticationAdapter; 

   std::string       selfname; 
   std::string       persistent; 
   MessageCache *    cache; 
   epoch_t           lamport_time; 
   epoch_t           causal_time; 
   const unsigned    max_message_payload; 

   virtual void      OnInit   (); 

  public:
   PublicKeyInfection(std::string cfg, int tgs, epoch_t _expiry_interval, unsigned nmesg_payload);

        /** 
         * Application calls the receive function to provide new messages
         * to the library.
         */
   virtual bool   Recv     (const peerid_t& peer, const std::string & mesg) ; 


        /**
         * Application calls the send method to see if library has any 
         * outgoing messages for the given peer.  If yes, the mesg is 
         * populated and return value is true 
         */
   virtual bool   Send     (const peerid_t& peer, std::string & mesg) ;
   virtual bool   SendMulti(const std::vector<peerid_t>& peers, std::string & mesg, bool = false) ;


   virtual bool   GetCacheSize(unsigned & messages, unsigned & bytes);
   virtual ~PublicKeyInfection(); 
};




#endif
