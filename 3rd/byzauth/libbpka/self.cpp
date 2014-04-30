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
#include "peerfactory.h"
#include "authenticationrequest.h"
#include "admissionrequestmessage.h" 
#include "challenge.h" 
#include "response.h" 
#include "proof.h"
#include "proofrequest.h"
#include "byzantinefault.h" 
#include "byzantineauthenticationmessage.h"
#include "publickeyrequest.h" 
#include "configfile.h" 
#include <cmath> 
#include <sstream>
#include <cstring> 






// all the configuration options should go into a 
// config file. 
// redo authentication more aggressively than trust expiry 
#define  REDOFRAC    4  
unsigned Self::CHALLENGE_BITS = 256; 





XLogger & protolog = * XLogManager::GetLogger("protolog"); 
XLogger & messagelog = * XLogManager::GetLogger( "messagelog");
XLogger & errorlog = * XLogManager::GetLogger("errorlog"); 
XLogger & authlog = * XLogManager::GetLogger("authlog"); 





bool Self::initialize_logging(std::string configfile)
{
   ConfigFile cfg;  
   if(!cfg.Init(configfile))
   {
      std::cerr << "Cannot init configfile " << configfile << std::endl; 
      ::abort(); 
   }

   std::string logdir = 
      cfg.GetStringValue( "Logging" , "LogDirectory" , "." ) ; 


   std::string protologfile = 
      cfg.GetStringValue( "Logging" , "ProtocolLogFile" , "protocol.log" ) ; 
   protolog.SetDestination( 
      XLogManager::GetFileLogDestination( logdir + "/" + protologfile ) 
      );


   std::string mesglogfile = 
      cfg.GetStringValue( "Logging" , "MessageLogFile" , "message.log" ) ;
   messagelog.SetDestination( 
      XLogManager::GetFileLogDestination( logdir + "/" + mesglogfile ) 
      );


   std::string errorlogfile = 
      cfg.GetStringValue( "Logging" , "ErrorLogFile" , "error.log" ) ;
   errorlog.SetDestination( 
      XLogManager::GetFileLogDestination( logdir + "/" + errorlogfile ) 
      );


   std::string authlogfile = 
      cfg.GetStringValue( "Logging" , "AuthenticationLogFile" , "authentication.log" ) ;   
   authlog.SetDestination( 
      XLogManager::GetFileLogDestination( logdir + "/" + authlogfile) 
      );

   return true; 
}



void Self::close_logging()
{
   XLogManager::Shutdown(); 
}






     // For debugging of crashes etc. 
static unsigned long long mcounter = 0;  

void Self::Assert(Message *m, Message * _m)
{   
   if(_m)
      return; 
   std::ostringstream outs;
   boost::archive::xml_oarchive oa(outs); 
   oa << BOOST_SERIALIZATION_NVP(m);  
   LOG( errorlog, "Fatal Error on Message %llu\n%s\n" , 
        mcounter, outs.str().c_str() ) ; 
   abort(); 
}












bool Self::Recv(const std::string& peer, const std::string& mesg)
{
   mcounter++;
   std::istringstream ins;
   ins.str(mesg); 
   boost::archive::xml_iarchive ia(ins);

   Message * m = 0; 
   ia >> BOOST_SERIALIZATION_NVP(m) ;

        // Ignoring message that seems to have reached wrong end point 
   if(!m || m->to != pid)
   {
      LOG( errorlog, "Self=%s receive message meant for destination %s : Ignoring", 
           pid.c_str(), m->to.c_str()) ; 
      return false; 
   }

        // Ignoring message from peers that are marked untrusted 
   else if( untrusted.find(m->from) != untrusted.end() )
   {
      LOG( errorlog, "Self=%s message from untrusted peer %s rejected", 
           pid.c_str(), m->from.c_str() ) ; 
      return false; 
   }

   
        // Optimization 
        // Each message has by default the public key of sender.  This is meaningful because public keys are
        // meant to be publicised and made available to as wide an audience as possible.  This change from 
        // the basic definition was done because it was found that too many messages were being sent for the 
        // purpose of getting the public key 

        // 
        // Do we have public key of the sender. If we do the signature should be verifiable in the 
        // common case.  If the sender is trusted or probaionary, then it should have updated
        // us with the new public key.  Therefore, we should ignore the message as malicious
        // However we can have keys that are old and the peer has changed to new public key
        // then we should ask for new key 
   KeyInfo ki; 
   if( keyrepository.find(m->from, ki) && 
       !m->verify(*ki.ep) && 
       bootstrap.find(m->from) == bootstrap.end()) 
   {
           // unverifiable signature and not from bootstrapping peer 
      if( probationary.find(m->from) != probationary.end() || 
          trusted.find( m->from ) != trusted.end())
      {
         LOG( errorlog, "Self=%s message (apparently) from active peer %s rejected" 
              "because of bad signature", pid.c_str(), m->from.c_str(), pid.c_str()) ; 
         return false; 
      }
      else 
      {
         LOG( errorlog, "Self=%s message apparently from inactive peer %s rejected"
              "because of bad signature : sending public key request", 
              pid.c_str(), m->from.c_str() );
         _send_public_key_request(m->from, m->causalid);   // note that the causal id will pass through but 
                                                           // expiry date will be different 
         return false; 
      }
   }

#if 0
   else if(!keyrepository.find(m->from, ki) && bootstrap.find(m->from) != bootstrap.end()) 
   {
      std::string sender = m->from; 
      PublicKeyEncryption * ep = m->commonpubkey.Clone(); 
      keyrepository.add(ep, sender, get_local_time(), get_local_time() + expiry_interval); 
      LOG( authlog, "Self=%s CommonKeyReceivedFromPeer=%s" , pid.c_str() , sender.c_str() ); 

      std::string sender = m->from; 
      AdmissionRequestMessage req;
      req.from = sender;
      req.messagetype = "AdmissionRequestMessage" ;
      req.pubkey = m->pubkey ; 
      req.since_time = 0;
      req.until_time = ~0ull;
      req.to = pid ;   
      LOG( authlog, "Fast key receive : Self=%s KeyReceivedFromPeer=%s" , pid.c_str() , sender.c_str() );
      admission_request(&req);
   }
#endif
   

   live[m->from] = get_local_time(); 
   if( nonlive.find(m->from) != nonlive.end() )
      nonlive.erase(m->from); 

   LOG( messagelog, "Receive Signed Message: Self=%s MessageType=%s Expiration=%llu CausalID=%lu DataSize=%u bytes FromPeer=%s",    
        pid.c_str(), m->messagetype.c_str(), m->expiration, m->causalid, mesg.size(), m->from.c_str()) ; 


   bool status = false; 
   if( m->messagetype == "PublicKeyRequestMessage" ) 
      status = public_key_request(m);

   else if( (m->messagetype == "AdmissionRequestMessage") )
      status = admission_request(m);

   else if( (m->messagetype == "AuthenticationRequestMessage") )
      status = authentication_request(m); 

   else if( (m->messagetype == "Challenge") ) 
      status = challenge(m);

   else if( (m->messagetype == "Response") ) 
      status = response(m); 

   else if( (m->messagetype == "AuthenticationVote") )
      status = vote(m);

   else if( (m->messagetype == "ProofRequest") ) 
      status = proof_request(m);

   else if( m->messagetype ==  "ByzantineVoteFromProbationary" )
      status = byzantine_vote(m); 

   else if( m->messagetype == "ByzantineFault" ) 
      status = byzantine_fault(m); 

   else if( m->messagetype == "ByzantineAuthenticationMessage" )
      status = byzantine_authentication(m);

   else
      assert(0); 

   delete m; 
   return status; 
}








