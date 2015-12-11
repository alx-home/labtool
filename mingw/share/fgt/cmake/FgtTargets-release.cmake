#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Fgt::Library" for configuration "RELEASE"
set_property(TARGET Fgt::Library APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Fgt::Library PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fgt/libfgt.dll.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Fgt::Library )
list(APPEND _IMPORT_CHECK_FILES_FOR_Fgt::Library "${_IMPORT_PREFIX}/lib/fgt/libfgt.dll.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
