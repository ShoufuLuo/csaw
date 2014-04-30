/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/toolkit/mozapps/update/nsIUpdateService.idl
 */

#ifndef __gen_nsIUpdateService_h__
#define __gen_nsIUpdateService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */

class nsIDOMElement; /* forward declaration */

class nsIDOMWindow; /* forward declaration */

class nsIRequest; /* forward declaration */

class nsIRequestObserver; /* forward declaration */

class nsISimpleEnumerator; /* forward declaration */

class nsIXMLHttpRequest; /* forward declaration */


/* starting interface:    nsIUpdatePatch */
#define NS_IUPDATEPATCH_IID_STR "60523512-bb69-417c-9b2c-87a0664b0bbe"

#define NS_IUPDATEPATCH_IID \
  {0x60523512, 0xbb69, 0x417c, \
    { 0x9b, 0x2c, 0x87, 0xa0, 0x66, 0x4b, 0x0b, 0xbe }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUpdatePatch : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUPDATEPATCH_IID)

  /* attribute AString type; */
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType) = 0;

  /* attribute AString URL; */
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsAString & aURL) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsAString & aURL) = 0;

  /* attribute AString finalURL; */
  NS_SCRIPTABLE NS_IMETHOD GetFinalURL(nsAString & aFinalURL) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetFinalURL(const nsAString & aFinalURL) = 0;

  /* attribute AString hashFunction; */
  NS_SCRIPTABLE NS_IMETHOD GetHashFunction(nsAString & aHashFunction) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetHashFunction(const nsAString & aHashFunction) = 0;

  /* attribute AString hashValue; */
  NS_SCRIPTABLE NS_IMETHOD GetHashValue(nsAString & aHashValue) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetHashValue(const nsAString & aHashValue) = 0;

  /* attribute unsigned long size; */
  NS_SCRIPTABLE NS_IMETHOD GetSize(PRUint32 *aSize) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSize(PRUint32 aSize) = 0;

  /* attribute AString state; */
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState) = 0;

  /* attribute boolean selected; */
  NS_SCRIPTABLE NS_IMETHOD GetSelected(PRBool *aSelected) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSelected(PRBool aSelected) = 0;

  /* nsIDOMElement serialize (in nsIDOMDocument updates); */
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUpdatePatch, NS_IUPDATEPATCH_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUPDATEPATCH \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType); \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType); \
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsAString & aURL); \
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsAString & aURL); \
  NS_SCRIPTABLE NS_IMETHOD GetFinalURL(nsAString & aFinalURL); \
  NS_SCRIPTABLE NS_IMETHOD SetFinalURL(const nsAString & aFinalURL); \
  NS_SCRIPTABLE NS_IMETHOD GetHashFunction(nsAString & aHashFunction); \
  NS_SCRIPTABLE NS_IMETHOD SetHashFunction(const nsAString & aHashFunction); \
  NS_SCRIPTABLE NS_IMETHOD GetHashValue(nsAString & aHashValue); \
  NS_SCRIPTABLE NS_IMETHOD SetHashValue(const nsAString & aHashValue); \
  NS_SCRIPTABLE NS_IMETHOD GetSize(PRUint32 *aSize); \
  NS_SCRIPTABLE NS_IMETHOD SetSize(PRUint32 aSize); \
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState); \
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState); \
  NS_SCRIPTABLE NS_IMETHOD GetSelected(PRBool *aSelected); \
  NS_SCRIPTABLE NS_IMETHOD SetSelected(PRBool aSelected); \
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUPDATEPATCH(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType) { return _to GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType) { return _to SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsAString & aURL) { return _to GetURL(aURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsAString & aURL) { return _to SetURL(aURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetFinalURL(nsAString & aFinalURL) { return _to GetFinalURL(aFinalURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetFinalURL(const nsAString & aFinalURL) { return _to SetFinalURL(aFinalURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetHashFunction(nsAString & aHashFunction) { return _to GetHashFunction(aHashFunction); } \
  NS_SCRIPTABLE NS_IMETHOD SetHashFunction(const nsAString & aHashFunction) { return _to SetHashFunction(aHashFunction); } \
  NS_SCRIPTABLE NS_IMETHOD GetHashValue(nsAString & aHashValue) { return _to GetHashValue(aHashValue); } \
  NS_SCRIPTABLE NS_IMETHOD SetHashValue(const nsAString & aHashValue) { return _to SetHashValue(aHashValue); } \
  NS_SCRIPTABLE NS_IMETHOD GetSize(PRUint32 *aSize) { return _to GetSize(aSize); } \
  NS_SCRIPTABLE NS_IMETHOD SetSize(PRUint32 aSize) { return _to SetSize(aSize); } \
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState) { return _to GetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState) { return _to SetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD GetSelected(PRBool *aSelected) { return _to GetSelected(aSelected); } \
  NS_SCRIPTABLE NS_IMETHOD SetSelected(PRBool aSelected) { return _to SetSelected(aSelected); } \
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM) { return _to Serialize(updates, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUPDATEPATCH(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsAString & aURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURL(aURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsAString & aURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetURL(aURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetFinalURL(nsAString & aFinalURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFinalURL(aFinalURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetFinalURL(const nsAString & aFinalURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFinalURL(aFinalURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetHashFunction(nsAString & aHashFunction) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetHashFunction(aHashFunction); } \
  NS_SCRIPTABLE NS_IMETHOD SetHashFunction(const nsAString & aHashFunction) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetHashFunction(aHashFunction); } \
  NS_SCRIPTABLE NS_IMETHOD GetHashValue(nsAString & aHashValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetHashValue(aHashValue); } \
  NS_SCRIPTABLE NS_IMETHOD SetHashValue(const nsAString & aHashValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetHashValue(aHashValue); } \
  NS_SCRIPTABLE NS_IMETHOD GetSize(PRUint32 *aSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSize(aSize); } \
  NS_SCRIPTABLE NS_IMETHOD SetSize(PRUint32 aSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSize(aSize); } \
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD GetSelected(PRBool *aSelected) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSelected(aSelected); } \
  NS_SCRIPTABLE NS_IMETHOD SetSelected(PRBool aSelected) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSelected(aSelected); } \
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Serialize(updates, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUpdatePatch : public nsIUpdatePatch
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUPDATEPATCH

  nsUpdatePatch();

private:
  ~nsUpdatePatch();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUpdatePatch, nsIUpdatePatch)

nsUpdatePatch::nsUpdatePatch()
{
  /* member initializers and constructor code */
}

nsUpdatePatch::~nsUpdatePatch()
{
  /* destructor code */
}

/* attribute AString type; */
NS_IMETHODIMP nsUpdatePatch::GetType(nsAString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetType(const nsAString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString URL; */
NS_IMETHODIMP nsUpdatePatch::GetURL(nsAString & aURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetURL(const nsAString & aURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString finalURL; */
NS_IMETHODIMP nsUpdatePatch::GetFinalURL(nsAString & aFinalURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetFinalURL(const nsAString & aFinalURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString hashFunction; */
NS_IMETHODIMP nsUpdatePatch::GetHashFunction(nsAString & aHashFunction)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetHashFunction(const nsAString & aHashFunction)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString hashValue; */
NS_IMETHODIMP nsUpdatePatch::GetHashValue(nsAString & aHashValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetHashValue(const nsAString & aHashValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned long size; */
NS_IMETHODIMP nsUpdatePatch::GetSize(PRUint32 *aSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetSize(PRUint32 aSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString state; */
NS_IMETHODIMP nsUpdatePatch::GetState(nsAString & aState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetState(const nsAString & aState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean selected; */
NS_IMETHODIMP nsUpdatePatch::GetSelected(PRBool *aSelected)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdatePatch::SetSelected(PRBool aSelected)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMElement serialize (in nsIDOMDocument updates); */
NS_IMETHODIMP nsUpdatePatch::Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIUpdate */
#define NS_IUPDATE_IID_STR "2379e2e1-8eab-4084-8d8c-94ffeee56804"

#define NS_IUPDATE_IID \
  {0x2379e2e1, 0x8eab, 0x4084, \
    { 0x8d, 0x8c, 0x94, 0xff, 0xee, 0xe5, 0x68, 0x04 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUpdate : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUPDATE_IID)

  /* attribute AString type; */
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType) = 0;

  /* attribute AString name; */
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) = 0;

  /* attribute AString displayVersion; */
  NS_SCRIPTABLE NS_IMETHOD GetDisplayVersion(nsAString & aDisplayVersion) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetDisplayVersion(const nsAString & aDisplayVersion) = 0;

  /* attribute AString appVersion; */
  NS_SCRIPTABLE NS_IMETHOD GetAppVersion(nsAString & aAppVersion) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetAppVersion(const nsAString & aAppVersion) = 0;

  /* attribute AString platformVersion; */
  NS_SCRIPTABLE NS_IMETHOD GetPlatformVersion(nsAString & aPlatformVersion) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetPlatformVersion(const nsAString & aPlatformVersion) = 0;

  /* attribute AString previousAppVersion; */
  NS_SCRIPTABLE NS_IMETHOD GetPreviousAppVersion(nsAString & aPreviousAppVersion) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetPreviousAppVersion(const nsAString & aPreviousAppVersion) = 0;

  /* attribute AString buildID; */
  NS_SCRIPTABLE NS_IMETHOD GetBuildID(nsAString & aBuildID) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetBuildID(const nsAString & aBuildID) = 0;

  /* attribute AString detailsURL; */
  NS_SCRIPTABLE NS_IMETHOD GetDetailsURL(nsAString & aDetailsURL) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetDetailsURL(const nsAString & aDetailsURL) = 0;

  /* attribute AString billboardURL; */
  NS_SCRIPTABLE NS_IMETHOD GetBillboardURL(nsAString & aBillboardURL) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetBillboardURL(const nsAString & aBillboardURL) = 0;

  /* attribute AString licenseURL; */
  NS_SCRIPTABLE NS_IMETHOD GetLicenseURL(nsAString & aLicenseURL) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetLicenseURL(const nsAString & aLicenseURL) = 0;

  /* attribute AString serviceURL; */
  NS_SCRIPTABLE NS_IMETHOD GetServiceURL(nsAString & aServiceURL) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetServiceURL(const nsAString & aServiceURL) = 0;

  /* attribute AString channel; */
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsAString & aChannel) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetChannel(const nsAString & aChannel) = 0;

  /* attribute boolean showPrompt; */
  NS_SCRIPTABLE NS_IMETHOD GetShowPrompt(PRBool *aShowPrompt) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetShowPrompt(PRBool aShowPrompt) = 0;

  /* attribute boolean showNeverForVersion; */
  NS_SCRIPTABLE NS_IMETHOD GetShowNeverForVersion(PRBool *aShowNeverForVersion) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetShowNeverForVersion(PRBool aShowNeverForVersion) = 0;

  /* attribute boolean showSurvey; */
  NS_SCRIPTABLE NS_IMETHOD GetShowSurvey(PRBool *aShowSurvey) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetShowSurvey(PRBool aShowSurvey) = 0;

  /* attribute boolean isCompleteUpdate; */
  NS_SCRIPTABLE NS_IMETHOD GetIsCompleteUpdate(PRBool *aIsCompleteUpdate) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetIsCompleteUpdate(PRBool aIsCompleteUpdate) = 0;

  /* attribute boolean isSecurityUpdate; */
  NS_SCRIPTABLE NS_IMETHOD GetIsSecurityUpdate(PRBool *aIsSecurityUpdate) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetIsSecurityUpdate(PRBool aIsSecurityUpdate) = 0;

  /* attribute long long installDate; */
  NS_SCRIPTABLE NS_IMETHOD GetInstallDate(PRInt64 *aInstallDate) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInstallDate(PRInt64 aInstallDate) = 0;

  /* attribute AString statusText; */
  NS_SCRIPTABLE NS_IMETHOD GetStatusText(nsAString & aStatusText) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetStatusText(const nsAString & aStatusText) = 0;

  /* readonly attribute nsIUpdatePatch selectedPatch; */
  NS_SCRIPTABLE NS_IMETHOD GetSelectedPatch(nsIUpdatePatch * *aSelectedPatch) = 0;

  /* attribute AString state; */
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState) = 0;

  /* attribute long errorCode; */
  NS_SCRIPTABLE NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetErrorCode(PRInt32 aErrorCode) = 0;

  /* readonly attribute unsigned long patchCount; */
  NS_SCRIPTABLE NS_IMETHOD GetPatchCount(PRUint32 *aPatchCount) = 0;

  /* nsIUpdatePatch getPatchAt (in unsigned long index); */
  NS_SCRIPTABLE NS_IMETHOD GetPatchAt(PRUint32 index, nsIUpdatePatch * *_retval NS_OUTPARAM) = 0;

  /* nsIDOMElement serialize (in nsIDOMDocument updates); */
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUpdate, NS_IUPDATE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUPDATE \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType); \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType); \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName); \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName); \
  NS_SCRIPTABLE NS_IMETHOD GetDisplayVersion(nsAString & aDisplayVersion); \
  NS_SCRIPTABLE NS_IMETHOD SetDisplayVersion(const nsAString & aDisplayVersion); \
  NS_SCRIPTABLE NS_IMETHOD GetAppVersion(nsAString & aAppVersion); \
  NS_SCRIPTABLE NS_IMETHOD SetAppVersion(const nsAString & aAppVersion); \
  NS_SCRIPTABLE NS_IMETHOD GetPlatformVersion(nsAString & aPlatformVersion); \
  NS_SCRIPTABLE NS_IMETHOD SetPlatformVersion(const nsAString & aPlatformVersion); \
  NS_SCRIPTABLE NS_IMETHOD GetPreviousAppVersion(nsAString & aPreviousAppVersion); \
  NS_SCRIPTABLE NS_IMETHOD SetPreviousAppVersion(const nsAString & aPreviousAppVersion); \
  NS_SCRIPTABLE NS_IMETHOD GetBuildID(nsAString & aBuildID); \
  NS_SCRIPTABLE NS_IMETHOD SetBuildID(const nsAString & aBuildID); \
  NS_SCRIPTABLE NS_IMETHOD GetDetailsURL(nsAString & aDetailsURL); \
  NS_SCRIPTABLE NS_IMETHOD SetDetailsURL(const nsAString & aDetailsURL); \
  NS_SCRIPTABLE NS_IMETHOD GetBillboardURL(nsAString & aBillboardURL); \
  NS_SCRIPTABLE NS_IMETHOD SetBillboardURL(const nsAString & aBillboardURL); \
  NS_SCRIPTABLE NS_IMETHOD GetLicenseURL(nsAString & aLicenseURL); \
  NS_SCRIPTABLE NS_IMETHOD SetLicenseURL(const nsAString & aLicenseURL); \
  NS_SCRIPTABLE NS_IMETHOD GetServiceURL(nsAString & aServiceURL); \
  NS_SCRIPTABLE NS_IMETHOD SetServiceURL(const nsAString & aServiceURL); \
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsAString & aChannel); \
  NS_SCRIPTABLE NS_IMETHOD SetChannel(const nsAString & aChannel); \
  NS_SCRIPTABLE NS_IMETHOD GetShowPrompt(PRBool *aShowPrompt); \
  NS_SCRIPTABLE NS_IMETHOD SetShowPrompt(PRBool aShowPrompt); \
  NS_SCRIPTABLE NS_IMETHOD GetShowNeverForVersion(PRBool *aShowNeverForVersion); \
  NS_SCRIPTABLE NS_IMETHOD SetShowNeverForVersion(PRBool aShowNeverForVersion); \
  NS_SCRIPTABLE NS_IMETHOD GetShowSurvey(PRBool *aShowSurvey); \
  NS_SCRIPTABLE NS_IMETHOD SetShowSurvey(PRBool aShowSurvey); \
  NS_SCRIPTABLE NS_IMETHOD GetIsCompleteUpdate(PRBool *aIsCompleteUpdate); \
  NS_SCRIPTABLE NS_IMETHOD SetIsCompleteUpdate(PRBool aIsCompleteUpdate); \
  NS_SCRIPTABLE NS_IMETHOD GetIsSecurityUpdate(PRBool *aIsSecurityUpdate); \
  NS_SCRIPTABLE NS_IMETHOD SetIsSecurityUpdate(PRBool aIsSecurityUpdate); \
  NS_SCRIPTABLE NS_IMETHOD GetInstallDate(PRInt64 *aInstallDate); \
  NS_SCRIPTABLE NS_IMETHOD SetInstallDate(PRInt64 aInstallDate); \
  NS_SCRIPTABLE NS_IMETHOD GetStatusText(nsAString & aStatusText); \
  NS_SCRIPTABLE NS_IMETHOD SetStatusText(const nsAString & aStatusText); \
  NS_SCRIPTABLE NS_IMETHOD GetSelectedPatch(nsIUpdatePatch * *aSelectedPatch); \
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState); \
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState); \
  NS_SCRIPTABLE NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode); \
  NS_SCRIPTABLE NS_IMETHOD SetErrorCode(PRInt32 aErrorCode); \
  NS_SCRIPTABLE NS_IMETHOD GetPatchCount(PRUint32 *aPatchCount); \
  NS_SCRIPTABLE NS_IMETHOD GetPatchAt(PRUint32 index, nsIUpdatePatch * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUPDATE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType) { return _to GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType) { return _to SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return _to GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return _to SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetDisplayVersion(nsAString & aDisplayVersion) { return _to GetDisplayVersion(aDisplayVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetDisplayVersion(const nsAString & aDisplayVersion) { return _to SetDisplayVersion(aDisplayVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetAppVersion(nsAString & aAppVersion) { return _to GetAppVersion(aAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetAppVersion(const nsAString & aAppVersion) { return _to SetAppVersion(aAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetPlatformVersion(nsAString & aPlatformVersion) { return _to GetPlatformVersion(aPlatformVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetPlatformVersion(const nsAString & aPlatformVersion) { return _to SetPlatformVersion(aPlatformVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetPreviousAppVersion(nsAString & aPreviousAppVersion) { return _to GetPreviousAppVersion(aPreviousAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetPreviousAppVersion(const nsAString & aPreviousAppVersion) { return _to SetPreviousAppVersion(aPreviousAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetBuildID(nsAString & aBuildID) { return _to GetBuildID(aBuildID); } \
  NS_SCRIPTABLE NS_IMETHOD SetBuildID(const nsAString & aBuildID) { return _to SetBuildID(aBuildID); } \
  NS_SCRIPTABLE NS_IMETHOD GetDetailsURL(nsAString & aDetailsURL) { return _to GetDetailsURL(aDetailsURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetDetailsURL(const nsAString & aDetailsURL) { return _to SetDetailsURL(aDetailsURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetBillboardURL(nsAString & aBillboardURL) { return _to GetBillboardURL(aBillboardURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetBillboardURL(const nsAString & aBillboardURL) { return _to SetBillboardURL(aBillboardURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetLicenseURL(nsAString & aLicenseURL) { return _to GetLicenseURL(aLicenseURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetLicenseURL(const nsAString & aLicenseURL) { return _to SetLicenseURL(aLicenseURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetServiceURL(nsAString & aServiceURL) { return _to GetServiceURL(aServiceURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetServiceURL(const nsAString & aServiceURL) { return _to SetServiceURL(aServiceURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsAString & aChannel) { return _to GetChannel(aChannel); } \
  NS_SCRIPTABLE NS_IMETHOD SetChannel(const nsAString & aChannel) { return _to SetChannel(aChannel); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowPrompt(PRBool *aShowPrompt) { return _to GetShowPrompt(aShowPrompt); } \
  NS_SCRIPTABLE NS_IMETHOD SetShowPrompt(PRBool aShowPrompt) { return _to SetShowPrompt(aShowPrompt); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowNeverForVersion(PRBool *aShowNeverForVersion) { return _to GetShowNeverForVersion(aShowNeverForVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetShowNeverForVersion(PRBool aShowNeverForVersion) { return _to SetShowNeverForVersion(aShowNeverForVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowSurvey(PRBool *aShowSurvey) { return _to GetShowSurvey(aShowSurvey); } \
  NS_SCRIPTABLE NS_IMETHOD SetShowSurvey(PRBool aShowSurvey) { return _to SetShowSurvey(aShowSurvey); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsCompleteUpdate(PRBool *aIsCompleteUpdate) { return _to GetIsCompleteUpdate(aIsCompleteUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SetIsCompleteUpdate(PRBool aIsCompleteUpdate) { return _to SetIsCompleteUpdate(aIsCompleteUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsSecurityUpdate(PRBool *aIsSecurityUpdate) { return _to GetIsSecurityUpdate(aIsSecurityUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SetIsSecurityUpdate(PRBool aIsSecurityUpdate) { return _to SetIsSecurityUpdate(aIsSecurityUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD GetInstallDate(PRInt64 *aInstallDate) { return _to GetInstallDate(aInstallDate); } \
  NS_SCRIPTABLE NS_IMETHOD SetInstallDate(PRInt64 aInstallDate) { return _to SetInstallDate(aInstallDate); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatusText(nsAString & aStatusText) { return _to GetStatusText(aStatusText); } \
  NS_SCRIPTABLE NS_IMETHOD SetStatusText(const nsAString & aStatusText) { return _to SetStatusText(aStatusText); } \
  NS_SCRIPTABLE NS_IMETHOD GetSelectedPatch(nsIUpdatePatch * *aSelectedPatch) { return _to GetSelectedPatch(aSelectedPatch); } \
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState) { return _to GetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState) { return _to SetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode) { return _to GetErrorCode(aErrorCode); } \
  NS_SCRIPTABLE NS_IMETHOD SetErrorCode(PRInt32 aErrorCode) { return _to SetErrorCode(aErrorCode); } \
  NS_SCRIPTABLE NS_IMETHOD GetPatchCount(PRUint32 *aPatchCount) { return _to GetPatchCount(aPatchCount); } \
  NS_SCRIPTABLE NS_IMETHOD GetPatchAt(PRUint32 index, nsIUpdatePatch * *_retval NS_OUTPARAM) { return _to GetPatchAt(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM) { return _to Serialize(updates, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUPDATE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetType(nsAString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(const nsAString & aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetDisplayVersion(nsAString & aDisplayVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDisplayVersion(aDisplayVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetDisplayVersion(const nsAString & aDisplayVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDisplayVersion(aDisplayVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetAppVersion(nsAString & aAppVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAppVersion(aAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetAppVersion(const nsAString & aAppVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAppVersion(aAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetPlatformVersion(nsAString & aPlatformVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPlatformVersion(aPlatformVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetPlatformVersion(const nsAString & aPlatformVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetPlatformVersion(aPlatformVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetPreviousAppVersion(nsAString & aPreviousAppVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPreviousAppVersion(aPreviousAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetPreviousAppVersion(const nsAString & aPreviousAppVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetPreviousAppVersion(aPreviousAppVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetBuildID(nsAString & aBuildID) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBuildID(aBuildID); } \
  NS_SCRIPTABLE NS_IMETHOD SetBuildID(const nsAString & aBuildID) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetBuildID(aBuildID); } \
  NS_SCRIPTABLE NS_IMETHOD GetDetailsURL(nsAString & aDetailsURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDetailsURL(aDetailsURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetDetailsURL(const nsAString & aDetailsURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDetailsURL(aDetailsURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetBillboardURL(nsAString & aBillboardURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBillboardURL(aBillboardURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetBillboardURL(const nsAString & aBillboardURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetBillboardURL(aBillboardURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetLicenseURL(nsAString & aLicenseURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLicenseURL(aLicenseURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetLicenseURL(const nsAString & aLicenseURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLicenseURL(aLicenseURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetServiceURL(nsAString & aServiceURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetServiceURL(aServiceURL); } \
  NS_SCRIPTABLE NS_IMETHOD SetServiceURL(const nsAString & aServiceURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetServiceURL(aServiceURL); } \
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsAString & aChannel) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetChannel(aChannel); } \
  NS_SCRIPTABLE NS_IMETHOD SetChannel(const nsAString & aChannel) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetChannel(aChannel); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowPrompt(PRBool *aShowPrompt) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetShowPrompt(aShowPrompt); } \
  NS_SCRIPTABLE NS_IMETHOD SetShowPrompt(PRBool aShowPrompt) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetShowPrompt(aShowPrompt); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowNeverForVersion(PRBool *aShowNeverForVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetShowNeverForVersion(aShowNeverForVersion); } \
  NS_SCRIPTABLE NS_IMETHOD SetShowNeverForVersion(PRBool aShowNeverForVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetShowNeverForVersion(aShowNeverForVersion); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowSurvey(PRBool *aShowSurvey) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetShowSurvey(aShowSurvey); } \
  NS_SCRIPTABLE NS_IMETHOD SetShowSurvey(PRBool aShowSurvey) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetShowSurvey(aShowSurvey); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsCompleteUpdate(PRBool *aIsCompleteUpdate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsCompleteUpdate(aIsCompleteUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SetIsCompleteUpdate(PRBool aIsCompleteUpdate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetIsCompleteUpdate(aIsCompleteUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsSecurityUpdate(PRBool *aIsSecurityUpdate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsSecurityUpdate(aIsSecurityUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SetIsSecurityUpdate(PRBool aIsSecurityUpdate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetIsSecurityUpdate(aIsSecurityUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD GetInstallDate(PRInt64 *aInstallDate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInstallDate(aInstallDate); } \
  NS_SCRIPTABLE NS_IMETHOD SetInstallDate(PRInt64 aInstallDate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInstallDate(aInstallDate); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatusText(nsAString & aStatusText) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStatusText(aStatusText); } \
  NS_SCRIPTABLE NS_IMETHOD SetStatusText(const nsAString & aStatusText) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetStatusText(aStatusText); } \
  NS_SCRIPTABLE NS_IMETHOD GetSelectedPatch(nsIUpdatePatch * *aSelectedPatch) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSelectedPatch(aSelectedPatch); } \
  NS_SCRIPTABLE NS_IMETHOD GetState(nsAString & aState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD SetState(const nsAString & aState) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD GetErrorCode(PRInt32 *aErrorCode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrorCode(aErrorCode); } \
  NS_SCRIPTABLE NS_IMETHOD SetErrorCode(PRInt32 aErrorCode) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetErrorCode(aErrorCode); } \
  NS_SCRIPTABLE NS_IMETHOD GetPatchCount(PRUint32 *aPatchCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPatchCount(aPatchCount); } \
  NS_SCRIPTABLE NS_IMETHOD GetPatchAt(PRUint32 index, nsIUpdatePatch * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPatchAt(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Serialize(updates, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUpdate : public nsIUpdate
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUPDATE

  nsUpdate();

private:
  ~nsUpdate();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUpdate, nsIUpdate)

nsUpdate::nsUpdate()
{
  /* member initializers and constructor code */
}

nsUpdate::~nsUpdate()
{
  /* destructor code */
}

/* attribute AString type; */
NS_IMETHODIMP nsUpdate::GetType(nsAString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetType(const nsAString & aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString name; */
NS_IMETHODIMP nsUpdate::GetName(nsAString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetName(const nsAString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString displayVersion; */
NS_IMETHODIMP nsUpdate::GetDisplayVersion(nsAString & aDisplayVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetDisplayVersion(const nsAString & aDisplayVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString appVersion; */
NS_IMETHODIMP nsUpdate::GetAppVersion(nsAString & aAppVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetAppVersion(const nsAString & aAppVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString platformVersion; */
NS_IMETHODIMP nsUpdate::GetPlatformVersion(nsAString & aPlatformVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetPlatformVersion(const nsAString & aPlatformVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString previousAppVersion; */
NS_IMETHODIMP nsUpdate::GetPreviousAppVersion(nsAString & aPreviousAppVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetPreviousAppVersion(const nsAString & aPreviousAppVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString buildID; */
NS_IMETHODIMP nsUpdate::GetBuildID(nsAString & aBuildID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetBuildID(const nsAString & aBuildID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString detailsURL; */
NS_IMETHODIMP nsUpdate::GetDetailsURL(nsAString & aDetailsURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetDetailsURL(const nsAString & aDetailsURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString billboardURL; */
NS_IMETHODIMP nsUpdate::GetBillboardURL(nsAString & aBillboardURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetBillboardURL(const nsAString & aBillboardURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString licenseURL; */
NS_IMETHODIMP nsUpdate::GetLicenseURL(nsAString & aLicenseURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetLicenseURL(const nsAString & aLicenseURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString serviceURL; */
NS_IMETHODIMP nsUpdate::GetServiceURL(nsAString & aServiceURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetServiceURL(const nsAString & aServiceURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString channel; */
NS_IMETHODIMP nsUpdate::GetChannel(nsAString & aChannel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetChannel(const nsAString & aChannel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean showPrompt; */
NS_IMETHODIMP nsUpdate::GetShowPrompt(PRBool *aShowPrompt)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetShowPrompt(PRBool aShowPrompt)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean showNeverForVersion; */
NS_IMETHODIMP nsUpdate::GetShowNeverForVersion(PRBool *aShowNeverForVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetShowNeverForVersion(PRBool aShowNeverForVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean showSurvey; */
NS_IMETHODIMP nsUpdate::GetShowSurvey(PRBool *aShowSurvey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetShowSurvey(PRBool aShowSurvey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean isCompleteUpdate; */
NS_IMETHODIMP nsUpdate::GetIsCompleteUpdate(PRBool *aIsCompleteUpdate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetIsCompleteUpdate(PRBool aIsCompleteUpdate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean isSecurityUpdate; */
NS_IMETHODIMP nsUpdate::GetIsSecurityUpdate(PRBool *aIsSecurityUpdate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetIsSecurityUpdate(PRBool aIsSecurityUpdate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long long installDate; */
NS_IMETHODIMP nsUpdate::GetInstallDate(PRInt64 *aInstallDate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetInstallDate(PRInt64 aInstallDate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString statusText; */
NS_IMETHODIMP nsUpdate::GetStatusText(nsAString & aStatusText)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetStatusText(const nsAString & aStatusText)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIUpdatePatch selectedPatch; */
NS_IMETHODIMP nsUpdate::GetSelectedPatch(nsIUpdatePatch * *aSelectedPatch)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString state; */
NS_IMETHODIMP nsUpdate::GetState(nsAString & aState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetState(const nsAString & aState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long errorCode; */
NS_IMETHODIMP nsUpdate::GetErrorCode(PRInt32 *aErrorCode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdate::SetErrorCode(PRInt32 aErrorCode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long patchCount; */
NS_IMETHODIMP nsUpdate::GetPatchCount(PRUint32 *aPatchCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIUpdatePatch getPatchAt (in unsigned long index); */
NS_IMETHODIMP nsUpdate::GetPatchAt(PRUint32 index, nsIUpdatePatch * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMElement serialize (in nsIDOMDocument updates); */
NS_IMETHODIMP nsUpdate::Serialize(nsIDOMDocument *updates, nsIDOMElement * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIUpdateCheckListener */
#define NS_IUPDATECHECKLISTENER_IID_STR "8cbceb6e-8e27-46f2-8808-444c6499f836"

#define NS_IUPDATECHECKLISTENER_IID \
  {0x8cbceb6e, 0x8e27, 0x46f2, \
    { 0x88, 0x08, 0x44, 0x4c, 0x64, 0x99, 0xf8, 0x36 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUpdateCheckListener : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUPDATECHECKLISTENER_IID)

  /* void onProgress (in nsIXMLHttpRequest request, in unsigned long position, in unsigned long totalSize); */
  NS_SCRIPTABLE NS_IMETHOD OnProgress(nsIXMLHttpRequest *request, PRUint32 position, PRUint32 totalSize) = 0;

  /* void onCheckComplete (in nsIXMLHttpRequest request, [array, size_is (updateCount)] in nsIUpdate updates, in unsigned long updateCount); */
  NS_SCRIPTABLE NS_IMETHOD OnCheckComplete(nsIXMLHttpRequest *request, nsIUpdate **updates, PRUint32 updateCount) = 0;

  /* void onError (in nsIXMLHttpRequest request, in nsIUpdate update); */
  NS_SCRIPTABLE NS_IMETHOD OnError(nsIXMLHttpRequest *request, nsIUpdate *update) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUpdateCheckListener, NS_IUPDATECHECKLISTENER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUPDATECHECKLISTENER \
  NS_SCRIPTABLE NS_IMETHOD OnProgress(nsIXMLHttpRequest *request, PRUint32 position, PRUint32 totalSize); \
  NS_SCRIPTABLE NS_IMETHOD OnCheckComplete(nsIXMLHttpRequest *request, nsIUpdate **updates, PRUint32 updateCount); \
  NS_SCRIPTABLE NS_IMETHOD OnError(nsIXMLHttpRequest *request, nsIUpdate *update); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUPDATECHECKLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnProgress(nsIXMLHttpRequest *request, PRUint32 position, PRUint32 totalSize) { return _to OnProgress(request, position, totalSize); } \
  NS_SCRIPTABLE NS_IMETHOD OnCheckComplete(nsIXMLHttpRequest *request, nsIUpdate **updates, PRUint32 updateCount) { return _to OnCheckComplete(request, updates, updateCount); } \
  NS_SCRIPTABLE NS_IMETHOD OnError(nsIXMLHttpRequest *request, nsIUpdate *update) { return _to OnError(request, update); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUPDATECHECKLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnProgress(nsIXMLHttpRequest *request, PRUint32 position, PRUint32 totalSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnProgress(request, position, totalSize); } \
  NS_SCRIPTABLE NS_IMETHOD OnCheckComplete(nsIXMLHttpRequest *request, nsIUpdate **updates, PRUint32 updateCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnCheckComplete(request, updates, updateCount); } \
  NS_SCRIPTABLE NS_IMETHOD OnError(nsIXMLHttpRequest *request, nsIUpdate *update) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnError(request, update); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUpdateCheckListener : public nsIUpdateCheckListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUPDATECHECKLISTENER

  nsUpdateCheckListener();

private:
  ~nsUpdateCheckListener();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUpdateCheckListener, nsIUpdateCheckListener)

nsUpdateCheckListener::nsUpdateCheckListener()
{
  /* member initializers and constructor code */
}

nsUpdateCheckListener::~nsUpdateCheckListener()
{
  /* destructor code */
}

/* void onProgress (in nsIXMLHttpRequest request, in unsigned long position, in unsigned long totalSize); */
NS_IMETHODIMP nsUpdateCheckListener::OnProgress(nsIXMLHttpRequest *request, PRUint32 position, PRUint32 totalSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onCheckComplete (in nsIXMLHttpRequest request, [array, size_is (updateCount)] in nsIUpdate updates, in unsigned long updateCount); */
NS_IMETHODIMP nsUpdateCheckListener::OnCheckComplete(nsIXMLHttpRequest *request, nsIUpdate **updates, PRUint32 updateCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onError (in nsIXMLHttpRequest request, in nsIUpdate update); */
NS_IMETHODIMP nsUpdateCheckListener::OnError(nsIXMLHttpRequest *request, nsIUpdate *update)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIUpdateChecker */
#define NS_IUPDATECHECKER_IID_STR "877ace25-8bc5-452a-8586-9c1cf2871994"

#define NS_IUPDATECHECKER_IID \
  {0x877ace25, 0x8bc5, 0x452a, \
    { 0x85, 0x86, 0x9c, 0x1c, 0xf2, 0x87, 0x19, 0x94 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUpdateChecker : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUPDATECHECKER_IID)

  /* void checkForUpdates (in nsIUpdateCheckListener listener, in boolean force); */
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(nsIUpdateCheckListener *listener, PRBool force) = 0;

  enum { CURRENT_CHECK = 1U };

  enum { CURRENT_SESSION = 2U };

  enum { ANY_CHECKS = 3U };

  /* void stopChecking (in unsigned short duration); */
  NS_SCRIPTABLE NS_IMETHOD StopChecking(PRUint16 duration) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUpdateChecker, NS_IUPDATECHECKER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUPDATECHECKER \
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(nsIUpdateCheckListener *listener, PRBool force); \
  NS_SCRIPTABLE NS_IMETHOD StopChecking(PRUint16 duration); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUPDATECHECKER(_to) \
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(nsIUpdateCheckListener *listener, PRBool force) { return _to CheckForUpdates(listener, force); } \
  NS_SCRIPTABLE NS_IMETHOD StopChecking(PRUint16 duration) { return _to StopChecking(duration); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUPDATECHECKER(_to) \
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(nsIUpdateCheckListener *listener, PRBool force) { return !_to ? NS_ERROR_NULL_POINTER : _to->CheckForUpdates(listener, force); } \
  NS_SCRIPTABLE NS_IMETHOD StopChecking(PRUint16 duration) { return !_to ? NS_ERROR_NULL_POINTER : _to->StopChecking(duration); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUpdateChecker : public nsIUpdateChecker
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUPDATECHECKER

  nsUpdateChecker();

private:
  ~nsUpdateChecker();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUpdateChecker, nsIUpdateChecker)

nsUpdateChecker::nsUpdateChecker()
{
  /* member initializers and constructor code */
}

nsUpdateChecker::~nsUpdateChecker()
{
  /* destructor code */
}

/* void checkForUpdates (in nsIUpdateCheckListener listener, in boolean force); */
NS_IMETHODIMP nsUpdateChecker::CheckForUpdates(nsIUpdateCheckListener *listener, PRBool force)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void stopChecking (in unsigned short duration); */
NS_IMETHODIMP nsUpdateChecker::StopChecking(PRUint16 duration)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIApplicationUpdateService */
#define NS_IAPPLICATIONUPDATESERVICE_IID_STR "b5811144-ed30-4343-aff9-c514034aa19a"

#define NS_IAPPLICATIONUPDATESERVICE_IID \
  {0xb5811144, 0xed30, 0x4343, \
    { 0xaf, 0xf9, 0xc5, 0x14, 0x03, 0x4a, 0xa1, 0x9a }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIApplicationUpdateService : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IAPPLICATIONUPDATESERVICE_IID)

  /* readonly attribute nsIUpdateChecker backgroundChecker; */
  NS_SCRIPTABLE NS_IMETHOD GetBackgroundChecker(nsIUpdateChecker * *aBackgroundChecker) = 0;

  /* nsIUpdate selectUpdate ([array, size_is (updateCount)] in nsIUpdate updates, in unsigned long updateCount); */
  NS_SCRIPTABLE NS_IMETHOD SelectUpdate(nsIUpdate **updates, PRUint32 updateCount, nsIUpdate * *_retval NS_OUTPARAM) = 0;

  /* void addDownloadListener (in nsIRequestObserver listener); */
  NS_SCRIPTABLE NS_IMETHOD AddDownloadListener(nsIRequestObserver *listener) = 0;

  /* void removeDownloadListener (in nsIRequestObserver listener); */
  NS_SCRIPTABLE NS_IMETHOD RemoveDownloadListener(nsIRequestObserver *listener) = 0;

  /* AString downloadUpdate (in nsIUpdate update, in boolean background); */
  NS_SCRIPTABLE NS_IMETHOD DownloadUpdate(nsIUpdate *update, PRBool background, nsAString & _retval NS_OUTPARAM) = 0;

  /* void pauseDownload (); */
  NS_SCRIPTABLE NS_IMETHOD PauseDownload(void) = 0;

  /* readonly attribute boolean isDownloading; */
  NS_SCRIPTABLE NS_IMETHOD GetIsDownloading(PRBool *aIsDownloading) = 0;

  /* readonly attribute boolean canCheckForUpdates; */
  NS_SCRIPTABLE NS_IMETHOD GetCanCheckForUpdates(PRBool *aCanCheckForUpdates) = 0;

  /* readonly attribute boolean canApplyUpdates; */
  NS_SCRIPTABLE NS_IMETHOD GetCanApplyUpdates(PRBool *aCanApplyUpdates) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIApplicationUpdateService, NS_IAPPLICATIONUPDATESERVICE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIAPPLICATIONUPDATESERVICE \
  NS_SCRIPTABLE NS_IMETHOD GetBackgroundChecker(nsIUpdateChecker * *aBackgroundChecker); \
  NS_SCRIPTABLE NS_IMETHOD SelectUpdate(nsIUpdate **updates, PRUint32 updateCount, nsIUpdate * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AddDownloadListener(nsIRequestObserver *listener); \
  NS_SCRIPTABLE NS_IMETHOD RemoveDownloadListener(nsIRequestObserver *listener); \
  NS_SCRIPTABLE NS_IMETHOD DownloadUpdate(nsIUpdate *update, PRBool background, nsAString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD PauseDownload(void); \
  NS_SCRIPTABLE NS_IMETHOD GetIsDownloading(PRBool *aIsDownloading); \
  NS_SCRIPTABLE NS_IMETHOD GetCanCheckForUpdates(PRBool *aCanCheckForUpdates); \
  NS_SCRIPTABLE NS_IMETHOD GetCanApplyUpdates(PRBool *aCanApplyUpdates); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIAPPLICATIONUPDATESERVICE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetBackgroundChecker(nsIUpdateChecker * *aBackgroundChecker) { return _to GetBackgroundChecker(aBackgroundChecker); } \
  NS_SCRIPTABLE NS_IMETHOD SelectUpdate(nsIUpdate **updates, PRUint32 updateCount, nsIUpdate * *_retval NS_OUTPARAM) { return _to SelectUpdate(updates, updateCount, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddDownloadListener(nsIRequestObserver *listener) { return _to AddDownloadListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveDownloadListener(nsIRequestObserver *listener) { return _to RemoveDownloadListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD DownloadUpdate(nsIUpdate *update, PRBool background, nsAString & _retval NS_OUTPARAM) { return _to DownloadUpdate(update, background, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD PauseDownload(void) { return _to PauseDownload(); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsDownloading(PRBool *aIsDownloading) { return _to GetIsDownloading(aIsDownloading); } \
  NS_SCRIPTABLE NS_IMETHOD GetCanCheckForUpdates(PRBool *aCanCheckForUpdates) { return _to GetCanCheckForUpdates(aCanCheckForUpdates); } \
  NS_SCRIPTABLE NS_IMETHOD GetCanApplyUpdates(PRBool *aCanApplyUpdates) { return _to GetCanApplyUpdates(aCanApplyUpdates); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIAPPLICATIONUPDATESERVICE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetBackgroundChecker(nsIUpdateChecker * *aBackgroundChecker) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBackgroundChecker(aBackgroundChecker); } \
  NS_SCRIPTABLE NS_IMETHOD SelectUpdate(nsIUpdate **updates, PRUint32 updateCount, nsIUpdate * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SelectUpdate(updates, updateCount, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddDownloadListener(nsIRequestObserver *listener) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDownloadListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveDownloadListener(nsIRequestObserver *listener) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveDownloadListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD DownloadUpdate(nsIUpdate *update, PRBool background, nsAString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->DownloadUpdate(update, background, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD PauseDownload(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->PauseDownload(); } \
  NS_SCRIPTABLE NS_IMETHOD GetIsDownloading(PRBool *aIsDownloading) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsDownloading(aIsDownloading); } \
  NS_SCRIPTABLE NS_IMETHOD GetCanCheckForUpdates(PRBool *aCanCheckForUpdates) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCanCheckForUpdates(aCanCheckForUpdates); } \
  NS_SCRIPTABLE NS_IMETHOD GetCanApplyUpdates(PRBool *aCanApplyUpdates) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCanApplyUpdates(aCanApplyUpdates); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsApplicationUpdateService : public nsIApplicationUpdateService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIAPPLICATIONUPDATESERVICE

  nsApplicationUpdateService();

private:
  ~nsApplicationUpdateService();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsApplicationUpdateService, nsIApplicationUpdateService)

nsApplicationUpdateService::nsApplicationUpdateService()
{
  /* member initializers and constructor code */
}

nsApplicationUpdateService::~nsApplicationUpdateService()
{
  /* destructor code */
}

/* readonly attribute nsIUpdateChecker backgroundChecker; */
NS_IMETHODIMP nsApplicationUpdateService::GetBackgroundChecker(nsIUpdateChecker * *aBackgroundChecker)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIUpdate selectUpdate ([array, size_is (updateCount)] in nsIUpdate updates, in unsigned long updateCount); */
NS_IMETHODIMP nsApplicationUpdateService::SelectUpdate(nsIUpdate **updates, PRUint32 updateCount, nsIUpdate * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addDownloadListener (in nsIRequestObserver listener); */
NS_IMETHODIMP nsApplicationUpdateService::AddDownloadListener(nsIRequestObserver *listener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeDownloadListener (in nsIRequestObserver listener); */
NS_IMETHODIMP nsApplicationUpdateService::RemoveDownloadListener(nsIRequestObserver *listener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AString downloadUpdate (in nsIUpdate update, in boolean background); */
NS_IMETHODIMP nsApplicationUpdateService::DownloadUpdate(nsIUpdate *update, PRBool background, nsAString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void pauseDownload (); */
NS_IMETHODIMP nsApplicationUpdateService::PauseDownload()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean isDownloading; */
NS_IMETHODIMP nsApplicationUpdateService::GetIsDownloading(PRBool *aIsDownloading)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean canCheckForUpdates; */
NS_IMETHODIMP nsApplicationUpdateService::GetCanCheckForUpdates(PRBool *aCanCheckForUpdates)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean canApplyUpdates; */
NS_IMETHODIMP nsApplicationUpdateService::GetCanApplyUpdates(PRBool *aCanApplyUpdates)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIUpdateManager */
#define NS_IUPDATEMANAGER_IID_STR "fede66a9-9f96-4507-a22a-775ee885577e"

#define NS_IUPDATEMANAGER_IID \
  {0xfede66a9, 0x9f96, 0x4507, \
    { 0xa2, 0x2a, 0x77, 0x5e, 0xe8, 0x85, 0x57, 0x7e }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUpdateManager : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUPDATEMANAGER_IID)

  /* nsIUpdate getUpdateAt (in long index); */
  NS_SCRIPTABLE NS_IMETHOD GetUpdateAt(PRInt32 index, nsIUpdate * *_retval NS_OUTPARAM) = 0;

  /* readonly attribute long updateCount; */
  NS_SCRIPTABLE NS_IMETHOD GetUpdateCount(PRInt32 *aUpdateCount) = 0;

  /* attribute nsIUpdate activeUpdate; */
  NS_SCRIPTABLE NS_IMETHOD GetActiveUpdate(nsIUpdate * *aActiveUpdate) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetActiveUpdate(nsIUpdate *aActiveUpdate) = 0;

  /* void saveUpdates (); */
  NS_SCRIPTABLE NS_IMETHOD SaveUpdates(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUpdateManager, NS_IUPDATEMANAGER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUPDATEMANAGER \
  NS_SCRIPTABLE NS_IMETHOD GetUpdateAt(PRInt32 index, nsIUpdate * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetUpdateCount(PRInt32 *aUpdateCount); \
  NS_SCRIPTABLE NS_IMETHOD GetActiveUpdate(nsIUpdate * *aActiveUpdate); \
  NS_SCRIPTABLE NS_IMETHOD SetActiveUpdate(nsIUpdate *aActiveUpdate); \
  NS_SCRIPTABLE NS_IMETHOD SaveUpdates(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUPDATEMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetUpdateAt(PRInt32 index, nsIUpdate * *_retval NS_OUTPARAM) { return _to GetUpdateAt(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUpdateCount(PRInt32 *aUpdateCount) { return _to GetUpdateCount(aUpdateCount); } \
  NS_SCRIPTABLE NS_IMETHOD GetActiveUpdate(nsIUpdate * *aActiveUpdate) { return _to GetActiveUpdate(aActiveUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SetActiveUpdate(nsIUpdate *aActiveUpdate) { return _to SetActiveUpdate(aActiveUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SaveUpdates(void) { return _to SaveUpdates(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUPDATEMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetUpdateAt(PRInt32 index, nsIUpdate * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUpdateAt(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUpdateCount(PRInt32 *aUpdateCount) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUpdateCount(aUpdateCount); } \
  NS_SCRIPTABLE NS_IMETHOD GetActiveUpdate(nsIUpdate * *aActiveUpdate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetActiveUpdate(aActiveUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SetActiveUpdate(nsIUpdate *aActiveUpdate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetActiveUpdate(aActiveUpdate); } \
  NS_SCRIPTABLE NS_IMETHOD SaveUpdates(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->SaveUpdates(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUpdateManager : public nsIUpdateManager
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUPDATEMANAGER

  nsUpdateManager();

private:
  ~nsUpdateManager();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUpdateManager, nsIUpdateManager)

nsUpdateManager::nsUpdateManager()
{
  /* member initializers and constructor code */
}

nsUpdateManager::~nsUpdateManager()
{
  /* destructor code */
}

/* nsIUpdate getUpdateAt (in long index); */
NS_IMETHODIMP nsUpdateManager::GetUpdateAt(PRInt32 index, nsIUpdate * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long updateCount; */
NS_IMETHODIMP nsUpdateManager::GetUpdateCount(PRInt32 *aUpdateCount)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIUpdate activeUpdate; */
NS_IMETHODIMP nsUpdateManager::GetActiveUpdate(nsIUpdate * *aActiveUpdate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUpdateManager::SetActiveUpdate(nsIUpdate *aActiveUpdate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void saveUpdates (); */
NS_IMETHODIMP nsUpdateManager::SaveUpdates()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIUpdatePrompt */
#define NS_IUPDATEPROMPT_IID_STR "599fd3c6-ec68-4499-ada5-2997739c97a6"

#define NS_IUPDATEPROMPT_IID \
  {0x599fd3c6, 0xec68, 0x4499, \
    { 0xad, 0xa5, 0x29, 0x97, 0x73, 0x9c, 0x97, 0xa6 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUpdatePrompt : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUPDATEPROMPT_IID)

  /* void checkForUpdates (); */
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(void) = 0;

  /* void showUpdateAvailable (in nsIUpdate update); */
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateAvailable(nsIUpdate *update) = 0;

  /* void showUpdateDownloaded (in nsIUpdate update, [optional] in boolean background); */
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateDownloaded(nsIUpdate *update, PRBool background) = 0;

  /* void showUpdateInstalled (); */
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateInstalled(void) = 0;

  /* void showUpdateError (in nsIUpdate update); */
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateError(nsIUpdate *update) = 0;

  /* void showUpdateHistory (in nsIDOMWindow parent); */
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateHistory(nsIDOMWindow *parent) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUpdatePrompt, NS_IUPDATEPROMPT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUPDATEPROMPT \
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(void); \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateAvailable(nsIUpdate *update); \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateDownloaded(nsIUpdate *update, PRBool background); \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateInstalled(void); \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateError(nsIUpdate *update); \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateHistory(nsIDOMWindow *parent); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUPDATEPROMPT(_to) \
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(void) { return _to CheckForUpdates(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateAvailable(nsIUpdate *update) { return _to ShowUpdateAvailable(update); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateDownloaded(nsIUpdate *update, PRBool background) { return _to ShowUpdateDownloaded(update, background); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateInstalled(void) { return _to ShowUpdateInstalled(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateError(nsIUpdate *update) { return _to ShowUpdateError(update); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateHistory(nsIDOMWindow *parent) { return _to ShowUpdateHistory(parent); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUPDATEPROMPT(_to) \
  NS_SCRIPTABLE NS_IMETHOD CheckForUpdates(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->CheckForUpdates(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateAvailable(nsIUpdate *update) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowUpdateAvailable(update); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateDownloaded(nsIUpdate *update, PRBool background) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowUpdateDownloaded(update, background); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateInstalled(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowUpdateInstalled(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateError(nsIUpdate *update) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowUpdateError(update); } \
  NS_SCRIPTABLE NS_IMETHOD ShowUpdateHistory(nsIDOMWindow *parent) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowUpdateHistory(parent); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUpdatePrompt : public nsIUpdatePrompt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUPDATEPROMPT

  nsUpdatePrompt();

private:
  ~nsUpdatePrompt();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUpdatePrompt, nsIUpdatePrompt)

nsUpdatePrompt::nsUpdatePrompt()
{
  /* member initializers and constructor code */
}

nsUpdatePrompt::~nsUpdatePrompt()
{
  /* destructor code */
}

/* void checkForUpdates (); */
NS_IMETHODIMP nsUpdatePrompt::CheckForUpdates()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void showUpdateAvailable (in nsIUpdate update); */
NS_IMETHODIMP nsUpdatePrompt::ShowUpdateAvailable(nsIUpdate *update)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void showUpdateDownloaded (in nsIUpdate update, [optional] in boolean background); */
NS_IMETHODIMP nsUpdatePrompt::ShowUpdateDownloaded(nsIUpdate *update, PRBool background)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void showUpdateInstalled (); */
NS_IMETHODIMP nsUpdatePrompt::ShowUpdateInstalled()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void showUpdateError (in nsIUpdate update); */
NS_IMETHODIMP nsUpdatePrompt::ShowUpdateError(nsIUpdate *update)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void showUpdateHistory (in nsIDOMWindow parent); */
NS_IMETHODIMP nsUpdatePrompt::ShowUpdateHistory(nsIDOMWindow *parent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIUpdateService_h__ */
