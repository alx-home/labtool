# vxl/config/cmake/config/CMakeLists.txt
#

PROJECT(vxl_config)
CMAKE_MINIMUM_REQUIRED(VERSION 1.8)

# When adding new configuration tests that cache results, please make
# sure they honour VXL_UPDATE_CONFIGURATION: if this variable is ON,
# redo the test and update the cached value.

#
# The tests results will be cached. Allow the user to re-run the tests
# if necessary This flag will be reset to "OFF" every time, so that
# the tests are typically just run once. Set it to ON to refresh your
# machine's configuration if you believe the test results are stale or
# wrong.
#
OPTION( VXL_UPDATE_CONFIGURATION "Re-run the configuration tests to update cached results?" "OFF" )
MARK_AS_ADVANCED( VXL_UPDATE_CONFIGURATION )

# The serial number below will allow the maintainers to force builds
# to update cached results. Whenever you make a change that makes it
# necessary for cached values to be updated, increment the serial
# number. The format follows a DNS-style numbering: the current date
# followed by a modification count within the day.
#
SET( VXL_CONFIG_SERIAL_CURRENT "2009-04-28-001" )

IF( ${VXL_CONFIG_SERIAL_CURRENT} MATCHES "^${VXL_CONFIG_SERIAL_LAST}$" )
  # The configuration is current
ELSE( ${VXL_CONFIG_SERIAL_CURRENT} MATCHES "^${VXL_CONFIG_SERIAL_LAST}$" )
  SET( VXL_UPDATE_CONFIGURATION "ON" )
  # Record that we've done the new config.
  SET( VXL_CONFIG_SERIAL_LAST ${VXL_CONFIG_SERIAL_CURRENT} CACHE INTERNAL "Serial number of last configuration" )
ENDIF( ${VXL_CONFIG_SERIAL_CURRENT} MATCHES "^${VXL_CONFIG_SERIAL_LAST}$" )



#
# Include necessary modules
#

INCLUDE (${CMAKE_ROOT}/Modules/CheckSymbolExists.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/TestBigEndian.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/CheckTypeSize.cmake)

INCLUDE (${vxl_SOURCE_DIR}/config/cmake/config/vxl_config_macros.cmake)
#
# Perform all the specific tests
#

PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_BOOL)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_TYPENAME)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_EXPORT)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_MUTABLE)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_EXPLICIT)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_DYNAMIC_CAST)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_RTTI)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_FOR_SCOPE_HACK)
  SET_INVERT(VCL_FOR_SCOPE_HACK "${VCL_FOR_SCOPE_HACK}")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_DEFAULT_VALUE)
  SET_BOOL(VCL_DEFAULT_VALUE "/* no need */" " = x")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_MEMBER_TEMPLATES)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_CAN_DO_PARTIAL_SPECIALIZATION)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_ALLOWS_INLINE_INSTANTIATION)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_NEEDS_INLINE_INSTANTIATION)
  SET_INVERT(VCL_NEEDS_INLINE_INSTANTIATION "${VCL_NEEDS_INLINE_INSTANTIATION}")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_STATIC_CONST_INIT_INT)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_STATIC_CONST_INIT_NO_DEFN)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_STATIC_CONST_INIT_FLOAT)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_CAN_DO_STATIC_TEMPLATE_MEMBER)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_CAN_DO_NON_TYPE_FUNCTION_TEMPLATE_PARAMETER)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_NEED_FRIEND_FOR_TEMPLATE_OVERLOAD)
  SET_INVERT(VCL_NEED_FRIEND_FOR_TEMPLATE_OVERLOAD "${VCL_NEED_FRIEND_FOR_TEMPLATE_OVERLOAD}")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_OVERLOAD_CAST)
  SET_BOOL(VCL_OVERLOAD_CAST "(x)" "((T)(x))")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_NULL_TMPL_ARGS)
  SET_BOOL(VCL_NULL_TMPL_ARGS "/* <> */" "<>")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_NO_STATIC_DATA_MEMBERS)
  SET_INVERT(VCL_NO_STATIC_DATA_MEMBERS "${VCL_NO_STATIC_DATA_MEMBERS}")
PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_HAS_TEMPLATE_SYMBOLS)
  SET_INVERT(VCL_HAS_TEMPLATE_SYMBOLS "${VCL_HAS_TEMPLATE_SYMBOLS}")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_CAN_DO_IMPLICIT_TEMPLATES)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_CAN_DO_COMPLETE_DEFAULT_TYPE_PARAMETER)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_CAN_DO_TEMPLATE_DEFAULT_TYPE_PARAMETER)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_TEMPLATE_MATCHES_TOO_OFTEN)
  SET_INVERT(VCL_TEMPLATE_MATCHES_TOO_OFTEN "${VCL_TEMPLATE_MATCHES_TOO_OFTEN}")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_SUNPRO_CLASS_SCOPE_HACK)
  SET_BOOL(VCL_SUNPRO_CLASS_SCOPE_HACK "/* , A */" ", A")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_EXCEPTIONS)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_HAS_NAMESPACES)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_ALLOWS_NAMESPACE_STD)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_NEEDS_NAMESPACE_STD)
  SET_INVERT(VCL_NEEDS_NAMESPACE_STD "${VCL_NEEDS_NAMESPACE_STD}")
PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_HAS_SLICED_DESTRUCTOR_BUG)
  SET_INVERT(VCL_HAS_SLICED_DESTRUCTOR_BUG "${VCL_HAS_SLICED_DESTRUCTOR_BUG}")
PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_HAS_WORKING_STRINGSTREAM)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_UNISTD_USLEEP_IS_VOID)
  SET_INVERT(VXL_UNISTD_USLEEP_IS_VOID "${VXL_UNISTD_USLEEP_IS_VOID}")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_STDLIB_HAS_QSORT)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_C_MATH_HAS_LROUND)
PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_HAS_LFS)
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_HAS_DBGHELP_H)

# Test how to define a template specialization, and whether
# specializations can be properly distinguished by top-level
# cv-qualifiers.
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_DEFINE_SPECIALIZATION)
IF(NOT VCL_DEFINE_SPECIALIZATION)
  SET(CMAKE_REQUIRED_FLAGS "-DNOT_CONFORMING_SPECIALIZATION")
ENDIF(NOT VCL_DEFINE_SPECIALIZATION)
  SET_BOOL(VCL_DEFINE_SPECIALIZATION "template <>" "/* template <> */")
PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VCL_CANNOT_SPECIALIZE_CV)
  SET_INVERT(VCL_CANNOT_SPECIALIZE_CV "${VCL_CANNOT_SPECIALIZE_CV}")
SET(CMAKE_REQUIRED_FLAGS)

# Check if apple has __isnand or __inline_isnand
IF(APPLE)
  PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_APPLE_HAS_ISNAND)
  IF(NOT ${VXL_APPLE_HAS_ISNAND})
    PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_APPLE_HAS_INLINE_ISNAND)
    IF( NOT ${VXL_APPLE_HAS_INLINE_ISNAND})
      MESSAGE(FATAL_ERROR "Neither the __isnand nor the __inline_isnand "
        "functions are available !")
    ENDIF( NOT ${VXL_APPLE_HAS_INLINE_ISNAND})  
  ENDIF(NOT ${VXL_APPLE_HAS_ISNAND})
ENDIF(APPLE)

# Check if Windows have wchar_t defined
IF(WIN32)
  PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_HAS_WIN_WCHAR_T)
ENDIF(WIN32)


# Test the ability of shared libraries to link to static vxl libriares
PERFORM_CMAKE_TEST_CUSTOM(vxl_shared_link_test VXL_PIC_COMPATIBLE)

#
# Find header files
#

