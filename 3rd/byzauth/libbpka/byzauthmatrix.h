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

#ifndef __BYZAUTHMATRIX_H__
#define __BYZAUTHMATRIX_H__

#include <string>
#include "proof.h" 
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>





     /**
      * Byzauth matrix stores the proofs from all the peers and computes the 
      * result of byzantine agreement.  This object is created at stage 2 of the 
      * byzantine authentication phase.  Note that this stage happens to the entire 
      * trust group.  Therefore at most one of these should be active at any given 
      * point of time
      */

class ByzAuthMatrix 
{
   peerid_t                         probationary; 
   std::map<peerid_t,int>           trusted;
   std::vector<std::vector<Proof> > proofs; 
   epoch_t                          start_time;
   static epoch_t                   max_time; 

   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);


  public:
   static void time_out (int seconds); 
   bool     init        (const group_t &_trusted, const std::string & _probationary);
   void     clear       ();
   bool     insert      (const peerid_t& challenger, const peerid_t& observer, const Proof&); 
   bool     agreement   (group_t & trust, group_t & untrust, group_t & prob, KeyRepository& ) ; 
   bool     operator !  ();
   bool     isRecent    ();
   bool     gotEnough   ();
}; 







template<class Archive> 
inline void  ByzAuthMatrix::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(probationary); 
   ar & BOOST_SERIALIZATION_NVP(trusted);
   ar & BOOST_SERIALIZATION_NVP(proofs);
   ar & BOOST_SERIALIZATION_NVP(start_time);
}




#endif