bool Self::_send_public_key_request(const peerid_t& p, unsigned long causalid)
{
   if(!causalid) 
      causalid = rand(); 
   
        /**
         * Prevent repeated sending of public key requests in time shorter than 
         * expiry/redo.  the condition means that request was sent , and it was
         * sent recently, i.e. elapsed time is less than interval 
         */
   if( (sent_public_key_request.find(p) != sent_public_key_request.end()) && 
      ((get_local_time() - sent_public_key_request[p]) <  (expiry_interval/REDOFRAC) ))
   {
      LOG( protolog , "Self=%s  PeerKeyUnknown=%s : not sending pub key request, sent recently" , 
           pid.c_str(), p.c_str() ) ; 
      return true; 
   }

   sent_public_key_request[p] = get_local_time(); 

   LOG( protolog , "Self=%s  PeerKeyUnknown=%s : sending public key request cid=%u" , 
        pid.c_str(), p.c_str(), causalid) ;

   PublicKeyRequestMessage req;
   req.causalid = causalid; 
   req.expiration = expiry_interval + get_local_time();   // expire requests that are too old to be interesting
   req.from = pid; 
   req.messagetype = "PublicKeyRequestMessage" ; 
   req.pubkey = encryptor; 
   req.to = p; 
   req.sign(decryptor); 

   return factory->Proxy(p)->public_key_request(&req); 
}








bool Self::_get_authentic_key(const peerid_t& p, 
                              std::string& pubkey, int & trust_value, bool & unknown)
{
   unknown = false; 
   trust_value = 0; 
   pubkey.clear(); 
   
   if( bootstrap.find(p) != bootstrap.end() )
   {
      KeyInfo info; 
      if(!keyrepository.find(p, info))
      {
         LOG( protolog , "Self=%s  BootstrapPeerKeyUnknown=%s : sending public key request" , 
              pid.c_str(), p.c_str() ) ;
         unknown = true; 
         trust_value = 1; 
         _send_public_key_request(p); 
         return false;
      }
      else
      {
         std::ostringstream outs;
         boost::archive::xml_oarchive oa(outs);
         oa << BOOST_SERIALIZATION_NVP(info);
         pubkey = outs.str(); 
         unknown = false;
         trust_value = 1; 
         return true; 
      }
   }

   else if( trusted.find(p) != trusted.end() )
   {
      KeyInfo info; 
      if(keyrepository.find(p, info))
      {
         std::ostringstream outs;
         boost::archive::xml_oarchive oa(outs);
         oa << BOOST_SERIALIZATION_NVP(info);
         pubkey = outs.str(); 
         trust_value = (int) log(info.group_migrations); 
         return true; 
      }
      LOG( errorlog, "Self=%s peer %s is trusted but has no known public key" , 
           pid.c_str(), p.c_str() ) ; 
      return false; 
   }

   else if(probationary.find(p) != probationary.end() )
   {
      KeyInfo info; 
      if(keyrepository.find(p, info))
      {
         std::ostringstream outs;
         boost::archive::xml_oarchive oa(outs);
         oa << BOOST_SERIALIZATION_NVP(info);
         pubkey = outs.str(); 
         trust_value = 0;
         return true; 
      }
      LOG( errorlog, "Self=%s peer %s is probationary but has no known public key" , 
           pid.c_str(), p.c_str() ) ; 
      return false; 
   }

   else if(untrusted.find(p) != untrusted.end())
   {
      LOG( protolog, "peer %s is untrusted : no authentic key provided" , p.c_str() ) ;
      trust_value = -1; 
      return false; 
   }

   else
   {
      LOG( protolog , "Self=%s UnknownPeer=%s : sending public key request" , 
           pid.c_str(), p.c_str()) ;
      unknown = true; 
      trust_value = 0; 
      _send_public_key_request(p); 
      return false;
   }
}








bool Self::public_key_request(Message * _m)
{
   PublicKeyRequestMessage * m = dynamic_cast<PublicKeyRequestMessage *> (_m) ; 
   Assert(_m,m);

        /**
         * See if the key is unknown 
         */
   KeyInfo info; 
   if( !keyrepository.find(m->from, info) )
   {
      PublicKeyEncryption * ep = m->pubkey.Clone();    // cannot add pubkey from message : it is going to be deleted 
      keyrepository.add(ep, m->from, 0, ~0); 
      LOG( protolog, "Self=%s KeyReceivedFromPeer=%s" , pid.c_str() , m->from.c_str() ); 
      LOG( authlog, "Self=%s KeyReceivedFromPeer=%s" , pid.c_str() , m->from.c_str() ); 
   }

   LOG( protolog , "Self=%s Requestor=%s needs authentic key of self cid=%lu"
        ": sending admission request", pid.c_str(), m->from.c_str(), m->causalid ) ;

   AdmissionRequestMessage req; 
   req.setcause(*m); 
   req.from = pid; 
   req.messagetype = "AdmissionRequestMessage" ; 
   req.pubkey = encryptor; 

        // TODO - encryptor should provide guidance on validity 
   req.since_time = 0; 
   req.until_time = ~0ull; 
   req.to = m->from; 
   req.sign(decryptor); 
   factory->Proxy(req.to)->admission_request(&req); 

   return true;
}















     /**
      * Admission request    
      * A peer $A$ makes a key possession claim by notifying the peer $B$. If $A$ has an expired 
      *	authenticated public key $K^\star_{A}$, it includes the proof of its possession 
      * ${\cal P} = \{A,K_A\}_{A^\star}$.  
      *
      * $B$ announces the claim to the group.
      *
      * A --> B  \{A,B,\text{\tt admission request},\{A,K_{A}[,{\cal P}]\}_A\}_A 
      * For each trusted peer P_i of B 
      *     B --> P_i   {\cal B}[i] = \{B,P_i,\text{\tt authentication request}, \{A,K_{A}[,{\cal P}]\}_A \}_B 
      *
      */
