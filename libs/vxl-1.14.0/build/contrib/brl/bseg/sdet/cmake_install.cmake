# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_edge_champher.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_region_edge.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_region_edge_sptr.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_edgel_regions.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_contour.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_detector_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_detector.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_region_proc_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_region_proc.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_harris_detector_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_harris_detector.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_fit_lines.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_fit_lines_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_fit_conics.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_fit_conics_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_grid_finder_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_grid_finder.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_region.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_region_sptr.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_watershed_region_proc_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_watershed_region_proc.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_nonmax_suppression_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_nonmax_suppression.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_gauss_fit.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/brl/bseg/sdet" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/sdet/sdet_img_edge.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/lib/libsdet.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/sdet/tests/cmake_install.cmake")

endif()

