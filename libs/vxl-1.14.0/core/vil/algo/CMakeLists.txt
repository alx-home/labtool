# core/vil/algo/CMakeLists.txt

PROJECT(vil_algo)


SET( vil_algo_sources
  vil_sobel_1x3.cxx                vil_sobel_1x3.h    vil_sobel_1x3.txx
  vil_sobel_3x3.cxx                vil_sobel_3x3.h    vil_sobel_3x3.txx
  vil_gauss_filter.cxx             vil_gauss_filter.h vil_gauss_filter.txx
  vil_gauss_reduce.cxx             vil_gauss_reduce.h vil_gauss_reduce.txx
  vil_median.txx                   vil_median.h
  vil_structuring_element.cxx      vil_structuring_element.h
  vil_binary_dilate.cxx            vil_binary_dilate.h
  vil_binary_erode.cxx             vil_binary_erode.h
  vil_greyscale_dilate.txx         vil_greyscale_dilate.h
  vil_greyscale_erode.txx          vil_greyscale_erode.h
                                   vil_greyscale_opening.h
                                   vil_greyscale_closing.h
                                   vil_binary_opening.h
                                   vil_binary_closing.h
                                   vil_convolve_1d.h
                                   vil_convolve_2d.h
                                   vil_correlate_1d.h
                                   vil_correlate_2d.h
                                   vil_dog_filter_5tap.h
                                   vil_dog_pyramid.h
                                   vil_exp_filter_1d.h
                                   vil_normalised_correlation_2d.h
                                   vil_exp_grad_filter_1d.h
                                   vil_exp_filter_2d.h
                                   vil_suppress_non_max.h
                                   vil_suppress_non_plateau.h
                                   vil_quad_distance_function.h
  vil_suppress_non_max_edges.txx   vil_suppress_non_max_edges.h
  vil_line_filter.txx              vil_line_filter.h
  vil_threshold.txx                vil_threshold.h
                                   vil_grid_merge.h
                                   vil_find_4con_boundary.h
                                   vil_find_peaks.h
                                   vil_find_plateaus.h
  vil_fft.txx                      vil_fft.h
  vil_histogram.cxx                vil_histogram.h
  vil_histogram_equalise.cxx       vil_histogram_equalise.h
  vil_trace_4con_boundary.cxx      vil_trace_4con_boundary.h
  vil_trace_8con_boundary.cxx      vil_trace_8con_boundary.h
  vil_blob_finder.cxx              vil_blob_finder.h
  vil_distance_transform.cxx       vil_distance_transform.h
  vil_corners.cxx                  vil_corners.h
  vil_region_finder.txx            vil_region_finder.h
  vil_cartesian_differential_invariants.txx  vil_cartesian_differential_invariants.h
                                   vil_tile_images.h
  vil_orientations.cxx             vil_orientations.h
  vil_colour_space.cxx             vil_colour_space.h
  vil_abs_shuffle_distance.txx     vil_abs_shuffle_distance.h
  vil_checker_board.txx            vil_checker_board.h
                                   vil_flood_fill.h
)

AUX_SOURCE_DIRECTORY(Templates vil_algo_sources)

ADD_LIBRARY(vil_algo ${vil_algo_sources})

TARGET_LINK_LIBRARIES( vil_algo vil vnl_algo vnl vcl )

INSTALL_TARGETS(/lib vil_algo)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/core/vil/algo ${vil_algo_sources})

IF( BUILD_EXAMPLES )
  SUBDIRS( examples )
ENDIF( BUILD_EXAMPLES )
IF( BUILD_TESTING )
  SUBDIRS(tests)
ENDIF( BUILD_TESTING )