PERFORM_CHECK_HEADER(cassert VCL_CXX_HAS_HEADER_CASSERT)
PERFORM_CHECK_HEADER(ciso646 VCL_CXX_HAS_HEADER_CISO646)
PERFORM_CHECK_HEADER(csetjmp VCL_CXX_HAS_HEADER_CSETJMP)
PERFORM_CHECK_HEADER(cstdio VCL_CXX_HAS_HEADER_CSTDIO)
PERFORM_CHECK_HEADER(ctime VCL_CXX_HAS_HEADER_CTIME)
PERFORM_CHECK_HEADER(cctype VCL_CXX_HAS_HEADER_CCTYPE)
PERFORM_CHECK_HEADER(climits VCL_CXX_HAS_HEADER_CLIMITS)
PERFORM_CHECK_HEADER(csignal VCL_CXX_HAS_HEADER_CSIGNAL)
PERFORM_CHECK_HEADER(cstdlib VCL_CXX_HAS_HEADER_CSTDLIB)
PERFORM_CHECK_HEADER(cwchar VCL_CXX_HAS_HEADER_CWCHAR)
PERFORM_CHECK_HEADER(cerrno VCL_CXX_HAS_HEADER_CERRNO)
PERFORM_CHECK_HEADER(clocale VCL_CXX_HAS_HEADER_CLOCALE)
PERFORM_CHECK_HEADER(cstdarg VCL_CXX_HAS_HEADER_CSTDARG)
PERFORM_CHECK_HEADER(cstring VCL_CXX_HAS_HEADER_CSTRING)
PERFORM_CHECK_HEADER(cwctype VCL_CXX_HAS_HEADER_CWCTYPE)
PERFORM_CHECK_HEADER(cfloat VCL_CXX_HAS_HEADER_CFLOAT)
PERFORM_CHECK_HEADER(cmath VCL_CXX_HAS_HEADER_CMATH)
PERFORM_CHECK_HEADER(cstddef VCL_CXX_HAS_HEADER_CSTDDEF)
PERFORM_CHECK_HEADER(algorithm VCL_CXX_HAS_HEADER_ALGORITHM)
PERFORM_CHECK_HEADER(iomanip VCL_CXX_HAS_HEADER_IOMANIP)
PERFORM_CHECK_HEADER(list VCL_CXX_HAS_HEADER_LIST)
PERFORM_CHECK_HEADER(ostream VCL_CXX_HAS_HEADER_OSTREAM)
PERFORM_CHECK_HEADER(streambuf VCL_CXX_HAS_HEADER_STREAMBUF)
PERFORM_CHECK_HEADER(bitset VCL_CXX_HAS_HEADER_BITSET)
PERFORM_CHECK_HEADER(ios VCL_CXX_HAS_HEADER_IOS)
PERFORM_CHECK_HEADER(locale VCL_CXX_HAS_HEADER_LOCALE)
PERFORM_CHECK_HEADER(queue VCL_CXX_HAS_HEADER_QUEUE)
PERFORM_CHECK_HEADER(string VCL_CXX_HAS_HEADER_STRING)
PERFORM_CHECK_HEADER(complex VCL_CXX_HAS_HEADER_COMPLEX)
PERFORM_CHECK_HEADER(iosfwd VCL_CXX_HAS_HEADER_IOSFWD)
PERFORM_CHECK_HEADER(map VCL_CXX_HAS_HEADER_MAP)
PERFORM_CHECK_HEADER(set VCL_CXX_HAS_HEADER_SET)
PERFORM_CHECK_HEADER(typeinfo VCL_CXX_HAS_HEADER_TYPEINFO)
PERFORM_CHECK_HEADER(deque VCL_CXX_HAS_HEADER_DEQUE)
PERFORM_CHECK_HEADER(iostream VCL_CXX_HAS_HEADER_IOSTREAM)
PERFORM_CHECK_HEADER(memory VCL_CXX_HAS_HEADER_MEMORY)
PERFORM_CHECK_HEADER(sstream VCL_CXX_HAS_HEADER_SSTREAM)
PERFORM_CHECK_HEADER(utility VCL_CXX_HAS_HEADER_UTILITY)
PERFORM_CHECK_HEADER(exception VCL_CXX_HAS_HEADER_EXCEPTION)
PERFORM_CHECK_HEADER(istream VCL_CXX_HAS_HEADER_ISTREAM)
PERFORM_CHECK_HEADER(new VCL_CXX_HAS_HEADER_NEW)
PERFORM_CHECK_HEADER(stack VCL_CXX_HAS_HEADER_STACK)
PERFORM_CHECK_HEADER(valarray VCL_CXX_HAS_HEADER_VALARRAY)
PERFORM_CHECK_HEADER(fstream VCL_CXX_HAS_HEADER_FSTREAM)
PERFORM_CHECK_HEADER(iterator VCL_CXX_HAS_HEADER_ITERATOR)
PERFORM_CHECK_HEADER(numeric VCL_CXX_HAS_HEADER_NUMERIC)
PERFORM_CHECK_HEADER(stdexcept VCL_CXX_HAS_HEADER_STDEXCEPT)
PERFORM_CHECK_HEADER(vector VCL_CXX_HAS_HEADER_VECTOR)
PERFORM_CHECK_HEADER(functional VCL_CXX_HAS_HEADER_FUNCTIONAL)
PERFORM_CHECK_HEADER(limits VCL_CXX_HAS_HEADER_LIMITS)
PERFORM_CHECK_HEADER(strstream VCL_CXX_HAS_HEADER_STRSTREAM)
PERFORM_CHECK_HEADER(pthread.h VXL_HAS_PTHREAD_H)
PERFORM_CHECK_HEADER(semaphore.h VXL_HAS_SEMAPHORE_H)
PERFORM_CHECK_HEADER(ieeefp.h VXL_HAS_IEEEFP_H)
PERFORM_CHECK_HEADER(iso646.h VCL_CXX_HAS_HEADER_ISO646_H)
PERFORM_CHECK_HEADER(emmintrin.h VXL_HAS_EMMINTRIN_H)

