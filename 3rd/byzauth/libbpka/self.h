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

#ifndef __SELF_H__
#define __SELF_H__ 

#define MESG_RECV_DEBUG 1

#include "defines.h" 
#include "rsa.h"
#include "proofrepository.h"
#include "keyrepository.h"
#include "peer.h"
#include "byzauthmatrix.h"
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include "logger.h" 


class PeerFactory; 




class Self : public Peer
{
   friend class PeerFactory; 
   friend class ByzantineAuthenticationAdapter; 
   virtual ~Self() ;
   Self();
   void Init(std::string config, bool dummy = false) ; 

   typedef std::map<peerid_t, std::set<peerid_t> > waiterset_t; 
   typedef std::map<peerid_t, ByzAuthMatrix>       byzauth_matrix_t; 

   peerid_t                pid; 
   group_t                 bootstrap;
   group_t                 trusted; 
   group_t                 probationary;
   group_t                 untrusted;

        // for measuring completion of the protocol
        // ignores group migration etc. 
   group_t                 initial_probationary_group;
   group_t                 peers_authenticated_once; 
#ifdef DEBUG 
   group_t                 prev_probationary;
   float                   prevcompletion; 
#endif 

        // for trimming the trusted groups for idleness 
        // and state for managing the protocol resends etc. 
   bool                    shortfall_in_groupsize; 
   group_t                 live; 
   group_t                 nonlive; 
   group_t                 sent_public_key_request; 
   waiterset_t             waiters; 
   waiterset_t             byzantine_probationary;
   byzauth_matrix_t        byzauth_matrix; 

        // cryptographic infrastructure 
   RSAPrivateKeyEncryption decryptor;
   RSAPublicKeyEncryption  encryptor; 

        // save all the known peers, proofs and keys etc 
   ProofRepository         proofs;
   KeyRepository           keyrepository; 
   PeerFactory *           factory; 

        // constants 
   unsigned                max_tg_sz;
   unsigned                min_tg_sz;
   epoch_t                 expiry_interval; 
   epoch_t *               plocal_time; 
   std::string             cfgfile; 
   static   int            refcount;   


        // logging related  
   bool     initialize_logging   (std::string configfile); 
   void     close_logging        ();
   static void Assert            (Message *, Message *);



   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);

   int         PruneTrustGroups              (); 
   bool        _byzantine_authentication_1   (peerid_t sender, unsigned long causalid = 0);
   bool        _byzantine_authentication_2   (peerid_t sender);
   void        _set_trusted                  (const peerid_t& pid);
   void        _set_untrusted                (const peerid_t& pid); 
   void        _set_probationary             (const peerid_t& pid, unsigned long causalid = 0); 
   bool        _get_authentic_key            (const peerid_t& pid, std::string& pubkey, int & trust_value, bool & unkn) ;
   bool        _send_public_key_request      (const peerid_t& pid, unsigned long causalid = 0);
   void        _authenticate_peers           (unsigned long causalid = 0); 
   void        _migrate_peer                 (const peerid_t& p); 
   int         _erase_slow_peers             () ; 


  public:

   virtual std::string GetName() { return pid; } 

   inline bool  Belongs(const peerid_t& peer, const group_t& group, epoch_t interval = 0) const
   {
      if(!interval) 
         interval = expiry_interval ; 
      group_t::const_iterator i = group.find(peer) ; 
      if ( i == group.end() )    
         return false; 
      assert( get_local_time() >= i->second ) ; 
      if ( (get_local_time() - i->second) > interval ) 
         return false; 
      return true; 
   }
     
   bool           Recv                    (const std::string& peer, const std::string& mesg); 

        /**
         * Sending a message to peer is same as making a fn call. 
         * Need to keep them virtual so that malicious peer derived types
         * can send various spoofed  messages
         */
   virtual bool   public_key_request      (Message * );

   virtual bool   admission_request       (Message * );

   virtual bool   authentication_request  (Message *);
   
   virtual bool   challenge               (Message *); 

   virtual bool   response                (Message *);    

   virtual bool   vote                    (Message *); 

   virtual bool   proof_request           (Message *); 

   virtual bool   byzantine_vote          (Message *); 

   virtual bool   byzantine_fault         (Message *); 
   
   virtual bool   byzantine_authentication(Message*); 

   void           PruneNonLive            (const peerid_t& peer); 

   void           MarkLive                (const peerid_t& peer); 

   double         GetCompletion           (unsigned int&, unsigned int&);
   
   bool           debug                   (); 

   void           set_local_time          (epoch_t * _p_local_time) ;

   epoch_t        get_local_time          () const ; 

   void           set_tg_size             (int max, int min);

   void           set_expiry_interval     (epoch_t interval); 

   void           check_expired           (); 

        /** 
         * Public tunable parameters 
         */
   static unsigned         CHALLENGE_BITS; 

        /**
         * interface to help sign and verify the messages 
         */
   void     Sign                    (const char * mesg, std::string & sig);
   bool     Verify                  (const char * mesg, const char * sig, const char * peer, bool & unknown);


   bool     GenerateNewKeyPair      (int keybits);
   bool     GetAuthenticators       (const peerid_t& pid, group_t & authenticators);
};





template<class Archive> 
inline void Self::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(pid);
   ar & BOOST_SERIALIZATION_NVP(max_tg_sz); 
   ar & BOOST_SERIALIZATION_NVP(min_tg_sz); 
   ar & BOOST_SERIALIZATION_NVP(bootstrap); 
   ar & BOOST_SERIALIZATION_NVP(trusted);
   ar & BOOST_SERIALIZATION_NVP(probationary);
   ar & BOOST_SERIALIZATION_NVP(untrusted);
   ar & BOOST_SERIALIZATION_NVP(live);
   ar & BOOST_SERIALIZATION_NVP(nonlive);

   ar & BOOST_SERIALIZATION_NVP(initial_probationary_group) ;
   ar & BOOST_SERIALIZATION_NVP(peers_authenticated_once); 

   ar & BOOST_SERIALIZATION_NVP(sent_public_key_request) ; 
   ar & BOOST_SERIALIZATION_NVP(proofs);
   ar & BOOST_SERIALIZATION_NVP(keyrepository);
   ar & BOOST_SERIALIZATION_NVP(waiters);
   ar & BOOST_SERIALIZATION_NVP(byzauth_matrix);
   ar & BOOST_SERIALIZATION_NVP(decryptor);
   ar & BOOST_SERIALIZATION_NVP(encryptor);
   ar & BOOST_SERIALIZATION_NVP(expiry_interval);
}





#endif 
