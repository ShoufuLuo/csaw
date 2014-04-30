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

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "defines.h" 
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include "bignum.h" 
#include "rsa.h" 



struct Message 
{
   std::string          from;
   std::string          to;
   std::string          messagetype;
#if 0
   RSAPublicKeyEncryption commonpubkey; 
#endif 
   epoch_t              timestamp;  // local at sender 
   epoch_t              expiration;
   unsigned long        causalid;
   UBigNum              signature; 

   Message() ;
   virtual ~Message()   {;} 

   virtual void   sign    (PrivateKeyEncryption &);   
   virtual bool   verify  (PublicKeyEncryption &);   
   void           setcause(const Message & cause);
      
      private:
   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);
};


BOOST_CLASS_EXPORT_KEY(Message)

 
template<class Archive> 
inline void Message::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_NVP(from); 
   ar & BOOST_SERIALIZATION_NVP(to);
   ar & BOOST_SERIALIZATION_NVP(messagetype);
#if 0
   ar & BOOST_SERIALIZATION_NVP(commonpubkey);    
#endif 
   ar & BOOST_SERIALIZATION_NVP(timestamp);   
   ar & BOOST_SERIALIZATION_NVP(expiration); 
   ar & BOOST_SERIALIZATION_NVP(causalid); 
   ar & BOOST_SERIALIZATION_NVP(signature); 
}





#endif //__MESSAGE_H__

