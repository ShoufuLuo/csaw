/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM ihelloxpcom.idl
 */

#ifndef __gen_ihelloxpcom_h__
#define __gen_ihelloxpcom_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    ihelloxpcom */
#define IHELLOXPCOM_IID_STR "f3774746-ff48-ff28-adc9-cee3e5cef5a5"

#define IHELLOXPCOM_IID \
  {0xf3774746, 0xff48, 0xff28, \
    { 0xad, 0xc9, 0xce, 0xe3, 0xe5, 0xce, 0xf5, 0xa5 }}

class NS_NO_VTABLE NS_SCRIPTABLE ihelloxpcom : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IHELLOXPCOM_IID)

  /* long multiple (in long a, in long b); */
  NS_SCRIPTABLE NS_IMETHOD Multiple(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(ihelloxpcom, IHELLOXPCOM_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IHELLOXPCOM \
  NS_SCRIPTABLE NS_IMETHOD Multiple(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IHELLOXPCOM(_to) \
  NS_SCRIPTABLE NS_IMETHOD Multiple(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return _to Multiple(a, b, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IHELLOXPCOM(_to) \
  NS_SCRIPTABLE NS_IMETHOD Multiple(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Multiple(a, b, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public ihelloxpcom
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IHELLOXPCOM

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, ihelloxpcom)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* long multiple (in long a, in long b); */
NS_IMETHODIMP _MYCLASS_::Multiple(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_ihelloxpcom_h__ */
