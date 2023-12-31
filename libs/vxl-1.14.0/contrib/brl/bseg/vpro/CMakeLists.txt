# video processor library
# brl/bseg/vpro/CMakeLists.txt

doxygen_add_library(contrib/brl/bseg/vpro
  DEPENDS contrib/brl/bseg/sdet core/vidl_vil1
  PACKAGE contrib/brl
  )

INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR}/bseg )
INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR})

SET(vpro_sources
    vpro_video_process.cxx           vpro_video_process.h  vpro_video_process_sptr.h
    vpro_region_process.cxx          vpro_region_process.h
    vpro_frame_diff_params.cxx       vpro_frame_diff_params.h
    vpro_frame_diff_process.cxx      vpro_frame_diff_process.h
    vpro_motion_params.cxx           vpro_motion_params.h
    vpro_motion_process.cxx          vpro_motion_process.h
    vpro_lucas_kanade_process.cxx    vpro_lucas_kanade_process.h
    vpro_epipolar_space_process.cxx  vpro_epipolar_space_process.h
    vpro_edge_process.cxx            vpro_edge_process.h
    vpro_harris_corner_process.cxx   vpro_harris_corner_process.h
    vpro_line_fit_process.cxx        vpro_line_fit_process.h
    vpro_edge_line_process.cxx       vpro_edge_line_process.h
    vpro_grid_finder_process.cxx     vpro_grid_finder_process.h
    vpro_fourier_params.cxx          vpro_fourier_params.h
    vpro_fourier_process.cxx         vpro_fourier_process.h
    vpro_spatial_filter_params.cxx   vpro_spatial_filter_params.h
    vpro_spatial_filter_process.cxx  vpro_spatial_filter_process.h
    vpro_ihs_process.cxx             vpro_ihs_process.h

    vpro_vil_video_process.cxx       vpro_vil_video_process.h
                                     vpro_vil_video_process_sptr.h
)
AUX_SOURCE_DIRECTORY(Templates vpro_sources)

IF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
SET(vpro_sources ${vpro_sources}
    vpro_capture_process.cxx         vpro_capture_process.h
    vpro_basis_generator_process.cxx vpro_basis_generator_process.h
    vpro_half_res_process.cxx        vpro_half_res_process.h
    vpro_roi_process.cxx             vpro_roi_process.h
)
ENDIF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)

ADD_LIBRARY(vpro ${vpro_sources})
INSTALL_TARGETS(/lib vpro)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/vpro ${vpro_sources})

TARGET_LINK_LIBRARIES(vpro sdet brip gevd vtol vsol vil1 vil vul vbl)
IF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
  TARGET_LINK_LIBRARIES(vpro vidl_vil1 vidl1)
ENDIF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)


IF(BUILD_TESTING)
  SUBDIRS(tests)
ENDIF(BUILD_TESTING)
