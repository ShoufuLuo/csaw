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

#ifndef __BYZ_AUTH_PEER_H__
#define __BYZ_AUTH_PEER_H__ 


#include <string>
   
typedef std::string peerid_t;
class Proof; 
class Message; 

class Peer 
{
  public:
     
   virtual std::string    GetName           () = 0;

        /**
         * Sending a message to peer is same as making a fn call. 
         */
   virtual bool   public_key_request      (Message *) = 0; 

   virtual bool   admission_request       (Message *) = 0;

   virtual bool   authentication_request  (Message *) = 0;
   
   virtual bool   challenge               (Message *) = 0; 

   virtual bool   response                (Message *) = 0; 

   virtual bool   vote                    (Message *) = 0; 

   virtual bool   proof_request           (Message *) = 0; 

   virtual bool   byzantine_vote          (Message *) = 0; 

   virtual bool   byzantine_fault         (Message *) = 0; 

   virtual bool   byzantine_authentication(Message *) = 0; 

   virtual        ~Peer                   () {;}
};







#endif 