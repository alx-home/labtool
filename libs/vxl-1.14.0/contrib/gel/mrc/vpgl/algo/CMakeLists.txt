# gel/mrc/vpgl/algo/CMakeLists.txt
# Photogrammetry Algorithms Library.

# vpgl/algo requires these other sections of contrib
IF(BUILD_RPL)

INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${RPL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR}/mrc)

SET( vpgl_algo_sources
  vpgl_construct_cameras.h         vpgl_construct_cameras.cxx
  vpgl_optimize_camera.h           vpgl_optimize_camera.cxx
  vpgl_project.h                   vpgl_project.cxx
  vpgl_camera_compute.h            vpgl_camera_compute.cxx
  vpgl_fm_compute_7_point.h        vpgl_fm_compute_7_point.cxx
  vpgl_fm_compute_8_point.h        vpgl_fm_compute_8_point.cxx
  vpgl_fm_compute_2_point.h        vpgl_fm_compute_2_point.cxx
  vpgl_fm_compute_ransac.h         vpgl_fm_compute_ransac.cxx
  vpgl_fm_compute_reg_ransac.h     vpgl_fm_compute_reg_ransac.cxx
  vpgl_fm_compute_affine_ransac.h  vpgl_fm_compute_affine_ransac.cxx
  vpgl_lens_warp_mapper.h
  vpgl_vsol_lens_warp.h            vpgl_vsol_lens_warp.cxx
  vpgl_list.h                      vpgl_list.txx
  vpgl_invmap_cost_function.h      vpgl_invmap_cost_function.cxx
  vpgl_backproject.h               vpgl_backproject.cxx
  vpgl_ray.h                       vpgl_ray.cxx
  vpgl_ortho_procrustes.h          vpgl_ortho_procrustes.cxx
  vpgl_ray_intersect.h             vpgl_ray_intersect.cxx
  vpgl_adjust_rational_trans_onept.h vpgl_adjust_rational_trans_onept.cxx
  vpgl_rational_geo_adjust.h        vpgl_rational_geo_adjust.cxx
  vpgl_bundle_adjust.h             vpgl_bundle_adjust.cxx
  vpgl_interpolate.h               vpgl_interpolate.cxx
  vpgl_camera_homographies.h       vpgl_camera_homographies.cxx
  vpgl_nitf_camera_coverage.h      vpgl_nitf_camera_coverage.cxx
)

AUX_SOURCE_DIRECTORY(Templates vpgl_algo_sources)

ADD_LIBRARY(vpgl_algo ${vpgl_algo_sources})
TARGET_LINK_LIBRARIES( vpgl_algo vpgl vpgl_file_formats rrel vsol bgeo vgl_algo vnl_algo vnl vgl vil vul )

IF( BUILD_TESTING )
  SUBDIRS(tests)
ENDIF( BUILD_TESTING )

IF( BUILD_EXAMPLES )
  SUBDIRS( examples )
ENDIF( BUILD_EXAMPLES )

ENDIF(BUILD_RPL)
