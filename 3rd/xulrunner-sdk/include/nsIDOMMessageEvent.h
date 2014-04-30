/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/events/nsIDOMMessageEvent.idl
 */

#ifndef __gen_nsIDOMMessageEvent_h__
#define __gen_nsIDOMMessageEvent_h__


#ifndef __gen_nsIDOMEvent_h__
#include "nsIDOMEvent.h"
#endif

#include "jspubtd.h"

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMMessageEvent */
#define NS_IDOMMESSAGEEVENT_IID_STR "dc8ec5c6-ebf2-4f95-be99-cd13e3c0d0c6"

#define NS_IDOMMESSAGEEVENT_IID \
  {0xdc8ec5c6, 0xebf2, 0x4f95, \
    { 0xbe, 0x99, 0xcd, 0x13, 0xe3, 0xc0, 0xd0, 0xc6 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMMessageEvent : public nsIDOMEvent {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMMESSAGEEVENT_IID)

  /* readonly attribute jsval data; */
  NS_SCRIPTABLE NS_IMETHOD GetData(jsval *aData) = 0;

  /* readonly attribute DOMString origin; */
  NS_SCRIPTABLE NS_IMETHOD GetOrigin(nsAString & aOrigin) = 0;

  /* readonly attribute DOMString lastEventId; */
  NS_SCRIPTABLE NS_IMETHOD GetLastEventId(nsAString & aLastEventId) = 0;

  /* readonly attribute nsIDOMWindow source; */
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsIDOMWindow * *aSource) = 0;

  /* void initMessageEvent (in DOMString aType, in boolean aCanBubble, in boolean aCancelable, in jsval aData, in DOMString aOrigin, in DOMString aLastEventId, in nsIDOMWindow aSource); */
  NS_SCRIPTABLE NS_IMETHOD InitMessageEvent(const nsAString & aType, PRBool aCanBubble, PRBool aCancelable, const jsval & aData, const nsAString & aOrigin, const nsAString & aLastEventId, nsIDOMWindow *aSource) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMMessageEvent, NS_IDOMMESSAGEEVENT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMMESSAGEEVENT \
  NS_SCRIPTABLE NS_IMETHOD GetData(jsval *aData); \
  NS_SCRIPTABLE NS_IMETHOD GetOrigin(nsAString & aOrigin); \
  NS_SCRIPTABLE NS_IMETHOD GetLastEventId(nsAString & aLastEventId); \
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsIDOMWindow * *aSource); \
  NS_SCRIPTABLE NS_IMETHOD InitMessageEvent(const nsAString & aType, PRBool aCanBubble, PRBool aCancelable, const jsval & aData, const nsAString & aOrigin, const nsAString & aLastEventId, nsIDOMWindow *aSource); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMMESSAGEEVENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetData(jsval *aData) { return _to GetData(aData); } \
  NS_SCRIPTABLE NS_IMETHOD GetOrigin(nsAString & aOrigin) { return _to GetOrigin(aOrigin); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastEventId(nsAString & aLastEventId) { return _to GetLastEventId(aLastEventId); } \
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsIDOMWindow * *aSource) { return _to GetSource(aSource); } \
  NS_SCRIPTABLE NS_IMETHOD InitMessageEvent(const nsAString & aType, PRBool aCanBubble, PRBool aCancelable, const jsval & aData, const nsAString & aOrigin, const nsAString & aLastEventId, nsIDOMWindow *aSource) { return _to InitMessageEvent(aType, aCanBubble, aCancelable, aData, aOrigin, aLastEventId, aSource); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMMESSAGEEVENT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetData(jsval *aData) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetData(aData); } \
  NS_SCRIPTABLE NS_IMETHOD GetOrigin(nsAString & aOrigin) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOrigin(aOrigin); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastEventId(nsAString & aLastEventId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastEventId(aLastEventId); } \
  NS_SCRIPTABLE NS_IMETHOD GetSource(nsIDOMWindow * *aSource) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSource(aSource); } \
  NS_SCRIPTABLE NS_IMETHOD InitMessageEvent(const nsAString & aType, PRBool aCanBubble, PRBool aCancelable, const jsval & aData, const nsAString & aOrigin, const nsAString & aLastEventId, nsIDOMWindow *aSource) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitMessageEvent(aType, aCanBubble, aCancelable, aData, aOrigin, aLastEventId, aSource); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMMessageEvent : public nsIDOMMessageEvent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMMESSAGEEVENT

  nsDOMMessageEvent();

private:
  ~nsDOMMessageEvent();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMMessageEvent, nsIDOMMessageEvent)

nsDOMMessageEvent::nsDOMMessageEvent()
{
  /* member initializers and constructor code */
}

nsDOMMessageEvent::~nsDOMMessageEvent()
{
  /* destructor code */
}

/* readonly attribute jsval data; */
NS_IMETHODIMP nsDOMMessageEvent::GetData(jsval *aData)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString origin; */
NS_IMETHODIMP nsDOMMessageEvent::GetOrigin(nsAString & aOrigin)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString lastEventId; */
NS_IMETHODIMP nsDOMMessageEvent::GetLastEventId(nsAString & aLastEventId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMWindow source; */
NS_IMETHODIMP nsDOMMessageEvent::GetSource(nsIDOMWindow * *aSource)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void initMessageEvent (in DOMString aType, in boolean aCanBubble, in boolean aCancelable, in jsval aData, in DOMString aOrigin, in DOMString aLastEventId, in nsIDOMWindow aSource); */
NS_IMETHODIMP nsDOMMessageEvent::InitMessageEvent(const nsAString & aType, PRBool aCanBubble, PRBool aCancelable, const jsval & aData, const nsAString & aOrigin, const nsAString & aLastEventId, nsIDOMWindow *aSource)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMMessageEvent_h__ */
