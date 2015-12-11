# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_fwd.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_bool_ostream.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_smart_ptr.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_smart_ptr.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_shared_pointer.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_scoped_ptr.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_checked_delete.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sort.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sort.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_qsort.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_array_1d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_array_1d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_array_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_array_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_array_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_array_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_bit_array_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_bit_array_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_base.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_base.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_1d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_1d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_sparse_array_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_big_sparse_array_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_big_sparse_array_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_ref_count.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_bounding_box.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_bounding_box.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_triple.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_triple.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_quadruple.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vbl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vbl/vbl_quadruple.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/lib/libvbl.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/core/vbl/examples/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/core/vbl/tests/cmake_install.cmake")

endif()

