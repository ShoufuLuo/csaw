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

#ifndef __DIGEST_H__
#define __DIGEST_H__ 

#include <stdlib.h>
#include <openssl/md5.h>
#include "bignum.h" 


class Digest 
{
   unsigned char  d[MD5_DIGEST_LENGTH];
   MD5_CTX        context;

   bool trimSignature  (std::string & out, const std::string & in) ; 

  public:
   Digest      () {Clear();} 

   void        Clear    ();
   void        getStr   (const char *p, int length); 
   UBigNum     operator () ();

   template<class M>
   Digest & operator | (const M& m);

};





template<class M>
inline Digest & Digest::operator | (const M& m)
{
   std::ostringstream outs;
   boost::archive::xml_oarchive oa(outs); 
   const M* pm = &m; 
   oa << BOOST_SERIALIZATION_NVP(pm);
   std::string t; 
   trimSignature( t, outs.str() ) ; 
   ::MD5_Update(&context, t.c_str(), t.length() ); 
   return *this;
}

#endif 
