# First release build with CMAKE 2.6.2.
# The prior versions of CMAKE have not been tested
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
# BTK: Biomechanical ToolKit
PROJECT(BTK)

# BTK version number.
SET(BTK_VERSION_MAJOR 0)
SET(BTK_VERSION_MINOR 3)
SET(BTK_VERSION_PATCH 0)
SET(BTK_VERSION_STRING "${BTK_VERSION_MAJOR}.${BTK_VERSION_MINOR}.${BTK_VERSION_PATCH}")
# The major.minor is enough to distinguish available features of the toolkit. Moreover, 
# this variable is used to create lib/share/include folders where the patch number does 
# not need to be included.
SET(BTK_LIBRARY_VERSION_STRING "${BTK_VERSION_MAJOR}.${BTK_VERSION_MINOR}")

# ------------------------------------------------------------------------
# COMPILATION INSTRUCTIONS
# ------------------------------------------------------------------------

add_definitions("-std=c++11")

# Using the configuration "Always full RPATH"
# from http://www.cmake.org/Wiki/CMake_RPATH_handling
#             --------------------------
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/btk-${BTK_LIBRARY_VERSION_STRING}")
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Extra CMake scripts
SET(BTK_CMAKE_MODULE_PATH "${BTK_SOURCE_DIR}/CMake")
SET(CMAKE_MODULE_PATH "${BTK_CMAKE_MODULE_PATH}")

# Load some macros.
INCLUDE(${BTK_CMAKE_MODULE_PATH}/btkMacCompilerFlags.cmake)
INCLUDE(CMakeDependentOption)
INCLUDE(CheckIncludeFile)
INCLUDE(CheckIncludeFileCXX)

