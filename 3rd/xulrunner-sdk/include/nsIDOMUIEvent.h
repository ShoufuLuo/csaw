/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/events/nsIDOMUIEvent.idl
 */

#ifndef __gen_nsIDOMUIEvent_h__
#define __gen_nsIDOMUIEvent_h__


#ifndef __gen_nsIDOMEvent_h__
#include "nsIDOMEvent.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMUIEvent */
#define NS_IDOMUIEVENT_IID_STR "25f28689-3f78-47e8-8d76-15b936faf8c1"

#define NS_IDOMUIEVENT_IID \
  {0x25f28689, 0x3f78, 0x47e8, \
    { 0x8d, 0x76, 0x15, 0xb9, 0x36, 0xfa, 0xf8, 0xc1 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMUIEvent : public nsIDOMEvent {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMUIEVENT_IID)

  /* readonly attribute nsIDOMWindow view; */
  NS_SCRIPTABLE NS_IMETHOD GetView(nsIDOMWindow * *aView) = 0;

  /* readonly attribute long detail; */
  NS_SCRIPTABLE NS_IMETHOD GetDetail(PRInt32 *aDetail) = 0;

  /* void initUIEvent (in DOMString typeArg, in boolean canBubbleArg, in boolean cancelableArg, in nsIDOMWindow viewArg, in long detailArg); */
  NS_SCRIPTABLE NS_IMETHOD InitUIEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool cancelableArg, nsIDOMWindow *viewArg, PRInt32 detailArg) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMUIEvent, NS_IDOMUIEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMUIEVENT \
  NS_SCRIPTABLE NS_IMETHOD GetView(nsIDOMWindow * *aView); \
  NS_SCRIPTABLE NS_IMETHOD GetDetail(PRInt32 *aDetail); \
  NS_SCRIPTABLE NS_IMETHOD InitUIEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool cancelableArg, nsIDOMWindow *viewArg, PRInt32 detailArg); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMUIEVENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetView(nsIDOMWindow * *aView) { return _to GetView(aView); } \
  NS_SCRIPTABLE NS_IMETHOD GetDetail(PRInt32 *aDetail) { return _to GetDetail(aDetail); } \
  NS_SCRIPTABLE NS_IMETHOD InitUIEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool cancelableArg, nsIDOMWindow *viewArg, PRInt32 detailArg) { return _to InitUIEvent(typeArg, canBubbleArg, cancelableArg, viewArg, detailArg); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMUIEVENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetView(nsIDOMWindow * *aView) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetView(aView); } \
  NS_SCRIPTABLE NS_IMETHOD GetDetail(PRInt32 *aDetail) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDetail(aDetail); } \
  NS_SCRIPTABLE NS_IMETHOD InitUIEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool cancelableArg, nsIDOMWindow *viewArg, PRInt32 detailArg) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitUIEvent(typeArg, canBubbleArg, cancelableArg, viewArg, detailArg); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMUIEvent : public nsIDOMUIEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMUIEVENT

  nsDOMUIEvent();

private:
  ~nsDOMUIEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMUIEvent, nsIDOMUIEvent)

nsDOMUIEvent::nsDOMUIEvent()
{
  /* member initializers and constructor code */
}

nsDOMUIEvent::~nsDOMUIEvent()
{
  /* destructor code */
}

/* readonly attribute nsIDOMWindow view; */
NS_IMETHODIMP nsDOMUIEvent::GetView(nsIDOMWindow * *aView)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long detail; */
NS_IMETHODIMP nsDOMUIEvent::GetDetail(PRInt32 *aDetail)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void initUIEvent (in DOMString typeArg, in boolean canBubbleArg, in boolean cancelableArg, in nsIDOMWindow viewArg, in long detailArg); */
NS_IMETHODIMP nsDOMUIEvent::InitUIEvent(const nsAString & typeArg, PRBool canBubbleArg, PRBool cancelableArg, nsIDOMWindow *viewArg, PRInt32 detailArg)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMUIEvent_h__ */