bool Self::admission_request(Message * _m)
{
   AdmissionRequestMessage* m = dynamic_cast<AdmissionRequestMessage *>(_m);
   Assert(_m,m);
   
   peerid_t sender = m->from; 
   LOG( protolog , "Self=%s AdmissionRequest from Peer=%s cid=%lu",
        pid.c_str(), m->from.c_str(), m->causalid) ;


        /**
         * Sender of admission request is already untrusted.  ignore the request 
         * to avoid denial of service.  Once economics is introduced, must keep track of the
         * cost incurred in coming till this point 
         */
   if( untrusted.find(sender) != untrusted.end() )
   {
      LOG( errorlog , "peer %s is untrusted by self %s"
           ": denying admission request", m->from.c_str(), pid.c_str() ) ;
      return false;
   }



          /**    
          * Multiple admission requests must be silently ignored.  
          * But, this becomes common in lazy mode of operation, so made this a 
          * weaker condition by having shorter expiry interval 
          */
   KeyInfo info; 
   if( Belongs(sender, probationary, expiry_interval/REDOFRAC) && keyrepository.find(sender, info) ) 
   {
      LOG( protolog , "peer %s is already probationary by %s"
           ": ignoring admission request ", m->from.c_str(), pid.c_str() ) ;
      return true; 
   }

   
        /**
         * Already trusted case 
         */ 
   if( Belongs(sender, trusted) && Belongs(sender, probationary) == false && keyrepository.find(sender, info) ) 
   {
      LOG( protolog , "peer %s is already trusted by %s"
           ": ignoring admission request ", m->from.c_str(), pid.c_str() ) ;
      return true; 
   }


        /**
         * These peers are trusted unless a byzantine phase is on
         */
   if( sender == pid || (Belongs(sender, bootstrap) && byzantine_probationary.empty()) ) 
   {
           // also know the key being authenticated, no point in starting auth 
           // which is triggered by unknown key 
      if( keyrepository.find(sender, info) )
      {
         _set_trusted(sender); 
         LOG( protolog, "Self=%s already has the public key - redundant KeyReceivedFromTrustedPeer=%s" , 
              pid.c_str() , sender.c_str() ); 
         return true; 
      }
      
#if 0
           // if we dont have a key then save key, mark trusted, and continue
           // with the auth protocol. note the case does not have a return  
      else if ( !Belongs(sender, trusted) )  
      {
         std::cerr << "Here" << std::endl ; 
         trusted[ sender ] = get_local_time(); 
         LOG( protolog, "Self=%s redundant KeyReceivedFromTrustedPeer=%s" , pid.c_str() , sender.c_str() ); 
      }
#endif 
   }


        /*
         * Keep note of the new probationary key 
         */
   PublicKeyEncryption * ep = m->pubkey.Clone();    // cannot add pubkey from message : it is going to be deleted 
   keyrepository.add(ep, sender, m->since_time, m->until_time); 
   if(!Belongs(sender, bootstrap))  
   {
      probationary.insert(std::make_pair(sender, get_local_time()));
      LOG( protolog , "Self=%s added Probationary=%s" , pid.c_str() , sender.c_str() );
   }       
   LOG( protolog, "Self=%s KeyReceivedFromPeer=%s" , pid.c_str() , sender.c_str() ); 
   LOG( authlog, "Self=%s KeyReceivedFromPeer=%s" , pid.c_str() , sender.c_str() ); 


        /* 
         * Send the authentication request to each peer 
         */ 
   AuthenticationRequestMessage req; 
   req.setcause(*m); 
   req.from = pid; 
   req.request = *m ; 
#if 0
   req.pubkey = encryptor; 
#endif 
   req.messagetype = "AuthenticationRequestMessage" ; 
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
   {

      LOG( protolog , "Self=%s  ProbationaryPeer=%s Authenticator=%s sending authentication request cid=%lu" , 
          pid.c_str(), m->from.c_str(), i->first.c_str(), m->causalid ) ;

      req.to = i->first;
      req.sign(decryptor); 
      factory->Proxy(i->first)->authentication_request(&req);
   }

        /*
         * If a bootsrapping peer's key is received, it migh have imact on 
         * authentication of peers. 
         */ 
   if( bootstrap.find(sender) != bootstrap.end() ) 
   {
      LOG( authlog, "Self=%s KeyReceivedFromBootStrapPeer=%s : triggering authentication routine cid=%lu" , 
           pid.c_str() , sender.c_str(), m->causalid ); 
      _authenticate_peers(m->causalid); 
   }

   return true; 
}












bool Self::authentication_request(Message * _m)
{
   struct AuthenticationRequestMessage* m = dynamic_cast<AuthenticationRequestMessage *>(_m);
   Assert(_m,m);

   LOG( protolog , "Self=%s VoteRequestor=%s Probationary=%s : request for authentication vote cid=%lu", 
        pid.c_str(), m->from.c_str(), m->request.from.c_str(), m->causalid ) ;

   peerid_t sender = m->from; 
   peerid_t whotoauth = m->request.from; 

        //-----------------------------------------------------------------------------
        // Keeping note of the waiters with waiterset of type map<peer, set<peer> > 
        // waiters[probationary] is supposed to be the set of peers that are interested 
        // in authentication vote on public key of probationary.
        // Whenever a new request comes the response if it exists in proof repository 
        // is sent to all the waiters in one shot.  This is shown in the two code 
        // snippets given below 
   if( waiters.find(whotoauth) == waiters.end() ) 
   {
      waiters[whotoauth] = std::set<peerid_t>() ; 
      for( group_t::iterator i = bootstrap.begin(); i != bootstrap.end(); i++ )
         waiters[whotoauth].insert(i->first); 
   }
   if( waiters[whotoauth].find(sender) == waiters[whotoauth].end() )
      waiters[whotoauth].insert(sender);
   LOG( authlog , "Self=%s  Probationary=%s has NumWaiters=%d for proof of posession", pid.c_str(), whotoauth.c_str(), waiters[whotoauth].size() ) ;


   ProofInfo pi;
   pi.challenger = pid;
   pi.responder = whotoauth;
   pi.observer = pid;


        //-----------------------------------------------------------------------------
        // Fast path to send known proofs to other peers and skip the challenge response
        // step : it has already been done earlier.
   Proof p;
   bool pinvalid, ainvalid, kinvalid; 
   if( proofs.getProof(p, pi) && keyrepository.isValid(p, pinvalid, ainvalid, kinvalid) )
   {
      p.from = pid; 
      p.messagetype = "AuthenticationVote" ; 
      p.setcause(*m);
#if 0
      p.pubkey = encryptor; 
#endif 
      p.sign(decryptor); 

      LOG( protolog, "Self=%s found valid (pv=%d,av=%d,kv=%d) proof for ProbationaryPeer=%s cid=%lu" , 
           pid.c_str(), pinvalid, ainvalid, kinvalid, whotoauth.c_str(), m->causalid) ;

      for( std::set<peerid_t>::iterator i = waiters[whotoauth].begin() ; i != waiters[whotoauth].end() ; i++ ) 
      {
         LOG( protolog , "Self=%s sending authentication vote for Probationary=%s to Authenticator=%s cid=%lu" ,
              pid.c_str(), whotoauth.c_str(), i->c_str(), m->causalid) ;
         p.to = *i ; 
         factory->Proxy(*i)->vote(&p);
      }
      waiters[whotoauth].clear(); 
      waiters.erase(whotoauth); 
      return true; 
   }


        //-----------------------------------------------------------------------------
        // Slow path used if the proof of posession is not found 
        // TODO: periodically remove old challenges and send challenge to the unchallenged peer
   if( !proofs.getChallenge(p, pi.responder) || get_local_time() > p.expiration ) 
   {
      Challenge c;
      c.setcause(*m); 
      c.from = pid; 
      c.to = whotoauth;
      c.messagetype = "Challenge" ; 
      c.challenge.random(CHALLENGE_BITS);
#if 0
      c.pubkey = encryptor; 
#endif 
      c.sign(decryptor);
   
      Proof p; 
      p.challenger = pid; 
      p.responder = whotoauth; 
      p.observer = pid; 
      p.challenge = c; 

      LOG( protolog , "Self=%s sending challenge to ProbationaryPeer=%s cid=%lu", 
           pid.c_str(), whotoauth.c_str(), m->causalid ) ; 

      proofs.putChallenge(p);

      factory->Proxy(whotoauth)->challenge(&c);
   }

   return true;
}








     /** 
      * this is run in the probationary peer 
      */
bool Self::challenge(Message * _m)
{
   Challenge * m = dynamic_cast<Challenge *>(_m);
   Assert(_m,m);


   LOG( protolog , "Self=%s received challenge %s from Challenger=%s cid=%lu", 
        pid.c_str(), m->challenge.print(10).c_str(), m->from.c_str(), m->causalid ) ;

   Response res; 
   res.setcause(*m);
   res.challenge = m->challenge ; 
#ifdef DRYRUN 
   res.response = m->challenge ; 
#else 
   decryptor.Decrypt( res.response, m->challenge ); 
#endif
   res.from = pid; 
   res.to = m->from; 
   res.messagetype = "Response" ; 
#if 0
   res.pubkey = encryptor; 
#endif 
   res.sign(decryptor); 

   Proof p; 
   p.challenge = *m ; 
   p.response = res; 
   p.challenger = m->from; 
   p.responder = pid; 
   p.observer = pid; 

   LOG( protolog , "Self=%s sending response %s to Challenger=%s cid=%lu", 
        pid.c_str(), res.response.print(10).c_str(), m->from.c_str(), m->causalid ) ;

   proofs.putResponse(p); 
   
   factory->Proxy(m->from)->response(&res);

   return true;
}










     /*
      * On receiving the response, the challenger should be executing this.
      * The challenger should check if the response is correct and send corresponding
      * votes to the waiters. 
      */
