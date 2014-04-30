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

#include "rsa.h"
#include <iostream>




#if 0
// #include "chunkifier.h" 

// bool RSACore::transform(std::string &r, const UBigNum& e, const UBigNum& n, const std::string& s)
// {
//    std::vector<UBigNum> result; 
//    std::vector<UBigNum> chunks; 
//    Chunkifier ch; 
//    if(!ch.init(n))
//       return false; 

//    if(!ch.chunkify(s, chunks))
//       return false; 

//    for(std::vector<UBigNum>::iterator i = chunks.begin(); i != chunks.end(); i++ ) 
//    {
//       UBigNum c = exp(*i, e, n) ; 
//       result.push_back(c);
//    }   

//    std::string resultstr; 
//    if(!ch.dechunkify(result, r))
//       return false; 

//    ch.deinit(); 
//    return true; 
// }

#else 

bool RSACore::transform(std::string &r, const UBigNum& e, const UBigNum& n, const std::string& s){return false;}

#endif



bool RSAPublicKeyEncryption::Modulus  (UBigNum & _modulus)
{
   _modulus = modulus; 
   return !!modulus; 
}



bool RSAPublicKeyEncryption::Encrypt(UBigNum &out, const UBigNum &in)
{
   assert( in < modulus ) ; 
   out = exp(in, exponent, modulus); 
   return true; 
}



bool RSAPublicKeyEncryption::Encrypt(std::string &r, const std::string& indata)
{
   return RSACore::transform(r, exponent, modulus, indata); 
} 




bool RSAPrivateKeyEncryption::Modulus  (UBigNum & _modulus)
{
   _modulus = modulus; 
   return !!modulus; 
}



bool RSAPrivateKeyEncryption::Decrypt(UBigNum &out, const UBigNum &in)
{
   assert( in < modulus ) ; 
   out = exp(in, exponent, modulus); 
   return true; 
}



bool RSAPrivateKeyEncryption::Decrypt(std::string &r, const std::string& indata)
{
   return RSACore::transform(r, exponent, modulus, indata); 
}











bool RSACore::createkeypair(PublicKeyEncryption *& public_key, 
                               PrivateKeyEncryption  *& private_key, 
                               int keybits) 
{
   assert( !public_key && !private_key ) ; 
   RSAPublicKeyEncryption * pubkey = new RSAPublicKeyEncryption;
   RSAPrivateKeyEncryption * privkey = new RSAPrivateKeyEncryption;

   UBigNum p = prime(keybits/2);
   UBigNum q = prime(keybits/2); 
   UBigNum n = p * q; 
   UBigNum m = (p-1) * (q-1); 
   UBigNum e; 

   while(true) 
   {
      e.random(keybits/2); 
      if( e > m || e == m )
         continue; 
      UBigNum g = gcd(m,e);
      if( g == 1 )
         break; 
   }

   UBigNum d;
   if(!inv(e,m,d))
      return false; 

   pubkey->modulus = privkey->modulus = n ; 
   pubkey->exponent = e;
   privkey->exponent = d; 
   public_key = pubkey; 
   private_key = privkey; 
   return true;
}




void RSAPublicKeyEncryption::digest(Digest& d) const
{
   d | modulus; 
   d | exponent; 
}

     
RSAPublicKeyEncryption::~RSAPublicKeyEncryption()
{
   assert(this); 
}



RSAPrivateKeyEncryption::~RSAPrivateKeyEncryption()
{
   assert(this); 
}


PublicKeyEncryption * RSAPublicKeyEncryption::Clone()
{
   return new RSAPublicKeyEncryption(*this); 
}




PrivateKeyEncryption * RSAPrivateKeyEncryption::Clone()
{
   return new RSAPrivateKeyEncryption(*this); 
}