#
# Check for new C++0x standard additions (including TR1)
#

PERFORM_CHECK_HEADER(tr1/memory VCL_CXX_HAS_TR1)
CHECK_TYPE_EXISTS_ZERO(std::shared_ptr<void> memory VCL_MEMORY_HAS_SHARED_PTR)
CHECK_TYPE_EXISTS_ZERO(std::tr1::shared_ptr<void> tr1/memory VCL_TR1_MEMORY_HAS_SHARED_PTR)

IF(VCL_MEMORY_HAS_SHARED_PTR OR VCL_TR1_MEMORY_HAS_SHARED_PTR)
  OPTION(VCL_INCLUDE_CXX_0X "Enable C++0x standard extensions" ${YES_FOR_VXL_DASHBOARD})
ELSE(VCL_MEMORY_HAS_SHARED_PTR OR VCL_TR1_MEMORY_HAS_SHARED_PTR)
  SET(VCL_INCLUDE_CXX_0X 0)
ENDIF(VCL_MEMORY_HAS_SHARED_PTR OR VCL_TR1_MEMORY_HAS_SHARED_PTR)

# Make sure boolean values are (0,1) not (NO,YES)
IF(VCL_INCLUDE_CXX_0X)
  SET(VCL_INCLUDE_CXX_0X 1)
ELSE(VCL_INCLUDE_CXX_0X)
  SET(VCL_INCLUDE_CXX_0X 0)
ENDIF(VCL_INCLUDE_CXX_0X)



# check for hardware support for sse2 with the current compiler flags
PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VXL_HAS_SSE2_HARDWARE_SUPPORT)

# if no support right now, see if the support exists if some flags
# are added.  This can be used to give the user some useful info.
IF(NOT VXL_HAS_SSE2_HARDWARE_SUPPORT)
  IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(VXL_SSE_TEST_FLAG_BACKUP ${CMAKE_REQUIRED_FLAGS})
    SET(CMAKE_REQUIRED_FLAGS " -msse2 ${VXL_SSE_TEST_FLAG_BACKUP} ")
    PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VXL_SSE2_HARDWARE_SUPPORT_POSSIBLE)
    SET( VXL_SSE2_HARDWARE_SUPPORT_POSSIBLE_HELP
      "The current compiler flags do not allow the SSE2 instructions to be used. "
      "It looks like if you add the flag '-msse2' you will be able to use the "
      "SSE2 instructions. If you make this change and still see this message, "
      " you may need to set VXL_UPDATE_CONFIGURATION to ON."
      CACHE INTERNAL "help string for how to enable SSE2 support" )
    SET(CMAKE_REQUIRED_FLAGS ${VXL_SSE_TEST_FLAG_BACKUP})
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF(NOT VXL_HAS_SSE2_HARDWARE_SUPPORT)


#
# Check for aligned dynamic memory allocation support, useful for sse
#

IF(VXL_HAS_EMMINTRIN_H)
  # check for memory allocation operations
  PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_HAS_MM_MALLOC)
  PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_HAS_ALIGNED_MALLOC)
  PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_HAS_MINGW_ALIGNED_MALLOC)
  PERFORM_CMAKE_TEST(vxl_platform_tests.cxx VXL_HAS_POSIX_MEMALIGN)

ELSE(VXL_HAS_EMMINTRIN_H)
  SET( VXL_HAS_MM_MALLOC 0 )
  SET( VXL_HAS_ALIGNED_MALLOC 0 )
  SET( VXL_HAS_MINGW_ALIGNED_MALLOC 0 )
  SET( VXL_HAS_POSIX_MEMALIGN 0 )