bool Self::response(Message * _m) 
{
   Response * m = dynamic_cast<Response *>(_m);
   Assert(_m,m);

   LOG( protolog , "Self=%s received response from Probationary=%s cid=%ul", 
        pid.c_str(), m->from.c_str(), m->causalid) ;


   Proof p; 
   if(!proofs.getChallenge(p, m->from))
   {
      LOG( errorlog , "received response from peer %s to self %s: but no challenge was sent", 
           m->from.c_str(), pid.c_str() ) ;
      return false; 
   }


   p.from = pid; 
   p.messagetype = "AuthenticationVote" ; 
   p.response = *m ; 
   p.setcause(*m);
#if 0
   p.pubkey = encryptor; 
#endif 


        /** 
         * testing eager sending of vote when received : too many wait votes found
         */ 
   for( group_t::const_iterator i = trusted.begin(); i != trusted.end(); i++ ) 
      if( waiters.find(m->from) == waiters.end() || waiters[m->from].find(i->first) == waiters[m->from].end())
      {
         waiters[m->from].insert(i->first); 
         LOG( protolog , "Self=%s eagerly added waiters Trusted=%s for proof from Probationary=%s " , 
              pid.c_str(), i->first.c_str(), m->from.c_str()) ;
      }



   if( waiters.find(m->from) == waiters.end() ) 
   {
      LOG( protolog , "Self=%s no waiters for proof from Probationary=%s " 
           " : no authentication vote sent" , pid.c_str(), m->from.c_str()) ;
      return true; 
   }

   for( std::set<peerid_t>::iterator i = waiters[m->from].begin() ; i != waiters[m->from].end() ; i++ ) 
   {
      LOG( protolog , "Self=%s sending authentication vote for Probationary=%s to Waiter=%s cid=%ul" ,
           pid.c_str(), m->from.c_str(), i->c_str(), m->causalid) ;

      p.to = *i ; 

      p.sign(decryptor); 

      factory->Proxy(*i)->vote(&p);
   }

        //waiters.erase(waiters.find(m->from)); 
   waiters.erase(m->from); 
   return true;
}













bool Self::vote(Message * _m) 
{
   Proof * m = dynamic_cast<Proof *>(_m);
   Assert(_m,m);


   LOG( protolog , "Self=%s received authentication vote about Probationary=%s from Authenticator=%s cid=%ul" , 
        pid.c_str(),  m->from.c_str(), m->responder.c_str(), m->causalid ) ; 

        /**
         * Insert the newly received proof into the proof database 
         */
   m->observer = pid; 
   m->sign(decryptor); 
   proofs.putProof(*m); 

        /** 
         * each time the vote is received, determine if some action can be taken
         */ 
   _authenticate_peers(m->causalid); 
   return true; 
}








     /*
      * Byzantine agreement 
      *
      * Phase 1: 
      *
      * $B$ is the authenticator, while $A$ is probationary peer.  $B$ asks the peer 
      * $A$ for the challenges it received, and its responses to them.  It then compares 
      * the proofs received from the peers and those received from $A$. 
      *
      *  B --> A    : \{B,A, \text{ {\tt proof request}}\}_B 
      *  A --> B    : \{A,B, \text{ {\tt proof}}, {\cal V}_A \}_A 
      * 
      * At this stage one can determine is any of the trusted peers or the probationary 
      * peer is provably malicious.  If yes .... 
      *
      * Phase 2: 
      *
      * Suppose nobody is provably malicious then move to next phase.  $B$ notifies 
      * the peers of the received proofs so that malicious parties are eliminated from the trusted group. 
      * 
      *  If $A$ is not proved malicious
      *     For each trusted peer P_i of  B  
      *        B  -->  P_i   :  \{ B, P_i, \text{ {\tt byzantine fault}}, {\cal B}, {\cal V}_B\}_{B} 
      *
      *     For each trusted peer P_j of P_i  
      *        P_i --> P_j   :   \{ P_i, P_j, \text{ {\tt byzantine agreement}}, {\cal B}, {\cal V}_j\}_{P_i} 
      *
      */


bool Self::_byzantine_authentication_1(peerid_t probationary, unsigned long causalid)
{
   if(!causalid) 
      causalid = rand(); 

   byzantine_probationary.insert( make_pair(probationary, std::set<peerid_t>()) ) ; 

   LOG( protolog, "self %s starting byzantine agreement on %s" , 
        pid.c_str(), probationary.c_str()); 

   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
   {
      ProofRequest pr; 
      pr.from = pid; 
      pr.to = probationary; 
      pr.messagetype = "ProofRequest" ; 
      pr.challenger = i->first; 
      pr.observer = pr.responder = probationary; 

      LOG(  protolog, "self %s send proof request to %s for proof wrt %s for byzantine agreement on %s" , 
            pid.c_str(), probationary.c_str(), i->first.c_str(), probationary.c_str()); 

      factory->Proxy(i->first)->proof_request(&pr);
      byzantine_probationary[probationary].insert(i->first);
   }
   return true; 
}






bool Self::proof_request(Message * _m)
{
   ProofRequest * m = dynamic_cast<ProofRequest *>(_m);
   Assert(_m,m);   

   LOG( protolog, "probationary peer %s received proof request from %s wrt challenger %s" , 
        pid.c_str(), m->from.c_str(), m->challenger.c_str() ) ; 

   Proof p; 
   if( proofs.getResponse(p, m->challenger) )
   {
      LOG( protolog, "sending byzantine vote to peer %s regarding %s from probationary self %s" , 
           m->from.c_str(), m->challenger.c_str(), pid.c_str() ) ; 

      p.from = pid; 
      p.to = m->from; 
      p.messagetype = "ByzantineVoteFromProbationary" ; 
      factory->Proxy(m->from)->byzantine_vote(&p);
   }

   return true; 
} 







