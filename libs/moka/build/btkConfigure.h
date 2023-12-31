/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2013, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __btkConfigure_h
#define __btkConfigure_h

#define BTK_VERSION_MAJOR 0
#define BTK_VERSION_MINOR 3
#define BTK_VERSION_PATCH 0
#define BTK_VERSION_STRING "0.3.0"

// Compiled on a 64 bit OS?
#if defined(__APPLE__)
  #if defined __x86_64__ || defined __ppc64__
    #define HAVE_64_BIT
  #endif
#else
  #define HAVE_64_BIT
#endif

// Looking for mmap
/* #undef HAVE_SYS_MMAP */

// Looking for std::shared_ptr in memory.h
#define HAVE_SYS_TR1_MEMORY_H
#define HAVE_SYS_MEMORY_H
/* #undef HAVE_BOOST_TR1_MEMORY_HPP */
/* #undef HAVE_BOOST_MEMORY_HPP */

// Special case for Matlab R2010b & MSVC2010
#if defined(_MSC_VER)
  #if (_MSC_VER >= 1600)
/* #undef FIX_MATLAB_CHAR16_T_TYPE */
  #endif
#endif

// For atomic timestamp
#define HAVE_PTHREADS
/* #undef HAVE_SPROC */
#define HAVE_PTHREADS
#define HAVE_WIN32_THREADS
/* #undef HAVE_ATOMIC_BUILTINS */

// For dll symbols in Windows
/* #undef BTK_BUILD_SHARED_LIBS */
#if (defined(BTK_BUILD_SHARED_LIBS))
  #if (defined(_MSC_VER)) 
    // BTKCommon
    #if defined(BTKCommon_EXPORTS)
      #define BTK_COMMON_EXPORT __declspec(dllexport)
    #else
      #define BTK_COMMON_EXPORT __declspec(dllimport)
    #endif
    // BTKIO
    #if defined(BTKIO_EXPORTS)
      #define BTK_IO_EXPORT __declspec(dllexport)
    #else
      #define BTK_IO_EXPORT __declspec(dllimport)
    #endif
    // BTKBasicFilters
    #if defined(BTKBasicFilters_EXPORTS)
      #define BTK_BASICFILTERS_EXPORT __declspec(dllexport)
    #else
      #define BTK_BASICFILTERS_EXPORT __declspec(dllimport)
    #endif
  #elif (defined(__GNUC__) && (__GNUC__ >= 4))
    #define BTK_COMMON_EXPORT __attribute__((visibility("default")))
    #define BTK_IO_EXPORT __attribute__((visibility("default")))
    #define BTK_BASICFILTERS_EXPORT __attribute__((visibility("default")))
  #else
    #error Unsupported compiler to build modules as dynamic libraries
  #endif
#else
  #define BTK_COMMON_EXPORT
  #define BTK_IO_EXPORT
  #define BTK_BASICFILTERS_EXPORT
#endif

// Addons for Eigen
#ifdef EIGEN_CORE_H
  #error The header btkConfigure.h must be included before the inclusion of any Eigen headers to integrate the implemented Eigen plugins
#endif
// Need to be defined before the inclusion of the Eigen headers
#define EIGEN_DENSEBASE_PLUGIN <btkEigen/Plugin/DenseBaseAddons.h>
#define EIGEN_VECTOROP_PLUGIN <btkEigen/Plugin/VectorOpAddons.h>
#include "btkEigen/Plugin/ForwardDeclarations.h"
#include <Eigen/Core>
#include "btkEigen/Plugin/Functors.h"

#endif // __btkConfigure_h
