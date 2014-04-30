/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IByzauthAdapter.idl
 */

#ifndef __gen_IByzauthAdapter_h__
#define __gen_IByzauthAdapter_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IByzantineAuthenticationAdapter */
#define IBYZANTINEAUTHENTICATIONADAPTER_IID_STR "f3774746-6f48-4f28-9dc9-cee3e5cef5a5"

#define IBYZANTINEAUTHENTICATIONADAPTER_IID \
  {0xf3774746, 0x6f48, 0x4f28, \
    { 0x9d, 0xc9, 0xce, 0xe3, 0xe5, 0xce, 0xf5, 0xa5 }}

/**
  * Interface for automatic mail authentication in thunderbird based on the 
  * authentication library interface given in publickeyinfectionadapter.h 
  */
class NS_NO_VTABLE NS_SCRIPTABLE IByzantineAuthenticationAdapter : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IBYZANTINEAUTHENTICATIONADAPTER_IID)

  /* boolean receiveIncomingAuthenticationMessage (in string peer, in string mesg); */
  NS_SCRIPTABLE NS_IMETHOD ReceiveIncomingAuthenticationMessage(const char *peer, const char *mesg, PRBool *_retval NS_OUTPARAM) = 0;

  /* string sendOutgoingAuthenticationMessage (in unsigned long count, [array, size_is (count)] in string dest); */
  NS_SCRIPTABLE NS_IMETHOD SendOutgoingAuthenticationMessage(PRUint32 count, const char **dest, char **_retval NS_OUTPARAM) = 0;

  /* boolean generateNewKeyPair (in unsigned long keybits); */
  NS_SCRIPTABLE NS_IMETHOD GenerateNewKeyPair(PRUint32 keybits, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean setTrusted (in string peer); */
  NS_SCRIPTABLE NS_IMETHOD SetTrusted(const char *peer, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean setUntrusted (in string peer); */
  NS_SCRIPTABLE NS_IMETHOD SetUntrusted(const char *peer, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean setProbationary (in string peer); */
  NS_SCRIPTABLE NS_IMETHOD SetProbationary(const char *peer, PRBool *_retval NS_OUTPARAM) = 0;

  /* void getTrusted (out PRUint32 count, [array, retval, size_is (count)] out string trusted); */
  NS_SCRIPTABLE NS_IMETHOD GetTrusted(PRUint32 *count NS_OUTPARAM, char ***trusted NS_OUTPARAM) = 0;

  /* void getUntrusted (out PRUint32 count, [array, retval, size_is (count)] out string untrusted); */
  NS_SCRIPTABLE NS_IMETHOD GetUntrusted(PRUint32 *count NS_OUTPARAM, char ***untrusted NS_OUTPARAM) = 0;

  /* void getProbationary (out PRUint32 count, [array, retval, size_is (count)] out string probationary); */
  NS_SCRIPTABLE NS_IMETHOD GetProbationary(PRUint32 *count NS_OUTPARAM, char ***probationary NS_OUTPARAM) = 0;

  /* string getAuthenticatedKey (in string peer, out long trust_value, out boolean unknown); */
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticatedKey(const char *peer, PRInt32 *trust_value NS_OUTPARAM, PRBool *unknown NS_OUTPARAM, char **_retval NS_OUTPARAM) = 0;

  /* void getAuthenticators (in string peer, out PRUint32 count, [array, retval, size_is (count)] out string authenticators); */
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticators(const char *peer, PRUint32 *count NS_OUTPARAM, char ***authenticators NS_OUTPARAM) = 0;

  /* boolean coldStart (in long keybits, in string selfname, in unsigned long count, [array, size_is (count)] in string bootstrap, in string serializefilename, in long ttl, in long tgshint, in long payload); */
  NS_SCRIPTABLE NS_IMETHOD ColdStart(PRInt32 keybits, const char *selfname, PRUint32 count, const char **bootstrap, const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean warmStart (in string serializefilename, in long ttl, in long tgshint, in long payload); */
  NS_SCRIPTABLE NS_IMETHOD WarmStart(const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean Stop (); */
  NS_SCRIPTABLE NS_IMETHOD Stop(PRBool *_retval NS_OUTPARAM) = 0;

  /* string Sign (in string mesg); */
  NS_SCRIPTABLE NS_IMETHOD Sign(const char *mesg, char **_retval NS_OUTPARAM) = 0;

  /* boolean Verify (in string mesg, in string sig, in string peer, out boolean unknown); */
  NS_SCRIPTABLE NS_IMETHOD Verify(const char *mesg, const char *sig, const char *peer, PRBool *unknown NS_OUTPARAM, PRBool *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IByzantineAuthenticationAdapter, IBYZANTINEAUTHENTICATIONADAPTER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IBYZANTINEAUTHENTICATIONADAPTER \
  NS_SCRIPTABLE NS_IMETHOD ReceiveIncomingAuthenticationMessage(const char *peer, const char *mesg, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SendOutgoingAuthenticationMessage(PRUint32 count, const char **dest, char **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GenerateNewKeyPair(PRUint32 keybits, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetTrusted(const char *peer, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetUntrusted(const char *peer, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetProbationary(const char *peer, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetTrusted(PRUint32 *count NS_OUTPARAM, char ***trusted NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetUntrusted(PRUint32 *count NS_OUTPARAM, char ***untrusted NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetProbationary(PRUint32 *count NS_OUTPARAM, char ***probationary NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticatedKey(const char *peer, PRInt32 *trust_value NS_OUTPARAM, PRBool *unknown NS_OUTPARAM, char **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticators(const char *peer, PRUint32 *count NS_OUTPARAM, char ***authenticators NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD ColdStart(PRInt32 keybits, const char *selfname, PRUint32 count, const char **bootstrap, const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD WarmStart(const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD Stop(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD Sign(const char *mesg, char **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD Verify(const char *mesg, const char *sig, const char *peer, PRBool *unknown NS_OUTPARAM, PRBool *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IBYZANTINEAUTHENTICATIONADAPTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD ReceiveIncomingAuthenticationMessage(const char *peer, const char *mesg, PRBool *_retval NS_OUTPARAM) { return _to ReceiveIncomingAuthenticationMessage(peer, mesg, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SendOutgoingAuthenticationMessage(PRUint32 count, const char **dest, char **_retval NS_OUTPARAM) { return _to SendOutgoingAuthenticationMessage(count, dest, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GenerateNewKeyPair(PRUint32 keybits, PRBool *_retval NS_OUTPARAM) { return _to GenerateNewKeyPair(keybits, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetTrusted(const char *peer, PRBool *_retval NS_OUTPARAM) { return _to SetTrusted(peer, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetUntrusted(const char *peer, PRBool *_retval NS_OUTPARAM) { return _to SetUntrusted(peer, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetProbationary(const char *peer, PRBool *_retval NS_OUTPARAM) { return _to SetProbationary(peer, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTrusted(PRUint32 *count NS_OUTPARAM, char ***trusted NS_OUTPARAM) { return _to GetTrusted(count, trusted); } \
  NS_SCRIPTABLE NS_IMETHOD GetUntrusted(PRUint32 *count NS_OUTPARAM, char ***untrusted NS_OUTPARAM) { return _to GetUntrusted(count, untrusted); } \
  NS_SCRIPTABLE NS_IMETHOD GetProbationary(PRUint32 *count NS_OUTPARAM, char ***probationary NS_OUTPARAM) { return _to GetProbationary(count, probationary); } \
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticatedKey(const char *peer, PRInt32 *trust_value NS_OUTPARAM, PRBool *unknown NS_OUTPARAM, char **_retval NS_OUTPARAM) { return _to GetAuthenticatedKey(peer, trust_value, unknown, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticators(const char *peer, PRUint32 *count NS_OUTPARAM, char ***authenticators NS_OUTPARAM) { return _to GetAuthenticators(peer, count, authenticators); } \
  NS_SCRIPTABLE NS_IMETHOD ColdStart(PRInt32 keybits, const char *selfname, PRUint32 count, const char **bootstrap, const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM) { return _to ColdStart(keybits, selfname, count, bootstrap, serializefilename, ttl, tgshint, payload, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD WarmStart(const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM) { return _to WarmStart(serializefilename, ttl, tgshint, payload, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(PRBool *_retval NS_OUTPARAM) { return _to Stop(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD Sign(const char *mesg, char **_retval NS_OUTPARAM) { return _to Sign(mesg, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD Verify(const char *mesg, const char *sig, const char *peer, PRBool *unknown NS_OUTPARAM, PRBool *_retval NS_OUTPARAM) { return _to Verify(mesg, sig, peer, unknown, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IBYZANTINEAUTHENTICATIONADAPTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD ReceiveIncomingAuthenticationMessage(const char *peer, const char *mesg, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReceiveIncomingAuthenticationMessage(peer, mesg, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SendOutgoingAuthenticationMessage(PRUint32 count, const char **dest, char **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SendOutgoingAuthenticationMessage(count, dest, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GenerateNewKeyPair(PRUint32 keybits, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GenerateNewKeyPair(keybits, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetTrusted(const char *peer, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTrusted(peer, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetUntrusted(const char *peer, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUntrusted(peer, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetProbationary(const char *peer, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProbationary(peer, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTrusted(PRUint32 *count NS_OUTPARAM, char ***trusted NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTrusted(count, trusted); } \
  NS_SCRIPTABLE NS_IMETHOD GetUntrusted(PRUint32 *count NS_OUTPARAM, char ***untrusted NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUntrusted(count, untrusted); } \
  NS_SCRIPTABLE NS_IMETHOD GetProbationary(PRUint32 *count NS_OUTPARAM, char ***probationary NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProbationary(count, probationary); } \
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticatedKey(const char *peer, PRInt32 *trust_value NS_OUTPARAM, PRBool *unknown NS_OUTPARAM, char **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAuthenticatedKey(peer, trust_value, unknown, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAuthenticators(const char *peer, PRUint32 *count NS_OUTPARAM, char ***authenticators NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAuthenticators(peer, count, authenticators); } \
  NS_SCRIPTABLE NS_IMETHOD ColdStart(PRInt32 keybits, const char *selfname, PRUint32 count, const char **bootstrap, const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->ColdStart(keybits, selfname, count, bootstrap, serializefilename, ttl, tgshint, payload, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD WarmStart(const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->WarmStart(serializefilename, ttl, tgshint, payload, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD Sign(const char *mesg, char **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Sign(mesg, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD Verify(const char *mesg, const char *sig, const char *peer, PRBool *unknown NS_OUTPARAM, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Verify(mesg, sig, peer, unknown, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IByzantineAuthenticationAdapter
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IBYZANTINEAUTHENTICATIONADAPTER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IByzantineAuthenticationAdapter)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* boolean receiveIncomingAuthenticationMessage (in string peer, in string mesg); */
NS_IMETHODIMP _MYCLASS_::ReceiveIncomingAuthenticationMessage(const char *peer, const char *mesg, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string sendOutgoingAuthenticationMessage (in unsigned long count, [array, size_is (count)] in string dest); */
NS_IMETHODIMP _MYCLASS_::SendOutgoingAuthenticationMessage(PRUint32 count, const char **dest, char **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean generateNewKeyPair (in unsigned long keybits); */
NS_IMETHODIMP _MYCLASS_::GenerateNewKeyPair(PRUint32 keybits, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean setTrusted (in string peer); */
NS_IMETHODIMP _MYCLASS_::SetTrusted(const char *peer, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean setUntrusted (in string peer); */
NS_IMETHODIMP _MYCLASS_::SetUntrusted(const char *peer, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean setProbationary (in string peer); */
NS_IMETHODIMP _MYCLASS_::SetProbationary(const char *peer, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getTrusted (out PRUint32 count, [array, retval, size_is (count)] out string trusted); */
NS_IMETHODIMP _MYCLASS_::GetTrusted(PRUint32 *count NS_OUTPARAM, char ***trusted NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getUntrusted (out PRUint32 count, [array, retval, size_is (count)] out string untrusted); */
NS_IMETHODIMP _MYCLASS_::GetUntrusted(PRUint32 *count NS_OUTPARAM, char ***untrusted NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getProbationary (out PRUint32 count, [array, retval, size_is (count)] out string probationary); */
NS_IMETHODIMP _MYCLASS_::GetProbationary(PRUint32 *count NS_OUTPARAM, char ***probationary NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string getAuthenticatedKey (in string peer, out long trust_value, out boolean unknown); */
NS_IMETHODIMP _MYCLASS_::GetAuthenticatedKey(const char *peer, PRInt32 *trust_value NS_OUTPARAM, PRBool *unknown NS_OUTPARAM, char **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getAuthenticators (in string peer, out PRUint32 count, [array, retval, size_is (count)] out string authenticators); */
NS_IMETHODIMP _MYCLASS_::GetAuthenticators(const char *peer, PRUint32 *count NS_OUTPARAM, char ***authenticators NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean coldStart (in long keybits, in string selfname, in unsigned long count, [array, size_is (count)] in string bootstrap, in string serializefilename, in long ttl, in long tgshint, in long payload); */
NS_IMETHODIMP _MYCLASS_::ColdStart(PRInt32 keybits, const char *selfname, PRUint32 count, const char **bootstrap, const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean warmStart (in string serializefilename, in long ttl, in long tgshint, in long payload); */
NS_IMETHODIMP _MYCLASS_::WarmStart(const char *serializefilename, PRInt32 ttl, PRInt32 tgshint, PRInt32 payload, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean Stop (); */
NS_IMETHODIMP _MYCLASS_::Stop(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string Sign (in string mesg); */
NS_IMETHODIMP _MYCLASS_::Sign(const char *mesg, char **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean Verify (in string mesg, in string sig, in string peer, out boolean unknown); */
NS_IMETHODIMP _MYCLASS_::Verify(const char *mesg, const char *sig, const char *peer, PRBool *unknown NS_OUTPARAM, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IByzauthAdapter_h__ */
