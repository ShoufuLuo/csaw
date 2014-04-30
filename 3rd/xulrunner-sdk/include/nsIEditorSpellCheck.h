/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/editor/idl/nsIEditorSpellCheck.idl
 */

#ifndef __gen_nsIEditorSpellCheck_h__
#define __gen_nsIEditorSpellCheck_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIEditor; /* forward declaration */

class nsITextServicesFilter; /* forward declaration */


/* starting interface:    nsIEditorSpellCheck */
#define NS_IEDITORSPELLCHECK_IID_STR "90c93610-c116-44ab-9793-62dccb9f43ce"

#define NS_IEDITORSPELLCHECK_IID \
  {0x90c93610, 0xc116, 0x44ab, \
    { 0x97, 0x93, 0x62, 0xdc, 0xcb, 0x9f, 0x43, 0xce }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIEditorSpellCheck : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IEDITORSPELLCHECK_IID)

  /* boolean canSpellCheck (); */
  NS_SCRIPTABLE NS_IMETHOD CanSpellCheck(PRBool *_retval NS_OUTPARAM) = 0;

  /* void InitSpellChecker (in nsIEditor editor, in boolean enableSelectionChecking); */
  NS_SCRIPTABLE NS_IMETHOD InitSpellChecker(nsIEditor *editor, PRBool enableSelectionChecking) = 0;

  /* wstring GetNextMisspelledWord (); */
  NS_SCRIPTABLE NS_IMETHOD GetNextMisspelledWord(PRUnichar * *_retval NS_OUTPARAM) = 0;

  /* wstring GetSuggestedWord (); */
  NS_SCRIPTABLE NS_IMETHOD GetSuggestedWord(PRUnichar * *_retval NS_OUTPARAM) = 0;

  /* boolean CheckCurrentWord (in wstring suggestedWord); */
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWord(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM) = 0;

  /* void ReplaceWord (in wstring misspelledWord, in wstring replaceWord, in boolean allOccurrences); */
  NS_SCRIPTABLE NS_IMETHOD ReplaceWord(const PRUnichar * misspelledWord, const PRUnichar * replaceWord, PRBool allOccurrences) = 0;

  /* void IgnoreWordAllOccurrences (in wstring word); */
  NS_SCRIPTABLE NS_IMETHOD IgnoreWordAllOccurrences(const PRUnichar * word) = 0;

  /* void GetPersonalDictionary (); */
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionary(void) = 0;

  /* wstring GetPersonalDictionaryWord (); */
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionaryWord(PRUnichar * *_retval NS_OUTPARAM) = 0;

  /* void AddWordToDictionary (in wstring word); */
  NS_SCRIPTABLE NS_IMETHOD AddWordToDictionary(const PRUnichar * word) = 0;

  /* void RemoveWordFromDictionary (in wstring word); */
  NS_SCRIPTABLE NS_IMETHOD RemoveWordFromDictionary(const PRUnichar * word) = 0;

  /* void GetDictionaryList ([array, size_is (count)] out wstring dictionaryList, out PRUint32 count); */
  NS_SCRIPTABLE NS_IMETHOD GetDictionaryList(PRUnichar * **dictionaryList NS_OUTPARAM, PRUint32 *count NS_OUTPARAM) = 0;

  /* wstring GetCurrentDictionary (); */
  NS_SCRIPTABLE NS_IMETHOD GetCurrentDictionary(PRUnichar * *_retval NS_OUTPARAM) = 0;

  /* void SetCurrentDictionary (in wstring dictionary); */
  NS_SCRIPTABLE NS_IMETHOD SetCurrentDictionary(const PRUnichar * dictionary) = 0;

  /* void saveDefaultDictionary (); */
  NS_SCRIPTABLE NS_IMETHOD SaveDefaultDictionary(void) = 0;

  /* void UninitSpellChecker (); */
  NS_SCRIPTABLE NS_IMETHOD UninitSpellChecker(void) = 0;

  /* void setFilter (in nsITextServicesFilter filter); */
  NS_SCRIPTABLE NS_IMETHOD SetFilter(nsITextServicesFilter *filter) = 0;

  /* boolean CheckCurrentWordNoSuggest (in wstring suggestedWord); */
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWordNoSuggest(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIEditorSpellCheck, NS_IEDITORSPELLCHECK_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIEDITORSPELLCHECK \
  NS_SCRIPTABLE NS_IMETHOD CanSpellCheck(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD InitSpellChecker(nsIEditor *editor, PRBool enableSelectionChecking); \
  NS_SCRIPTABLE NS_IMETHOD GetNextMisspelledWord(PRUnichar * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetSuggestedWord(PRUnichar * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWord(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD ReplaceWord(const PRUnichar * misspelledWord, const PRUnichar * replaceWord, PRBool allOccurrences); \
  NS_SCRIPTABLE NS_IMETHOD IgnoreWordAllOccurrences(const PRUnichar * word); \
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionary(void); \
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionaryWord(PRUnichar * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AddWordToDictionary(const PRUnichar * word); \
  NS_SCRIPTABLE NS_IMETHOD RemoveWordFromDictionary(const PRUnichar * word); \
  NS_SCRIPTABLE NS_IMETHOD GetDictionaryList(PRUnichar * **dictionaryList NS_OUTPARAM, PRUint32 *count NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentDictionary(PRUnichar * *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetCurrentDictionary(const PRUnichar * dictionary); \
  NS_SCRIPTABLE NS_IMETHOD SaveDefaultDictionary(void); \
  NS_SCRIPTABLE NS_IMETHOD UninitSpellChecker(void); \
  NS_SCRIPTABLE NS_IMETHOD SetFilter(nsITextServicesFilter *filter); \
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWordNoSuggest(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIEDITORSPELLCHECK(_to) \
  NS_SCRIPTABLE NS_IMETHOD CanSpellCheck(PRBool *_retval NS_OUTPARAM) { return _to CanSpellCheck(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD InitSpellChecker(nsIEditor *editor, PRBool enableSelectionChecking) { return _to InitSpellChecker(editor, enableSelectionChecking); } \
  NS_SCRIPTABLE NS_IMETHOD GetNextMisspelledWord(PRUnichar * *_retval NS_OUTPARAM) { return _to GetNextMisspelledWord(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetSuggestedWord(PRUnichar * *_retval NS_OUTPARAM) { return _to GetSuggestedWord(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWord(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM) { return _to CheckCurrentWord(suggestedWord, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD ReplaceWord(const PRUnichar * misspelledWord, const PRUnichar * replaceWord, PRBool allOccurrences) { return _to ReplaceWord(misspelledWord, replaceWord, allOccurrences); } \
  NS_SCRIPTABLE NS_IMETHOD IgnoreWordAllOccurrences(const PRUnichar * word) { return _to IgnoreWordAllOccurrences(word); } \
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionary(void) { return _to GetPersonalDictionary(); } \
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionaryWord(PRUnichar * *_retval NS_OUTPARAM) { return _to GetPersonalDictionaryWord(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddWordToDictionary(const PRUnichar * word) { return _to AddWordToDictionary(word); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveWordFromDictionary(const PRUnichar * word) { return _to RemoveWordFromDictionary(word); } \
  NS_SCRIPTABLE NS_IMETHOD GetDictionaryList(PRUnichar * **dictionaryList NS_OUTPARAM, PRUint32 *count NS_OUTPARAM) { return _to GetDictionaryList(dictionaryList, count); } \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentDictionary(PRUnichar * *_retval NS_OUTPARAM) { return _to GetCurrentDictionary(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCurrentDictionary(const PRUnichar * dictionary) { return _to SetCurrentDictionary(dictionary); } \
  NS_SCRIPTABLE NS_IMETHOD SaveDefaultDictionary(void) { return _to SaveDefaultDictionary(); } \
  NS_SCRIPTABLE NS_IMETHOD UninitSpellChecker(void) { return _to UninitSpellChecker(); } \
  NS_SCRIPTABLE NS_IMETHOD SetFilter(nsITextServicesFilter *filter) { return _to SetFilter(filter); } \
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWordNoSuggest(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM) { return _to CheckCurrentWordNoSuggest(suggestedWord, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIEDITORSPELLCHECK(_to) \
  NS_SCRIPTABLE NS_IMETHOD CanSpellCheck(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->CanSpellCheck(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD InitSpellChecker(nsIEditor *editor, PRBool enableSelectionChecking) { return !_to ? NS_ERROR_NULL_POINTER : _to->InitSpellChecker(editor, enableSelectionChecking); } \
  NS_SCRIPTABLE NS_IMETHOD GetNextMisspelledWord(PRUnichar * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNextMisspelledWord(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetSuggestedWord(PRUnichar * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSuggestedWord(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWord(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->CheckCurrentWord(suggestedWord, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD ReplaceWord(const PRUnichar * misspelledWord, const PRUnichar * replaceWord, PRBool allOccurrences) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReplaceWord(misspelledWord, replaceWord, allOccurrences); } \
  NS_SCRIPTABLE NS_IMETHOD IgnoreWordAllOccurrences(const PRUnichar * word) { return !_to ? NS_ERROR_NULL_POINTER : _to->IgnoreWordAllOccurrences(word); } \
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionary(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPersonalDictionary(); } \
  NS_SCRIPTABLE NS_IMETHOD GetPersonalDictionaryWord(PRUnichar * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPersonalDictionaryWord(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddWordToDictionary(const PRUnichar * word) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddWordToDictionary(word); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveWordFromDictionary(const PRUnichar * word) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveWordFromDictionary(word); } \
  NS_SCRIPTABLE NS_IMETHOD GetDictionaryList(PRUnichar * **dictionaryList NS_OUTPARAM, PRUint32 *count NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDictionaryList(dictionaryList, count); } \
  NS_SCRIPTABLE NS_IMETHOD GetCurrentDictionary(PRUnichar * *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCurrentDictionary(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCurrentDictionary(const PRUnichar * dictionary) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCurrentDictionary(dictionary); } \
  NS_SCRIPTABLE NS_IMETHOD SaveDefaultDictionary(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->SaveDefaultDictionary(); } \
  NS_SCRIPTABLE NS_IMETHOD UninitSpellChecker(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->UninitSpellChecker(); } \
  NS_SCRIPTABLE NS_IMETHOD SetFilter(nsITextServicesFilter *filter) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFilter(filter); } \
  NS_SCRIPTABLE NS_IMETHOD CheckCurrentWordNoSuggest(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->CheckCurrentWordNoSuggest(suggestedWord, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsEditorSpellCheck : public nsIEditorSpellCheck
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIEDITORSPELLCHECK

  nsEditorSpellCheck();

private:
  ~nsEditorSpellCheck();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsEditorSpellCheck, nsIEditorSpellCheck)

nsEditorSpellCheck::nsEditorSpellCheck()
{
  /* member initializers and constructor code */
}

nsEditorSpellCheck::~nsEditorSpellCheck()
{
  /* destructor code */
}

/* boolean canSpellCheck (); */
NS_IMETHODIMP nsEditorSpellCheck::CanSpellCheck(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void InitSpellChecker (in nsIEditor editor, in boolean enableSelectionChecking); */
NS_IMETHODIMP nsEditorSpellCheck::InitSpellChecker(nsIEditor *editor, PRBool enableSelectionChecking)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring GetNextMisspelledWord (); */
NS_IMETHODIMP nsEditorSpellCheck::GetNextMisspelledWord(PRUnichar * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring GetSuggestedWord (); */
NS_IMETHODIMP nsEditorSpellCheck::GetSuggestedWord(PRUnichar * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean CheckCurrentWord (in wstring suggestedWord); */
NS_IMETHODIMP nsEditorSpellCheck::CheckCurrentWord(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ReplaceWord (in wstring misspelledWord, in wstring replaceWord, in boolean allOccurrences); */
NS_IMETHODIMP nsEditorSpellCheck::ReplaceWord(const PRUnichar * misspelledWord, const PRUnichar * replaceWord, PRBool allOccurrences)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void IgnoreWordAllOccurrences (in wstring word); */
NS_IMETHODIMP nsEditorSpellCheck::IgnoreWordAllOccurrences(const PRUnichar * word)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetPersonalDictionary (); */
NS_IMETHODIMP nsEditorSpellCheck::GetPersonalDictionary()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring GetPersonalDictionaryWord (); */
NS_IMETHODIMP nsEditorSpellCheck::GetPersonalDictionaryWord(PRUnichar * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddWordToDictionary (in wstring word); */
NS_IMETHODIMP nsEditorSpellCheck::AddWordToDictionary(const PRUnichar * word)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void RemoveWordFromDictionary (in wstring word); */
NS_IMETHODIMP nsEditorSpellCheck::RemoveWordFromDictionary(const PRUnichar * word)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetDictionaryList ([array, size_is (count)] out wstring dictionaryList, out PRUint32 count); */
NS_IMETHODIMP nsEditorSpellCheck::GetDictionaryList(PRUnichar * **dictionaryList NS_OUTPARAM, PRUint32 *count NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring GetCurrentDictionary (); */
NS_IMETHODIMP nsEditorSpellCheck::GetCurrentDictionary(PRUnichar * *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCurrentDictionary (in wstring dictionary); */
NS_IMETHODIMP nsEditorSpellCheck::SetCurrentDictionary(const PRUnichar * dictionary)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void saveDefaultDictionary (); */
NS_IMETHODIMP nsEditorSpellCheck::SaveDefaultDictionary()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UninitSpellChecker (); */
NS_IMETHODIMP nsEditorSpellCheck::UninitSpellChecker()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setFilter (in nsITextServicesFilter filter); */
NS_IMETHODIMP nsEditorSpellCheck::SetFilter(nsITextServicesFilter *filter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean CheckCurrentWordNoSuggest (in wstring suggestedWord); */
NS_IMETHODIMP nsEditorSpellCheck::CheckCurrentWordNoSuggest(const PRUnichar * suggestedWord, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIEditorSpellCheck_h__ */
