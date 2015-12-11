# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_fwd.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_bounding_box.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_dist.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_kd_tree.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_kd_tree_sptr.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_point.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_bins_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_bins_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_borgefors.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_borgefors.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_bins.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/rpl/rsdl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/rpl/rsdl/rsdl_bins.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/lib/librsdl.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/rpl/rsdl/tests/cmake_install.cmake")

endif()

