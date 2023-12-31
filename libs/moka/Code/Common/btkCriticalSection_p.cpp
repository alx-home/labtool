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
#include <windows.h>
#include "btkCriticalSection_p.h"

// Note: The implementation of this class is mostly based on the code of the class vtkCriticalSection

namespace btk
{
  critical_section_p::critical_section_p()
  {
    this->Init();
  };

  critical_section_p::critical_section_p(int isLocked)
  {
    this->Init();
    if(isLocked)
      this->Lock();
  };

  critical_section_p::~critical_section_p()
  {
#if defined(HAVE_WIN32_THREADS)
    DeleteCriticalSection((LPCRITICAL_SECTION)&(this->m_CS));
#elif defined(HAVE_PTHREADS)
    pthread_mutex_destroy(&(this->m_CS));
#endif
  };

  void critical_section_p::Init()
  {
#if defined(HAVE_SPROC)
    init_lock(&(this->m_CS));
#elif defined(HAVE_WIN32_THREADS)
    InitializeCriticalSection((LPCRITICAL_SECTION)&(this->m_CS));
#elif defined(HAVE_PTHREADS)
  #if defined(HAVE_HP_PTHREADS)
      pthread_mutex_init(&(this->m_CS), pthread_mutexattr_default);
  #else
      pthread_mutex_init(&(this->m_CS), NULL);
  #endif
#endif
  };

  void critical_section_p::Lock()
  {
#if defined(HAVE_SPROC)
    spin_lock(&(this->m_CS));
#elif defined(HAVE_WIN32_THREADS)
    EnterCriticalSection((LPCRITICAL_SECTION)&(this->m_CS));
#elif defined(HAVE_PTHREADS)
    pthread_mutex_lock( &(this->m_CS));
#endif
  };

  void critical_section_p::Unlock()
  {
#if defined(HAVE_SPROC)
    release_lock(&(this->m_CS) );
#elif defined(HAVE_WIN32_THREADS)
    LeaveCriticalSection((LPCRITICAL_SECTION)&(this->m_CS));
#elif defined(HAVE_PTHREADS)
    pthread_mutex_unlock(&(this->m_CS));
#endif
  };
};
