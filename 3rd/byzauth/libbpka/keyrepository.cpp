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

#include <fstream>
#include <cmath>
#include "keyrepository.h" 
#include "proof.h"




bool KeyRepository::find(const std::string& peer, KeyInfo & out)
{
#ifdef DEBUG 
   for( std::map<std::string, KeyInfo>::iterator i = curr_keys.begin(); i != curr_keys.end(); i++ ) 
   {
      KeyInfo info = i->second; 
      assert( info.until_time > 0 ) ; 
   }
#endif
   std::map<std::string, KeyInfo>::iterator pos = curr_keys.find(peer); 
   if( pos == curr_keys.end() ) 
      return false;
   else
   {
      out = pos->second;
      return true; 
   }
}




bool  KeyRepository::migrate(const std::string& peer, epoch_t deltat)
{
   std::map<std::string, KeyInfo>::iterator pos = curr_keys.find(peer); 
   if( pos == curr_keys.end() ) 
      return false;
   else
   {
      pos->second.group_migrations++;  
      if( deltat > 0 ) 
         pos->second.trust_level += log(deltat); 
      return true; 
   }
}



bool KeyRepository::add(PublicKeyEncryption * ep, 
                        const std::string & peer,
                        unsigned long long since_time, 
                        unsigned long long until_time
   )
{
   KeyInfo ki; 
   ki.ep = ep; 
   ki.peer_name = peer;    
   ki.since_time = since_time; 
   ki.until_time = until_time; 
   ki.group_migrations = 0; 
   ki.trust_level = 0; 


//   std::cout << "peer = " << peer << std::endl ; 
//   boost::archive::xml_oarchive oa(std::cout); 
//   oa << BOOST_SERIALIZATION_NVP(ep); 
   

   std::map<std::string, KeyInfo>::iterator pos = curr_keys.find(peer);
   if( pos != curr_keys.end() )
   {
      ki.group_migrations = curr_keys[peer].group_migrations + 1; 
      ki.trust_level = ki.group_migrations; 
      old_keys.push_front(curr_keys[peer]) ; 
   }

   curr_keys[peer] = ki ; 

#ifdef DEBUG 
   KeyInfo ki2; 
   return find(peer, ki2) && ki2.peer_name == peer ; 
#else
   return true; 
#endif 
}




bool KeyRepository::save(const std::string& filename) 
{
   std::ofstream ofs(filename.c_str());
   if(!ofs.good())
      return false; 

   boost::archive::xml_oarchive oa(ofs);
   oa << BOOST_SERIALIZATION_NVP(curr_keys);
   oa << BOOST_SERIALIZATION_NVP(old_keys); 
   return true; 
}



bool KeyRepository::restore(const std::string& filename)
{
   std::ifstream ifs(filename.c_str());
   if(!ifs.good())
      return false ;

   clear();

   boost::archive::xml_iarchive ia(ifs);
   ia >> BOOST_SERIALIZATION_NVP(curr_keys);
   ia >> BOOST_SERIALIZATION_NVP(old_keys); 
   return true; 
}



void KeyRepository::clear() 
{
   for( std::map<std::string, KeyInfo>::iterator i = curr_keys.begin(); i != curr_keys.end(); i++ ) 
      if( i->second.ep ) 
         delete i->second.ep ; 

   curr_keys.clear(); 
}



     /**
      * Let a proof of possession be  $P$-invalid
      * if the challenge is not properly signed, $A$-invalid if the response is not
      * property signed, $K$-invalid if $c_i \ne K_A(r_i)$ and faulty if it is valid
      * but $K_A$ is not owned by $A$.
      */

bool KeyRepository::isValid(Proof &p, bool& pi, bool& ai, bool & ki)
{
   pi = ai = ki = false; 

   KeyInfo ch; 
   if(!find(p.challenger, ch))
      return false; 

   if(!p.challenge.verify(*ch.ep))
   {
      pi = true; 
      return false; 
   }

   KeyInfo re; 
   if(!find(p.responder, re))
      return false; 

   if(!p.response.verify(*re.ep))
   {
      ai = true; 
      return false; 
   }

#ifdef DRYRUN 
   return true; 
#endif

   UBigNum c2; 
   if(!re.ep->Encrypt(c2, p.response.response))
      return false ;

   if( p.challenge.challenge != c2 ) 
   {
      ki = true; 
      return false; 
   }

        // passed all the tests
        // now it can only be faulty or genuine 
   return true; 
} 



bool KeyRepository::debug() 
{
   std::string null("/dev/null"); 
   return this->save(null); 
}