ENDIF(VXL_HAS_EMMINTRIN_H)


#
# Check complex pow stuff
#

IF(VCL_CXX_HAS_HEADER_COMPLEX)
  PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_COMPLEX_POW_WORKS)
ENDIF(VCL_CXX_HAS_HEADER_COMPLEX)



# Tests of math.h may need math library on UNIX.
IF(UNIX)
  SET(CMAKE_REQUIRED_LIBRARIES "${CMAKE_REQUIRED_LIBRARIES};m")
ENDIF(UNIX)

PERFORM_C_CHECK_FUNCTION(sqrtf "math.h" VXL_C_MATH_HAS_SQRTF)
PERFORM_C_CHECK_FUNCTION(finite "math.h" VXL_C_MATH_HAS_FINITE)
PERFORM_C_CHECK_FUNCTION(finitef "math.h" VXL_C_MATH_HAS_FINITEF)
PERFORM_C_CHECK_FUNCTION(finitel "math.h" VXL_C_MATH_HAS_FINITEL)
PERFORM_C_CHECK_FUNCTION(finite "ieeefp.h" VXL_IEEEFP_HAS_FINITE)
#PERFORM_C_CHECK_FUNCTION(qsort "stdlib.h" VXL_STDLIB_HAS_QSORT)
PERFORM_C_CHECK_FUNCTION(lrand48 "stdlib.h" VXL_STDLIB_HAS_LRAND48)
PERFORM_C_CHECK_FUNCTION(drand48 "stdlib.h" VXL_STDLIB_HAS_DRAND48)
PERFORM_C_CHECK_FUNCTION(srand48 "stdlib.h" VXL_STDLIB_HAS_SRAND48)

TEST_BIG_ENDIAN(VXL_BIG_ENDIAN)
SET_INVERT(VXL_LITTLE_ENDIAN "${VXL_BIG_ENDIAN}")

#
# Values which are to be manually set
#

SET(VCL_USE_NATIVE_STL 1) # change if no
SET(VCL_USE_NATIVE_COMPLEX 1)
SET(VCL_USE_IMPLICIT_TEMPLATES 1) # change if no
SET(VCL_USE_ATOMIC_COUNT 1)
#OPTION(VCL_USE_ATOMIC_COUNT
#  "Whether thread-safe vcl_atomic_count implementations are used." ON)
#MARK_AS_ADVANCED( VCL_USE_ATOMIC_COUNT )
## Need to enforce 1/0 values for configuration.
#IF(VCL_USE_ATOMIC_COUNT)
#  SET(VCL_USE_ATOMIC_COUNT 1)
#ELSE(VCL_USE_ATOMIC_COUNT)
#  SET(VCL_USE_ATOMIC_COUNT 0)
#ENDIF(VCL_USE_ATOMIC_COUNT)

SET(VXL_TWO_ARG_GETTIME 0) # not used

IF(NOT VCL_CAN_DO_IMPLICIT_TEMPLATES)
  MESSAGE("Warning: turning off implicit template instantiation")
  SET(VCL_USE_IMPLICIT_TEMPLATES 0)
ENDIF(NOT VCL_CAN_DO_IMPLICIT_TEMPLATES)

PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_CHAR_IS_SIGNED)

#
# Check type sizes
#

SET(CMAKE_REQUIRED_FLAGS ${CMAKE_ANSI_CFLAGS})

# The types are listed in reverse order of preference. That is, the
# last type is should be the most preferred type name.
#
DETERMINE_TYPE(BYTE     1 8   "char")
DETERMINE_TYPE(INT_8    1 8   "short;char")
DETERMINE_TYPE(INT_16   1 16  "char;int;short")
DETERMINE_TYPE(INT_32   1 32  "short;long;int")
DETERMINE_TYPE(INT_64   1 64  "__int64;long long;long")
DETERMINE_TYPE(IEEE_32  0 32  "long double;double;float")
DETERMINE_TYPE(IEEE_64  0 64  "float;long double;double")
DETERMINE_TYPE(IEEE_96  0 96  "float;double;long double")
DETERMINE_TYPE(IEEE_128 0 128 "float;double;long double")
IF (${VXL_INT_64} MATCHES "^long$")
  SET(VXL_INT_64_IS_LONG 1)
