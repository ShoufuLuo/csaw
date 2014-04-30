/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/events/nsIDOMPageTransitionEvent.idl
 */

#ifndef __gen_nsIDOMPageTransitionEvent_h__
#define __gen_nsIDOMPageTransitionEvent_h__


#ifndef __gen_nsIDOMEvent_h__
#include "nsIDOMEvent.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMPageTransitionEvent */
#define NS_IDOMPAGETRANSITIONEVENT_IID_STR "b712418b-376f-4f75-b156-5d9ad99fe51f"

#define NS_IDOMPAGETRANSITIONEVENT_IID \
  {0xb712418b, 0x376f, 0x4f75, \
    { 0xb1, 0x56, 0x5d, 0x9a, 0xd9, 0x9f, 0xe5, 0x1f }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMPageTransitionEvent : public nsIDOMEvent {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMPAGETRANSITIONEVENT_IID)

  /* readonly attribute boolean persisted; */
  NS_SCRIPTABLE NS_IMETHOD GetPersisted(PRBool *aPersisted) = 0;

  /* void initPageTransitionEvent (in DOMString typeArg, in boolean canBubbleArg, in boolean canCancelArg, in boolean persisted); */
  NS_SCRIPTABLE NS_IMETHOD InitPageTransitionEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool canCancelArg, PRBool persisted) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMPageTransitionEvent, NS_IDOMPAGETRANSITIONEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMPAGETRANSITIONEVENT \
  NS_SCRIPTABLE NS_IMETHOD GetPersisted(PRBool *aPersisted); \
  NS_SCRIPTABLE NS_IMETHOD InitPageTransitionEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool canCancelArg, PRBool persisted); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMPAGETRANSITIONEVENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetPersisted(PRBool *aPersisted) { return _to GetPersisted(aPersisted); } \
  NS_SCRIPTABLE NS_IMETHOD InitPageTransitionEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool canCancelArg, PRBool persisted) { return _to InitPageTransitionEvent(typeArg, canBubbleArg, canCancelArg, persisted); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMPAGETRANSITIONEVENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetPersisted(PRBool *aPersisted) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPersisted(aPersisted); } \
  NS_SCRIPTABLE NS_IMETHOD InitPageTransitionEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool canCancelArg, PRBool persisted) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitPageTransitionEvent(typeArg, canBubbleArg, canCancelArg, persisted); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMPageTransitionEvent : public nsIDOMPageTransitionEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMPAGETRANSITIONEVENT

  nsDOMPageTransitionEvent();

private:
  ~nsDOMPageTransitionEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMPageTransitionEvent, nsIDOMPageTransitionEvent)

nsDOMPageTransitionEvent::nsDOMPageTransitionEvent()
{
  /* member initializers and constructor code */
}

nsDOMPageTransitionEvent::~nsDOMPageTransitionEvent()
{
  /* destructor code */
}

/* readonly attribute boolean persisted; */
NS_IMETHODIMP nsDOMPageTransitionEvent::GetPersisted(PRBool *aPersisted)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void initPageTransitionEvent (in DOMString typeArg, in boolean canBubbleArg, in boolean canCancelArg, in boolean persisted); */
NS_IMETHODIMP nsDOMPageTransitionEvent::InitPageTransitionEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool canCancelArg, PRBool persisted)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMPageTransitionEvent_h__ */