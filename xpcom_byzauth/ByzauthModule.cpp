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
 *	Author: Shoufu Luo
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#include "mozilla/ModuleUtils.h"
#include "nsIClassInfoImpl.h"
#include "ByzauthAdapterImpl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(ByzantineAuthenticationAdapterImpl) 

NS_DEFINE_NAMED_CID(BYZANTINE_AUTHENTICATION_ADAPTER_CID);

static const mozilla::Module::CIDEntry	ByzantineAuthenticationAdapterCIDs[] = 
{
	{ &kBYZANTINE_AUTHENTICATION_ADAPTER_CID, false, NULL, ByzantineAuthenticationAdapterImplConstructor },
	{ NULL }
};

static const mozilla::Module::ContractIDEntry ByzantineAUthenticationAdapterContracts[] = 
{
	{ BYZANTINE_AUTHENTICATION_ADAPTER_CONTRACTID, &kBYZANTINE_AUTHENTICATION_ADAPTER_CID}, 
	{ NULL }
};

static const mozilla::Module::CategoryEntry byzantineAuthenCategories[] = 
{
	{ "Byzantine", "authen", BYZANTINE_AUTHENTICATION_ADAPTER_CONTRACTID },
	{ NULL }
};

static const mozilla::Module kByzantineAuthenticationAdapterImplModule =
{
	mozilla::Module::kVersion,
	ByzantineAuthenticationAdapterCIDs,
	ByzantineAUthenticationAdapterContracts,
	byzantineAuthenCategories,
};

NSMODULE_DEFN(ByzantineAuthenticationAdapterImpleModule) = &kByzantineAuthenticationAdapterImplModule;

NS_IMPL_MOZILLA192_NSGETMODULE(&kByzantineAuthenticationAdapterImplModule)
