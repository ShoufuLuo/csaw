/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/modules/libpref/public/nsIPrefBranch2.idl
 */

#ifndef __gen_nsIPrefBranch2_h__
#define __gen_nsIPrefBranch2_h__


#ifndef __gen_nsIPrefBranch_h__
#include "nsIPrefBranch.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIObserver; /* forward declaration */


/* starting interface:    nsIPrefBranch2 */
#define NS_IPREFBRANCH2_IID_STR "784de8e2-e72f-441a-ae74-9d5fdfe13be3"

#define NS_IPREFBRANCH2_IID \
  {0x784de8e2, 0xe72f, 0x441a, \
    { 0xae, 0x74, 0x9d, 0x5f, 0xdf, 0xe1, 0x3b, 0xe3 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIPrefBranch2 : public nsIPrefBranch {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IPREFBRANCH2_IID)

  /* void addObserver (in string aDomain, in nsIObserver aObserver, in boolean aHoldWeak); */
  NS_SCRIPTABLE NS_IMETHOD AddObserver(const char * aDomain, nsIObserver *aObserver, PRBool aHoldWeak) = 0;

  /* void removeObserver (in string aDomain, in nsIObserver aObserver); */
  NS_SCRIPTABLE NS_IMETHOD RemoveObserver(const char * aDomain, nsIObserver *aObserver) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIPrefBranch2, NS_IPREFBRANCH2_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPREFBRANCH2 \
  NS_SCRIPTABLE NS_IMETHOD AddObserver(const char * aDomain, nsIObserver *aObserver, PRBool aHoldWeak); \
  NS_SCRIPTABLE NS_IMETHOD RemoveObserver(const char * aDomain, nsIObserver *aObserver); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPREFBRANCH2(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddObserver(const char * aDomain, nsIObserver *aObserver, PRBool aHoldWeak) { return _to AddObserver(aDomain, aObserver, aHoldWeak); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveObserver(const char * aDomain, nsIObserver *aObserver) { return _to RemoveObserver(aDomain, aObserver); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPREFBRANCH2(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddObserver(const char * aDomain, nsIObserver *aObserver, PRBool aHoldWeak) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddObserver(aDomain, aObserver, aHoldWeak); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveObserver(const char * aDomain, nsIObserver *aObserver) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveObserver(aDomain, aObserver); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsPrefBranch2 : public nsIPrefBranch2
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPREFBRANCH2

  nsPrefBranch2();

private:
  ~nsPrefBranch2();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsPrefBranch2, nsIPrefBranch2)

nsPrefBranch2::nsPrefBranch2()
{
  /* member initializers and constructor code */
}

nsPrefBranch2::~nsPrefBranch2()
{
  /* destructor code */
}

/* void addObserver (in string aDomain, in nsIObserver aObserver, in boolean aHoldWeak); */
NS_IMETHODIMP nsPrefBranch2::AddObserver(const char * aDomain, nsIObserver *aObserver, PRBool aHoldWeak)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeObserver (in string aDomain, in nsIObserver aObserver); */
NS_IMETHODIMP nsPrefBranch2::RemoveObserver(const char * aDomain, nsIObserver *aObserver)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/**
 * Notification sent when a preference changes.
 */
#define NS_PREFBRANCH_PREFCHANGE_TOPIC_ID "nsPref:changed"

#endif /* __gen_nsIPrefBranch2_h__ */
