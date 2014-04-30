/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/docshell/base/nsIGlobalHistory3.idl
 */

#ifndef __gen_nsIGlobalHistory3_h__
#define __gen_nsIGlobalHistory3_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIGlobalHistory2_h__
#include "nsIGlobalHistory2.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIChannel; /* forward declaration */


// This is NOT part of the interface! It could change.
#define NS_GECKO_FLAG_NEEDS_VERTICAL_SCROLLBAR (1 << 0)

/* starting interface:    nsIGlobalHistory3 */
#define NS_IGLOBALHISTORY3_IID_STR "24306852-c60e-49c3-a455-90f6747118ba"

#define NS_IGLOBALHISTORY3_IID \
  {0x24306852, 0xc60e, 0x49c3, \
    { 0xa4, 0x55, 0x90, 0xf6, 0x74, 0x71, 0x18, 0xba }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIGlobalHistory3 : public nsIGlobalHistory2 {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IGLOBALHISTORY3_IID)

  /* void addDocumentRedirect (in nsIChannel aOldChannel, in nsIChannel aNewChannel, in PRInt32 aFlags, in boolean aTopLevel); */
  NS_SCRIPTABLE NS_IMETHOD AddDocumentRedirect(nsIChannel *aOldChannel, nsIChannel *aNewChannel, PRInt32 aFlags, PRBool aTopLevel) = 0;

  /* unsigned long getURIGeckoFlags (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD GetURIGeckoFlags(nsIURI *aURI, PRUint32 *_retval NS_OUTPARAM) = 0;

  /* void setURIGeckoFlags (in nsIURI aURI, in unsigned long aFlags); */
  NS_SCRIPTABLE NS_IMETHOD SetURIGeckoFlags(nsIURI *aURI, PRUint32 aFlags) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIGlobalHistory3, NS_IGLOBALHISTORY3_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIGLOBALHISTORY3 \
  NS_SCRIPTABLE NS_IMETHOD AddDocumentRedirect(nsIChannel *aOldChannel, nsIChannel *aNewChannel, PRInt32 aFlags, PRBool aTopLevel); \
  NS_SCRIPTABLE NS_IMETHOD GetURIGeckoFlags(nsIURI *aURI, PRUint32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetURIGeckoFlags(nsIURI *aURI, PRUint32 aFlags); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIGLOBALHISTORY3(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddDocumentRedirect(nsIChannel *aOldChannel, nsIChannel *aNewChannel, PRInt32 aFlags, PRBool aTopLevel) { return _to AddDocumentRedirect(aOldChannel, aNewChannel, aFlags, aTopLevel); } \
  NS_SCRIPTABLE NS_IMETHOD GetURIGeckoFlags(nsIURI *aURI, PRUint32 *_retval NS_OUTPARAM) { return _to GetURIGeckoFlags(aURI, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetURIGeckoFlags(nsIURI *aURI, PRUint32 aFlags) { return _to SetURIGeckoFlags(aURI, aFlags); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIGLOBALHISTORY3(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddDocumentRedirect(nsIChannel *aOldChannel, nsIChannel *aNewChannel, PRInt32 aFlags, PRBool aTopLevel) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDocumentRedirect(aOldChannel, aNewChannel, aFlags, aTopLevel); } \
  NS_SCRIPTABLE NS_IMETHOD GetURIGeckoFlags(nsIURI *aURI, PRUint32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURIGeckoFlags(aURI, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetURIGeckoFlags(nsIURI *aURI, PRUint32 aFlags) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetURIGeckoFlags(aURI, aFlags); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsGlobalHistory3 : public nsIGlobalHistory3
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIGLOBALHISTORY3

  nsGlobalHistory3();

private:
  ~nsGlobalHistory3();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsGlobalHistory3, nsIGlobalHistory3)

nsGlobalHistory3::nsGlobalHistory3()
{
  /* member initializers and constructor code */
}

nsGlobalHistory3::~nsGlobalHistory3()
{
  /* destructor code */
}

/* void addDocumentRedirect (in nsIChannel aOldChannel, in nsIChannel aNewChannel, in PRInt32 aFlags, in boolean aTopLevel); */
NS_IMETHODIMP nsGlobalHistory3::AddDocumentRedirect(nsIChannel *aOldChannel, nsIChannel *aNewChannel, PRInt32 aFlags, PRBool aTopLevel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long getURIGeckoFlags (in nsIURI aURI); */
NS_IMETHODIMP nsGlobalHistory3::GetURIGeckoFlags(nsIURI *aURI, PRUint32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setURIGeckoFlags (in nsIURI aURI, in unsigned long aFlags); */
NS_IMETHODIMP nsGlobalHistory3::SetURIGeckoFlags(nsIURI *aURI, PRUint32 aFlags)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIGlobalHistory3_h__ */
