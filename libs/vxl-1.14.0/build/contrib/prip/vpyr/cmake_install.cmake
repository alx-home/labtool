# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_pyramid.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_pyramid.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_pyramid_base.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_pyramid_level_elts.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_pyramid_level.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_pyramid_level.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_tpyramid.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_tpyramid.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_tpyramid_base.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_tpyramid_builder.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_tpyramid_level_elts.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_tpyramid_level.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_2_tpyramid_level.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_top_tmap.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/prip/vpyr" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/prip/vpyr/vpyr_top_tmap.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/lib/libvpyr.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/prip/vpyr/examples/simple_segmentation/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/prip/vpyr/tests/cmake_install.cmake")

endif()

