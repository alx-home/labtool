# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_tracker_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_tracker.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_info_tracker_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_info_tracker.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_tracking_face_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_tracking_face_2d_sptr.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_art_info_model.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_art_info_model_sptr.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_info_model_tracker.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_info_model_tracker_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_info_model_tracker_process.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_art_model_display_process.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_corr_tracker_process.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_info_tracker_process.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_track_display_process.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_region_info_params.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_region_info.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_io.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/strk" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/contrib/brl/bseg/strk/strk_feature_capture_process.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/lib/libstrk.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/contrib/brl/bseg/strk/tests/cmake_install.cmake")

endif()

