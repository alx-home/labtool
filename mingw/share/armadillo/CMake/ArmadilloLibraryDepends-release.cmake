#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "armadillo" for configuration "RELEASE"
set_property(TARGET armadillo APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(armadillo PROPERTIES
  IMPORTED_IMPLIB_RELEASE "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/lib/armadillo/libarmadillo.dll.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/lib/lapack/libblas.dll.a;C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/lib/lapack/liblapack.dll.a;C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/lib/lapack/libarpack.dll.a;gfortran"
  IMPORTED_LOCATION_RELEASE "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/bin/armadillo/libarmadillo.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS armadillo )
list(APPEND _IMPORT_CHECK_FILES_FOR_armadillo "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/lib/armadillo/libarmadillo.dll.a" "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/bin/armadillo/libarmadillo.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
