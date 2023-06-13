# Install script for directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_fwd.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_tolerance.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_tolerance.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_box_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_box_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_box_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_box_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_vector_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_vector_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_vector_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_vector_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_1d_basis.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_1d_basis.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_point_1d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_point_1d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_point_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_point_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_point_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_point_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_point_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_point_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_point_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_point_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_line_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_line_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_line_3d_2_points.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_line_3d_2_points.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_3d_2_points.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_3d_2_points.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_segment_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_segment_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_segment_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_line_segment_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_infinite_line_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_infinite_line_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_conic.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_conic.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_conic_segment_2d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_conic_segment_2d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_polygon.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_polygon.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_sphere_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_sphere_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_cylinder.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_cylinder.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_plane_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_plane_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_plane_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_homg_plane_3d.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_closest_point.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_closest_point.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_distance.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_distance.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_clip.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_clip.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_area.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_area.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_convex.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_convex.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_intersection.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_intersection.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_lineseg_test.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_lineseg_test.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_triangle_test.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_triangle_test.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_polygon_test.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_polygon_test.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_triangle_3d.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_region_scan_iterator.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_triangle_scan_iterator.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_triangle_scan_iterator.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_window_scan_iterator.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_window_scan_iterator.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_polygon_scan_iterator.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_polygon_scan_iterator.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_ellipse_scan_iterator.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vxl/core/vgl" TYPE FILE FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/vgl/vgl_ellipse_scan_iterator.txx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/lib/libvgl.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/core/vgl/algo/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/core/vgl/examples/cmake_install.cmake")
  include("C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/core/vgl/tests/cmake_install.cmake")

endif()