# By default BTK is compiled in Release mode
IF(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  MESSAGE(STATUS "Setting build type to 'Release' as none was specified.")
  SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
ENDIF(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

# Output directories.
IF(NOT LIBRARY_OUTPUT_PATH)
  SET (LIBRARY_OUTPUT_PATH ${BTK_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
ENDIF(NOT LIBRARY_OUTPUT_PATH)
IF(NOT EXECUTABLE_OUTPUT_PATH)
  SET (EXECUTABLE_OUTPUT_PATH ${BTK_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
ENDIF(NOT EXECUTABLE_OUTPUT_PATH)
SET(BTK_LIBRARY_PATH "${LIBRARY_OUTPUT_PATH}")
SET(BTK_EXECUTABLE_PATH "${EXECUTABLE_OUTPUT_PATH}")
SET(CXX_TEST_PATH ${EXECUTABLE_OUTPUT_PATH})

# 64 Build detection
IF( (CMAKE_SIZEOF_VOID_P EQUAL 8) OR CMAKE_CL_64)
  SET(HAVE_64_BIT 1)
ENDIF( (CMAKE_SIZEOF_VOID_P EQUAL 8) OR CMAKE_CL_64)

# Try to find mmap
CHECK_INCLUDE_FILE(sys/mman.h HAVE_SYS_MMAP)

# Find the header memory[.hpp] in specific path.
# This header contains the share_ptr class.
CHECK_INCLUDE_FILE_CXX(memory HAVE_SYS_MEMORY_H)
CHECK_INCLUDE_FILE_CXX(tr1/memory HAVE_SYS_TR1_MEMORY_H)
CHECK_INCLUDE_FILE(boost/memory.hpp HAVE_BOOST_MEMORY_HPP)
CHECK_INCLUDE_FILE(boost/tr1/memory.hpp HAVE_BOOST_TR1_MEMORY_HPP)
IF (NOT HAVE_BOOST_MEMORY_HPP AND NOT HAVE_BOOST_TR1_MEMORY_HPP)
  IF(MSVC AND MSVC_VERSION LESS 1500)
    SET(USE_INCLUDED_BOOST 1)
  ELSEIF(UNIX AND NOT HAVE_SYS_TR1_MEMORY_H)
    SET(USE_INCLUDED_BOOST 1)
  ENDIF(MSVC AND MSVC_VERSION LESS 1500)
  IF(USE_INCLUDED_BOOST)
    SET(BTK_INCLUDE_DIRS_BUILD_TREE ${BTK_INCLUDE_DIRS_BUILD_TREE} ${BTK_SOURCE_DIR}/Utilities/boost)
  ENDIF(USE_INCLUDED_BOOST)
ENDIF (NOT HAVE_BOOST_MEMORY_HPP AND NOT HAVE_BOOST_TR1_MEMORY_HPP)

# Macro to detect if a CMake variable exist or not
MACRO(CHECK_CMAKE_VARIABLE invar outvar)
  IF(${invar})
    SET(${outvar} 1)
  ELSE(${invar})
    SET(${outvar})
  ENDIF(${invar})
ENDMACRO(CHECK_CMAKE_VARIABLE)
# Check for the atomic timestamp
FIND_PACKAGE(Threads)
CHECK_CMAKE_VARIABLE(CMAKE_USE_SPROC_INIT HAVE_SPROC)
CHECK_CMAKE_VARIABLE(CMAKE_USE_WIN32_THREADS_INIT HAVE_WIN32_THREADS)
CHECK_CMAKE_VARIABLE(CMAKE_USE_PTHREADS_INIT HAVE_PTHREADS)
CHECK_CMAKE_VARIABLE(CMAKE_HP_PTHREADS_INIT HAVE_HP_PTHREADS)
INCLUDE(${BTK_CMAKE_MODULE_PATH}/btkTestAtomicBuiltins.cmake) # HAVE_ATOMIC_BUILTINS

# Extra compiler flags for the debug mode
INCLUDE(${BTK_CMAKE_MODULE_PATH}/btkExtraCompilerFlags.cmake)
# The entire BTK tree should use the same include path
# Create the list of include directories needed for BTK header files.
INCLUDE(${BTK_CMAKE_MODULE_PATH}/btkIncludeDirectories.cmake)
# This should be the only INCLUDE_DIRECTORIES command in the entire
# tree, except for the Utilities and Wrapping directories.  We need to
# do this in one place to make sure the order is correct.
INCLUDE_DIRECTORIES(
  ${BTK_INCLUDE_DIRS_BUILD_TREE}
  ${BTK_INCLUDE_DIRS_SYSTEM}
)

# BTK build configuration options.
OPTION(BUILD_SHARED_LIBS "Build BTK with shared libraries." OFF)
SET(BTK_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
IF(WIN32)
   IF(BUILD_SHARED_LIBS)
     SET(BTK_LIBS_BUILD_TYPE "SHARED")
   ELSE(BUILD_SHARED_LIBS)
     SET(BTK_LIBS_BUILD_TYPE "STATIC")
   ENDIF(BUILD_SHARED_LIBS)
ENDIF(WIN32)
# Configure files with settings for use by the build.
CONFIGURE_FILE(${BTK_SOURCE_DIR}/btkConfigure.h.in
               ${BTK_BINARY_DIR}/btkConfigure.h @ONLY IMMEDIATE)

IF(NOT BTK_NO_LIBRARY_VERSION)
  # This setting of SOVERSION assumes that any API change
  # will increment either the minor or major version number of BTK.
  SET(BTK_LIBRARY_PROPERTIES 
      VERSION   "${BTK_VERSION_MAJOR}.${BTK_VERSION_MINOR}.${BTK_VERSION_PATCH}"
      SOVERSION "${BTK_VERSION_MAJOR}.${BTK_VERSION_MINOR}"
     )
ENDIF(NOT BTK_NO_LIBRARY_VERSION)

# ------------------------------------------------------------------------
# INSTALLATION VARIABLES
# ------------------------------------------------------------------------

# Installation vars.
# BTK_INSTALL_BIN_DIR          - binary dir (executables)
# BTK_INSTALL_LIB_DIR          - library dir (libs)
# BTK_INSTALL_SHARE_DIR        - share dir (documentations, examples, data, etc)
# BTK_INSTALL_INCLUDE_DIR      - include dir (headers)
# BTK_INSTALL_PACKAGE_DIR      - package/export configuration files
# BTK_INSTALL_NO_DEVELOPMENT   - do not install development files
# BTK_INSTALL_NO_RUNTIME       - do not install runtime files
# BTK_INSTALL_NO_DOCUMENTATION - do not install documentation files

IF(NOT BTK_INSTALL_BIN_DIR)
  SET(BTK_INSTALL_BIN_DIR "/bin")
ENDIF(NOT BTK_INSTALL_BIN_DIR)

IF(NOT BTK_INSTALL_LIB_DIR)
  SET(BTK_INSTALL_LIB_DIR "/lib/btk-${BTK_LIBRARY_VERSION_STRING}")
ENDIF(NOT BTK_INSTALL_LIB_DIR)

IF(NOT BTK_INSTALL_SHARE_DIR)
  SET(BTK_INSTALL_SHARE_DIR "/share/btk-${BTK_LIBRARY_VERSION_STRING}")
ENDIF(NOT BTK_INSTALL_SHARE_DIR)

IF(NOT BTK_INSTALL_INCLUDE_DIR)
  SET(BTK_INSTALL_INCLUDE_DIR "/include/btk-${BTK_LIBRARY_VERSION_STRING}")
ENDIF(NOT BTK_INSTALL_INCLUDE_DIR)

IF(NOT BTK_INSTALL_PACKAGE_DIR)
  SET(BTK_INSTALL_PACKAGE_DIR ${BTK_INSTALL_LIB_DIR}
    CACHE INTERNAL "")
ENDIF(NOT BTK_INSTALL_PACKAGE_DIR)

# There are three basic components to the BTK installation: runtime,
# development, and documentation.  Install rules for each component
# are surrounded by blockers.  Parent projects or users can specify
# BTK_INSTALL_NO_RUNTIME, BTK_INSTALL_NO_DEVELOPMENT, or
# BTK_INSTALL_NO_DOCUMENTATION to avoid installation of the
# corresponding component.
IF(NOT BTK_INSTALL_NO_DEVELOPMENT)
  SET(BTK_INSTALL_NO_DEVELOPMENT 0)
ENDIF(NOT BTK_INSTALL_NO_DEVELOPMENT)

IF(NOT BTK_INSTALL_NO_RUNTIME)
  SET(BTK_INSTALL_NO_RUNTIME 0)
ENDIF(NOT BTK_INSTALL_NO_RUNTIME)

IF(NOT BTK_INSTALL_NO_DOCUMENTATION)
  SET(BTK_INSTALL_NO_DOCUMENTATION 0)
ENDIF(NOT BTK_INSTALL_NO_DOCUMENTATION)

# Shared libraries are considered both runtime and development and
# static libraries are considered development only.  In order to
# switch library installation on and off correctly we make the
# decision here.
SET(BTK_INSTALL_NO_LIBRARIES)
IF(BTK_BUILD_SHARED_LIBS)
  IF(BTK_INSTALL_NO_RUNTIME AND BTK_INSTALL_NO_DEVELOPMENT)
    SET(BTK_INSTALL_NO_LIBRARIES 1)
  ENDIF(BTK_INSTALL_NO_RUNTIME AND BTK_INSTALL_NO_DEVELOPMENT)
ELSE(BTK_BUILD_SHARED_LIBS)
  IF(BTK_INSTALL_NO_DEVELOPMENT)
    SET(BTK_INSTALL_NO_LIBRARIES 1)
  ENDIF(BTK_INSTALL_NO_DEVELOPMENT)
ENDIF(BTK_BUILD_SHARED_LIBS)

# Because INSTALL_* commands require a leading / and because INSTALL (cmake 2.4
# and newer) requires no leading / to install under INSTALL_PREFIX, we
# are stripping the leading /. In the future, there should be no leading
# / in any install directory variables
STRING(REGEX REPLACE "^/" "" BTK_INSTALL_BIN_DIR_CM24 "${BTK_INSTALL_BIN_DIR}")
STRING(REGEX REPLACE "^/" "" BTK_INSTALL_LIB_DIR_CM24 "${BTK_INSTALL_LIB_DIR}")
STRING(REGEX REPLACE "^/" "" BTK_INSTALL_SHARE_DIR_CM24 "${BTK_INSTALL_SHARE_DIR}")
STRING(REGEX REPLACE "^/" "" BTK_INSTALL_INCLUDE_DIR_CM24 "${BTK_INSTALL_INCLUDE_DIR}")

STRING(REGEX REPLACE "^/" "" BTK_INSTALL_PACKAGE_DIR_CM24 "${BTK_INSTALL_PACKAGE_DIR}")

# Make sure the user does not try to install on top of the build tree.
IF(WIN32 OR APPLE OR UNIX)
  STRING(TOLOWER "${CMAKE_INSTALL_PREFIX}" _PREFIX)
  STRING(TOLOWER "${BTK_BINARY_DIR}" _BUILD)
ELSE(WIN32 OR APPLE OR UNIX)
  SET(_PREFIX "${CMAKE_INSTALL_PREFIX}")
  SET(_BUILD "${BTK_BINARY_DIR}")
ENDIF(WIN32 OR APPLE OR UNIX)
IF("${_PREFIX}" STREQUAL "${_BUILD}")
  MESSAGE(FATAL_ERROR
    "The current CMAKE_INSTALL_PREFIX points at the build tree:\n"
    "  ${CMAKE_INSTALL_PREFIX}\n"
    "This is not supported."
    )
ENDIF("${_PREFIX}" STREQUAL "${_BUILD}")

# set BTK_DIR so it can be used by subprojects
SET(BTK_DIR "${CMAKE_BINARY_DIR}" CACHE INTERNAL "BTK dir to be used by subprojects")

# ------------------------------------------------------------------------
# PROJECT'S SUBDIRECTORIES
# ------------------------------------------------------------------------


SET(BTK_LIBRARIES "" CACHE INTERNAL "BTK modules compiled" FORCE)

# Code
ADD_SUBDIRECTORY(Code)

# Wrapping
ADD_SUBDIRECTORY(Wrapping)
# PYTHON wrapping
OPTION(BTK_WRAP_PYTHON "Wrap BTK classes into Python (Require SWIG 2.x)." OFF)
IF(BTK_WRAP_PYTHON)
  ADD_SUBDIRECTORY(Wrapping/Python)
ENDIF(BTK_WRAP_PYTHON)
# Matlab wrapping
OPTION(BTK_WRAP_MATLAB "Wrap BTK classes into Matlab functions." OFF)
IF(BTK_WRAP_MATLAB)
  SET(BTK_WRAPPING_DOCUMENTATION "${BTK_SOURCE_DIR}/Wrapping")
  SET(BTK_WRAPPING_DOCUMENTATION_MATLAB "${BTK_SOURCE_DIR}/Wrapping/Matlab")
  ADD_SUBDIRECTORY(Wrapping/Matlab)
  IF(MATLAB_MATLABR2010B_FOUND)
    SET(FIX_MATLAB_CHAR16_T_TYPE 1)
  ENDIF(MATLAB_MATLABR2010B_FOUND)
ENDIF(BTK_WRAP_MATLAB)
IF(NOT BTK_WRAP_MATLAB OR NOT BTK_WRAP_MATLAB_REDISTRIBUTABLE_MEX_FILES)
  IF (CMAKE_BUILD_MRD)
    SET(CMAKE_BUILD_MRD 0 CACHE STRING "" FORCE)
    SET(CMAKE_C_FLAGS_RELEASE ${CMAKE_OLD_C_FLAGS_RELEASE} CACHE STRING "Flags used by the compiler during release builds (/MD /Ob1 /Oi Ot /Oy /Gs will produce slightly less optimized but smaller files)" FORCE)
    SET(CMAKE_OLD_C_FLAGS_RELEASE 0 CACHE STRING "" FORCE)
    IF (NOT CMAKE_BUILD_SRD)
      SET(CMAKE_BUILD_TYPE ${CMAKE_OLD_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
      SET(CMAKE_OLD_BUILD_TYPE 0 CACHE STRING "" FORCE)
      IF (MSVC)
        SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_OLD_CXX_FLAGS_RELEASE} CACHE STRING "Flags used by the compiler during release builds (/MD /Ob1 /Oi Ot /Oy /Gs will produce slightly less optimized but smaller files)" FORCE)
        SET(CMAKE_OLD_CXX_FLAGS_RELEASE 0 CACHE STRING "" FORCE)
      ENDIF(MSVC)
    ENDIF (NOT CMAKE_BUILD_SRD)
  ENDIF(CMAKE_BUILD_MRD)
ENDIF(NOT BTK_WRAP_MATLAB OR NOT BTK_WRAP_MATLAB_REDISTRIBUTABLE_MEX_FILES)
# Scilab wrapping
# NOTE: THE CMAKE OPTION BTK_WRAP_SCILAB IS DISCARDED UNTIL THE ISSUE #6886 IS FIXED.
#OPTION(BTK_WRAP_SCILAB "Wrap BTK classes into Scilab functions." OFF)
IF(BTK_WRAP_SCILAB)
  SET(BTK_WRAPPING_DOCUMENTATION "${BTK_SOURCE_DIR}/Wrapping")
  SET(BTK_WRAPPING_DOCUMENTATION_SCILAB "${BTK_SOURCE_DIR}/Wrapping/Scilab")
  ADD_SUBDIRECTORY(Wrapping/Scilab)
ENDIF(BTK_WRAP_SCILAB)
IF(NOT BTK_WRAP_SCILAB OR NOT BTK_WRAP_SCILAB_REDISTRIBUTABLE_FILES)
  IF (CMAKE_BUILD_SRD)
    SET(CMAKE_BUILD_SRD 0 CACHE STRING "" FORCE)
    SET(CMAKE_C_FLAGS_RELEASE ${CMAKE_OLD_C_FLAGS_RELEASE} CACHE STRING "Flags used by the compiler during release builds (/MD /Ob1 /Oi Ot /Oy /Gs will produce slightly less optimized but smaller files)" FORCE)
    SET(CMAKE_OLD_C_FLAGS_RELEASE 0 CACHE STRING "" FORCE)
    IF (NOT CMAKE_BUILD_MRD)
      SET(CMAKE_BUILD_TYPE ${CMAKE_OLD_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
      SET(CMAKE_OLD_BUILD_TYPE 0 CACHE STRING "" FORCE)
      IF (MSVC)
        SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_OLD_CXX_FLAGS_RELEASE} CACHE STRING "Flags used by the compiler during release builds (/MD /Ob1 /Oi Ot /Oy /Gs will produce slightly less optimized but smaller files)" FORCE)
        SET(CMAKE_OLD_CXX_FLAGS_RELEASE 0 CACHE STRING "" FORCE)
      ENDIF(MSVC)
    ENDIF(NOT CMAKE_BUILD_MRD)
  ENDIF(CMAKE_BUILD_SRD)
ENDIF(NOT BTK_WRAP_SCILAB OR NOT BTK_WRAP_SCILAB_REDISTRIBUTABLE_FILES)
# Octave wrapping
OPTION(BTK_WRAP_OCTAVE "Wrap BTK classes into Octave functions." OFF)
IF(BTK_WRAP_OCTAVE)
  SET(BTK_WRAPPING_DOCUMENTATION "${BTK_SOURCE_DIR}/Wrapping")
  SET(BTK_WRAPPING_DOCUMENTATION_OCTAVE "${BTK_SOURCE_DIR}/Wrapping/Octave")
  ADD_SUBDIRECTORY(Wrapping/Octave)
ENDIF(BTK_WRAP_OCTAVE)
IF(NOT BTK_WRAP_OCTAVE OR NOT BTK_WRAP_OCTAVE_REDISTRIBUTABLE_FILES)
  IF (CMAKE_BUILD_SRD)
    SET(CMAKE_BUILD_SRD 0 CACHE STRING "" FORCE)
    SET(CMAKE_C_FLAGS_RELEASE ${CMAKE_OLD_C_FLAGS_RELEASE} CACHE STRING "Flags used by the compiler during release builds (/MD /Ob1 /Oi Ot /Oy /Gs will produce slightly less optimized but smaller files)" FORCE)
    SET(CMAKE_OLD_C_FLAGS_RELEASE 0 CACHE STRING "" FORCE)
    IF (NOT CMAKE_BUILD_MRD)
      SET(CMAKE_BUILD_TYPE ${CMAKE_OLD_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
      SET(CMAKE_OLD_BUILD_TYPE 0 CACHE STRING "" FORCE)
      IF (MSVC)
        SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_OLD_CXX_FLAGS_RELEASE} CACHE STRING "Flags used by the compiler during release builds (/MD /Ob1 /Oi Ot /Oy /Gs will produce slightly less optimized but smaller files)" FORCE)
        SET(CMAKE_OLD_CXX_FLAGS_RELEASE 0 CACHE STRING "" FORCE)
      ENDIF(MSVC)
    ENDIF(NOT CMAKE_BUILD_MRD)
  ENDIF(CMAKE_BUILD_SRD)
ENDIF(NOT BTK_WRAP_OCTAVE OR NOT BTK_WRAP_OCTAVE_REDISTRIBUTABLE_FILES)

# TDD (Test-driven development) code
OPTION(BUILD_TESTING "Build BTK unit and regression tests." OFF)
IF(BUILD_TESTING)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(Testing)
ENDIF(BUILD_TESTING)

# Documentation
OPTION(BUILD_DOCUMENTATION "Build BTK Documentation." OFF)
IF(BUILD_DOCUMENTATION)
  ADD_SUBDIRECTORY(Utilities/Doxygen)
ENDIF(BUILD_DOCUMENTATION)

# BTK examples
OPTION(BUILD_EXAMPLES "Build BTK Examples." OFF)
IF(BUILD_EXAMPLES)
  ADD_SUBDIRECTORY(Examples)
ENDIF(BUILD_EXAMPLES)

# Utilities (boost/eigen3/...)
ADD_SUBDIRECTORY(Utilities)

# ------------------------------------------------------------------------
# PACKAGING INSTRUCTIONS
# ------------------------------------------------------------------------
ADD_SUBDIRECTORY(Packaging)

# ------------------------------------------------------------------------
# INSTALLATION INSTRUCTIONS
# ------------------------------------------------------------------------

IF(NOT BTK_INSTALL_NO_DEVELOPMENT)
  INSTALL(FILES ${BTK_BINARY_DIR}/btkConfigure.h
    DESTINATION ${BTK_INSTALL_INCLUDE_DIR_CM24}
    COMPONENT Development)
ENDIF(NOT BTK_INSTALL_NO_DEVELOPMENT)

CONFIGURE_FILE(${BTK_CMAKE_MODULE_PATH}/UseBTK.cmake.in
               ${BTK_BINARY_DIR}/UseBTK.cmake COPYONLY IMMEDIATE)

# Save the compiler settings so another project can import them.
INCLUDE(${CMAKE_ROOT}/Modules/CMakeExportBuildSettings.cmake)
CMAKE_EXPORT_BUILD_SETTINGS(${BTK_BINARY_DIR}/BTKBuildSettings.cmake)

# Save library dependencies.
EXPORT_LIBRARY_DEPENDENCIES(${BTK_BINARY_DIR}/BTKLibraryDepends.cmake)

# Create the BTKConfig.cmake file containing the BTK configuration.
INCLUDE (${BTK_CMAKE_MODULE_PATH}/btkGenerateBTKConfig.cmake)

IF(NOT BTK_INSTALL_NO_DEVELOPMENT)
  INSTALL(FILES
    ${BTK_BINARY_DIR}/BTKBuildSettings.cmake
    ${BTK_BINARY_DIR}/BTKLibraryDepends.cmake
    ${BTK_CMAKE_MODULE_PATH}/FindBTK.cmake
    ${BTK_BINARY_DIR}/UseBTK.cmake
    DESTINATION ${BTK_INSTALL_SHARE_DIR_CM24}
    COMPONENT Development
  )
ENDIF(NOT BTK_INSTALL_NO_DEVELOPMENT)