bool Self::byzantine_vote(Message * _m)
{
   Proof * m = dynamic_cast<Proof *>(_m);
   Assert(_m,m);   

   bool pinvalid, ainvalid, kinvalid; 
   if(!keyrepository.isValid(*m, pinvalid, ainvalid, kinvalid))
   {
      LOG( protolog, "received incorrect proof from peer %s (pi=%d,ai=%d,ki=%d) wrt. %s to self %s" 
           " : making untrusted" , 
           m->responder.c_str(), 
           pinvalid, ainvalid, kinvalid, 
           m->challenger.c_str(), pid.c_str() ); 

      _set_untrusted(m->responder); 
      byzantine_probationary.erase(m->responder); 
      return true; 
   }


   if(untrusted.find(m->responder) != untrusted.end())
   {
      LOG(protolog, "already untrusted peer %s sends a correct message to self %s" 
           " : should not be the case if it was honest, just ignore it" , 
           m->responder.c_str(), pid.c_str()); 

      byzantine_probationary.erase(m->responder);
      return true;
   }

   ProofInfo pi; 
   pi.challenger = m->challenger; 
   pi.responder = m->responder; 
   pi.observer = m->observer; 
   proofs.putProof(*m);

   Proof p; 
   pi.observer = m->challenger;

   if( proofs.getProof(p, pi) && 
       keyrepository.isValid(p, pinvalid, ainvalid, kinvalid) != 
       keyrepository.isValid(*m, pinvalid, ainvalid, kinvalid))
   {
      LOG( protolog, "%s is provably malicious on challenge response for probaitionary %s as seen"
           "by self %s" , 
           m->challenger.c_str(), m->responder.c_str() , pid.c_str() ); 

      probationary.erase(m->challenger);
      trusted.erase(m->challenger);
      time_t epoch = time(0);
      untrusted.insert( make_pair(m->challenger, epoch)) ; 
      byzantine_probationary.erase(m->responder); 
      return true; 
   }

   byzantine_probationary[m->responder].erase(m->challenger);
   if( byzantine_probationary[m->responder].empty()) 
   {
      LOG( protolog, "probationary peer %s succesfully shows all"
           "correct challenge response pairs to self %s  : need phase 2 of byzantine agreement", 
           m->responder.c_str(), pid.c_str() ) ; 

      return _byzantine_authentication_2(m->responder);
   }
   else
      LOG( protolog, "probationary peer %s still pending %d challenge response shows for self %s",
           m->responder.c_str(), byzantine_probationary[m->responder].size(), pid.c_str()) ; 

   return true; 
}





     /* Phase 2: 
      *
      * Suppose nobody is provably malicious then move to next phase.  $B$ notifies 
      * the peers of the received proofs so that malicious parties are eliminated from the trusted group. 
      * 
      *  If $A$ is not proved malicious
      *     For each trusted peer P_i of  B  
      *        B  -->  P_i   :  \{ B, P_i, \text{ {\tt byzantine fault}}, {\cal B}, {\cal V}_B\}_{B} 
      *
      *     For each trusted peer P_j of P_i  
      *        P_i --> P_j   :   \{ P_i, P_j, \text{ {\tt byzantine agreement}}, {\cal B}, {\cal V}_j\}_{P_i} 
      *
      */

bool Self::_byzantine_authentication_2(peerid_t probationary)
{
   LOG( protolog, "probationary %s causes byzantine authentication on peers of self %s", 
        probationary.c_str(), pid.c_str() ); 

   byzantine_probationary.erase(probationary); 
   if( byzauth_matrix.find(probationary) != byzauth_matrix.end() && 
       byzauth_matrix[probationary].isRecent())
   {
      LOG( protolog, "another byzantine agreement going on for probationary %s for self %s :"   
           " subsuming second agreement in first", 
           probationary.c_str(), pid.c_str() ); 

      return true; 
   }

   ByzAuthMatrix bm; 
   byzauth_matrix.insert(make_pair(probationary, bm)); 
   byzauth_matrix[probationary].init(trusted, probationary) ; 

   std::vector<Proof> from_trusted;
   std::vector<Proof> from_probationary;
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
   {  
      Proof p; 
      ProofInfo pi; 
      pi.challenger = i->first;
      pi.responder = probationary; 
      pi.observer = i->first; 
      if( proofs.getProof(p, pi) )
         from_trusted.push_back(p);

      pi.observer = probationary;
      if( proofs.getProof(p, pi) )
         from_probationary.push_back(p);
   }

   
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
   {
      ByzantineFault bf; 
      bf.from = pid; 
      bf.to = i->first; 
      bf.messagetype = "ByzantineFault" ; 
      bf.probationary = probationary;
      bf.from_probationary = from_probationary;
      bf.from_trusted = from_trusted; 

      LOG( protolog, "sending byzantine fault caused by %s to trusted peer %s from self %s" , 
           probationary.c_str(), i->first.c_str(), pid.c_str() ) ; 

      factory->Proxy(i->first)->byzantine_fault(&bf);
   }

   return true; 
}




bool Self::byzantine_fault(Message * _m)
{
   ByzantineFault * m = dynamic_cast<ByzantineFault *>(_m);
   Assert(_m,m);   

   LOG( protolog, "received byzantine fault about probationary %s from trusted %s to self %s" , 
        m->probationary.c_str(), m->from.c_str(), pid.c_str() ) ; 

   std::vector<Proof> from_trusted;
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
   {
      Proof p; 
      ProofInfo pi; 
      pi.challenger = i->first;
      pi.responder = m->probationary; 
      pi.observer = pid; 
      if( proofs.getProof(p, pi) )
         from_trusted.push_back(p);
   }   
        /**
         * so far none of the peers trusted or probationary is provably malicious or 
         * faulty 
         */
   if( byzauth_matrix.find(m->probationary) != byzauth_matrix.end() && 
       byzauth_matrix[m->probationary].isRecent())
   {
      LOG( protolog, "another recent byzantine fault is active  about probationary %s to self %s",
           m->probationary.c_str(), pid.c_str() ) ; 
      return true; 
   }

   ByzAuthMatrix bm; 
   byzauth_matrix.insert(make_pair(m->probationary, bm)); 
   byzauth_matrix[m->probationary].init(trusted, m->probationary) ; 

   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
   {
      LOG( protolog, "acknowledge byzantine fault by sending byzantine authentication message"
           "to trusted peer %s from self %s",  
           i->first.c_str() , pid.c_str() ) ; 

      ByzantineAuthenticationMessage ba; 
      ba.from = pid; 
      ba.to = i->first; 
      ba.messagetype = "ByzantineAuthenticationMessage" ; 
      ba.probationary = m->probationary;
      ba.from_trusted = from_trusted; 
      factory->Proxy(i->first)->byzantine_authentication(&ba);
   }

   return true; 
}
   









bool Self::byzantine_authentication(Message * _m)
{
   ByzantineAuthenticationMessage * m = dynamic_cast<ByzantineAuthenticationMessage *>(_m);
   Assert(_m,m);   

   LOG( protolog, "peer %s sends ack ByzantineAuthenticationMessage (probationary=%s)" 
        "for byzantine fault to self %s", 
        m->from.c_str(), m->probationary.c_str(), pid.c_str() ); 

   if( byzauth_matrix.find(m->probationary) == byzauth_matrix.end() ) 
   {
      LOG( errorlog, "peer %s sends ack ByzantineAuthenticationMessage (probationary=%s) to self %s" 
           " but there was no known byzantine fault (bad trusted group ?? )" , 
           m->from.c_str(), m->probationary.c_str(), pid.c_str() ); 

      return false;
   }

   for(std::vector<Proof>::iterator i = m->from_trusted.begin(); i != m->from_trusted.end(); i++) 
   { 
      if(byzauth_matrix[m->probationary].insert(i->challenger, m->from, *i))
      {
         if(byzauth_matrix[m->probationary].gotEnough())
         {
            LOG( protolog, "byzantine agreement for probationary %s at self %s concludes", 
                  m->probationary.c_str(), pid.c_str() ); 
                 // TODO : need more details in error log. 
                 // who was trusted before and got deleted... etc 
            
            byzauth_matrix[m->probationary].agreement(trusted, untrusted, probationary, keyrepository);
            byzauth_matrix.erase(m->probationary); 
         }
      }
      else
         LOG( protolog, "could not accept proof from %s for probationary %s"  
              " and challenger %s at self %s", m->from.c_str() , 
              m->probationary.c_str(), i->challenger.c_str(), pid.c_str() ); 
           // TODO : need more details in error log, send ref to errorlog to matrix
   }
   

   return true; 
}






int Self::refcount = 0; 



Self::~Self()
{
   if(!--refcount)
      close_logging() ; 
}


Self::Self()
   : plocal_time(0)
{
#ifdef DEBUG 
   prevcompletion = 0.0; 
#endif 
   shortfall_in_groupsize = false; 
}



