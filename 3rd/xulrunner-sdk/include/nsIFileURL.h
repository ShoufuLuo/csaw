/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/netwerk/base/public/nsIFileURL.idl
 */

#ifndef __gen_nsIFileURL_h__
#define __gen_nsIFileURL_h__


#ifndef __gen_nsIURL_h__
#include "nsIURL.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIFile; /* forward declaration */


/* starting interface:    nsIFileURL */
#define NS_IFILEURL_IID_STR "93a4f94e-1dae-4056-ac4e-08e13691ee8e"

#define NS_IFILEURL_IID \
  {0x93a4f94e, 0x1dae, 0x4056, \
    { 0xac, 0x4e, 0x08, 0xe1, 0x36, 0x91, 0xee, 0x8e }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIFileURL : public nsIURL {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IFILEURL_IID)

  /* attribute nsIFile file; */
  NS_SCRIPTABLE NS_IMETHOD GetFile(nsIFile * *aFile) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetFile(nsIFile *aFile) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIFileURL, NS_IFILEURL_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIFILEURL \
  NS_SCRIPTABLE NS_IMETHOD GetFile(nsIFile * *aFile); \
  NS_SCRIPTABLE NS_IMETHOD SetFile(nsIFile *aFile); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIFILEURL(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetFile(nsIFile * *aFile) { return _to GetFile(aFile); } \
  NS_SCRIPTABLE NS_IMETHOD SetFile(nsIFile *aFile) { return _to SetFile(aFile); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIFILEURL(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetFile(nsIFile * *aFile) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFile(aFile); } \
  NS_SCRIPTABLE NS_IMETHOD SetFile(nsIFile *aFile) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFile(aFile); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsFileURL : public nsIFileURL
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIFILEURL

  nsFileURL();

private:
  ~nsFileURL();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsFileURL, nsIFileURL)

nsFileURL::nsFileURL()
{
  /* member initializers and constructor code */
}

nsFileURL::~nsFileURL()
{
  /* destructor code */
}

/* attribute nsIFile file; */
NS_IMETHODIMP nsFileURL::GetFile(nsIFile * *aFile)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsFileURL::SetFile(nsIFile *aFile)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIFileURL_h__ */
