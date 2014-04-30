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

#include "byzantineauthenticationwrapper.h" 
#include "byzantineauthenticationadapter.h"
#include <ctime> 

bool ByzantineAuthenticationWrapper:: Init(std::string cfg, int keybits, const peerid_t& self, 
                                           const std::vector<peerid_t>& bootstrap, std::string filename,
                                           int tgs, unsigned expiry_interval, unsigned nmesg_payload)
{
   try 
   {
      if(!(p = ByzantineAuthenticationAdapter::New(cfg, tgs, expiry_interval, nmesg_payload)))
         return false; 
      epoch_t t = ::time(0); 
      return p->Init(keybits, self, bootstrap, filename, t);
   }
   catch(...)
   {
      return false; 
   }
}





bool ByzantineAuthenticationWrapper:: Init(std::string cfg, std::string filename,
                                           int tgs, unsigned expiry_interval, unsigned nmesg_payload)
{
   try 
   {
      if(!(p = ByzantineAuthenticationAdapter::New(cfg, tgs, expiry_interval, nmesg_payload)))
         return false; 
      epoch_t t = ::time(0); 
      return p->Init(filename, t);
   }
   catch(...)
   {
      return false; 
   }
}



void ByzantineAuthenticationWrapper:: DeInit() 
{
   try 
   {
      p->DeInit(); 
      ByzantineAuthenticationAdapter::Delete(p);
      p = 0; 
   }
   catch(...)
   {
      p = 0; 
   }
}



bool ByzantineAuthenticationWrapper::Recv(const peerid_t& peer, const std::string & mesg)
{
   try 
   { 
      return p->Recv(peer, mesg); 
   } 
   catch(...)
   {
      return false; 
   }
}



bool ByzantineAuthenticationWrapper::Send(const peerid_t& peer, std::string & mesg) 
{
   try 
   {
      return p->Send(peer, mesg); 
   }
   catch(...)
   {
      return false; 
   }
}




bool ByzantineAuthenticationWrapper::SendMulti(const std::vector<peerid_t>& peers, std::string & mesg) 
{
   try 
   {
      return p->SendMulti(peers, mesg); 
   }
   catch(...)
   {
      return false; 
   }
}





bool ByzantineAuthenticationWrapper::SetTrusted(const peerid_t& pid)
{
   try 
   {
      p->SetTrusted(pid); 
      return true; 
   }
   catch(...)
   {
      return false; 
   }
}





bool ByzantineAuthenticationWrapper::SetUntrusted(const peerid_t& pid)
{
   try 
   {
      p->SetUntrusted(pid);
      return true; 
   }
   catch(...)
   {
      return false; 
   }
}





bool ByzantineAuthenticationWrapper::SetProbationary(const peerid_t& pid)
{
   try 
   {
      p->SetProbationary(pid); 
      return true; 
   }
   catch(...)
   {
      return false; 
   }
}






bool ByzantineAuthenticationWrapper::GetAuthenticatedKey(const peerid_t& pid, std::string& pubkey, int & trust_value, bool & unknown)
{
   try 
   {
      return p->GetAuthenticatedKey(pid, pubkey, trust_value, unknown); 
   }
   catch(...)
   {
      return false; 
   }
}


        /* 
         * sign messages and verify signatures
         */
bool ByzantineAuthenticationWrapper::Sign(const char * mesg, std::string & sig)
{
   try 
   {
      p->Sign(mesg, sig);  
      return true; 
   }
   catch(...)
   {
      return false; 
   }
}






bool ByzantineAuthenticationWrapper::Verify(const char * mesg, const char * sig, const char * peer, bool & unknown)
{
   try 
   {
      return p->Verify(mesg, sig, peer, unknown) ; 
   }
   catch(...)  
   {
      return false; 
   }
}





bool ByzantineAuthenticationWrapper::GetTrusted(group_t& trusted)
{
   try 
   {
      p->GetTrusted(trusted); 
      return true; 
   }
   catch(...)  
   {
      return false; 
   }
}



bool ByzantineAuthenticationWrapper::GetUntrusted(group_t& untrusted)
{
   try 
   {
      p->GetUntrusted(untrusted); 
      return true; 
   }
   catch(...)  
   {
      return false; 
   }
}






bool ByzantineAuthenticationWrapper::GetProbationary(group_t& probationary)
{
   try 
   {
      p->GetProbationary(probationary); 
      return true; 
   }
   catch(...)  
   {
      return false; 
   }
}




bool ByzantineAuthenticationWrapper::GenerateNewKeyPair(int keybits)
{
   try 
   {
      return p->GenerateNewKeyPair(keybits); 
   }
   catch(...)  
   {
      return false; 
   }
}


bool ByzantineAuthenticationWrapper::GetAuthenticators(const peerid_t& pid, group_t & authenticators)
{
   try 
   {
      return p->GetAuthenticators(pid, authenticators); 
   }
   catch(...)  
   {
      return false; 
   }
}