void Self::Init(std::string _cfgfile, bool dummy) 
{
   if(!dummy && !refcount++)
   {  
      cfgfile = _cfgfile; 
      initialize_logging(cfgfile) ; 
   }


        // need to clone to prevent boost pointer conflict on serielization on exit.  Cannot serialize the
        // same key tgrough key repository and encryptor. 
   PublicKeyEncryption * pubkey = encryptor.Clone(); 
   keyrepository.add(pubkey, pid, 0, 10000000000ull);
   _set_trusted(pid); 

        // shouldnt we get public key and authenticate all bootstrap peers if their
        // key is unknown. yes of course else how to bootstrap 
   for( group_t::iterator p = bootstrap.begin() ; p != bootstrap.end() ; p++ )
   {
      KeyInfo ki; 
      if(!keyrepository.find( p->first , ki ))
      {
         _send_public_key_request( p->first ) ; 
      }
   }
}




bool Self::debug()
{
   std::cout << "self = " << pid << std::endl;
   for( group_t::iterator p = probationary.begin() ; p != probationary.end() ; p++ )
      std::cout << p->first << " : " << p->second << std::endl; 
   std::cout << std::endl;
   return true; 
   // return keyrepository.debug(); 
}








     /*
      * Rescan the set of probationary peers to check if any of them can be authenticated
      * i.e. we have received enough information to decide on whether it is honest or not
      */
void Self::_authenticate_peers(unsigned long causalid)
{
   std::set<std::string> admitted;
   std::map<std::string, int> optimistic;
   std::set<std::string> suspected;  
   std::set<std::string> todo; 
   for( group_t::iterator p = probationary.begin(), q=p ; p != probationary.end() ; p++ )
   {
      KeyInfo ki;

      std::string peername = p->first; 
      if( !keyrepository.find(peername, ki) && bootstrap.find(peername) != bootstrap.end() ) 
      {
         _send_public_key_request(peername, causalid);
         continue; 
      }

      assert( keyrepository.find(peername, ki));

      int count = 0; 
      int correct = 0; 
      int incorrect = 0; 
      int total = 0; 
      int pending = 0; 
      std::map<std::string, std::string> detail_info; 
      for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
      {
              /**
               * We are receiving votes about a probationary peer. Need to iterate only 
               * over the peers that were trusted before the peer became probationary 
               */
         if( i->second > p->second && bootstrap.find(i->first) == bootstrap.end()) 
         {
#ifndef DRYRUN
            LOG( protolog , "Self=%s  ignoring Trusted=%s  became trusted after Probationary=%s became probationary cid=%ul" ,
                 pid.c_str() , i->first.c_str() , p->first.c_str(), causalid ) ; 
            detail_info[ "Ignored" ] += (i->first + " "); 
#endif
            continue; 
         }


              /*
               * There is a trusted peer whose key we do not have.  Cannot test validy of proofs
               * from this peer
               */
         if(!keyrepository.find(i->first, ki))
         {
            total++; 
            pending++;
#ifndef DRYRUN
            detail_info[ "WaitKey" ] += (i->first + " "); 
#endif
            continue;
         }
   

         ProofInfo pi;
         pi.challenger = i->first; 
         pi.responder = p->first;
         pi.observer =  pid;

         Proof p;    
         bool pinvalid = false, ainvalid = false, kinvalid = false;
         if( proofs.getProof(p, pi) ) 
         {
            count++; 
            if( keyrepository.isValid(p, pinvalid, ainvalid, kinvalid)) 
            {
#ifndef DRYRUN
               detail_info[ "Agree" ] += (i->first + " "); 
#endif
               correct++; 
            }

            else if ( pinvalid && !ainvalid && !kinvalid )
            {
#ifndef DRYRUN
               detail_info[ "Agree" ] += (i->first + " "); 
#endif 
               correct++; 
            }

            else
            {
#ifndef DRYRUN
               detail_info[ "Disagree" ] += (i->first + " "); 
#endif 
               incorrect++; 
#ifdef DEBUG
               BREAK(); 
               keyrepository.isValid(p, pinvalid, ainvalid, kinvalid) ;
#endif
            }
         }
         else
         {
#ifndef DRYRUN
            detail_info[ "WaitVote" ] += (i->first + " "); 
            LOG( protolog, "Self=%s waiting for vote from Peer=%s for Probationary=%s because of ainvalid=%d " 
                 " pinvalid=%d kinvalid=%d" , pid.c_str() , i->first.c_str(),  pi.responder.c_str(), 
                 ainvalid, pinvalid, kinvalid ) ; 
#endif
         }

         total++; 
      }

      if( correct > 0 && initial_probationary_group.find(p->first) != initial_probationary_group.end()) 
         optimistic[ p->first ] = correct ; 


           //-------------------------------------------------
           // Print out very detailed authentication status 
           // to compute how far we are from completing authentication 
      std::string detail_info_mesg; 
      for( std::map<std::string, std::string>::iterator i = detail_info.begin(); 
           i != detail_info.end() ; i++ ) 
         detail_info_mesg += ( i->first + "={" + i->second + "} " ) ; 
      
      LOG( authlog, "Self=%s  :  Probationary=%s authentication status Agree=%d Disagree=%d out of Total=%d  cid=%ul LocalTime=%llu :  %s" , 
           pid.c_str(), p->first.c_str(), correct, incorrect, total, causalid, get_local_time(), detail_info_mesg.c_str() ) ; 

      
           //-----------------------------------------------------
           // If enough information is there to get a good decision
      if(total > 3 && correct >= (total/2)) 
      {
         admitted.insert( p->first ) ; 
         LOG( protolog , "Self=%s has enough information (correct = %d count = %d) in vote cid=%ul on Probationary=%s : MakeTrusted " , 
              pid.c_str(), correct, count, causalid, p->first.c_str()) ;
      }


           //-------------------------------------------------------
           // some votes differ, need to call a byzantine authentication on
           // the supposed public key 
      if( correct != count ) 
      {
         LOG( protolog , "Self=%s has disagreement (correct = %d count = %d) in vote cid=%ul on Probationary=%s : ByzantineAgreement" , 
              pid.c_str(), correct, count, causalid, p->first.c_str()) ;
         suspected.insert( p->first ) ; 
      }

           /*
            * Could not decide anything - redo to get way out of indefinite wait 
            */
      else
         todo.insert( p->first ) ; 
   }

   bool change = false; 
   for( std::set<std::string>::iterator i = suspected.begin() ; i != suspected.end(); i++ ) 
   {
      change = true; 
      _byzantine_authentication_1(*i, causalid);
   }


   for( std::set<std::string>::iterator i = admitted.begin() ; i != admitted.end(); i++ ) 
   {
      change = true; 
      _set_trusted(*i); 
   }

   int numremoved = PruneTrustGroups();
   unsigned nknown, ntrusted; 
   float completion = GetCompletion( ntrusted, nknown ) ; 
   LOG( authlog, "SENDER=%s  :  AUTHSTATUS TIME=%llu COMPLETION=%f Trusted=%d  Migrated=%d  Probationary=%d  Bootstrap=%d" ,  
        pid.c_str(), get_local_time(), completion, trusted.size(), numremoved,  probationary.size(), bootstrap.size() ) ; 

/*
#define MAXOPTSTAT 5       

     // did not work properly 
   int optstats[MAXOPTSTAT]; 
   for( int i = 0; i < MAXOPTSTAT; i++ ) 
      optstats[i] = 0; 
   for( std::map<std::string, int>::iterator i = optimistic.begin() ; i != optimistic.end() ; i++ ) 
      if( i->second < MAXOPTSTAT ) 
         optstats[i->second] ++ ; 
   for( int i = MAXOPTSTAT-2; i >= 0; i-- ) 
      optstats[i] += optstats[i+1] ; 
   for( int i = 0; i < MAXOPTSTAT; i++ ) 
      LOG( authlog, "SENDER=%s  :  OPTSTATUS OptLevel=%d TIME=%llu COMPLETION=%f " , pid.c_str(), i, get_local_time(), 100.0*optstats[i]/initial_probationary_group.size() ) ;
*/
   
  
   for( std::set<peerid_t>::iterator i = todo.begin() ; i != todo.end() ; i++ ) 
      if( Belongs(*i, probationary, expiry_interval/REDOFRAC) )
      {
         LOG( authlog, "Self=%s : Resend authentication protocol to Probationary=%s" ,   pid.c_str(), i->c_str() );
         _send_public_key_request(*i) ; 
      }
   
}
 














