#ifndef mpeg_config_cmake_h_
#define mpeg_config_cmake_h_
/**
 * \file
 * This file either is or was generated from mpeg/include/config_cmake.h.in
 */

/*--------------------------------------------------------------------------*/

/* ppc architecture */
#define MPEG_ARCH_PPC 0
#if MPEG_ARCH_PPC
# define ARCH_PPC
#endif

/* x86 architecture */
/* n.b. The original configure script doesn't define this on my Linux x86 box.
   It seems to turn MMX commands, and so should have speed effects only. */
#define MPEG_ARCH_X86 0
#if MPEG_ARCH_X86
# define ARCH_X86
#endif

/* maximum supported data alignment */
#define MPEG_ATTRIBUTE_ALIGNED_MAX 0
#if MPEG_ATTRIBUTE_ALIGNED_MAX
# define ATTRIBUTE_ALIGNED_MAX 0
#endif

/* Define if you have the <dlfcn.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_DLFCN_H */

/* Define if you have the <inttypes.h> header file. */
/* This doesn't appear to be used, but you will need
   provide and inttypes.h if it is missing */
/* #undef HAVE_INTTYPES_H */

/* Define if you have the `memalign' function. */
#define MPEG_HAVE_MEMALIGN 0
#if MPEG_HAVE_MEMALIGN
# define HAVE_MEMALIGN
#endif

/* Define if you have the <memory.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_MEMORY_H */

/* Define if you have the <stdint.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_STDINT_H */

/* Define if you have the <stdlib.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_STDLIB_H */

/* Define if you have the <strings.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_STRINGS_H */

/* Define if you have the <string.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_STRING_H */

/* Define if you have the <sys/stat.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_SYS_STAT_H */

/* Define if you have the <sys/time.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_SYS_TIME_H */

/* Define if you have the <sys/types.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_SYS_TYPES_H */

/* Define if you have the <unistd.h> header file. */
/* This doesn't appear to be used: IMS */
/* #undef HAVE_UNISTD_H */

/* libmpeg2 mediaLib support */
/* #undef LIBMPEG2_MLIB */

/* libvo MGA support */
/* #undef LIBVO_MGA */

/* libvo mediaLib support */
/* #undef LIBVO_MLIB */

/* libvo SDL support */
/* #undef LIBVO_SDL */

/* libvo X11 support */
/* #undef LIBVO_X11 */

/* libvo Xv support */
/* #undef LIBVO_XV */

/* mpeg2dec profiling */
/* This doesn't appear to be used: IMS */
/* #undef MPEG2DEC_GPROF */

/* Name of package */
/* This doesn't appear to be used: IMS */
/* #undef PACKAGE */

/* Define as the return type of signal handlers (`int' or `void'). */
/* This doesn't appear to be used: IMS */
/* #undef RETSIGTYPE */

/* The size of a `char', as computed by sizeof. */
/* This doesn't appear to be used: IMS */
/* #undef SIZEOF_CHAR */

/* The size of a `int', as computed by sizeof. */
/* This doesn't appear to be used: IMS */
/* #undef SIZEOF_INT */

/* The size of a `short', as computed by sizeof. */
/* #undef SIZEOF_SHORT */

/* Define if you have the ANSI C header files. */
/* This doesn't appear to be used: IMS */
/* #undef STDC_HEADERS */

/* Version number of package */
/* This doesn't appear to be used: IMS */
/* #undef VERSION */

/* Define if your processor stores words with the most significant byte first
   (like Motorola and SPARC, unlike Intel and VAX). */
/* This only appears to be used in video_out_x11.c, which is never compiled: IMS */
/* #undef WORDS_BIGENDIAN */

/* Define if the X Window System is missing or not being used. */
/* This doesn't appear to be used: IMS */
/* #undef X_DISPLAY_MISSING */

/* Define to empty if `const' does not conform to ANSI C. */
/* We don't support compilers this broken: IMS */
/* #undef const */

/* Define as `__inline' if that's what the C compiler calls it, or to nothing
   if it is not supported. */
/* We don't support compilers this broken: IMS */
#define inline __inline

/* Define as `__restrict' if that's what the C compiler calls it, or to
   nothing if it is not supported. */
/* This doesn't appear to be used: IMS */
/* #undef restrict */

/* Define to `unsigned' if <sys/types.h> does not define. */
/* We don't support compilers this broken: IMS */
/* #undef size_t */

#endif /* mpeg_config_cmake_h_ */
