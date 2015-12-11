#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Cpd::Library" for configuration "Release"
set_property(TARGET Cpd::Library APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Cpd::Library PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/cpd/libcpd.dll.a"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Fgt::Library"
  )

list(APPEND _IMPORT_CHECK_TARGETS Cpd::Library )
list(APPEND _IMPORT_CHECK_FILES_FOR_Cpd::Library "${_IMPORT_PREFIX}/lib/cpd/libcpd.dll.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