int Self::PruneTrustGroups() 
{
        // if a peer is trusted and does not respond for 
        // a long time and we are waiting for its input for 
        // a long time, then it makes sense to migrate it or 
        // remove it from bootstrapping group 
   int erased = _erase_slow_peers(); 

        // the trusted group may have shrunk need to get more of 
        // bootstrapping live peers back 
   if ( trusted.size() < min_tg_sz )
   {
           // gather candidates
      std::set<std::string> candidates; 
      int todo = (min_tg_sz - trusted.size());  
      for( group_t::iterator i = bootstrap.begin() ; i != bootstrap.end() && todo > 0 ; i++ ) 
      {
         if( nonlive.find(i->first) != nonlive.end() )
            continue; 
         if( trusted.find(i->first) != trusted.end() ) 
            continue; 
         candidates.insert(i->first); 
         todo--; 
      }

           // todo
           // gather migrated candidates

      if( todo > 0 ) 
      {
         LOG( protolog, "Self=%s while repopulating trust group has shortfall below group size %d" , pid.c_str() , todo ); 
         shortfall_in_groupsize = true; 
      } 
      
      for( std::set<std::string>::iterator i = candidates.begin() ; i != candidates.end() ; i++ ) 
         _set_trusted(*i); 
   }
   

   
        // if the trusted group outgrows application suggested
        // size then need to migrate some peers out of the 
        // trusted group 
   if( max_tg_sz > trusted.size() )
      return erased; 

   unsigned int todelete = ( trusted.size() - max_tg_sz ) ; 
   std::multimap<epoch_t , peerid_t> timeorder; 
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ ) 
   {
      if ( i->first == pid ) 
         continue; 
      if( live.find(i->first) != live.end() ) 
         timeorder.insert( make_pair( -live[i->first], i->first ) ) ; 
      else
         timeorder.insert( make_pair( 0 , i->first ) ) ; 
   }

   int count = 0; 
   while( todelete-- ) 
   {
      _migrate_peer(timeorder.begin()->second); 
      timeorder.erase( timeorder.begin() ) ; 
      ++count; 
   }
   return count + erased; 
}







int Self::_erase_slow_peers() 
{
        // For each peer we rely upon, if it is not live 
        // then it makes sense to erase it as a slow peer.
        // if it is trusted for too long, then just migrate 
        // it so that trusteg group can get new peers. 
        // so we can treat these cases together. 
   int tcount = 0, pcount = 0; 
   std::set<std::string> deleteset; 
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ ) 
   {
           // this condition avoids migrating new trusted peers
      if( (get_local_time() - i->second) < expiry_interval )
         continue; 

           // this one avoids pruning peers that are live 
      if( (get_local_time() - live[i->first]) < expiry_interval ) 
         continue; 

           // it is questionable what is the best way to 
           // handle byzantine and waiters. 
           // collect what is to be deleted into the set 
      if( ///// waiters.find(i->first) != waiters.end() || 
          byzantine_probationary.find(i->first) != byzantine_probationary.end() )
         deleteset.insert(i->first); 
   }

        // physically delete the collected peers 
   for( std::set<std::string>::iterator i = deleteset.begin() ; i != deleteset.end() ; i++ ) 
   {
      if( probationary.find(*i) != probationary.end() )
         pcount++; 

      if( trusted.find(*i) != trusted.end() ) 
         tcount++; 

      PruneNonLive(*i);

      nonlive.insert( make_pair( *i, get_local_time() ) ) ; 
      LOG( protolog, "Self=%s marking peer non live NonLive=%s" , pid.c_str(), i->c_str() ) ; 
   }

   LOG( authlog, "Self=%s DeleteNumPeers=%d from Trusted set" , pid.c_str(), tcount ) ;    
   LOG( authlog, "Self=%s DeleteNumPeers=%d from Probationary set" , pid.c_str(), pcount ) ;   

   return deleteset.size(); 
}









void Self::_migrate_peer(const peerid_t & peer) 
{
   if(trusted.find(peer) == trusted.end())
   {
      LOG( errorlog, "Self=%s beleives that peer Trusted=%s needs migration but trust group doest have the entry" , 
           pid.c_str(), peer.c_str()) ; 
      return; 
   }

   epoch_t now = get_local_time(); 
   keyrepository.migrate(peer, now - trusted[peer]); 
   trusted.erase(peer); 
   LOG( authlog, "Self=%s  :  Migrated Peer Trusted=%s" , pid.c_str(), peer.c_str()) ; 
}







void Self::PruneNonLive(const peerid_t& peer) 
{
        // already authenticated peers need migration 
   if( trusted.find(peer) != trusted.end() && probationary.find(peer) == probationary.end() )
      _migrate_peer(peer); 

   if( probationary.find(peer) != probationary.end() ) 
   {
      probationary.erase(peer); 
      LOG( protolog, "probationary_peer=%s marked non live by self=%s", peer.c_str(), pid.c_str() ) ;
   }


   if( initial_probationary_group.find(peer) != initial_probationary_group.end() ) 
   {
      initial_probationary_group.erase(peer); 
      LOG( protolog, "initial_probationary_peer=%s marked non live by self=%s", peer.c_str(), pid.c_str() ) ;
   }

   if( trusted.find(peer) != trusted.end() ) 
   {
      trusted.erase(peer); 
      LOG( protolog, "trustedpeer=%s marked non live by self=%s", peer.c_str(), pid.c_str() ) ;
   }

   nonlive.insert( make_pair( peer, get_local_time() ) ) ; 
   LOG( protolog, "NonLivePeer=%s marked non live by self=%s", peer.c_str(), pid.c_str() ) ;
}











void  Self::_set_probationary(const peerid_t& p, unsigned long causalid)
{
   if(!causalid) 
      causalid = rand(); 

   untrusted.erase(p);
   if( trusted.find(p) != trusted.end() )
      _migrate_peer(p); 

   if(probationary.find(p) == probationary.end())
   {
      KeyInfo ki; 
      if( keyrepository.find( p, ki ) )
      {  
         probationary.insert( make_pair( p, get_local_time() ) ) ; 
         LOG( protolog, "Peer %s marked probationary by self %s", p.c_str(), pid.c_str() ) ;
      }
           // the key is unknown - cant start the authentication protocol 
           // unless we get the key from peer
      else
         _send_public_key_request(p, causalid); 
   }
}






void  Self::_set_trusted(const peerid_t& p)
{
   untrusted.erase(p); 
   probationary.erase(p);
   bootstrap.insert(make_pair(p, get_local_time())); 
   trusted.insert(make_pair(p, get_local_time())); 
   peers_authenticated_once.insert(make_pair(p, get_local_time())); 
   LOG( protolog, "Peer %s marked trusted by self %s", p.c_str(), pid.c_str() ) ; 
}







