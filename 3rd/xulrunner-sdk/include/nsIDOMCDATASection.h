/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/core/nsIDOMCDATASection.idl
 */

#ifndef __gen_nsIDOMCDATASection_h__
#define __gen_nsIDOMCDATASection_h__


#ifndef __gen_nsIDOMText_h__
#include "nsIDOMText.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMCDATASection */
#define NS_IDOMCDATASECTION_IID_STR "f1eea89d-8af3-4c2a-90df-6c3a75cb5005"

#define NS_IDOMCDATASECTION_IID \
  {0xf1eea89d, 0x8af3, 0x4c2a, \
    { 0x90, 0xdf, 0x6c, 0x3a, 0x75, 0xcb, 0x50, 0x05 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMCDATASection : public nsIDOMText {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMCDATASECTION_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMCDATASection, NS_IDOMCDATASECTION_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMCDATASECTION \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMCDATASECTION(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMCDATASECTION(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMCDATASection : public nsIDOMCDATASection
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMCDATASECTION

  nsDOMCDATASection();

private:
  ~nsDOMCDATASection();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMCDATASection, nsIDOMCDATASection)

nsDOMCDATASection::nsDOMCDATASection()
{
  /* member initializers and constructor code */
}

nsDOMCDATASection::~nsDOMCDATASection()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMCDATASection_h__ */
