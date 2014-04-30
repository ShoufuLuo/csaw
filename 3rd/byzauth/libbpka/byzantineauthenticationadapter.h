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

#ifndef __BYZAUTH_H__
#define __BYZAUTH_H__


#include "defines.h" 
#include <vector> 
#include <iostream>

/**
 * Interface to the Real World 
 * 
 * The library makes Send calls to to enque outgoing messages. 
 * Since the system is deferred send, the application will periodically call 
 * the Deque method to gather messages for a given destination 
 *
 * Also define API for authentication of keys
 */



class MessageProcessor; 

class ByzantineAuthenticationAdapter 
{
  protected:
   MessageProcessor *   messageprocessor;
   void *               peerfactory; 
   void *               self; 
   std::string          filename;
   std::string          cfgfile; 
   int                  max_trust_group_size; 

  protected:
   epoch_t              local_time; 
   epoch_t              expiry_interval; 


   virtual void   OnInit () {}

   ByzantineAuthenticationAdapter(std::string cfgfile, 
                                  int tgs, 
                                  epoch_t interval = MAX_EXPIRY_INTERVAL_DEF);

   virtual ~ByzantineAuthenticationAdapter() {} 

  public:

   bool   Debug() ; 

   static ByzantineAuthenticationAdapter* New (
      std::string cfg,         // any extensible config items 

      int tgs,                 // trusted group size used by the library
                               // this size has performance implications for 
                               // nummessages and resistance to the number
                               // of malicious peers in the p2p system

      epoch_t expiry_interval, // how many seconds to hold on to messages 
                               // that can not be delivered to the recipient 

      unsigned nmesg_payload,  // how many max authentication protocol messages 
                               // are allowed to be piggybacked on one 
                               // application message

      bool lazy = true         // allow lazy operation - i.e. protocol messages 
                               // can be delivered through other peers
   ); 


   static void  Delete(ByzantineAuthenticationAdapter *); 

        /*
         * Keep the adapter uptodate with local time to 
         * keep meaningful logging. protocol timestamps 
         * are logical and dont help inerpretaton  
         */
   virtual void   LocalTime (epoch_t t) ; 
  

   virtual bool   GetCacheSize(unsigned & messages, unsigned & bytes);

        /** 
         * Application calls the receive function to provide new messages
         * to the library.
         */
   virtual bool   Recv     (const peerid_t& peer, const std::string & mesg);

        /**
         * Application calls the send method to see if library has any 
         * outgoing messages for the given peer.  If yes, the mesg is 
         * populated and return value is true 
         */
   virtual bool   Send     (const peerid_t& peer, std::string & mesg) ;
   virtual bool   SendMulti(const std::vector<peerid_t>& peers, std::string & mesg, bool = false) ;



        /*
         * Safely start and stop the authentication engine 
         */
   virtual bool     Init      (int keybits, const peerid_t& self, const std::vector<peerid_t>& bootstrap, std::string filename, epoch_t curr_time); 
   virtual bool     Init      (std::string filename, epoch_t curr_time);

   virtual bool     DeInit    ();

   bool GenerateNewKeyPair    (int keybits);   


        /* 
         * The API of authentication engine 
         */
   void     SetTrusted              (const peerid_t& pid);
   void     SetUntrusted            (const peerid_t& pid); 
   void     SetProbationary         (const peerid_t& pid); 
   bool     GetAuthenticatedKey     (const peerid_t& pid, std::string& pubkey, int & trust_value, bool & unknown);   // TODO : Convert to compatible n, d format 
   bool     GetAuthenticators       (const peerid_t& pid, group_t & authenticators); 

        /* 
         * access to trust groups nonlive peers 
         */
   void     GetTrusted              (group_t& trusted);
   void     GetUntrusted            (group_t& untrusted);
   void     GetProbationary         (group_t& probationary); 
   void     MarkNonLive             (const peerid_t& peer); 
   double   GetCompletion           (unsigned int&, unsigned int&); 


        /* 
         * sign messages and verify signatures
         */
   void     Sign                    (const char * mesg, std::string & sig);
   bool     Verify                  (const char * mesg, const char * sig, const char * peer, bool & unknown);


};




#endif //__BYZAUTH_H__

