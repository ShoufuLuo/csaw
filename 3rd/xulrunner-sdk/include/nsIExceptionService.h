/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/xpcom/base/nsIExceptionService.idl
 */

#ifndef __gen_nsIExceptionService_h__
#define __gen_nsIExceptionService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIException_h__
#include "nsIException.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIExceptionProvider */
#define NS_IEXCEPTIONPROVIDER_IID_STR "0577744c-c1d2-47f2-8bcc-ce7a9e5a88fc"

#define NS_IEXCEPTIONPROVIDER_IID \
  {0x0577744c, 0xc1d2, 0x47f2, \
    { 0x8b, 0xcc, 0xce, 0x7a, 0x9e, 0x5a, 0x88, 0xfc }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIExceptionProvider : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IEXCEPTIONPROVIDER_IID)

  /* nsIException getException (in nsresult result, in nsIException defaultException); */
  NS_SCRIPTABLE NS_IMETHOD GetException(nsresult result, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIExceptionProvider, NS_IEXCEPTIONPROVIDER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIEXCEPTIONPROVIDER \
  NS_SCRIPTABLE NS_IMETHOD GetException(nsresult result, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIEXCEPTIONPROVIDER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetException(nsresult result, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM) { return _to GetException(result, defaultException, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIEXCEPTIONPROVIDER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetException(nsresult result, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetException(result, defaultException, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsExceptionProvider : public nsIExceptionProvider
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIEXCEPTIONPROVIDER

  nsExceptionProvider();

private:
  ~nsExceptionProvider();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsExceptionProvider, nsIExceptionProvider)

nsExceptionProvider::nsExceptionProvider()
{
  /* member initializers and constructor code */
}

nsExceptionProvider::~nsExceptionProvider()
{
  /* destructor code */
}

/* nsIException getException (in nsresult result, in nsIException defaultException); */
NS_IMETHODIMP nsExceptionProvider::GetException(nsresult result, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIExceptionManager */
#define NS_IEXCEPTIONMANAGER_IID_STR "efc9d00b-231c-4feb-852c-ac017266a415"

#define NS_IEXCEPTIONMANAGER_IID \
  {0xefc9d00b, 0x231c, 0x4feb, \
    { 0x85, 0x2c, 0xac, 0x01, 0x72, 0x66, 0xa4, 0x15 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIExceptionManager : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IEXCEPTIONMANAGER_IID)

  /* void setCurrentException (in nsIException error); */
  NS_SCRIPTABLE NS_IMETHOD SetCurrentException(nsIException *error) = 0;

  /* nsIException getCurrentException (); */
  NS_SCRIPTABLE NS_IMETHOD GetCurrentException(nsIException * *_retval NS_OUTPARAM) = 0;

  /* nsIException getExceptionFromProvider (in nsresult rc, in nsIException defaultException); */
  NS_SCRIPTABLE NS_IMETHOD GetExceptionFromProvider(nsresult rc, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIExceptionManager, NS_IEXCEPTIONMANAGER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIEXCEPTIONMANAGER \
  NS_SCRIPTABLE NS_IMETHOD SetCurrentException(nsIException *error); \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentException(nsIException * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetExceptionFromProvider(nsresult rc, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIEXCEPTIONMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetCurrentException(nsIException *error) { return _to SetCurrentException(error); } \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentException(nsIException * *_retval NS_OUTPARAM) { return _to GetCurrentException(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetExceptionFromProvider(nsresult rc, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM) { return _to GetExceptionFromProvider(rc, defaultException, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIEXCEPTIONMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetCurrentException(nsIException *error) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCurrentException(error); } \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentException(nsIException * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCurrentException(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetExceptionFromProvider(nsresult rc, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetExceptionFromProvider(rc, defaultException, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsExceptionManager : public nsIExceptionManager
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIEXCEPTIONMANAGER

  nsExceptionManager();

private:
  ~nsExceptionManager();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsExceptionManager, nsIExceptionManager)

nsExceptionManager::nsExceptionManager()
{
  /* member initializers and constructor code */
}

nsExceptionManager::~nsExceptionManager()
{
  /* destructor code */
}

/* void setCurrentException (in nsIException error); */
NS_IMETHODIMP nsExceptionManager::SetCurrentException(nsIException *error)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIException getCurrentException (); */
NS_IMETHODIMP nsExceptionManager::GetCurrentException(nsIException * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIException getExceptionFromProvider (in nsresult rc, in nsIException defaultException); */
NS_IMETHODIMP nsExceptionManager::GetExceptionFromProvider(nsresult rc, nsIException *defaultException, nsIException * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIExceptionService */
#define NS_IEXCEPTIONSERVICE_IID_STR "35a88f54-f267-4414-92a7-191f6454ab52"

#define NS_IEXCEPTIONSERVICE_IID \
  {0x35a88f54, 0xf267, 0x4414, \
    { 0x92, 0xa7, 0x19, 0x1f, 0x64, 0x54, 0xab, 0x52 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIExceptionService : public nsIExceptionManager {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IEXCEPTIONSERVICE_IID)

  /* readonly attribute nsIExceptionManager currentExceptionManager; */
  NS_SCRIPTABLE NS_IMETHOD GetCurrentExceptionManager(nsIExceptionManager * *aCurrentExceptionManager) = 0;

  /* void registerExceptionProvider (in nsIExceptionProvider provider, in PRUint32 moduleCode); */
  NS_SCRIPTABLE NS_IMETHOD RegisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode) = 0;

  /* void unregisterExceptionProvider (in nsIExceptionProvider provider, in PRUint32 moduleCode); */
  NS_SCRIPTABLE NS_IMETHOD UnregisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIExceptionService, NS_IEXCEPTIONSERVICE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIEXCEPTIONSERVICE \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentExceptionManager(nsIExceptionManager * *aCurrentExceptionManager); \
  NS_SCRIPTABLE NS_IMETHOD RegisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode); \
  NS_SCRIPTABLE NS_IMETHOD UnregisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIEXCEPTIONSERVICE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentExceptionManager(nsIExceptionManager * *aCurrentExceptionManager) { return _to GetCurrentExceptionManager(aCurrentExceptionManager); } \
  NS_SCRIPTABLE NS_IMETHOD RegisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode) { return _to RegisterExceptionProvider(provider, moduleCode); } \
  NS_SCRIPTABLE NS_IMETHOD UnregisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode) { return _to UnregisterExceptionProvider(provider, moduleCode); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIEXCEPTIONSERVICE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentExceptionManager(nsIExceptionManager * *aCurrentExceptionManager) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCurrentExceptionManager(aCurrentExceptionManager); } \
  NS_SCRIPTABLE NS_IMETHOD RegisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode) { return !_to ? NS_ERROR_NULL_POINTER : _to->RegisterExceptionProvider(provider, moduleCode); } \
  NS_SCRIPTABLE NS_IMETHOD UnregisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode) { return !_to ? NS_ERROR_NULL_POINTER : _to->UnregisterExceptionProvider(provider, moduleCode); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsExceptionService : public nsIExceptionService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIEXCEPTIONSERVICE

  nsExceptionService();

private:
  ~nsExceptionService();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsExceptionService, nsIExceptionService)

nsExceptionService::nsExceptionService()
{
  /* member initializers and constructor code */
}

nsExceptionService::~nsExceptionService()
{
  /* destructor code */
}

/* readonly attribute nsIExceptionManager currentExceptionManager; */
NS_IMETHODIMP nsExceptionService::GetCurrentExceptionManager(nsIExceptionManager * *aCurrentExceptionManager)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void registerExceptionProvider (in nsIExceptionProvider provider, in PRUint32 moduleCode); */
NS_IMETHODIMP nsExceptionService::RegisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void unregisterExceptionProvider (in nsIExceptionProvider provider, in PRUint32 moduleCode); */
NS_IMETHODIMP nsExceptionService::UnregisterExceptionProvider(nsIExceptionProvider *provider, PRUint32 moduleCode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_EXCEPTIONSERVICE_CLASSNAME "Exception Service"
// {35A88F54-F267-4414-92A7-191F6454AB52}
#define NS_EXCEPTIONSERVICE_CID \
{ 0x35a88f54, 0xf267, 0x4414, { 0x92, 0xa7, 0x19, 0x1f, 0x64, 0x54, 0xab, 0x52 } }
#define NS_EXCEPTIONSERVICE_CONTRACTID "@mozilla.org/exceptionservice;1"

#endif /* __gen_nsIExceptionService_h__ */