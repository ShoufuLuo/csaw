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

#ifndef __DIGITS_H__
#define __DIGITS_H__ 

/** 
 * Class Digits 
 * Class for efficient book keeping of the digits used for 
 * multiple precision arithmetic.  
 * 
 * 1/18/06 
 * Current implementation uses STL deque but that is slow in 
 * size() method.  If we use vector then we become slow in push_front. 
 * The idea of using a rolling buffer will provide better constant 
 * time performance for following ops: 
 * size(), [i], push_front() and push_back(). 
 * TODO: Iterator for the class. Note: iterators can remain valid across 
 * size growth and push_back and push_front (keep integer into digits array)
 */

typedef unsigned long dig_t; 

#define  MAX_DIGITS   20000 

class Digits 
{
   dig_t *        digits; 
   short          start; 
   short          end; 
   unsigned short alloc; 

   inline void grow(short newsize = -1) 
   {
      if( newsize == -1 )
      {
         alloc = alloc ? 2*alloc : 8 ;
         assert( alloc < MAX_DIGITS ) ;
      }
      else if( newsize < alloc )
         return; 
      else 
         alloc = newsize; 
      digits = (dig_t *) realloc( digits, sizeof(dig_t) * alloc ) ; 
      assert( digits ) ; 
   }   

   inline copy(const Digits& c) 
   {
      deinit();  
      grow(c.alloc); 
      start = c.start; 
      end = c.end; 
      for( int i = start; i < end; i++ ) 
         digits[i] = c.digits[i]; 
   }

  public:

   inline Digits()
      : start(0), end(0)
   {
      alloc = 8; 
      digits = (dig_t *) malloc( sizeof(dig_t) * alloc ) ; 
   }


   inline void push_back(dig_t d) 
   {
      int gap = (end-start)%alloc; 
      if( gap == -1 || gap == 1 )
         grow(); 

      digits[end++] = d; 
   }


   inline void push_front(dig_t d) 
   {
      int gap = (end-start)%alloc; 
      if( gap == -1 || gap == 1 )
         grow(); 

      digits[start--] = d; 
   }


   inline unsigned short size()
   {
      int gap = (end-start)%alloc; 
      return gap < 0 ? -gap : gap; 
   }

   
   inline dig_t& operator []  (unsigned short i)
   {
      assert( i < alloc && ( (i%alloc) < (i%alloc) && (i%alloc) >= (start%alloc) ) ); 
      return digits[(i + start) % alloc] ; 
   }
      
   inline const dig_t& operator []  (unsigned short i) const
   {
      assert( i < alloc && ( (i%alloc) < (i%alloc) && (i%alloc) >= (start%alloc) ) ); 
      return digits[(i + start) % alloc] ; 
   }

} ; 



      






















#endif 
