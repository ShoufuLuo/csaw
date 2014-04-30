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

#ifndef __BIG_NUM_H__ 
#define __BIG_NUM_H__ 

#include <iostream>
#include <sstream>
#include <string> 
#include <deque>
#include <map>
#include <boost/config.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>



typedef unsigned long dig_t; 
class UBigNum; 


std::ostream & operator << (std::ostream& stream, const UBigNum & n); 
std::istream & operator >> (std::istream& stream, UBigNum & n); 
UBigNum operator *   (const UBigNum& a, const UBigNum& b); 
UBigNum operator +   (const UBigNum& a, const UBigNum& b);    
UBigNum operator -   (const UBigNum& a, const UBigNum& b); 
UBigNum operator /   (const UBigNum& a, const UBigNum& b); 
UBigNum operator %   (const UBigNum& a, const UBigNum& b);
UBigNum exp          (const UBigNum& a, const UBigNum& b, const UBigNum &n);    
UBigNum gcd          (const UBigNum& a, const UBigNum& b);
bool    inv          (const UBigNum& a, const UBigNum& n, UBigNum &); 
UBigNum prime        (int bits, int trials = 8); 



class UBigNum 
{
   std::deque<dig_t>    number; 
   mutable std::string  hex;

   const static dig_t   DIG_BASE; 
   const static int     DIG_MASK;
   const static char    DIG_SHIFT; 
   static char          randombits [256]; 
   static bool          initialized; 
   static const char    base64_value[]; 
   static std::map<char,int> base64_inverse; 

  public:
   
        // performance improvement by explicitly having
        // empty constructor for 0 case 
   inline UBigNum() {;}   
   UBigNum(const unsigned long long n);
   UBigNum(const UBigNum& c); 



   const UBigNum& operator =  (const UBigNum& c) ; 
   bool           operator <  (const UBigNum& c) const; 
   bool           operator == (const UBigNum& c) const;
   bool           operator >  (const UBigNum& c) const;   
   bool           operator != (const UBigNum& c) const;
   bool           operator !  () const ; 

   template<class Archive> void save(Archive & ar, const unsigned int version) const 
   {
      std::ostringstream outs; 
      outs << (*this); 
      hex = outs.str(); 
      ar << BOOST_SERIALIZATION_NVP(hex); 
   }

   template<class Archive> void load(Archive & ar, const unsigned int version) 
   {
      ar >> BOOST_SERIALIZATION_NVP(hex); 
      std::istringstream ins;
      ins.str(hex); 
      ins >> (*this); 
   }

   BOOST_SERIALIZATION_SPLIT_MEMBER()


   void        random   (int bits); 
   std::string print    (int base) const;
   void        assign   (unsigned long long n);    
   void        clear    ();
   static void divide   (const UBigNum& a, const UBigNum& b, UBigNum& q, UBigNum& r); 
   dig_t       toi      (unsigned index = 0) const; 
   void        debug    () const; 

  private: 
   void        trim     (); 

   static void divide_by_trial_error
      (const UBigNum& a, const UBigNum& b, dig_t & q, UBigNum& r) ;
   friend UBigNum operator *  (const UBigNum& a, const UBigNum& b); 
   friend UBigNum operator +  (const UBigNum& a, const UBigNum& b);    
   friend UBigNum operator -  (const UBigNum& a, const UBigNum& b); 
   friend UBigNum operator /  (const UBigNum& a, const UBigNum& b); 
   friend UBigNum operator %  (const UBigNum& a, const UBigNum& b); 
   friend UBigNum exp         (const UBigNum& a, const UBigNum& b, const UBigNum &n); 
   friend bool    inv         (const UBigNum& a, const UBigNum& n, UBigNum&);
   static UBigNum euclid      (const UBigNum& a, const UBigNum& b, UBigNum &x, UBigNum &y, bool &xb, bool &yb, bool do_check = false); 
   static void    check_euclid(const UBigNum& d, 
                               const UBigNum& a, 
                               const UBigNum& b, 
                               const UBigNum& x, 
                               const UBigNum& y, 
                               bool xb, 
                               bool yb);
   static bool    witness     (const UBigNum & a, const UBigNum & n);
   friend UBigNum prime        (int bits, int trials); 
   friend std::ostream & operator << (std::ostream& stream, const UBigNum & n); 
   friend std::istream & operator >> (std::istream& stream, UBigNum & n); 

};








#endif 


            
