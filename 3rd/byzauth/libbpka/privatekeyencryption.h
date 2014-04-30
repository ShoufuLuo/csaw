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

#ifndef __PRIVATEKEYENCRYPTION_H__
#define __PRIVATEKEYENCRYPTION_H__

#include <string>
#include "encryption.h"


/**
 * Class PrivateKeyEncryption
 * Implements decryption by private key  
 */

class PrivateKeyEncryption : public Encryption 
{
  public:
   virtual PrivateKeyEncryption * Clone() = 0;
   /**
    * 
    * @param indata 
    * Encrypt the text and return cipher text.  Possibly throw exception if there 
    * is a problem with encrypting the data eg: trying to decrypt with private key 
    */
   virtual bool Encrypt (std::string &, const std::string& indata)
   {
      throw 0; 
   }
   virtual bool   Encrypt  (UBigNum &out, const UBigNum &in)
   {
      throw 0; 
   }
      
   
   /**
    * 
    * @param ciphertext 
    * Inverse of encrypt.  Takes in cipher text and returns the text.  If any problem 
    * (eg: not initialized etc) then throw an exception 
    * 
    */
   virtual bool   Decrypt  (std::string &, const std::string& ciphertext) = 0;
   virtual bool   Decrypt  (UBigNum &out, const UBigNum &in) = 0; 


   virtual ~PrivateKeyEncryption() {}  
};



#endif //__PRIVATEKEYENCRYPTION_H__

