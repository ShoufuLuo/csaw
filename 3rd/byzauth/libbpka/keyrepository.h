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

#ifndef __KEYREPOSITORY_H__
#define __KEYREPOSITORY_H__



#include "rsa.h"
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp> 
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>



class KeyInfo 
{
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version); 
  public:

      KeyInfo() : ep(0), since_time(0), until_time(0), group_migrations(0), trust_level(-1) 
      {} 

      PublicKeyEncryption *      ep; 
      std::string                peer_name; 
      unsigned long long         since_time; 
      unsigned long long         until_time; 
      unsigned long long         group_migrations; 
      float                      trust_level;    
}; 



template<class Archive>
inline void KeyInfo::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(ep); 
   ar & BOOST_SERIALIZATION_NVP(peer_name); 
   ar & BOOST_SERIALIZATION_NVP(since_time); 
   ar & BOOST_SERIALIZATION_NVP(until_time); 
   ar & BOOST_SERIALIZATION_NVP(group_migrations); 
   ar & BOOST_SERIALIZATION_NVP(trust_level);
}



class Proof ;


class KeyRepository 
{
   std::map<std::string, KeyInfo>   curr_keys; 
   std::list<KeyInfo>               old_keys;

   friend class boost::serialization::access;
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version); 

  public: 

   bool                    find     (const std::string& peer, KeyInfo & out);
   bool                    add      (PublicKeyEncryption * ep, const std::string & name, 
                                     unsigned long long since_time, unsigned long long until_time) ; 
   bool                    save     (const std::string& file);
   bool                    restore  (const std::string& file); 
   void                    clear    ();
   bool                    isValid  (Proof &pf, bool& pi, bool& ai, bool& ki); 
   bool                    debug    () ;    
   bool                    migrate  (const std::string& peer, epoch_t timeinterval); 
};





template<class Archive>
inline void KeyRepository::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(curr_keys);
   ar & BOOST_SERIALIZATION_NVP(old_keys); 
}

 

#endif //KEYREPOSITORY_H

