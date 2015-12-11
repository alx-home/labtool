# - Config file for the Armadillo package
# It defines the following variables
#  ARMADILLO_INCLUDE_DIRS - include directories for Armadillo
#  ARMADILLO_LIBRARY_DIRS - library directories for Armadillo (normally not used!)
#  ARMADILLO_LIBRARIES    - libraries to link against

# Tell the user project where to find our headers and libraries
set(ARMADILLO_INCLUDE_DIRS "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/include/armadillo")
set(ARMADILLO_LIBRARY_DIRS "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/lib/armadillo")

# Our library dependencies (contains definitions for IMPORTED targets)
include("C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/share/armadillo/CMake/ArmadilloLibraryDepends.cmake")

# These are IMPORTED targets created by ArmadilloLibraryDepends.cmake
set(ARMADILLO_LIBRARIES armadillo)

