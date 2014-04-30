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

#ifndef __PROOF_REPOSITORY_H__
#define __PROOF_REPOSITORY_H__ 

#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "proof.h" 
#include <boost/serialization/map.hpp>

struct ProofInfo 
{
   std::string    challenger; 
   std::string    responder;
   std::string    observer; 
   template<class Archive> void serialize(Archive & ar, const unsigned int version);
   bool operator <(const ProofInfo& c) const;
};





class ProofRepository
{
   std::map<ProofInfo, Proof>    proofs; 
   std::map<std::string, Proof>  challenges; 
   std::map<std::string, Proof>  responses; 

   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);

  public:
   bool  save           (const std::string& file);
   bool  restore        (const std::string& file);
   void  clear          ();

   bool  getProof       (Proof &, const ProofInfo&);
   void  putProof       (const Proof& ); 

   bool  getChallenge   (Proof &, const std::string& responder); 
   void  putChallenge   (const Proof &);

   bool  getResponse    (Proof &, const std::string& challenger);
   void  putResponse    (const Proof &);

   bool  getAuthenticators(const peerid_t& peer, const peerid_t& self, group_t & authenticators); 
};






 
template<class Archive> 
inline void ProofInfo::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(challenger); 
   ar & BOOST_SERIALIZATION_NVP(responder);
   ar & BOOST_SERIALIZATION_NVP(observer); 
}

 
template<class Archive> 
inline void ProofRepository::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(proofs);
   ar & BOOST_SERIALIZATION_NVP(challenges);
   ar & BOOST_SERIALIZATION_NVP(responses);
}

#endif
