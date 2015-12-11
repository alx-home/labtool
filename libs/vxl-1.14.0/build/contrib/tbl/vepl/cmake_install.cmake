# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_threshold.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_add_random_noise.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_monadic.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_dyadic.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_erode_disk.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_dilate_disk.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_sobel.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_gaussian_convolution.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_x_gradient.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_y_gradient.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_gradient_mag.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_gradient_dir.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_median.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_moment.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_histogram.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_convert.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl/vepl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/tbl/vepl/vepl_convert.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/lib/libvepl.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/tbl/vepl/examples/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/tbl/vepl/tests/cmake_install.cmake")

endif()

