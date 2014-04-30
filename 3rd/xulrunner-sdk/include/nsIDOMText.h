/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/core/nsIDOMText.idl
 */

#ifndef __gen_nsIDOMText_h__
#define __gen_nsIDOMText_h__


#ifndef __gen_nsIDOMCharacterData_h__
#include "nsIDOMCharacterData.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMText */
#define NS_IDOMTEXT_IID_STR "04a1ec2b-491f-4a80-8db4-694c37e31a6f"

#define NS_IDOMTEXT_IID \
  {0x04a1ec2b, 0x491f, 0x4a80, \
    { 0x8d, 0xb4, 0x69, 0x4c, 0x37, 0xe3, 0x1a, 0x6f }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMText : public nsIDOMCharacterData {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMTEXT_IID)

  /* nsIDOMText splitText (in unsigned long offset) raises (DOMException); */
  NS_SCRIPTABLE NS_IMETHOD SplitText(PRUint32 offset, nsIDOMText * *_retval NS_OUTPARAM) = 0;

  /* readonly attribute boolean isElementContentWhitespace; */
  NS_SCRIPTABLE NS_IMETHOD GetIsElementContentWhitespace(PRBool *aIsElementContentWhitespace) = 0;

  /* readonly attribute DOMString wholeText; */
  NS_SCRIPTABLE NS_IMETHOD GetWholeText(nsAString & aWholeText) = 0;

  /* nsIDOMText replaceWholeText (in DOMString content) raises (DOMException); */
  NS_SCRIPTABLE NS_IMETHOD ReplaceWholeText(const nsAString & content, nsIDOMText * *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMText, NS_IDOMTEXT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMTEXT \
  NS_SCRIPTABLE NS_IMETHOD SplitText(PRUint32 offset, nsIDOMText * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetIsElementContentWhitespace(PRBool *aIsElementContentWhitespace); \
  NS_SCRIPTABLE NS_IMETHOD GetWholeText(nsAString & aWholeText); \
  NS_SCRIPTABLE NS_IMETHOD ReplaceWholeText(const nsAString & content, nsIDOMText * *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMTEXT(_to) \
  NS_SCRIPTABLE NS_IMETHOD SplitText(PRUint32 offset, nsIDOMText * *_retval NS_OUTPARAM) { return _to SplitText(offset, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsElementContentWhitespace(PRBool *aIsElementContentWhitespace) { return _to GetIsElementContentWhitespace(aIsElementContentWhitespace); } \
  NS_SCRIPTABLE NS_IMETHOD GetWholeText(nsAString & aWholeText) { return _to GetWholeText(aWholeText); } \
  NS_SCRIPTABLE NS_IMETHOD ReplaceWholeText(const nsAString & content, nsIDOMText * *_retval NS_OUTPARAM) { return _to ReplaceWholeText(content, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMTEXT(_to) \
  NS_SCRIPTABLE NS_IMETHOD SplitText(PRUint32 offset, nsIDOMText * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SplitText(offset, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsElementContentWhitespace(PRBool *aIsElementContentWhitespace) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsElementContentWhitespace(aIsElementContentWhitespace); } \
  NS_SCRIPTABLE NS_IMETHOD GetWholeText(nsAString & aWholeText) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWholeText(aWholeText); } \
  NS_SCRIPTABLE NS_IMETHOD ReplaceWholeText(const nsAString & content, nsIDOMText * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReplaceWholeText(content, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMText : public nsIDOMText
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMTEXT

  nsDOMText();

private:
  ~nsDOMText();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMText, nsIDOMText)

nsDOMText::nsDOMText()
{
  /* member initializers and constructor code */
}

nsDOMText::~nsDOMText()
{
  /* destructor code */
}

/* nsIDOMText splitText (in unsigned long offset) raises (DOMException); */
NS_IMETHODIMP nsDOMText::SplitText(PRUint32 offset, nsIDOMText * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean isElementContentWhitespace; */
NS_IMETHODIMP nsDOMText::GetIsElementContentWhitespace(PRBool *aIsElementContentWhitespace)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute DOMString wholeText; */
NS_IMETHODIMP nsDOMText::GetWholeText(nsAString & aWholeText)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMText replaceWholeText (in DOMString content) raises (DOMException); */
NS_IMETHODIMP nsDOMText::ReplaceWholeText(const nsAString & content, nsIDOMText * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMText_h__ */
