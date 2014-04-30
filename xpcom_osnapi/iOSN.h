/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM iOSN.idl
 */

#ifndef __gen_iOSN_h__
#define __gen_iOSN_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    iOSNAPI */
#define IOSNAPI_IID_STR "356471e3-be51-45e2-80b6-f492a3f744bc"

#define IOSNAPI_IID \
  {0x356471e3, 0xbe51, 0x45e2, \
    { 0x80, 0xb6, 0xf4, 0x92, 0xa3, 0xf7, 0x44, 0xbc }}

class NS_NO_VTABLE NS_SCRIPTABLE iOSNAPI : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IOSNAPI_IID)

  /* string helloOSNAPI (); */
  NS_SCRIPTABLE NS_IMETHOD HelloOSNAPI(char **_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(iOSNAPI, IOSNAPI_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IOSNAPI \
  NS_SCRIPTABLE NS_IMETHOD HelloOSNAPI(char **_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IOSNAPI(_to) \
  NS_SCRIPTABLE NS_IMETHOD HelloOSNAPI(char **_retval NS_OUTPARAM) { return _to HelloOSNAPI(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IOSNAPI(_to) \
  NS_SCRIPTABLE NS_IMETHOD HelloOSNAPI(char **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->HelloOSNAPI(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public iOSNAPI
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IOSNAPI

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, iOSNAPI)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* string helloOSNAPI (); */
NS_IMETHODIMP _MYCLASS_::HelloOSNAPI(char **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_iOSN_h__ */
