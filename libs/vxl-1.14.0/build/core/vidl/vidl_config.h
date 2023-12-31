#ifndef vidl_config_h_
#define vidl_config_h_

// If the suffix of this file in ".in", this is the source file used
// to generate the actual configuration file.  To examine the actual
// configuration of the library, look at the vidl_config.h file in
// the _build_ tree.

#define FFMPEG_FOUND
#ifdef FFMPEG_FOUND
#define VIDL_HAS_FFMPEG 1
#define FFMPEG_FOUND_SEVERAL
#ifdef FFMPEG_FOUND_SEVERAL
#define FFMPEG_IN_SEVERAL_DIRECTORIES 1
#else
#define FFMPEG_IN_SEVERAL_DIRECTORIES 0
#endif
#undef FFMPEG_FOUND_SEVERAL
#else
#define VIDL_HAS_FFMPEG 0
#endif
#undef FFMPEG_FOUND

/* #undef DIRECTSHOW_FOUND */
#ifdef DIRECTSHOW_FOUND
#define VIDL_HAS_DSHOW 1
#else
#define VIDL_HAS_DSHOW 0
#endif
#undef DIRECTSHOW_FOUND

/* #undef DIRECTSHOW_FOUND */
#ifdef DIRECTSHOW_FOUND
#define VIDL_HAS_DSHOW 1
#else
#define VIDL_HAS_DSHOW 0
#endif
#undef DIRECTSHOW_FOUND

/* #undef DIRECTSHOW_ESF_FOUND */
#ifdef DIRECTSHOW_ESF_FOUND
#define VIDL_HAS_DSHOW_ESF 1
#else
#define VIDL_HAS_DSHOW_ESF 0
#endif
#undef DIRECTSHOW_ESF_FOUND

/* #undef DC1394_FOUND */
#ifdef DC1394_FOUND
#define VIDL_HAS_DC1394 1
#else
#define VIDL_HAS_DC1394 0
#endif
#undef DC1394_FOUND

/* #undef VIDEODEV_FOUND */
#ifdef VIDEODEV_FOUND
#define VIDL_HAS_VIDEODEV 1
#else
#define VIDL_HAS_VIDEODEV 0
#endif
#undef VIDEODEV_FOUND

/* #undef VIDEODEV2_FOUND */
#ifdef VIDEODEV2_FOUND
#define VIDL_HAS_VIDEODEV2 1
#else
#define VIDL_HAS_VIDEODEV2 0
#endif
#undef VIDEODEV2_FOUND

#endif // vidl_config_h_
