# mul/vimt/algo/CMakeLists.txt

SET( vimt_algo_sources
  vimt_correlate_2d.h
  vimt_find_peaks.h
  vimt_find_troughs.h
  vimt_normalised_correlation_2d.h
  vimt_pyramid_values_at_point.h
  # This file merely forces the creation of an actual library
  vimt_dummy.cxx
)

ADD_LIBRARY(vimt_algo ${vimt_algo_sources})
INSTALL_TARGETS(/lib vimt_algo)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/mul/vimt/algo ${vimt_algo_sources})
TARGET_LINK_LIBRARIES( vimt_algo vimt vil_algo vgl vcl )
