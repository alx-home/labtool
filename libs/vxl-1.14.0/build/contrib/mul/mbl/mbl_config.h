#ifndef MBL_CONFIG_H_ // file guard
//:
// \file
// \author Ian Scott
// \brief Allows cmake to set up macros for mbl

// Note: The make system (eg cmake) should generate a file, mbl_config.h, from
// this, in which the macro is set correctly.
// For non-cmake systems this might cause a problem.  In particular if there is
// no mbl_config.h, some other stuff might not compile.

#define MBL_CONFIG_TEST_SAVE_MEASUREMENT_ROOT ""
#define MBL_CONFIG_BUILD_NAME "Win32-mingw32-make"

#endif
