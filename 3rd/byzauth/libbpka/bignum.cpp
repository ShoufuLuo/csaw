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

#include "bignum.h" 
#include <sstream>
#include <iostream>
#include <cassert>   
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>

using namespace std; 

#define QUICK_MODE_DIV
#ifdef __LP64__
#define _64_BIT_
#endif


#ifndef QUICK_MODE_DIV
const dig_t UBigNum::DIG_BASE = 11 ;
const int UBigNum::DIG_MASK = 0;
const char UBigNum::DIG_SHIFT = 0;
#define REM(x) (x%(UBigNum::DIG_BASE)) 
#define DIV(x) (x/(UBigNum::DIG_BASE))
#else
#  ifdef _64_BIT_
const dig_t UBigNum::DIG_BASE = (1+0x3fffffff) ;
const int UBigNum::DIG_MASK = 0x3fffffff;
const char UBigNum::DIG_SHIFT = 30; 
#  else     
const dig_t UBigNum::DIG_BASE = (1+0xffff) ;
const int UBigNum::DIG_MASK = 0xffff;
const char UBigNum::DIG_SHIFT = 16; 
#  endif
#define REM(x) (x&(UBigNum::DIG_MASK)) 
#define DIV(x) (x>>(UBigNum::DIG_SHIFT)) 
#endif



char UBigNum::randombits [256] = {0}; 
bool UBigNum::initialized = false; 






UBigNum::UBigNum(const unsigned long long n)  
{
   if(!initialized)
   {
      initialized = true;

#ifdef __CYGWIN__
      // cygwin doesnt seem to support initstate
      // just do a flat rand copy into the random state
      // to question is there is a better way to do it
      // i.e. internet randomness generator 
#elif defined(_DEBUG) 
      initstate( 1456167, randombits, 256 ) ; 
#else 
      int fd = open( "/dev/urandom" , O_RDONLY ) ; 
      assert( fd != -1) ; 
      if( 256 != read( fd, randombits, 256 ) )
      {
         cerr << "Cannot read random device" << endl; 
         abort();
      }
      close(fd);
      initstate( getpid() , randombits, 256 ) ; 
#endif 
   }
   assign(n); 
}




UBigNum::UBigNum(const UBigNum& c)
{
   number.clear(); 
   for( deque<dig_t>::const_iterator i = c.number.begin(); i != c.number.end(); i++ ) 
   {
      number.push_back(*i); 
   }
}




const UBigNum& UBigNum::operator = (const UBigNum& c) 
{
   number.clear(); 
   for( deque<dig_t>::const_iterator i = c.number.begin(); i != c.number.end(); i++ ) 
   {
      number.push_back(*i); 
   }
   return *this; 
}




bool UBigNum::operator != (const UBigNum& c) const
{
   return !( (*this) == c ) ; 
}



bool UBigNum::operator == (const UBigNum& c) const
{
   deque<dig_t>::const_reverse_iterator l = number.rbegin(), r = c.number.rbegin(); 
   while(l != number.rend() && r != c.number.rend())
      if( *l++ != *r++ ) 
         return false;

   if( l != number.rend() || r != c.number.rend())
      return false; 

   return true; 
}





bool  UBigNum::operator < (const UBigNum& c) const
{
   int lsize = number.size();
   int rsize = c.number.size(); 
   if( lsize < rsize ) 
      return true; 
   else if (rsize < lsize) 
      return false; 
   else
   {
      deque<dig_t>::const_iterator l = number.begin(), r = c.number.begin(); 
      while(l != number.end())
      {
         if( *l < *r )
            return true; 
         else if( *l > *r ) 
            return false; 
         l++;
         r++;
      }
      return false; 
   }
}  






bool  UBigNum::operator > (const UBigNum& c) const
{
   int lsize = number.size();
   int rsize = c.number.size(); 
   if( lsize < rsize ) 
      return false ; 
   else if (rsize < lsize) 
      return true; 
   else
   {
      deque<dig_t>::const_iterator l = number.begin(), r = c.number.begin(); 
      while(l != number.end())
      {
         if( *l < *r )
            return false; 
         else if( *l > *r ) 
            return true; 
         l++;
         r++;
      }
      return false; 
   }
}






bool UBigNum::operator ! () const
{
   return number.empty(); 
}






