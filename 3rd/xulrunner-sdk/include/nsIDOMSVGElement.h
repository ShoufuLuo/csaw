/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/svg/nsIDOMSVGElement.idl
 */

#ifndef __gen_nsIDOMSVGElement_h__
#define __gen_nsIDOMSVGElement_h__


#ifndef __gen_nsIDOMElement_h__
#include "nsIDOMElement.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMSVGSVGElement; /* forward declaration */


/* starting interface:    nsIDOMSVGElement */
#define NS_IDOMSVGELEMENT_IID_STR "c358d048-be72-4d39-93dc-0e85b8c9f07b"

#define NS_IDOMSVGELEMENT_IID \
  {0xc358d048, 0xbe72, 0x4d39, \
    { 0x93, 0xdc, 0x0e, 0x85, 0xb8, 0xc9, 0xf0, 0x7b }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMSVGElement : public nsIDOMElement {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMSVGELEMENT_IID)

  /* attribute DOMString id; */
  NS_SCRIPTABLE NS_IMETHOD GetId(nsAString & aId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetId(const nsAString & aId) = 0;

  /* readonly attribute nsIDOMSVGSVGElement ownerSVGElement; */
  NS_SCRIPTABLE NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGSVGElement * *aOwnerSVGElement) = 0;

  /* readonly attribute nsIDOMSVGElement viewportElement; */
  NS_SCRIPTABLE NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMSVGElement, NS_IDOMSVGELEMENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMSVGELEMENT \
  NS_SCRIPTABLE NS_IMETHOD GetId(nsAString & aId); \
  NS_SCRIPTABLE NS_IMETHOD SetId(const nsAString & aId); \
  NS_SCRIPTABLE NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGSVGElement * *aOwnerSVGElement); \
  NS_SCRIPTABLE NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMSVGELEMENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(nsAString & aId) { return _to GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(const nsAString & aId) { return _to SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGSVGElement * *aOwnerSVGElement) { return _to GetOwnerSVGElement(aOwnerSVGElement); } \
  NS_SCRIPTABLE NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement) { return _to GetViewportElement(aViewportElement); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMSVGELEMENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(nsAString & aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(const nsAString & aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetOwnerSVGElement(nsIDOMSVGSVGElement * *aOwnerSVGElement) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOwnerSVGElement(aOwnerSVGElement); } \
  NS_SCRIPTABLE NS_IMETHOD GetViewportElement(nsIDOMSVGElement * *aViewportElement) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetViewportElement(aViewportElement); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMSVGElement : public nsIDOMSVGElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMSVGELEMENT

  nsDOMSVGElement();

private:
  ~nsDOMSVGElement();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMSVGElement, nsIDOMSVGElement)

nsDOMSVGElement::nsDOMSVGElement()
{
  /* member initializers and constructor code */
}

nsDOMSVGElement::~nsDOMSVGElement()
{
  /* destructor code */
}

/* attribute DOMString id; */
NS_IMETHODIMP nsDOMSVGElement::GetId(nsAString & aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMSVGElement::SetId(const nsAString & aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMSVGSVGElement ownerSVGElement; */
NS_IMETHODIMP nsDOMSVGElement::GetOwnerSVGElement(nsIDOMSVGSVGElement * *aOwnerSVGElement)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMSVGElement viewportElement; */
NS_IMETHODIMP nsDOMSVGElement::GetViewportElement(nsIDOMSVGElement * *aViewportElement)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMSVGElement_h__ */
