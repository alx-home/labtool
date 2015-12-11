# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/brip/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/sdet/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/vpro/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/strk/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/segv/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/sbin/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bbgm/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bbgm_batch/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bvxm/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bvxm_batch/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bmdl/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bmdl_batch/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/brec/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/brec_batch/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/boct/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/boxm/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/boxm_batch/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bvpl/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bvpl_batch/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/bvpl_octree_batch/cmake_install.cmake")

endif()

