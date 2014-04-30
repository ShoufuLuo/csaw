/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/core/nsIDOMXMLDocument.idl
 */

#ifndef __gen_nsIDOMXMLDocument_h__
#define __gen_nsIDOMXMLDocument_h__


#ifndef __gen_nsIDOMDocument_h__
#include "nsIDOMDocument.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMXMLDocument */
#define NS_IDOMXMLDOCUMENT_IID_STR "f97b36ff-425f-4c87-b6dc-fcfcfb4d5c77"

#define NS_IDOMXMLDOCUMENT_IID \
  {0xf97b36ff, 0x425f, 0x4c87, \
    { 0xb6, 0xdc, 0xfc, 0xfc, 0xfb, 0x4d, 0x5c, 0x77 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMXMLDocument : public nsIDOMDocument {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMXMLDOCUMENT_IID)

  /* attribute boolean async; */
  NS_SCRIPTABLE NS_IMETHOD GetAsync(PRBool *aAsync) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetAsync(PRBool aAsync) = 0;

  /* boolean load (in DOMString url); */
  NS_SCRIPTABLE NS_IMETHOD Load(const nsAString & url, PRBool *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMXMLDocument, NS_IDOMXMLDOCUMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMXMLDOCUMENT \
  NS_SCRIPTABLE NS_IMETHOD GetAsync(PRBool *aAsync); \
  NS_SCRIPTABLE NS_IMETHOD SetAsync(PRBool aAsync); \
  NS_SCRIPTABLE NS_IMETHOD Load(const nsAString & url, PRBool *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMXMLDOCUMENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetAsync(PRBool *aAsync) { return _to GetAsync(aAsync); } \
  NS_SCRIPTABLE NS_IMETHOD SetAsync(PRBool aAsync) { return _to SetAsync(aAsync); } \
  NS_SCRIPTABLE NS_IMETHOD Load(const nsAString & url, PRBool *_retval NS_OUTPARAM) { return _to Load(url, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMXMLDOCUMENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetAsync(PRBool *aAsync) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAsync(aAsync); } \
  NS_SCRIPTABLE NS_IMETHOD SetAsync(PRBool aAsync) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAsync(aAsync); } \
  NS_SCRIPTABLE NS_IMETHOD Load(const nsAString & url, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Load(url, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMXMLDocument : public nsIDOMXMLDocument
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMXMLDOCUMENT

  nsDOMXMLDocument();

private:
  ~nsDOMXMLDocument();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMXMLDocument, nsIDOMXMLDocument)

nsDOMXMLDocument::nsDOMXMLDocument()
{
  /* member initializers and constructor code */
}

nsDOMXMLDocument::~nsDOMXMLDocument()
{
  /* destructor code */
}

/* attribute boolean async; */
NS_IMETHODIMP nsDOMXMLDocument::GetAsync(PRBool *aAsync)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMXMLDocument::SetAsync(PRBool aAsync)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean load (in DOMString url); */
NS_IMETHODIMP nsDOMXMLDocument::Load(const nsAString & url, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMXMLDocument_h__ */
