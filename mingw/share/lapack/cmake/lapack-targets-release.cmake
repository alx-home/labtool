#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "blas" for configuration "RELEASE"
set_property(TARGET blas APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(blas PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/lapack/libblas.dll.a"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/lapack/libblas.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS blas )
list(APPEND _IMPORT_CHECK_FILES_FOR_blas "${_IMPORT_PREFIX}/lib/lapack/libblas.dll.a" "${_IMPORT_PREFIX}/bin/lapack/libblas.dll" )

# Import target "lapack" for configuration "RELEASE"
set_property(TARGET lapack APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(lapack PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/lapack/liblapack.dll.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "blas"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/lapack/liblapack.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS lapack )
list(APPEND _IMPORT_CHECK_FILES_FOR_lapack "${_IMPORT_PREFIX}/lib/lapack/liblapack.dll.a" "${_IMPORT_PREFIX}/bin/lapack/liblapack.dll" )

# Import target "tmglib" for configuration "RELEASE"
set_property(TARGET tmglib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(tmglib PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/lapack/libtmglib.dll.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "lapack"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/lapack/libtmglib.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS tmglib )
list(APPEND _IMPORT_CHECK_FILES_FOR_tmglib "${_IMPORT_PREFIX}/lib/lapack/libtmglib.dll.a" "${_IMPORT_PREFIX}/bin/lapack/libtmglib.dll" )

# Import target "lapacke" for configuration "RELEASE"
set_property(TARGET lapacke APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(lapacke PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/lapack/liblapacke.dll.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "lapack;blas"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/lapack/liblapacke.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS lapacke )
list(APPEND _IMPORT_CHECK_FILES_FOR_lapacke "${_IMPORT_PREFIX}/lib/lapack/liblapacke.dll.a" "${_IMPORT_PREFIX}/bin/lapack/liblapacke.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
