/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/html/nsIDOMHTMLMenuItemElement.idl
 */

#ifndef __gen_nsIDOMHTMLMenuItemElement_h__
#define __gen_nsIDOMHTMLMenuItemElement_h__


#ifndef __gen_nsIDOMHTMLCommandElement_h__
#include "nsIDOMHTMLCommandElement.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMHTMLMenuItemElement */
#define NS_IDOMHTMLMENUITEMELEMENT_IID_STR "613f28ee-01f5-42dc-8224-161f85f0f20b"

#define NS_IDOMHTMLMENUITEMELEMENT_IID \
  {0x613f28ee, 0x01f5, 0x42dc, \
    { 0x82, 0x24, 0x16, 0x1f, 0x85, 0xf0, 0xf2, 0x0b }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMHTMLMenuItemElement : public nsIDOMHTMLCommandElement {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMHTMLMENUITEMELEMENT_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMHTMLMenuItemElement, NS_IDOMHTMLMENUITEMELEMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMHTMLMENUITEMELEMENT \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMHTMLMENUITEMELEMENT(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMHTMLMENUITEMELEMENT(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMHTMLMenuItemElement : public nsIDOMHTMLMenuItemElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMHTMLMENUITEMELEMENT

  nsDOMHTMLMenuItemElement();

private:
  ~nsDOMHTMLMenuItemElement();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMHTMLMenuItemElement, nsIDOMHTMLMenuItemElement)

nsDOMHTMLMenuItemElement::nsDOMHTMLMenuItemElement()
{
  /* member initializers and constructor code */
}

nsDOMHTMLMenuItemElement::~nsDOMHTMLMenuItemElement()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMHTMLMenuItemElement_h__ */
