/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/toolkit/components/places/mozIAsyncFavicons.idl
 */

#ifndef __gen_mozIAsyncFavicons_h__
#define __gen_mozIAsyncFavicons_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIURI; /* forward declaration */

class nsIFaviconDataCallback; /* forward declaration */


/* starting interface:    mozIAsyncFavicons */
#define MOZIASYNCFAVICONS_IID_STR "6d2b0507-245f-452d-9718-5595dcd3cd14"

#define MOZIASYNCFAVICONS_IID \
  {0x6d2b0507, 0x245f, 0x452d, \
    { 0x97, 0x18, 0x55, 0x95, 0xdc, 0xd3, 0xcd, 0x14 }}

class NS_NO_VTABLE NS_SCRIPTABLE mozIAsyncFavicons : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(MOZIASYNCFAVICONS_IID)

  /* void setAndFetchFaviconForPage (in nsIURI aPageURI, in nsIURI aFaviconURI, in boolean aForceReload, [optional] in nsIFaviconDataCallback aCallback); */
  NS_SCRIPTABLE NS_IMETHOD SetAndFetchFaviconForPage(nsIURI *aPageURI, nsIURI *aFaviconURI, PRBool aForceReload, nsIFaviconDataCallback *aCallback) = 0;

  /* void getFaviconURLForPage (in nsIURI aPageURI, in nsIFaviconDataCallback aCallback); */
  NS_SCRIPTABLE NS_IMETHOD GetFaviconURLForPage(nsIURI *aPageURI, nsIFaviconDataCallback *aCallback) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(mozIAsyncFavicons, MOZIASYNCFAVICONS_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_MOZIASYNCFAVICONS \
  NS_SCRIPTABLE NS_IMETHOD SetAndFetchFaviconForPage(nsIURI *aPageURI, nsIURI *aFaviconURI, PRBool aForceReload, nsIFaviconDataCallback *aCallback); \
  NS_SCRIPTABLE NS_IMETHOD GetFaviconURLForPage(nsIURI *aPageURI, nsIFaviconDataCallback *aCallback); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_MOZIASYNCFAVICONS(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetAndFetchFaviconForPage(nsIURI *aPageURI, nsIURI *aFaviconURI, PRBool aForceReload, nsIFaviconDataCallback *aCallback) { return _to SetAndFetchFaviconForPage(aPageURI, aFaviconURI, aForceReload, aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetFaviconURLForPage(nsIURI *aPageURI, nsIFaviconDataCallback *aCallback) { return _to GetFaviconURLForPage(aPageURI, aCallback); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_MOZIASYNCFAVICONS(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetAndFetchFaviconForPage(nsIURI *aPageURI, nsIURI *aFaviconURI, PRBool aForceReload, nsIFaviconDataCallback *aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAndFetchFaviconForPage(aPageURI, aFaviconURI, aForceReload, aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetFaviconURLForPage(nsIURI *aPageURI, nsIFaviconDataCallback *aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFaviconURLForPage(aPageURI, aCallback); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public mozIAsyncFavicons
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_MOZIASYNCFAVICONS

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, mozIAsyncFavicons)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void setAndFetchFaviconForPage (in nsIURI aPageURI, in nsIURI aFaviconURI, in boolean aForceReload, [optional] in nsIFaviconDataCallback aCallback); */
NS_IMETHODIMP _MYCLASS_::SetAndFetchFaviconForPage(nsIURI *aPageURI, nsIURI *aFaviconURI, PRBool aForceReload, nsIFaviconDataCallback *aCallback)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getFaviconURLForPage (in nsIURI aPageURI, in nsIFaviconDataCallback aCallback); */
NS_IMETHODIMP _MYCLASS_::GetFaviconURLForPage(nsIURI *aPageURI, nsIFaviconDataCallback *aCallback)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_mozIAsyncFavicons_h__ */
