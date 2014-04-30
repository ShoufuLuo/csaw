/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /builds/slave/rel-m-rel-xr-osx64-bld/build/gfx/src/gfxIFormats.idl
 */

#ifndef __gen_gfxIFormats_h__
#define __gen_gfxIFormats_h__


#ifndef __gen_gfxidltypes_h__
#include "gfxidltypes.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    gfxIFormats */
#define GFXIFORMATS_IID_STR "96d086e6-1dd1-11b2-b6b2-b77b59390247"

#define GFXIFORMATS_IID \
  {0x96d086e6, 0x1dd1, 0x11b2, \
    { 0xb6, 0xb2, 0xb7, 0x7b, 0x59, 0x39, 0x02, 0x47 }}

class NS_NO_VTABLE NS_SCRIPTABLE gfxIFormats {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(GFXIFORMATS_IID)

  enum { RGB = 0 };

  enum { BGR = 1 };

  enum { RGB_A1 = 2 };

  enum { BGR_A1 = 3 };

  enum { RGB_A8 = 4 };

  enum { BGR_A8 = 5 };

  enum { RGBA = 6 };

  enum { BGRA = 7 };

  enum { PAL = 8 };

  enum { PAL_A1 = 9 };

};

  NS_DEFINE_STATIC_IID_ACCESSOR(gfxIFormats, GFXIFORMATS_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_GFXIFORMATS \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_GFXIFORMATS(_to) \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_GFXIFORMATS(_to) \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public gfxIFormats
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_GFXIFORMATS

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, gfxIFormats)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_gfxIFormats_h__ */
