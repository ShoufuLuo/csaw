/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/dom/interfaces/html/nsIDOMNSHTMLOptionCollectn.idl
 */

#ifndef __gen_nsIDOMNSHTMLOptionCollectn_h__
#define __gen_nsIDOMNSHTMLOptionCollectn_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMHTMLOptionElement; /* forward declaration */

class nsIDOMHTMLSelectElement; /* forward declaration */

class nsIVariant; /* forward declaration */


/* starting interface:    nsIDOMNSHTMLOptionCollection */
#define NS_IDOMNSHTMLOPTIONCOLLECTION_IID_STR "03bd61d6-b851-465a-ab3f-99945f77cfa5"

#define NS_IDOMNSHTMLOPTIONCOLLECTION_IID \
  {0x03bd61d6, 0xb851, 0x465a, \
    { 0xab, 0x3f, 0x99, 0x94, 0x5f, 0x77, 0xcf, 0xa5 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDOMNSHTMLOptionCollection : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMNSHTMLOPTIONCOLLECTION_IID)

  /* attribute long selectedIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex) = 0;

  /* [noscript] void setOption (in long index, in nsIDOMHTMLOptionElement option); */
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option) = 0;

  /* [noscript] readonly attribute nsIDOMHTMLSelectElement select; */
  NS_IMETHOD GetSelect(nsIDOMHTMLSelectElement * *aSelect) = 0;

  /* void add (in nsIDOMHTMLOptionElement option, [optional] in nsIVariant before); */
  NS_SCRIPTABLE NS_IMETHOD Add(nsIDOMHTMLOptionElement *option, nsIVariant *before) = 0;

  /* void remove (in long index); */
  NS_SCRIPTABLE NS_IMETHOD Remove(PRInt32 index) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDOMNSHTMLOptionCollection, NS_IDOMNSHTMLOPTIONCOLLECTION_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMNSHTMLOPTIONCOLLECTION \
  NS_SCRIPTABLE NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex); \
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option); \
  NS_IMETHOD GetSelect(nsIDOMHTMLSelectElement * *aSelect); \
  NS_SCRIPTABLE NS_IMETHOD Add(nsIDOMHTMLOptionElement *option, nsIVariant *before); \
  NS_SCRIPTABLE NS_IMETHOD Remove(PRInt32 index); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMNSHTMLOPTIONCOLLECTION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex) { return _to GetSelectedIndex(aSelectedIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex) { return _to SetSelectedIndex(aSelectedIndex); } \
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option) { return _to SetOption(index, option); } \
  NS_IMETHOD GetSelect(nsIDOMHTMLSelectElement * *aSelect) { return _to GetSelect(aSelect); } \
  NS_SCRIPTABLE NS_IMETHOD Add(nsIDOMHTMLOptionElement *option, nsIVariant *before) { return _to Add(option, before); } \
  NS_SCRIPTABLE NS_IMETHOD Remove(PRInt32 index) { return _to Remove(index); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMNSHTMLOPTIONCOLLECTION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSelectedIndex(aSelectedIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSelectedIndex(aSelectedIndex); } \
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOption(index, option); } \
  NS_IMETHOD GetSelect(nsIDOMHTMLSelectElement * *aSelect) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSelect(aSelect); } \
  NS_SCRIPTABLE NS_IMETHOD Add(nsIDOMHTMLOptionElement *option, nsIVariant *before) { return !_to ? NS_ERROR_NULL_POINTER : _to->Add(option, before); } \
  NS_SCRIPTABLE NS_IMETHOD Remove(PRInt32 index) { return !_to ? NS_ERROR_NULL_POINTER : _to->Remove(index); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMNSHTMLOptionCollection : public nsIDOMNSHTMLOptionCollection
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMNSHTMLOPTIONCOLLECTION

  nsDOMNSHTMLOptionCollection();

private:
  ~nsDOMNSHTMLOptionCollection();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMNSHTMLOptionCollection, nsIDOMNSHTMLOptionCollection)

nsDOMNSHTMLOptionCollection::nsDOMNSHTMLOptionCollection()
{
  /* member initializers and constructor code */
}

nsDOMNSHTMLOptionCollection::~nsDOMNSHTMLOptionCollection()
{
  /* destructor code */
}

/* attribute long selectedIndex; */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::GetSelectedIndex(PRInt32 *aSelectedIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::SetSelectedIndex(PRInt32 aSelectedIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void setOption (in long index, in nsIDOMHTMLOptionElement option); */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] readonly attribute nsIDOMHTMLSelectElement select; */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::GetSelect(nsIDOMHTMLSelectElement * *aSelect)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void add (in nsIDOMHTMLOptionElement option, [optional] in nsIVariant before); */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::Add(nsIDOMHTMLOptionElement *option, nsIVariant *before)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void remove (in long index); */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::Remove(PRInt32 index)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMNSHTMLOptionCollectn_h__ */
