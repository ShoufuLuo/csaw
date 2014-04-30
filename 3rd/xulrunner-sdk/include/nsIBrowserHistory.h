/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/toolkit/components/places/nsIBrowserHistory.idl
 */

#ifndef __gen_nsIBrowserHistory_h__
#define __gen_nsIBrowserHistory_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIGlobalHistory2_h__
#include "nsIGlobalHistory2.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIBrowserHistory */
#define NS_IBROWSERHISTORY_IID_STR "540aca25-1e01-467f-b24c-df89cbe40f8d"

#define NS_IBROWSERHISTORY_IID \
  {0x540aca25, 0x1e01, 0x467f, \
    { 0xb2, 0x4c, 0xdf, 0x89, 0xcb, 0xe4, 0x0f, 0x8d }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIBrowserHistory : public nsIGlobalHistory2 {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IBROWSERHISTORY_IID)

  /* void addPageWithDetails (in nsIURI aURI, in wstring aTitle, in long long aLastVisited); */
  NS_SCRIPTABLE NS_IMETHOD AddPageWithDetails(nsIURI *aURI, const PRUnichar * aTitle, PRInt64 aLastVisited) = 0;

  /* readonly attribute AUTF8String lastPageVisited; */
  NS_SCRIPTABLE NS_IMETHOD GetLastPageVisited(nsACString & aLastPageVisited) = 0;

  /* readonly attribute PRUint32 count; */
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRUint32 *aCount) = 0;

  /* void removePage (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD RemovePage(nsIURI *aURI) = 0;

  /* void removePages ([array, size_is (aLength)] in nsIURI aURIs, in unsigned long aLength, in boolean aDoBatchNotify); */
  NS_SCRIPTABLE NS_IMETHOD RemovePages(nsIURI **aURIs, PRUint32 aLength, PRBool aDoBatchNotify) = 0;

  /* void removePagesFromHost (in AUTF8String aHost, in boolean aEntireDomain); */
  NS_SCRIPTABLE NS_IMETHOD RemovePagesFromHost(const nsACString & aHost, PRBool aEntireDomain) = 0;

  /* void removePagesByTimeframe (in long long aBeginTime, in long long aEndTime); */
  NS_SCRIPTABLE NS_IMETHOD RemovePagesByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime) = 0;

  /* void removeVisitsByTimeframe (in long long aBeginTime, in long long aEndTime); */
  NS_SCRIPTABLE NS_IMETHOD RemoveVisitsByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime) = 0;

  /* void removeAllPages (); */
  NS_SCRIPTABLE NS_IMETHOD RemoveAllPages(void) = 0;

  /* void hidePage (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD HidePage(nsIURI *aURI) = 0;

  /* void markPageAsTyped (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsTyped(nsIURI *aURI) = 0;

  /* void markPageAsFollowedLink (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsFollowedLink(nsIURI *aURI) = 0;

  /* [deprecated] void registerOpenPage (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD RegisterOpenPage(nsIURI *aURI) = 0;

  /* [deprecated] void unregisterOpenPage (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD UnregisterOpenPage(nsIURI *aURI) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIBrowserHistory, NS_IBROWSERHISTORY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIBROWSERHISTORY \
  NS_SCRIPTABLE NS_IMETHOD AddPageWithDetails(nsIURI *aURI, const PRUnichar * aTitle, PRInt64 aLastVisited); \
  NS_SCRIPTABLE NS_IMETHOD GetLastPageVisited(nsACString & aLastPageVisited); \
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRUint32 *aCount); \
  NS_SCRIPTABLE NS_IMETHOD RemovePage(nsIURI *aURI); \
  NS_SCRIPTABLE NS_IMETHOD RemovePages(nsIURI **aURIs, PRUint32 aLength, PRBool aDoBatchNotify); \
  NS_SCRIPTABLE NS_IMETHOD RemovePagesFromHost(const nsACString & aHost, PRBool aEntireDomain); \
  NS_SCRIPTABLE NS_IMETHOD RemovePagesByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime); \
  NS_SCRIPTABLE NS_IMETHOD RemoveVisitsByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime); \
  NS_SCRIPTABLE NS_IMETHOD RemoveAllPages(void); \
  NS_SCRIPTABLE NS_IMETHOD HidePage(nsIURI *aURI); \
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsTyped(nsIURI *aURI); \
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsFollowedLink(nsIURI *aURI); \
  NS_SCRIPTABLE NS_IMETHOD RegisterOpenPage(nsIURI *aURI); \
  NS_SCRIPTABLE NS_IMETHOD UnregisterOpenPage(nsIURI *aURI); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIBROWSERHISTORY(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddPageWithDetails(nsIURI *aURI, const PRUnichar * aTitle, PRInt64 aLastVisited) { return _to AddPageWithDetails(aURI, aTitle, aLastVisited); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastPageVisited(nsACString & aLastPageVisited) { return _to GetLastPageVisited(aLastPageVisited); } \
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRUint32 *aCount) { return _to GetCount(aCount); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePage(nsIURI *aURI) { return _to RemovePage(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePages(nsIURI **aURIs, PRUint32 aLength, PRBool aDoBatchNotify) { return _to RemovePages(aURIs, aLength, aDoBatchNotify); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePagesFromHost(const nsACString & aHost, PRBool aEntireDomain) { return _to RemovePagesFromHost(aHost, aEntireDomain); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePagesByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime) { return _to RemovePagesByTimeframe(aBeginTime, aEndTime); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveVisitsByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime) { return _to RemoveVisitsByTimeframe(aBeginTime, aEndTime); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveAllPages(void) { return _to RemoveAllPages(); } \
  NS_SCRIPTABLE NS_IMETHOD HidePage(nsIURI *aURI) { return _to HidePage(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsTyped(nsIURI *aURI) { return _to MarkPageAsTyped(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsFollowedLink(nsIURI *aURI) { return _to MarkPageAsFollowedLink(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD RegisterOpenPage(nsIURI *aURI) { return _to RegisterOpenPage(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD UnregisterOpenPage(nsIURI *aURI) { return _to UnregisterOpenPage(aURI); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIBROWSERHISTORY(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddPageWithDetails(nsIURI *aURI, const PRUnichar * aTitle, PRInt64 aLastVisited) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddPageWithDetails(aURI, aTitle, aLastVisited); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastPageVisited(nsACString & aLastPageVisited) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastPageVisited(aLastPageVisited); } \
  NS_SCRIPTABLE NS_IMETHOD GetCount(PRUint32 *aCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCount(aCount); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePage(nsIURI *aURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemovePage(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePages(nsIURI **aURIs, PRUint32 aLength, PRBool aDoBatchNotify) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemovePages(aURIs, aLength, aDoBatchNotify); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePagesFromHost(const nsACString & aHost, PRBool aEntireDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemovePagesFromHost(aHost, aEntireDomain); } \
  NS_SCRIPTABLE NS_IMETHOD RemovePagesByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemovePagesByTimeframe(aBeginTime, aEndTime); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveVisitsByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveVisitsByTimeframe(aBeginTime, aEndTime); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveAllPages(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveAllPages(); } \
  NS_SCRIPTABLE NS_IMETHOD HidePage(nsIURI *aURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->HidePage(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsTyped(nsIURI *aURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->MarkPageAsTyped(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD MarkPageAsFollowedLink(nsIURI *aURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->MarkPageAsFollowedLink(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD RegisterOpenPage(nsIURI *aURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->RegisterOpenPage(aURI); } \
  NS_SCRIPTABLE NS_IMETHOD UnregisterOpenPage(nsIURI *aURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->UnregisterOpenPage(aURI); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsBrowserHistory : public nsIBrowserHistory
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIBROWSERHISTORY

  nsBrowserHistory();

private:
  ~nsBrowserHistory();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsBrowserHistory, nsIBrowserHistory)

nsBrowserHistory::nsBrowserHistory()
{
  /* member initializers and constructor code */
}

