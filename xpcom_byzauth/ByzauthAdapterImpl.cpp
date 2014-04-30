/**
 *  Copyright (c) 2012 Stevens Institute of Technology. 
 *  
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *	Author: Vivek Pathak
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#include "ByzauthAdapterImpl.h" 
#include "byzantineauthenticationwrapper.h" 
#include "nsMemory.h"
#include <stdlib.h>
#include <zlib.h>
#include <string> 
#include <stdio.h> 
#include <assert.h>


NS_IMPL_ISUPPORTS1(ByzantineAuthenticationAdapterImpl, IByzantineAuthenticationAdapter)


extern bool to_base_64(std::string & out, const std::string & in); 
extern bool from_base_64(std::string& out, const std::string& in);
static const long base_alloc_sz = 4*1024*1024; 

ByzantineAuthenticationAdapterImpl::ByzantineAuthenticationAdapterImpl() 
   : _to(0) , _buffer(0) 
{
   _buffer = NS_Alloc(base_alloc_sz); 
   _nallocated = base_alloc_sz; 
   NS_ASSERTION(_buffer, "Could not initialize compression buffer");

   _logstream.open("byzauthmodule.log", std::ios::app ) ; 
} 








ByzantineAuthenticationAdapterImpl::~ByzantineAuthenticationAdapterImpl()
{
   if(_to)
   {
      _to->DeInit(); 
      _to = 0; 

      assert(_buffer);

      NS_Free(_buffer); 
      _nallocated = 0; 
      _buffer = 0; 
   }
}







NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::Stop(PRBool *_retval)
{
   if(!_to)
      return NS_ERROR_NULL_POINTER; 

   _to->DeInit(); 
   delete _to; 
   _to = 0; 

   assert(_buffer);
   
   NS_Free(_buffer);
   _nallocated = 0; 
   _buffer = 0;  
   return NS_OK;
}




bool ByzantineAuthenticationAdapterImpl::GrowBuffer(unsigned int newsize)
{
   NS_ASSERTION(_buffer, "Cannot grow null compression buffer");
   if( newsize < _nallocated ) 
      return true; 
   else
   {  
           // find a buffer size that is multiple of base_alloc_sz and greater than 
           // newsize
      if( (newsize % base_alloc_sz) )
         newsize += (base_alloc_sz - (newsize % base_alloc_sz)); 


      assert(  !(newsize % base_alloc_sz)  ) ; 

      void * _newbuffer = NS_Realloc(_buffer, newsize) ; 
      if(!_newbuffer) 
         return false; 
      
      _buffer = _newbuffer; 
      _nallocated = newsize; 
      return true; 
   }
}





NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::ReceiveIncomingAuthenticationMessage(const char *peer, 
                                                                         const char *mesg, 
                                                                         PRBool *_retval) 
{ 
   if(!_to)
      return NS_ERROR_NULL_POINTER; 

   std::string _peer(peer); 
   std::string recvd(mesg); 
   std::string compressed; 
   if(!from_base_64(compressed, recvd))
   {
      _logstream << "Error in base 64 conversion" << std::endl; 
      return NS_ERROR_FAILURE; 
   }

   uLongf destLen = _nallocated; 
   int ret = 0; 
   if(Z_BUF_ERROR == (ret = uncompress( (Bytef *) _buffer,  &destLen, (const Bytef *) compressed.data(), compressed.length())))
   {
      if(!GrowBuffer(destLen))
         return NS_ERROR_OUT_OF_MEMORY;
      
      uLongf destLen = _nallocated;
      if(Z_OK != (ret = uncompress( (Bytef *) _buffer,  &destLen, (const Bytef *) compressed.data(), compressed.length())))
      {
         NS_ASSERTION(ret == Z_OK, "error uncompress");
         uncompress( (Bytef *) _buffer,  &destLen, (const Bytef *) compressed.data(), compressed.length()); 
         return NS_ERROR_FAILURE; 
      }
   }
   else if( Z_OK != ret  )
   {
      _logstream << "error code " << ret << " on decompress" << std::endl; 
      return NS_ERROR_FAILURE; 
   }

   std::string _mesg((char *)_buffer, destLen ); 
   *_retval = _to->Recv(_peer, _mesg);
   return NS_OK;
} 







NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::SendOutgoingAuthenticationMessage(PRUint32 count, 
                                                                      const char **dest, 
                                                                      char **mesg)
{ 
   if(!_to)
      return NS_ERROR_NULL_POINTER; 

   std::vector<peerid_t> dests; 
   for( unsigned int i = 0; i < count; i++ ) 
      dests.push_back(dest[i]); 
   
   std::string outmesg;
   if((_to->SendMulti(dests, outmesg)))
   {
      uLongf destLen = compressBound(outmesg.size()) ; 
      while( destLen > _nallocated ) 
      {
         _nallocated *= 2; 
         if(!(_buffer = realloc(_buffer, _nallocated)))
            return NS_ERROR_OUT_OF_MEMORY;
      }
      Bytef *dest = (Bytef *) _buffer ; 
      const Bytef *source = (Bytef *) outmesg.data();
      uLong sourceLen = outmesg.size();
      int ret = 0;
      if( Z_OK != (ret = compress(dest, &destLen, source, sourceLen)))
      {
         return NS_ERROR_FAILURE; 
      }

      std::string compressed((char *)dest, destLen); 
      std::string toattach; 
      to_base_64(toattach, compressed);

      if(!(*mesg = (char *) nsMemory::Clone( toattach.c_str() , strlen(toattach.c_str()) + 1 )))
         return NS_ERROR_OUT_OF_MEMORY;
   }
   else 
      return NS_ERROR_FAILURE; 

   return NS_OK; 
}






NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::ColdStart(PRInt32 keybits, 
                                         const char *selfname, 
                                         PRUint32 count, 
                                         const char **bootstrap, 
                                         const char *serializefilename, 
                                         PRInt32 ttl, 
                                         PRInt32 tgshint,
                                         PRInt32 payload, 
                                         PRBool *_retval) 
{ 
   if(_to)
      return NS_ERROR_ALREADY_INITIALIZED; 

   if(!(_to = new ByzantineAuthenticationWrapper))
      return NS_ERROR_OUT_OF_MEMORY;      

   std::vector<peerid_t> trusted; 
   for( unsigned int i = 0; i < count; i++ ) 
      trusted.push_back(bootstrap[i]); 

   if(!(*_retval = _to->Init("", keybits, selfname, trusted, serializefilename,
                             ttl, tgshint, payload)))
      return  NS_ERROR_FAILURE; 

   return NS_OK; 
}






NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::WarmStart(const char *serializefilename, 
                                              PRInt32 ttl, 
                                              PRInt32 tgshint,
                                              PRInt32 payload, 
                                              PRBool *_retval)
{
   if(_to)
      return NS_ERROR_ALREADY_INITIALIZED; 

   if(!(_to = new ByzantineAuthenticationWrapper))
      return NS_ERROR_OUT_OF_MEMORY;      

   if(!(*_retval = _to->Init("", serializefilename, 
                             ttl, tgshint, payload)))
      return  NS_ERROR_FAILURE; 

   return NS_OK; 
}








NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::SetTrusted(const char *peer, PRBool *_retval)
{
   if(!_to)
      return NS_ERROR_NULL_POINTER; 
   _to->SetTrusted(peer);
   *_retval =  true; 
   return NS_OK; 
}






NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::SetUntrusted(const char *peer, PRBool *_retval)
{
   if(!_to)
      return NS_ERROR_NULL_POINTER; 
   _to->SetUntrusted(peer);
   *_retval = true; 
   return NS_OK; 
}




NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::SetProbationary(const char *peer, PRBool *_retval)
{
   if(!_to)
      return NS_ERROR_NULL_POINTER; 
   _to->SetProbationary(peer);
   *_retval = true; 
   return NS_OK; 
}






NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::GetAuthenticatedKey(const char *peer, 
                                                        PRInt32 *trust_value, 
                                                        PRBool *unknown, 
                                                        char **_retval)
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;
   
   std::string pubkey_; 
   int trust_value_;
   bool unknown_; 

   if((_to->GetAuthenticatedKey(peer, pubkey_, trust_value_, unknown_)))
      if(!(*_retval = (char *) nsMemory::Clone( pubkey_.c_str(), strlen(pubkey_.c_str()) + 1 )))
         return NS_ERROR_OUT_OF_MEMORY;

   *unknown = unknown_; 
   *trust_value = trust_value_; 
   
   return NS_OK; 
}



  /* string Sign (in string mesg); */
NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::Sign(const char *mesg, char **_retval)
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;
   std::string sig; 
   _to->Sign(mesg, sig);
   if(!(*_retval = (char *)nsMemory::Clone( sig.c_str(), sig.length() + 1)))
      return NS_ERROR_OUT_OF_MEMORY;
   else
      return NS_OK; 
}



NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::Verify(const char *mesg, const char *sig, const char *peer, PRBool *unknown, PRBool *_retval)
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;
   bool isunknown; 
   *_retval = _to->Verify(mesg, sig, peer, isunknown); 
   *unknown = isunknown; 
   return NS_OK; 
}  




static int
copy_group_info(const group_t group, PRUint32 *count, char ***trusted)
{
   if(!group.size())
   {
      *count = 0; 
      *trusted = 0; 
      return NS_OK;
   } 

   char** peers =  static_cast<char**>(nsMemory::Alloc(group.size() * sizeof(char*)));
   if(!peers)
      return NS_ERROR_OUT_OF_MEMORY;

   int j = 0; 
   for( group_t::const_iterator i = group.begin(); i != group.end(); i++, j++ ) 
      if(!(peers[j] = (char *) nsMemory::Clone( i->first.c_str(), i->first.length() + 1 )))
         return NS_ERROR_OUT_OF_MEMORY;
   
   *trusted = peers; 
   *count = group.size(); 
   return NS_OK; 
}



  /* void getTrusted (out PRUint32 count, [array, size_is (count)] out string trusted); */
NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::GetTrusted(PRUint32 *count, char ***trusted)
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;

   group_t group; 
   if(!_to->GetTrusted(group))
      return NS_ERROR_FAILURE;
   return copy_group_info(group, count, trusted) ; 
}





  /* void getUntrusted (out PRUint32 count, [array, size_is (count)] out string untrusted); */
NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::GetUntrusted(PRUint32 *count, char ***untrusted)
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;

   group_t group; 
   if(!_to->GetUntrusted(group))
      return NS_ERROR_FAILURE;
   return copy_group_info(group, count, untrusted) ; 
}


  /* void getProbationary (out PRUint32 count, [array, size_is (count)] out string probationary); */
NS_IMETHODIMP
ByzantineAuthenticationAdapterImpl::GetProbationary(PRUint32 *count, char ***probationary)
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;

   group_t group; 
   if(!_to->GetProbationary(group))
      return NS_ERROR_FAILURE;
   return copy_group_info(group, count, probationary) ; 
}





NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::GenerateNewKeyPair(PRUint32 keybits, PRBool *_retval)
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;
   if(!_to->GenerateNewKeyPair(keybits))
      return NS_ERROR_FAILURE;
   else 
   {
      *_retval = true; 
      return NS_OK ; 
   }
}




NS_IMETHODIMP 
ByzantineAuthenticationAdapterImpl::GetAuthenticators(const char *peer, PRUint32 *count, char ***authenticators) 
{
   if (!_to)
      return NS_ERROR_NULL_POINTER;

   peerid_t pid(peer); 
   group_t auth_group; 
   if(!_to->GetAuthenticators(pid, auth_group))
      return NS_OK; 

   return copy_group_info(auth_group, count, authenticators) ; 
}