UBigNum operator *  (const UBigNum& a, const UBigNum& b) 
{
   int left_shift_count = 0; 
   UBigNum c; 
   for( deque<dig_t>::const_reverse_iterator i = a.number.rbegin(); i != a.number.rend(); i++ )
   {
      UBigNum d; 
      dig_t carry = 0; 
      for(deque<dig_t>::const_reverse_iterator j = b.number.rbegin(); j != b.number.rend(); j++ )
      {
         unsigned long long prod = *i * *j + carry ; 
         carry = DIV(prod);  
         d.number.push_front(REM(prod)); 
      }
      if(carry) 
         d.number.push_front(carry); 

      for( int k = 0; k < left_shift_count; k++ )
         d.number.push_back(0);
      
      c = c + d; 
      left_shift_count++; 
   } 
   return c; 
}





UBigNum operator + (const UBigNum& a, const UBigNum& b)
{
   if(!a) 
      return b;
   else if(!b) 
      return a; 

   UBigNum c; 
   deque<dig_t>::const_reverse_iterator i = a.number.rbegin(); 
   deque<dig_t>::const_reverse_iterator j = b.number.rbegin();
   dig_t carry = 0; 
   do  
   {
      unsigned long long sum = carry + 
         (i == a.number.rend() ? 0 : *i++) + 
         (j == b.number.rend() ? 0 : *j++); 

      c.number.push_front(REM(sum)); 
      carry = DIV(sum);
   } while( i != a.number.rend() || j != b.number.rend() ); 

   if(carry) 
      c.number.push_front(REM(carry)); 
   assert( !(DIV(carry)) ) ; 

   return c; 
}




void UBigNum::trim()
{
   while(!number.empty() && *number.begin() == 0)
      number.pop_front();   
}


 


UBigNum operator - (const UBigNum& a, const UBigNum& b)
{
   if( a < b ) 
   {
      a.debug(); 
      b.debug(); 
      assert(0);
   }
   
   else if( a == b ) 
      return UBigNum(0); 

   else if( !b ) 
      return a; 


   UBigNum d; 
   UBigNum atemp = a; 

   deque<dig_t>::reverse_iterator i = atemp.number.rbegin(); 
   deque<dig_t>::const_reverse_iterator j = b.number.rbegin();
   do  
   {
      unsigned long long totala = 0; 
      unsigned long long totalb = 0; 

      if( j != b.number.rend() && *i < *j )
      {
         deque<dig_t>::reverse_iterator k, l; 

         k = l = i; 
         do 
         {
            k++ ; 
         } while( *k == 0 ); 

         *k -= 1; 
         
         for( l++ ; l != k ; l++ )
            *l += UBigNum::DIG_BASE - 1;

         totala += UBigNum::DIG_BASE;          
      }

      totala += *i++ ;

      if( j != b.number.rend() ) 
         totalb = *j++ ; 

      d.number.push_front(totala - totalb);

   } while( i != atemp.number.rend() ) ; 

   d.trim(); 
   return d; 
}






UBigNum operator / (const UBigNum &a, const UBigNum& b)
{
   UBigNum r, q; 
   UBigNum::divide(a, b, q, r); 
   return q; 
}





UBigNum operator % (const UBigNum& a, const UBigNum& b)
{
   UBigNum r, q; 
   UBigNum::divide(a, b, q, r); 
   return r; 
}




void UBigNum::assign(unsigned long long n) 
{
   number.clear(); 
   for( int i = 0; n; i++ ) 
   {
      number.push_front(REM(n)); 
      n = DIV(n); 
   }
}




dig_t UBigNum::toi(unsigned index) const
{
#ifdef _DEBUG
   assert( (number.empty() && !index) || index < number.size() ) ; 
#endif
   return number.empty() ? 0 : number[index]; 
}



std::string UBigNum::print(int base) const 
{
   assert( base <= 36 ); 
   std::string result; 
   UBigNum n(*this); 
   for(; n > 0; ) 
   {
      UBigNum div, rem; 
      divide(n, base, div, rem); 
      int digit = rem.toi(); 
      if( digit > 9 ) 
         result.push_back('a' + rem.toi()) ; 
      else
         result.push_back('0' + rem.toi()) ; 
      n = div; 
   }
   reverse(result.begin(), result.end());
   return result; 
}