ELSE(${VXL_INT_64} MATCHES "^long$")
  SET(VXL_INT_64_IS_LONG 0)
ENDIF(${VXL_INT_64} MATCHES "^long$")

#
# Check unistd stuff
#

CHECK_INCLUDE_FILE_CXX("unistd.h" HAVE_UNISTD_H)
IF(HAVE_UNISTD_H)
  CHECK_TYPE_EXISTS_ZERO(useconds_t "unistd.h" VXL_UNISTD_HAS_USECONDS_T)
  CHECK_TYPE_EXISTS_ZERO(intptr_t "unistd.h" VXL_UNISTD_HAS_INTPTR_T)
  CHECK_FUNCTION_EXISTS_ZERO(ualarm VXL_UNISTD_HAS_UALARM)
  CHECK_FUNCTION_EXISTS_ZERO(usleep VXL_UNISTD_HAS_USLEEP)
  CHECK_FUNCTION_EXISTS_ZERO(lchown VXL_UNISTD_HAS_LCHOWN)
  CHECK_FUNCTION_EXISTS_ZERO(pread VXL_UNISTD_HAS_PREAD)
  CHECK_FUNCTION_EXISTS_ZERO(pwrite VXL_UNISTD_HAS_PWRITE)
  CHECK_FUNCTION_EXISTS_ZERO(tell VXL_UNISTD_HAS_TELL)
  CHECK_FUNCTION_EXISTS_ZERO(getpid VXL_UNISTD_HAS_GETPID)
ELSE(HAVE_UNISTD_H)
  # If there is not unistd.h, assume windows and therefore hardcode results.
  SET(VXL_UNISTD_HAS_USECONDS_T 0)
  SET(VXL_UNISTD_HAS_INTPTR_T 0)
  SET(VXL_UNISTD_HAS_UALARM 1)
  SET(VXL_UNISTD_HAS_USLEEP 1)
  SET(VXL_UNISTD_HAS_LCHOWN 1)
  SET(VXL_UNISTD_HAS_PREAD 1)
  SET(VXL_UNISTD_HAS_PWRITE 1)
  SET(VXL_UNISTD_HAS_TELL 1)
  SET(VXL_UNISTD_HAS_GETPID 1)
ENDIF(HAVE_UNISTD_H)


#
# Check numeric_limits infinity stuff
#

IF(VCL_CXX_HAS_HEADER_LIMITS)
  PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_NUMERIC_LIMITS_HAS_INFINITY)
  IF(VCL_CXX_HAS_HEADER_CFLOAT)
    PERFORM_CMAKE_TEST_RUN(vxl_platform_tests.cxx VCL_PROCESSOR_HAS_INFINITY)
  ELSE(VCL_CXX_HAS_HEADER_CFLOAT)
    SET(VCL_PROCESSOR_HAS_INFINITY 0)
  ENDIF(VCL_CXX_HAS_HEADER_CFLOAT)
ELSE(VCL_CXX_HAS_HEADER_LIMITS)
  SET(VCL_NUMERIC_LIMITS_HAS_INFINITY 0)
  SET(VCL_PROCESSOR_HAS_INFINITY 0)
ENDIF(VCL_CXX_HAS_HEADER_LIMITS)


#
# configure files
#

CONFIGURE_FILE(${vxl_SOURCE_DIR}/vcl/vcl_config_compiler.h.in ${vxl_BINARY_DIR}/vcl/vcl_config_compiler.h)
CONFIGURE_FILE(${vxl_SOURCE_DIR}/vcl/vcl_config_headers.h.in ${vxl_BINARY_DIR}/vcl/vcl_config_headers.h)
CONFIGURE_FILE(${vxl_SOURCE_DIR}/vcl/vcl_config_manual.h.in ${vxl_BINARY_DIR}/vcl/vcl_config_manual.h)
CONFIGURE_FILE(${vxl_SOURCE_DIR}/vcl/vcl_where_root_dir.h.in ${vxl_BINARY_DIR}/vcl/vcl_where_root_dir.h)
CONFIGURE_FILE(${vxl_SOURCE_DIR}/core/vxl_config.h.in ${vxl_BINARY_DIR}/core/vxl_config.h)

# Reset the update configuration flag
SET( VXL_UPDATE_CONFIGURATION "OFF" CACHE BOOL "Re-run the configuration tests?" FORCE )
