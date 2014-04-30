
#include "mozilla/ModuleUtils.h"
#include "nsIClassInfoImpl.h"
#include "helloxpcomImpl.h"

// this line generates the helloxpcomConstructor
NS_GENERIC_FACTORY_CONSTRUCTOR(helloxpcomImpl) 

//this line generates the kHELLOXPCOM_CID
NS_DEFINE_NAMED_CID(HELLOXPCOM_CID);

static const mozilla::Module::CIDEntry	helloxpcomCIDs[] = 
{
	{ &kHELLOXPCOM_CID, false, NULL, helloxpcomImplConstructor },
	{ NULL }
};

static const mozilla::Module::ContractIDEntry helloxpcomContracts[] = 
{
	{ HELLOXPCOM_CONTRACTID, &kHELLOXPCOM_CID}, 
	{ NULL }
};

static const mozilla::Module::CategoryEntry helloxpcomCategories[] = 
{
	{ "profile-after-change", "xpcomdemo", HELLOXPCOM_CONTRACTID },
	{ NULL }
};

static const mozilla::Module kHelloxpcomModule =
{
	mozilla::Module::kVersion,
	helloxpcomCIDs,
	helloxpcomContracts,
	helloxpcomCategories
};

NSMODULE_DEFN(helloxpcomMudle) = &kHelloxpcomModule;

NS_IMPL_MOZILLA192_NSGETMODULE(&kHelloxpcomModule)
