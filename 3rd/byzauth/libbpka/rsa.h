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

#ifndef __RSAFACTORY_H__
#define __RSAFACTORY_H__


#include <string>
#include "defines.h"
#include "bignum.h"
#include "digest.h"
#include "publickeyencryption.h"
#include "privatekeyencryption.h"



class RSAPublicKeyEncryption : public PublicKeyEncryption
{
   UBigNum  modulus;
   UBigNum  exponent; 
   epoch_t  since_time; 
   epoch_t  until_time; 

   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);

public:   
   virtual PublicKeyEncryption * Clone(); 
   virtual bool   Encrypt  (std::string& , const std::string& indata); 
   virtual bool   Encrypt  (UBigNum &out, const UBigNum &in);
   virtual bool   Modulus  (UBigNum & modulus); 
   void digest(Digest& d) const;
   friend class RSACore; 
   virtual ~RSAPublicKeyEncryption();
};

BOOST_CLASS_EXPORT_KEY(RSAPublicKeyEncryption)



class RSAPrivateKeyEncryption : public PrivateKeyEncryption
{
   UBigNum  modulus;
   UBigNum  exponent; 

   friend class boost::serialization::access;
   template<class Archive> void serialize(Archive & ar, const unsigned int version);

  public:     
   virtual PrivateKeyEncryption * Clone();
   virtual bool   Decrypt  (std::string& , const std::string& ciphertext);
   virtual bool   Decrypt  (UBigNum &out, const UBigNum &in); 
   virtual bool   Modulus  (UBigNum & modulus); 
   friend class RSACore; 
   virtual ~RSAPrivateKeyEncryption();
};

BOOST_CLASS_EXPORT_KEY(RSAPrivateKeyEncryption)






class RSACore  
{

public:
   static bool    transform(std::string &r, 
                            const UBigNum& e, 
                            const UBigNum& n,   
                            const std::string& s);
 
   static bool    createkeypair(PublicKeyEncryption*& public_key, 
                                PrivateKeyEncryption*& private_key, 
                                int keybits);

}; 










 
template<class Archive> 
inline void RSAPublicKeyEncryption::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PublicKeyEncryption);
   ar & BOOST_SERIALIZATION_NVP(modulus); 
   ar & BOOST_SERIALIZATION_NVP(exponent); 
}



 
template<class Archive> 
inline void RSAPrivateKeyEncryption::serialize(Archive & ar, const unsigned int version)
{
   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PrivateKeyEncryption);
   ar & BOOST_SERIALIZATION_NVP(modulus); 
   ar & BOOST_SERIALIZATION_NVP(exponent); 
}


#endif // __RSAFACTORY_H__

