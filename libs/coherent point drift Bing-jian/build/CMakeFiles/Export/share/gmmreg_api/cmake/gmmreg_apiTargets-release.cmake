#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "gmmreg_api" for configuration "Release"
set_property(TARGET gmmreg_api APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(gmmreg_api PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vnl_algo;vnl;vcl"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/gmmreg_api/libgmmreg_api.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS gmmreg_api )
list(APPEND _IMPORT_CHECK_FILES_FOR_gmmreg_api "${_IMPORT_PREFIX}/lib/gmmreg_api/libgmmreg_api.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
