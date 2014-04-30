/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM iChimeraRider.idl
 */

#ifndef __gen_iChimeraRider_h__
#define __gen_iChimeraRider_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    iQueryCmmtCB */
#define IQUERYCMMTCB_IID_STR "caa85635-2700-4354-8e6d-95dd0d2ab433"

#define IQUERYCMMTCB_IID \
  {0xcaa85635, 0x2700, 0x4354, \
    { 0x8e, 0x6d, 0x95, 0xdd, 0x0d, 0x2a, 0xb4, 0x33 }}

class NS_NO_VTABLE NS_SCRIPTABLE iQueryCmmtCB : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IQUERYCMMTCB_IID)

  /* void showCmmts (); */
  NS_SCRIPTABLE NS_IMETHOD ShowCmmts(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(iQueryCmmtCB, IQUERYCMMTCB_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IQUERYCMMTCB \
  NS_SCRIPTABLE NS_IMETHOD ShowCmmts(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IQUERYCMMTCB(_to) \
  NS_SCRIPTABLE NS_IMETHOD ShowCmmts(void) { return _to ShowCmmts(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IQUERYCMMTCB(_to) \
  NS_SCRIPTABLE NS_IMETHOD ShowCmmts(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowCmmts(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public iQueryCmmtCB
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IQUERYCMMTCB

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, iQueryCmmtCB)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void showCmmts (); */
NS_IMETHODIMP _MYCLASS_::ShowCmmts()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    iChimeraRider */
#define ICHIMERARIDER_IID_STR "9361ffe4-bdbd-4c69-ac73-da477b32ce43"

#define ICHIMERARIDER_IID \
  {0x9361ffe4, 0xbdbd, 0x4c69, \
    { 0xac, 0x73, 0xda, 0x47, 0x7b, 0x32, 0xce, 0x43 }}

class NS_NO_VTABLE NS_SCRIPTABLE iChimeraRider : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(ICHIMERARIDER_IID)

  /* void submitComment (in string url, in string author, in string content, in long inherit, in long permission); */
  NS_SCRIPTABLE NS_IMETHOD SubmitComment(const char *url, const char *author, const char *content, PRInt32 inherit, PRInt32 permission) = 0;

  /* void queryCmmtsbyURL (in string url, in iQueryCmmtCB func); */
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURL(const char *url, iQueryCmmtCB *func) = 0;

  /* void queryCmmtsbyURLAuthor (in string url, in string author, in iQueryCmmtCB func); */
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLAuthor(const char *url, const char *author, iQueryCmmtCB *func) = 0;

  /* void queryCmmtsbyURLKeyword (in string url, in string keyword, in iQueryCmmtCB func); */
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLKeyword(const char *url, const char *keyword, iQueryCmmtCB *func) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(iChimeraRider, ICHIMERARIDER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_ICHIMERARIDER \
  NS_SCRIPTABLE NS_IMETHOD SubmitComment(const char *url, const char *author, const char *content, PRInt32 inherit, PRInt32 permission); \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURL(const char *url, iQueryCmmtCB *func); \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLAuthor(const char *url, const char *author, iQueryCmmtCB *func); \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLKeyword(const char *url, const char *keyword, iQueryCmmtCB *func); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_ICHIMERARIDER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SubmitComment(const char *url, const char *author, const char *content, PRInt32 inherit, PRInt32 permission) { return _to SubmitComment(url, author, content, inherit, permission); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURL(const char *url, iQueryCmmtCB *func) { return _to QueryCmmtsbyURL(url, func); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLAuthor(const char *url, const char *author, iQueryCmmtCB *func) { return _to QueryCmmtsbyURLAuthor(url, author, func); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLKeyword(const char *url, const char *keyword, iQueryCmmtCB *func) { return _to QueryCmmtsbyURLKeyword(url, keyword, func); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_ICHIMERARIDER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SubmitComment(const char *url, const char *author, const char *content, PRInt32 inherit, PRInt32 permission) { return !_to ? NS_ERROR_NULL_POINTER : _to->SubmitComment(url, author, content, inherit, permission); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURL(const char *url, iQueryCmmtCB *func) { return !_to ? NS_ERROR_NULL_POINTER : _to->QueryCmmtsbyURL(url, func); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLAuthor(const char *url, const char *author, iQueryCmmtCB *func) { return !_to ? NS_ERROR_NULL_POINTER : _to->QueryCmmtsbyURLAuthor(url, author, func); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCmmtsbyURLKeyword(const char *url, const char *keyword, iQueryCmmtCB *func) { return !_to ? NS_ERROR_NULL_POINTER : _to->QueryCmmtsbyURLKeyword(url, keyword, func); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public iChimeraRider
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_ICHIMERARIDER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, iChimeraRider)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void submitComment (in string url, in string author, in string content, in long inherit, in long permission); */
NS_IMETHODIMP _MYCLASS_::SubmitComment(const char *url, const char *author, const char *content, PRInt32 inherit, PRInt32 permission)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void queryCmmtsbyURL (in string url, in iQueryCmmtCB func); */
NS_IMETHODIMP _MYCLASS_::QueryCmmtsbyURL(const char *url, iQueryCmmtCB *func)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void queryCmmtsbyURLAuthor (in string url, in string author, in iQueryCmmtCB func); */
NS_IMETHODIMP _MYCLASS_::QueryCmmtsbyURLAuthor(const char *url, const char *author, iQueryCmmtCB *func)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void queryCmmtsbyURLKeyword (in string url, in string keyword, in iQueryCmmtCB func); */
NS_IMETHODIMP _MYCLASS_::QueryCmmtsbyURLKeyword(const char *url, const char *keyword, iQueryCmmtCB *func)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_iChimeraRider_h__ */