void UBigNum::clear()
{
   number.clear(); 
}






void UBigNum::debug() const
{
   if( DIG_BASE > 10 )
   {
      cout << print(10) << endl ; 
      return; 
   }

   for( deque<dig_t>::const_iterator i = number.begin(); i != number.end(); i++ ) 
      cout << *i ; 
   cout << endl ; 
}





void UBigNum::divide(const UBigNum& a, const UBigNum& b, UBigNum& q, UBigNum& r) 
{
   assert(!!b); 

   q.clear() ; 
   r.clear() ; 
   
   if( a < b ) 
   {
      r = a; 
      q = 0; 
      return; 
   }

   UBigNum candidate; 
   deque<dig_t>::const_iterator i = a.number.begin();
   while( i != a.number.end() && candidate < b ) 
   {
      candidate.number.push_back(*i++);
      candidate.trim(); 
      dig_t divisor; 
      UBigNum remainder; 
      divide_by_trial_error(candidate, b, divisor, remainder); 
      q.number.push_back(divisor);
      candidate = remainder; 
   }

   q.trim(); 
   assert( r < b ) ; 
   r = candidate; 
   return; 
}






void UBigNum::divide_by_trial_error(const UBigNum& a, const UBigNum& b, dig_t & q, UBigNum& r) 
{
   if( a < b ) 
   {
      q = 0; 
      r = a; 
      return; 
   }
   else if( a == b ) 
   {
      q = 1; 
      r = 0; 
      return;
   }

   unsigned long long all = a.number[0] & (UBigNum::DIG_MASK); 
   unsigned long long bll = b.number[0] & (UBigNum::DIG_MASK); 
   if( a.number.size() != b.number.size() )
   {
      all <<= DIG_SHIFT; 
      all += a.number[1] & (UBigNum::DIG_MASK); 
   }

   dig_t left = (all-1)/(bll+1);
   dig_t right = (all+1)/(bll > 1 ? (bll-1) : bll); 
   dig_t mid; 
   while( left <= right ) 
   {
      assert( a > b ); 
      assert( left < DIG_BASE ); 
      mid = (left + right) / 2; 
      UBigNum prod(b * mid);

      if( prod > a ) 
         right = mid;


      else if( (r = (a - prod)) > b || r == b )
         left = mid + 1; 

      else 
      {
         q = mid; 
         return; 
      }
   }
   assert(0);
}




UBigNum exp(const UBigNum& a, const UBigNum& b, const UBigNum &n)
{
   UBigNum result(1); 
   UBigNum temp = a;
   for( std::deque<dig_t>::const_reverse_iterator i = b.number.rbegin(); 
        i != b.number.rend(); i++ ) 
   {
      dig_t bitmask = 1; 
      for( int j = 0; j < UBigNum::DIG_SHIFT; j++ )
      { 
         if( bitmask & *i ) 
            result = result * temp; 
         temp = temp * temp; 
         bitmask <<= 1; 
         temp = temp % n; 
         result = result % n; 
      }
   }
   return result; 
}





UBigNum gcd (const UBigNum& a, const UBigNum& b)
{
   if( a == 0 )
      return b; 
   if( b == 0 )
      return a;
   return gcd( b, a % b ); 
}




bool inv(const UBigNum& a, const UBigNum& n, UBigNum &inverse)
{  
   bool xb, yb; 
   UBigNum y; 
   if( UBigNum::euclid(a, n, inverse, y, xb, yb, true) == 1)
   {
      if(!xb) 
         inverse = n - inverse; 
      return true; 
   }
   return false; 
}




void UBigNum::random(int bits) 
{
   bool rem = bits % DIG_SHIFT; 
   bits /= DIG_SHIFT;
   if( rem ) 
      bits++; 
   
   number.clear(); 
   dig_t carry = 0;
   while(bits > 0 )
   {
      dig_t digit = carry + ::random(); 
      number.push_back( REM(digit) ) ;
      carry = DIV(digit);
      bits -= DIG_SHIFT; 
   } 
}












