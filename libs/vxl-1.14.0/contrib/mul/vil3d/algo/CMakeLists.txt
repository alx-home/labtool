# mul/vil3d/algo/CMakeLists.txt

SET(vil3d_algo_sources
  vil3d_gauss_reduce.h        vil3d_gauss_reduce.txx
  vil3d_threshold.h           vil3d_threshold.txx
  vil3d_grad_1x3.h            vil3d_grad_1x3.cxx           vil3d_grad_1x3.txx
  vil3d_grad_3x3x3.h
  vil3d_structuring_element.h vil3d_structuring_element.cxx
  vil3d_binary_dilate.h       vil3d_binary_dilate.cxx
  vil3d_binary_erode.h        vil3d_binary_erode.cxx
  vil3d_erode.h
  vil3d_histogram_equalise.h  vil3d_histogram_equalise.cxx
  vil3d_histogram.h           vil3d_histogram.cxx
  vil3d_binary_opening.h
  vil3d_binary_closing.h
  vil3d_exp_filter.h
  vil3d_locally_z_normalise.h
  vil3d_normalised_correlation_3d.h
  vil3d_convolve_1d.h
  vil3d_distance_transform.h    vil3d_distance_transform.cxx
  vil3d_exp_distance_transform.h 
  vil3d_fill_boundary.h         vil3d_fill_boundary.cxx
  vil3d_anisotropic_filter.h
  vil3d_max_product_filter.h
  vil3d_corners.h               vil3d_corners.txx
  vil3d_find_peaks.h
  vil3d_quad_distance_function.h 
  vil3d_smooth_121.h
  vil3d_abs_shuffle_distance.h  vil3d_abs_shuffle_distance.txx
  vil3d_make_distance_filter.h  vil3d_make_distance_filter.cxx
  vil3d_make_edt_filter.h       vil3d_make_edt_filter.cxx  
  vil3d_overlap.h               vil3d_overlap.cxx
  vil3d_find_blobs.h            vil3d_find_blobs.cxx
)

AUX_SOURCE_DIRECTORY(Templates vil3d_algo_sources)

ADD_LIBRARY(vil3d_algo ${vil3d_algo_sources})
INSTALL_TARGETS(/lib vil3d_algo)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/mul/vil3d/algo ${vil3d_algo_sources})
TARGET_LINK_LIBRARIES( vil3d_algo vil3d vil_algo vil vnl vgl )
