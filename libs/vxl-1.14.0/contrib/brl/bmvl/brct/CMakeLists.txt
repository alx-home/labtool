# brl/bmvl/brct/CMakeLists.txt

# 3D reconstruction from multiple views library

doxygen_add_library(contrib/brl/bmvl/brct
  DEPENDS contrib/brl/bseg/sdet contrib/brl/bbas/bugl
  PACKAGE contrib/brl
  )

IF( BUILD_OXL )
IF( BUILD_RPL )

INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR}/bmvl )
INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR}/mrc )
INCLUDE_DIRECTORIES(${OXL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${RPL_INCLUDE_DIR} )

SET(brct_sources
    brct_algos.h                  brct_algos.cpp
    kalman_filter.h               kalman_filter.cpp
    brct_structure_estimator.h    brct_structure_estimator.cxx
    brct_epi_reconstructor.h      brct_epi_reconstructor.cxx
    brct_plane_calibrator.h       brct_plane_calibrator.cxx
    brct_corr.h                   brct_corr.cxx          brct_corr_sptr.h
    brct_plane_corr.h             brct_plane_corr.cxx    brct_plane_corr_sptr.h
    brct_plane_sweeper_params.h   brct_plane_sweeper_params.cxx
    brct_plane_sweeper.h          brct_plane_sweeper.cxx
    brct_volume_processor_params.h    brct_volume_processor_params.cxx
    brct_volume_processor.h       brct_volume_processor.cxx
)
AUX_SOURCE_DIRECTORY(Templates brct_sources)

IF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
SET(brct_sources ${brct_sources}
    brct_dense_reconstructor.h    brct_dense_reconstructor.cxx
)
ENDIF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)

ADD_LIBRARY(brct ${brct_sources})
INSTALL_TARGETS(/lib brct)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/brl/bmvl/brct ${brct_sources})

TARGET_LINK_LIBRARIES(brct sdet brip rrel bsol vpgl gevd vdgl vsol mvl bdgl bugl vil vil1 vgl_algo vgl vnl_algo vnl vbl)
IF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
  # vsrl is only used by brct_dense_reconstructor
  TARGET_LINK_LIBRARIES(brct vsrl)
ENDIF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)

IF(BUILD_TESTING)
  SUBDIRS(tests)
ENDIF(BUILD_TESTING)

ENDIF( BUILD_RPL )
ENDIF( BUILD_OXL )
