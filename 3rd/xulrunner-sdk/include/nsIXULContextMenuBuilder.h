/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/content/xul/content/public/nsIXULContextMenuBuilder.idl
 */

#ifndef __gen_nsIXULContextMenuBuilder_h__
#define __gen_nsIXULContextMenuBuilder_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocumentFragment; /* forward declaration */


/* starting interface:    nsIXULContextMenuBuilder */
#define NS_IXULCONTEXTMENUBUILDER_IID_STR "f0c35053-14cc-4e23-a9db-f9a68fae8375"

#define NS_IXULCONTEXTMENUBUILDER_IID \
  {0xf0c35053, 0x14cc, 0x4e23, \
    { 0xa9, 0xdb, 0xf9, 0xa6, 0x8f, 0xae, 0x83, 0x75 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIXULContextMenuBuilder : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IXULCONTEXTMENUBUILDER_IID)

  /* void init (in nsIDOMDocumentFragment aDocumentFragment, in AString aGeneratedAttrName, in AString aIdentAttrName); */
  NS_SCRIPTABLE NS_IMETHOD Init(nsIDOMDocumentFragment *aDocumentFragment, const nsAString & aGeneratedAttrName, const nsAString & aIdentAttrName) = 0;

  /* void click (in DOMString aIdent); */
  NS_SCRIPTABLE NS_IMETHOD Click(const nsAString & aIdent) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIXULContextMenuBuilder, NS_IXULCONTEXTMENUBUILDER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIXULCONTEXTMENUBUILDER \
  NS_SCRIPTABLE NS_IMETHOD Init(nsIDOMDocumentFragment *aDocumentFragment, const nsAString & aGeneratedAttrName, const nsAString & aIdentAttrName); \
  NS_SCRIPTABLE NS_IMETHOD Click(const nsAString & aIdent); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIXULCONTEXTMENUBUILDER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(nsIDOMDocumentFragment *aDocumentFragment, const nsAString & aGeneratedAttrName, const nsAString & aIdentAttrName) { return _to Init(aDocumentFragment, aGeneratedAttrName, aIdentAttrName); } \
  NS_SCRIPTABLE NS_IMETHOD Click(const nsAString & aIdent) { return _to Click(aIdent); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIXULCONTEXTMENUBUILDER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(nsIDOMDocumentFragment *aDocumentFragment, const nsAString & aGeneratedAttrName, const nsAString & aIdentAttrName) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(aDocumentFragment, aGeneratedAttrName, aIdentAttrName); } \
  NS_SCRIPTABLE NS_IMETHOD Click(const nsAString & aIdent) { return !_to ? NS_ERROR_NULL_POINTER : _to->Click(aIdent); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsXULContextMenuBuilder : public nsIXULContextMenuBuilder
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIXULCONTEXTMENUBUILDER

  nsXULContextMenuBuilder();

private:
  ~nsXULContextMenuBuilder();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsXULContextMenuBuilder, nsIXULContextMenuBuilder)

nsXULContextMenuBuilder::nsXULContextMenuBuilder()
{
  /* member initializers and constructor code */
}

nsXULContextMenuBuilder::~nsXULContextMenuBuilder()
{
  /* destructor code */
}

/* void init (in nsIDOMDocumentFragment aDocumentFragment, in AString aGeneratedAttrName, in AString aIdentAttrName); */
NS_IMETHODIMP nsXULContextMenuBuilder::Init(nsIDOMDocumentFragment *aDocumentFragment, const nsAString & aGeneratedAttrName, const nsAString & aIdentAttrName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void click (in DOMString aIdent); */
NS_IMETHODIMP nsXULContextMenuBuilder::Click(const nsAString & aIdent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIXULContextMenuBuilder_h__ */
