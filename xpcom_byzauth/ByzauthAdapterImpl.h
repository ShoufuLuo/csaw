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

#ifndef __PUBLIC_KEY_INFECTION_ADAPTER_IMPL_H__ 
#define __PUBLIC_KEY_INFECTION_ADAPTER_IMPL_H__ 



#include "IByzauthAdapter.h" 
#include <fstream>


#define BYZANTINE_AUTHENTICATION_ADAPTER_CONTRACTID "@rutgers.edu/XPCOM/ByzauthAdapter;1" 
#define BYZANTINE_AUTHENTICATION_ADAPTER_COMPONENT_CLASSNAME "XPCOM Object for Automatic Public Key Authentication in Email" 
#define BYZANTINE_AUTHENTICATION_ADAPTER_CID	{ 0x597a60b0, 0x5272, 0x4284, { 0x90, 0xf6, 0xee, 0x6c, 0x24, 0x2d, 0x74, 0x8 } }

class ByzantineAuthenticationWrapper; 


class ByzantineAuthenticationAdapterImpl : public IByzantineAuthenticationAdapter 
{
  public:
   NS_DECL_ISUPPORTS;
   NS_DECL_IBYZANTINEAUTHENTICATIONADAPTER;

   ByzantineAuthenticationAdapterImpl(); 
   virtual ~ByzantineAuthenticationAdapterImpl();   

  private:
   ByzantineAuthenticationWrapper * _to;     
   unsigned int                     _nallocated; 
   void *                           _buffer; 
   std::ofstream                    _logstream;
   bool     GrowBuffer     (unsigned int newsize); 
}; 



#endif 
