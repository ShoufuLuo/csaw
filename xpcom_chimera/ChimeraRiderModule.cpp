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
 *	Author: Shoufu Luo (sluo2@stevens.edu)
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#include "mozilla/ModuleUtils.h"
#include "nsIClassInfoImpl.h"
#include "ChimeraRider.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(ChimeraRider) 

NS_DEFINE_NAMED_CID(CHIMERA_RIDER_CID);

static const mozilla::Module::CIDEntry	ChimeraRiderCIDs[] = 
{
	{ &kCHIMERA_RIDER_CID, false, NULL, ChimeraRiderConstructor },
	{ NULL }
};

static const mozilla::Module::ContractIDEntry ChimeraRiderContracts[] = 
{
	{ CHIMERA_RIDER_CONTRACTID, &kCHIMERA_RIDER_CID}, 
	{ NULL }
};

static const mozilla::Module::CategoryEntry ChimeraRiderCategories[] = 
{
	{ "profile-after-change", "ChimeraRider", CHIMERA_RIDER_CONTRACTID },
	{ NULL }
};

static const mozilla::Module kChimeraRiderModule =
{
	mozilla::Module::kVersion,
	ChimeraRiderCIDs,
	ChimeraRiderContracts,
	ChimeraRiderCategories,
};

NSMODULE_DEFN(ChimeraRiderModule) = &kChimeraRiderModule;

NS_IMPL_MOZILLA192_NSGETMODULE(&kChimeraRiderModule)
