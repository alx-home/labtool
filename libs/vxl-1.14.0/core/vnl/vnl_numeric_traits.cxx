// This is core/vnl/vnl_numeric_traits.cxx
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma implementation
#endif
//:
// \file
// \author Andrew W. Fitzgibbon, Oxford RRG
// Created: 12 Feb 98
//
//-----------------------------------------------------------------------------

#include "vnl_numeric_traits.h"
#include <vcl_complex.h>
#include <vxl_config.h>

static constexpr long s16 = 0x7fffL;
static constexpr unsigned long u16 = 0xffffL;
static constexpr long s32 = 0x7fffffffL;
static constexpr unsigned long u32 = 0xffffffffL;
#if VXL_HAS_INT_64 // need this arithmetic magic to avoid compiler errors
static constexpr vxl_uint_64 u64 = (vxl_uint_64)(-1);
static constexpr vxl_sint_64 s64 = u64/2;
#else // dummy
static constexpr long s64 = 0L;
static constexpr unsigned long u64 = 0L;
#endif

#if !VCL_STATIC_CONST_INIT_INT_NO_DEFN
constexpr bool vnl_numeric_traits<bool>::zero VCL_STATIC_CONST_INIT_INT_DEFN(false);
constexpr char vnl_numeric_traits<char>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr unsigned char vnl_numeric_traits<unsigned char>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr signed char vnl_numeric_traits<signed char>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr short vnl_numeric_traits<short>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr unsigned short vnl_numeric_traits<unsigned short>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr int vnl_numeric_traits<int>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr unsigned int vnl_numeric_traits<unsigned int>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr long vnl_numeric_traits<long>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
constexpr unsigned long vnl_numeric_traits<unsigned long>::zero VCL_STATIC_CONST_INIT_INT_DEFN(0);
#endif

#if !VCL_STATIC_CONST_INIT_INT_NO_DEFN
constexpr bool vnl_numeric_traits<bool>::one VCL_STATIC_CONST_INIT_INT_DEFN(true);
constexpr char vnl_numeric_traits<char>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr unsigned char vnl_numeric_traits<unsigned char>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr signed char vnl_numeric_traits<signed char>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr short vnl_numeric_traits<short>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr unsigned short vnl_numeric_traits<unsigned short>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr int vnl_numeric_traits<int>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr unsigned int vnl_numeric_traits<unsigned int>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr long vnl_numeric_traits<long>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
constexpr unsigned long vnl_numeric_traits<unsigned long>::one VCL_STATIC_CONST_INIT_INT_DEFN(1);
#endif

#if !VCL_STATIC_CONST_INIT_INT_NO_DEFN
constexpr bool vnl_numeric_traits<bool>::maxval VCL_STATIC_CONST_INIT_INT_DEFN(true);
constexpr char vnl_numeric_traits<char>::maxval VCL_STATIC_CONST_INIT_INT_DEFN(char(255)<0?127:255);
//  It is 127 when "char" is signed and 255 when "char" is unsigned.
constexpr unsigned char vnl_numeric_traits<unsigned char>::maxval VCL_STATIC_CONST_INIT_INT_DEFN(255);
constexpr signed char vnl_numeric_traits<signed char>::maxval VCL_STATIC_CONST_INIT_INT_DEFN(127);
#endif

constexpr short vnl_numeric_traits<short>::maxval = s16;
constexpr unsigned short vnl_numeric_traits<unsigned short>::maxval = u16;
constexpr int vnl_numeric_traits<int>::maxval = sizeof(int)==4?s32:s16;
constexpr unsigned int vnl_numeric_traits<unsigned int>::maxval = sizeof(unsigned int)==4?u32:u16;
constexpr long vnl_numeric_traits<long>::maxval = sizeof(long)==8?s64:s32;
constexpr unsigned long vnl_numeric_traits<unsigned long>::maxval = sizeof(unsigned long)==8?u64:u32;

#if !VCL_STATIC_CONST_INIT_FLOAT_NO_DEFN
constexpr float vnl_numeric_traits<float>::zero VCL_STATIC_CONST_INIT_FLOAT_DEFN(0.0F);
constexpr double vnl_numeric_traits<double>::zero VCL_STATIC_CONST_INIT_FLOAT_DEFN(0.0);
constexpr long double vnl_numeric_traits<long double>::zero VCL_STATIC_CONST_INIT_FLOAT_DEFN(0.0);

constexpr float vnl_numeric_traits<float>::one VCL_STATIC_CONST_INIT_FLOAT_DEFN(1.0F);
constexpr double vnl_numeric_traits<double>::one VCL_STATIC_CONST_INIT_FLOAT_DEFN(1.0);
constexpr long double vnl_numeric_traits<long double>::one VCL_STATIC_CONST_INIT_FLOAT_DEFN(1.0);

constexpr float vnl_numeric_traits<float>::maxval VCL_STATIC_CONST_INIT_FLOAT_DEFN(3.40282346638528860e+38F);
constexpr double vnl_numeric_traits<double>::maxval VCL_STATIC_CONST_INIT_FLOAT_DEFN(1.7976931348623157E+308);
constexpr long double vnl_numeric_traits<long double>::maxval VCL_STATIC_CONST_INIT_FLOAT_DEFN(1.7976931348623157E+308);
#endif

// Must use constructor-call syntax for initialization of complex
// specializations for Borland compiler.
constexpr vcl_complex<float> vnl_numeric_traits<vcl_complex<float> >::zero(0.0f);
constexpr vcl_complex<double> vnl_numeric_traits<vcl_complex<double> >::zero(0.0);
constexpr vcl_complex<long double> vnl_numeric_traits<vcl_complex<long double> >::zero(0.0);

constexpr vcl_complex<float> vnl_numeric_traits<vcl_complex<float> >::one(1.0f);
constexpr vcl_complex<double> vnl_numeric_traits<vcl_complex<double> >::one(1.0);
constexpr vcl_complex<long double> vnl_numeric_traits<vcl_complex<long double> >::one(1.0);

// Unknown, so undefined. Will cause link errors if someone refers to it.
//constexpr vcl_complex<float> vnl_numeric_traits<vcl_complex<float> >::maxval;
//constexpr vcl_complex<double> vnl_numeric_traits<vcl_complex<double> >::maxval;
//constexpr vcl_complex<long double> vnl_numeric_traits<vcl_complex<long double> >::maxval;

//--------------------------------------------------------------------------------
