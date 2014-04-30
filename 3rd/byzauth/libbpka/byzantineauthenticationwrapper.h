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

#ifndef __BYZANTINE_AUTHENTICATION_WRAPPER_H__ 
#define __BYZANTINE_AUTHENTICATION_WRAPPER_H__  

#include <vector>
#include "defines.h" 

class ByzantineAuthenticationAdapter ; 

class ByzantineAuthenticationWrapper 
{
   ByzantineAuthenticationAdapter * p ; 
   
  public:

   ByzantineAuthenticationWrapper() : p(0) {} 

   bool Init(std::string cfg, int keybits, const peerid_t& self, 
             const std::vector<peerid_t>& bootstrap, std::string filename,
             int tgs, unsigned expiry_interval, unsigned nmesg_payload); 

   bool Init(std::string cfg, std::string filename, int tgs, unsigned expiry_interval, unsigned nmesg_payload); 


   bool GenerateNewKeyPair(int keybits);     


   void DeInit(); 

        /** 
         * Application calls the receive function to provide new messages
         * to the library.
         */
   bool   Recv     (const peerid_t& peer, const std::string & mesg);

        /**
         * Application calls the send method to see if library has any 
         * outgoing messages for the given peer.  If yes, the mesg is 
         * populated and return value is true 
         */
   bool   Send     (const peerid_t& peer, std::string & mesg) ;
   bool   SendMulti(const std::vector<peerid_t>& peers, std::string & mesg) ;

   
        /* 
         * The API of authentication engine 
         */
   bool     SetTrusted              (const peerid_t& pid);
   bool     SetUntrusted            (const peerid_t& pid); 
   bool     SetProbationary         (const peerid_t& pid); 

   bool     GetAuthenticatedKey     (const peerid_t& pid, std::string& pubkey, int & trust_value, bool & unknown); 
   bool     GetAuthenticators       (const peerid_t& pid, group_t & authenticators);

   bool     GetTrusted              (group_t& trusted);
   bool     GetUntrusted            (group_t& untrusted);
   bool     GetProbationary         (group_t& probationary); 

        /* 
         * sign messages and verify signatures
         */
   bool     Sign                    (const char * mesg, std::string & sig);
   bool     Verify                  (const char * mesg, const char * sig, const char * peer, bool & unknown);
};


#endif