nsBrowserHistory::~nsBrowserHistory()
{
  /* destructor code */
}

/* void addPageWithDetails (in nsIURI aURI, in wstring aTitle, in long long aLastVisited); */
NS_IMETHODIMP nsBrowserHistory::AddPageWithDetails(nsIURI *aURI, const PRUnichar * aTitle, PRInt64 aLastVisited)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AUTF8String lastPageVisited; */
NS_IMETHODIMP nsBrowserHistory::GetLastPageVisited(nsACString & aLastPageVisited)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRUint32 count; */
NS_IMETHODIMP nsBrowserHistory::GetCount(PRUint32 *aCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removePage (in nsIURI aURI); */
NS_IMETHODIMP nsBrowserHistory::RemovePage(nsIURI *aURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removePages ([array, size_is (aLength)] in nsIURI aURIs, in unsigned long aLength, in boolean aDoBatchNotify); */
NS_IMETHODIMP nsBrowserHistory::RemovePages(nsIURI **aURIs, PRUint32 aLength, PRBool aDoBatchNotify)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removePagesFromHost (in AUTF8String aHost, in boolean aEntireDomain); */
NS_IMETHODIMP nsBrowserHistory::RemovePagesFromHost(const nsACString & aHost, PRBool aEntireDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removePagesByTimeframe (in long long aBeginTime, in long long aEndTime); */
NS_IMETHODIMP nsBrowserHistory::RemovePagesByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeVisitsByTimeframe (in long long aBeginTime, in long long aEndTime); */
NS_IMETHODIMP nsBrowserHistory::RemoveVisitsByTimeframe(PRInt64 aBeginTime, PRInt64 aEndTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeAllPages (); */
NS_IMETHODIMP nsBrowserHistory::RemoveAllPages()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void hidePage (in nsIURI aURI); */
NS_IMETHODIMP nsBrowserHistory::HidePage(nsIURI *aURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void markPageAsTyped (in nsIURI aURI); */
NS_IMETHODIMP nsBrowserHistory::MarkPageAsTyped(nsIURI *aURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void markPageAsFollowedLink (in nsIURI aURI); */
NS_IMETHODIMP nsBrowserHistory::MarkPageAsFollowedLink(nsIURI *aURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [deprecated] void registerOpenPage (in nsIURI aURI); */
NS_IMETHODIMP nsBrowserHistory::RegisterOpenPage(nsIURI *aURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [deprecated] void unregisterOpenPage (in nsIURI aURI); */
NS_IMETHODIMP nsBrowserHistory::UnregisterOpenPage(nsIURI *aURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIBrowserHistory_h__ */