void UBigNum::check_euclid(const UBigNum& d, 
                           const UBigNum& a, 
                           const UBigNum& b, 
                           const UBigNum& x, 
                           const UBigNum& y, 
                           bool xb, 
                           bool yb)
{  
   UBigNum p; 
   if( xb == true && yb == false )
      assert( d == (p = (a*x - b*y)) );

   else if( xb == true && yb == true )
      assert( d == (p = (a*x + b*y)) );

   else if( xb == false && yb == true ) 
      assert( d == (p = (b*y - a*x)) );

   else if( xb == false && yb == false ) 
      assert(0);
}




UBigNum UBigNum::euclid(const UBigNum& a, const UBigNum& b, UBigNum &x, UBigNum & y, bool &xb, bool &yb, bool check)
{
   if( b == 0 )
   {
      x = 1; 
      y = 0;
      xb = true; 
      yb = true; 
      return a;
   } 

   UBigNum divisor, remainder; 
   UBigNum::divide( a, b, divisor, remainder); 
   
   UBigNum xx, yy;
   bool xxb, yyb; 
   UBigNum d = euclid( b, remainder, xx, yy, xxb, yyb, check);
   xb = yyb;
   x = yy; 

   UBigNum temp = divisor * yy; 
   if( yyb == xxb ) 
   { 
      if( temp > xx ) 
      {
         y = temp - xx; 
         yb = !xxb; 
      }
      else
      {
         y = xx - temp; 
         yb = xxb; 
      }
   }
   else
   {
      y = xx + temp; 
      yb = xxb;  
   }

   if(check) 
      check_euclid(d, a, b, x, y, xb, yb); 

   return d; 
}






static int small_primes [] = 
{ 
   2,3,5,7,11,13,17,19,23,29, 31,37,41,43, 47,53,59,61,67,71,73,79,83,89,97, 0 
};



bool simple_composite(const UBigNum & p) 
{
   for( int i = 0; small_primes[i]; i++ ) 
   {
      UBigNum a(small_primes[i]); 
      UBigNum rem = p%a; 
      if(!rem)
         return true; 
   }
   return false; 
}


bool miller_rabin_composite(const UBigNum & p, int t, int bits) 
{
   const UBigNum ndec(p-1); 
   int s = 0; 
   UBigNum r(ndec); 
   while( !(r%2) )
   {
      s++; 
      r = r/2; 
   }
   for( int i = 0; i < t; i++ ) 
   {
      UBigNum a; 
      a.random(bits); 
      a = 2 + (a%(ndec-4));

      UBigNum y = exp(a,r, p); 
      if( y != 1 || y != ndec )
      {
         for( int j = 1; j < s && y != ndec ; j++ )
         {
            y = exp( y, 2, p ); 
            if( y == 1 ) 
               return true; 
         }
         if( y != ndec )
            return true; 
      }
   }
   return false; 
}





UBigNum prime(int bits, int trials)
{
   UBigNum p;
   p.random(bits); 
   if( p%2 == 0 )
      p = p + 1; 

   for( ;simple_composite(p) || miller_rabin_composite(p, trials, bits); p = p + 2 )
      ;

   return p; 
}






std::ostream & operator << (std::ostream& stream, const UBigNum & _n)
{
   if (_n.number.empty())
   {
      stream << '0' ; 
      return stream; 
   }
   UBigNum n(_n); 
   const int base = 16;
   std::string result; 
   for(; n > 0; ) 
   {
      UBigNum div, rem; 
      UBigNum::divide(n, base, div, rem); 
      int digit = rem.toi(); 
      if( digit > 9 ) 
         result.push_back('a' + rem.toi() - 10) ; 
      else
         result.push_back('0' + rem.toi()) ; 
      n = div; 
   }
   reverse(result.begin(), result.end());
   stream << result ; 
   return stream;
}





std::istream & operator >> (std::istream& stream, UBigNum & n)
{
   n = 0; 
   const int base = 16; 
   char c; 
   while( stream >> c ) 
   {
      int digit; 
      if(c >= '0' && c <= '9')
         digit = c - '0' ; 

      else if (c >= 'a' && c <= 'f')
         digit = c - 'a' + 10; 

      else if (c >= 'A' && c <= 'F' ) 
         digit = c - 'A' + 10; 
      
      else
      {
         stream.unget(); 
         break; 
      }
      n = n * base + digit; 
   }
   return stream; 
}



