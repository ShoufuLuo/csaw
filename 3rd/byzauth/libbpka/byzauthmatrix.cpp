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

#include "proxypeer.h"
#include "rsa.h"
#include "messageprocessor.h"
#include "peerfactory.h"
#include "keyrepository.h"
#include "self.h"



bool ByzAuthMatrix::init(const group_t &_trusted, const std::string & _probationary)
{
   clear();

   int j = 0; 
   for( group_t::const_iterator i = _trusted.begin(); i != _trusted.end(); i++, j++ ) 
      trusted.insert(make_pair(i->first, j)); 

   probationary = _probationary; 

   proofs.reserve(trusted.size());
   for(unsigned int i = 0; i < trusted.size(); i++ ) 
      proofs[i].reserve(trusted.size());

   start_time = time(0);
   return true;
}





void ByzAuthMatrix::clear() 
{
   start_time = 0; 
   proofs.clear(); 
   trusted.clear(); 
   probationary.clear(); 
}




bool ByzAuthMatrix::insert(const peerid_t& challenger, const peerid_t& observer, const Proof& p)
{
   if( trusted.find(challenger) == trusted.end() || 
       trusted.find(observer) == trusted.end() )
      return false;

   if( p.challenger != challenger || p.from != observer || p.responder != probationary ) 
      return false; 

   proofs[ trusted[challenger] ][ trusted[observer] ] = p ; 
   return true ; 
} 





   
bool ByzAuthMatrix::gotEnough()
{
   int total = 0; 
   int enough = (trusted.size()*2/3); 
   enough *= enough; 

   for( int i = 0, n = trusted.size(); i < n; i++ ) 
      for( int j = 0; j < n; j++ )
      {
         Proof & p = proofs[i][j]; 
         if( p.from.length() && p.to.length() )
            total++; 
      }
   if( total > enough )
      return true;
   else
      return false; 
}





bool ByzAuthMatrix::agreement (group_t & trust, group_t & untrust, group_t & prob, KeyRepository& rep)
{
   std::set<int> deleteset; 
   for( int i = 0, n = trusted.size(); i < n; i++ ) 
   {
      int pos = 0; 
      int neg = 0; 
      for( int j = 0; j < n; j++ ) 
      {
         bool pinvalid, ainvalid, kinvalid; 
         if( rep.isValid(proofs[i][j], pinvalid, ainvalid, kinvalid) )
            pos ++ ; 
         else
            neg ++ ; 
      }
      if( pos <= neg )
         deleteset.insert(i); 
   }

   for( std::map<peerid_t, int>::iterator i = trusted.begin(); i != trusted.end(); i++ ) 
      if( deleteset.find(i->second) != deleteset.end() ) 
      {
         trust.erase(i->first);
         untrust.insert( make_pair(i->first, time(0))) ; 
      }

   for( int i = 0, n = trusted.size(); i < n; i++ ) 
   {
      if( deleteset.find(i) != deleteset.end() )
         continue; 

      int pos = 0; 
      int neg = 0; 
      for( int j = 0; j < n; j++ ) 
      {
         if( deleteset.find(j) != deleteset.end() )
            continue; 
         bool pinvalid, ainvalid, kinvalid; 
         if( rep.isValid(proofs[i][j], pinvalid, ainvalid, kinvalid) )
            pos ++ ; 
         else
            neg ++ ; 
      }  
   
      if( neg )
      { 
         prob.erase(probationary);
         untrust.insert( make_pair(probationary, time(0))) ; 
      }
   }

   return true;
}




bool ByzAuthMatrix::operator !  ()
{
   if( trusted.size() || proofs.size() || probationary.size() ) 
      return false;
   return true; 
}




epoch_t ByzAuthMatrix::max_time = ~0ull; 


void ByzAuthMatrix::time_out(int seconds)
{
   max_time = seconds; 
}


bool ByzAuthMatrix::isRecent()
{
   epoch_t curr = time(0); 
   if( (curr - start_time) >= max_time ) 
      return false;
   return true; 
}



