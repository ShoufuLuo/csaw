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
#include "proofrepository.h" 



bool ProofInfo::operator <(const ProofInfo& c) const
{
   const ProofInfo& b = *this; 
   if( b.challenger < c.challenger ) 
      return true; 
   if( c.challenger < b.challenger ) 
      return false;
   if( b.responder < c.responder )
      return true; 
   if( c.responder < b.responder )
      return false;
   if( b.observer < c.observer )
      return true; 
   if( c.observer < b.observer )
      return false;
   return false; 
}




bool ProofRepository::save(const std::string& filename)
{
   std::ofstream ofs(filename.c_str());
   if(!ofs.good())
      return false; 

   boost::archive::xml_oarchive oa(ofs);
   const ProofRepository & repository = *this; 
   oa << BOOST_SERIALIZATION_NVP(repository);
   return true; 
}




bool ProofRepository::restore(const std::string& filename)
{
   std::ifstream ifs(filename.c_str());
   if(!ifs.good())
      return false ;

   clear();

   boost::archive::xml_iarchive ia(ifs);
   ProofRepository & repository = *this; 
   ia >> BOOST_SERIALIZATION_NVP(repository); 
   return true; 
}



void ProofRepository::clear() 
{
   proofs.clear(); 
   challenges.clear();
   responses.clear();
}




bool ProofRepository::getProof(Proof & p, const ProofInfo& pi)
{
   if( proofs.find(pi) != proofs.end() )
   {
      p = proofs[pi];
      return true; 
   }
   return false; 
}




void ProofRepository::putProof(const Proof & p)
{

   // Need to log the receipt and sent of proofs 
   // perhaps along with details of challenge and 
   // response numbers
   // note that the execution reaches here. 

   ProofInfo pi;
   pi.challenger = p.challenger; 
   pi.responder = p.responder; 
   pi.observer = p.observer; 

#ifdef DEBUG 
#ifndef DRYRUN 
   if( proofs.find(pi) != proofs.end() )
      std::cout << "already existing proof found " << std::endl; 
        // does it reach here??? 
#endif 
#endif 

   proofs[pi] = p; 
}


bool ProofRepository::getChallenge(Proof &p, const std::string& responder)
{
   if( challenges.find(responder) == challenges.end() )
      return false;
   p = challenges[responder];
   return true; 
}



void ProofRepository::putChallenge(const Proof &p)
{
   challenges[p.responder] = p; 
}



bool ProofRepository::getResponse(Proof &p, const std::string& challenger)
{
   if( responses.find(challenger) == responses.end() ) 
      return false; 
   p = responses[challenger];
   return true; 
}



void ProofRepository::putResponse(const Proof &p)
{
   responses[p.challenger] = p; 
}



bool ProofRepository::getAuthenticators(const peerid_t& peer, const peerid_t& self, group_t & authenticators)
{
   authenticators.clear(); 
   for( std::map<ProofInfo, Proof>::iterator i = proofs.begin() ; i!=proofs.end() ; i++ ) 
      if( i->first.responder == peer && i->first.observer == self ) 
         authenticators[i->first.challenger] = i->second.response.timestamp ; 

   return authenticators.size() != 0; 
}