void  Self::_set_untrusted(const peerid_t& p)
{
   trusted.erase(p); 
   bootstrap.erase(p); 
   probationary.erase(p);  
   untrusted.insert(make_pair(p, get_local_time())); 
   LOG( protolog, "Peer %s marked un-trusted by self %s", p.c_str(), pid.c_str() ) ; 
}




void Self::set_local_time(epoch_t * _p_local_time) 
{
   bool fixed = false; 
   plocal_time = _p_local_time;
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
      if( i->second > get_local_time() )
      {
         fixed = true;
         trusted[i->first] = get_local_time(); 
      }

   for( group_t::iterator i = probationary.begin() ; i != probationary.end() ; i++ )
      if( i->second > get_local_time() )
      {
         fixed = true;
         probationary[i->first] = get_local_time(); 
      }

   for( group_t::iterator i = bootstrap.begin() ; i != bootstrap.end() ; i++ )
      if( i->second > get_local_time() )
      {
         fixed = true;
         bootstrap[i->first] = get_local_time(); 
      }

   if(fixed) 
      LOG( errorlog, "Moved forward time for Self=%s" , pid.c_str() ) ;
}



epoch_t Self::get_local_time() const 
{
   if (plocal_time)
      return *plocal_time; 

        // TODO: optimization: make get_local_time inline 
        // and interolate with fake_time ; call time(0) occasionally 

   return time(0);
}



void Self::set_tg_size(int max, int min)
{
   max_tg_sz = max;
   min_tg_sz = min;
   assert( max_tg_sz > 3 );
   assert( min_tg_sz > 3 );

   unsigned count = 0; 
   std::set<std::string> deleteset; 
   for( group_t::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
   {
      initial_probationary_group.insert( make_pair( i->first, i->second ) ) ;
     _send_public_key_request( i->first ) ;
      if(count++ < max_tg_sz)
         continue;
      if(bootstrap.find(i->first) != bootstrap.end())
         deleteset.insert(i->first); 
      else
      {
         LOG ( errorlog, "Self=%s has trusted peers not from bootstrap, " 
               "violating assumption that this method is only called on cold start" , 
               pid.c_str() ) ; 
         abort(); 
      }
   }
   for( std::set<std::string>::iterator i = deleteset.begin(); i != deleteset.end() ; i++ )  
   {
      trusted.erase(*i); 
      probationary.erase(*i); 
   }
}






void Self::set_expiry_interval(epoch_t interval)
{
        //if(!strcmp( pid.c_str() , "af99499e165cd398e95bc01cdb0e6ea2")) 
        //BREAK(); 
 
   expiry_interval = interval ; 
}




void Self::check_expired() 
{
   _authenticate_peers(rand()) ; 
}



void Self::MarkLive(const peerid_t& peer) 
{
   live[peer] = get_local_time(); 
   if( nonlive.find(peer) != nonlive.end() )
      nonlive.erase(peer); 
}




double Self::GetCompletion(unsigned & ntrusted, unsigned & nknown)
{
   if( shortfall_in_groupsize ) 
      return 1.0; 

   std::string todolist = "{" ; 
   int total = 0 , todo = 0; 
   for( group_t::iterator p = initial_probationary_group.begin(); p != initial_probationary_group.end() ; p++ )
   {
      if( p->first != pid && 
          peers_authenticated_once.find(p->first) == peers_authenticated_once.end() && 
          probationary.find(p->first) != probationary.end() )
      {
         todolist += p->first ; 
         todolist += ',' ; 
         todo++; 
      }
      total++; 
   }
   todolist += "}"; 
   ntrusted = trusted.size() ; 

   std::set<peerid_t> knowns; 
   for( group_t ::iterator i = trusted.begin() ; i != trusted.end() ; i++ )
      knowns.insert(i->first); 

   for( group_t ::iterator i = probationary.begin() ; i != probationary.end() ; i++ )
      knowns.insert(i->first); 

   nknown = knowns.size() ; 

   float completion = (total > 0) ? (1.0 - (1.0 * todo)/total) : 1.0 ; 


#ifdef DEBUG
   if( completion < prevcompletion ) 
   {
      for( group_t::iterator p = probationary.begin(); p != probationary.end() ; p++ )
         if( prev_probationary.find(p->first) == prev_probationary.end() )
            std::cerr << p->first << " has become probationary again for self " << pid << std::endl ; 

      for( group_t::iterator p = initial_probationary_group.begin(); p != initial_probationary_group.end() ; p++ )
         std::cerr << pid << " initial probationary " << p->first << std::endl ; 
         
      for( group_t::iterator p = prev_probationary.begin(); p != prev_probationary.end() ; p++ )
         std::cerr << pid << " prev probationary " << p->first << std::endl ; 

      for( group_t ::iterator p = probationary.begin() ; p != probationary.end() ; p++ )
         std::cerr << pid << " probationary " << p->first << std::endl ; 
   }

        //The assertion ceases to be meaningful after enough time has passed
        // and peers get marked as non live. expiry interval issues.  this is also
        // expected and normal. still show it in debug mode as an fyi 

        //assert( completion >= prevcompletion ) ; 
   prevcompletion = completion ; 
   prev_probationary = probationary;
#endif 


   LOG( protolog, "Self=%s completion level %f", pid.c_str(), completion ) ; 
   LOG( authlog, "SELF=%s COMPLETION=%f HOLDUP=%s" , 
        pid.c_str(), 
        completion, 
        todolist.c_str() ) ; 
   return completion; 
}







void Self::Sign(const char * mesg, std::string & sig)
{
   UBigNum modulus; 
   decryptor.Modulus(modulus); 
   Digest d; 
   d.getStr(mesg, strlen(mesg)); 
   UBigNum digest = d() % modulus;
   UBigNum signature; 
   decryptor.Decrypt(signature, digest); 
   std::ostringstream output; 
   output << signature; 
   sig = output.str();
}


bool Self::Verify(const char * mesg, const char * sig, const char * peer, bool & unknown)
{
   KeyInfo ki;
   std::string sender(peer); 
   if( !keyrepository.find( sender, ki ) ) 
   {
      unknown = true; 
      return false; 
   }
   else
      unknown = false; 

   UBigNum modulus; 
   ki.ep->Modulus(modulus); 

   Digest d; 
   d.getStr(mesg, strlen(mesg)); 
   UBigNum digest = d() % modulus;
   UBigNum signature, digest2;  
   std::istringstream input(sig); 
   input >> signature; 

   if(!ki.ep->Encrypt(digest2, signature))
   {
      LOG(errorlog, "Problem encrypting to verify signature self=%s sender=%s" , pid.c_str(), peer) ; 
      return false; 
   }

   if( digest != digest2 ) 
   {
      LOG(errorlog, "Incorrect signature self=%s sender=%s" , pid.c_str(), peer) ; 
      return false;
   }

   return true;
}





bool Self::GenerateNewKeyPair(int keybits)
{
   PublicKeyEncryption *pub = 0; 
   PrivateKeyEncryption *priv = 0; 
   if(!RSACore::createkeypair(pub, priv, keybits))
      return false; 
   encryptor = *( dynamic_cast<RSAPublicKeyEncryption *> (pub) ) ; 
   decryptor = *( dynamic_cast<RSAPrivateKeyEncryption *> (priv) ) ;   
   delete pub; 
   delete priv;
   Init(cfgfile, true) ; 
   return true; 
}


bool Self::GetAuthenticators(const peerid_t& peer, group_t & authenticators)
{
   return proofs.getAuthenticators(peer, pid, authenticators);
}  

