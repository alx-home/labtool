# segmentation detection library
# brl/bseg/sdet/CMakeLists.txt

doxygen_add_library(contrib/brl/bseg/sdet
  DEPENDS contrib/brl/bseg/brip contrib/brl/bbas/btol core/vil1
  PACKAGE contrib/brl
  )

INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR}/bseg )
INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR} )

SET(sdet_sources
    sdet_edge_champher.cxx       sdet_edge_champher.h
    sdet_region_edge.cxx         sdet_region_edge.h  sdet_region_edge_sptr.h
    sdet_edgel_regions.cxx       sdet_edgel_regions.h
    sdet_contour.cxx             sdet_contour.h
    sdet_detector_params.cxx     sdet_detector_params.h
    sdet_detector.cxx            sdet_detector.h
    sdet_region_proc_params.cxx  sdet_region_proc_params.h
    sdet_region_proc.cxx         sdet_region_proc.h
    sdet_harris_detector_params.cxx sdet_harris_detector_params.h
    sdet_harris_detector.cxx     sdet_harris_detector.h
    sdet_fit_lines.cxx           sdet_fit_lines.h
    sdet_fit_lines_params.cxx    sdet_fit_lines_params.h
    sdet_fit_conics.cxx           sdet_fit_conics.h
    sdet_fit_conics_params.cxx    sdet_fit_conics_params.h
    sdet_grid_finder_params.cxx  sdet_grid_finder_params.h
    sdet_grid_finder.cxx         sdet_grid_finder.h
    sdet_region.cxx    sdet_region.h sdet_region_sptr.h
    sdet_watershed_region_proc_params.cxx   sdet_watershed_region_proc_params.h
    sdet_watershed_region_proc.cxx   sdet_watershed_region_proc.h
    sdet_nonmax_suppression_params.cxx sdet_nonmax_suppression_params.h
    sdet_nonmax_suppression.cxx     sdet_nonmax_suppression.h
    sdet_gauss_fit.cxx              sdet_gauss_fit.h
    sdet_img_edge.cxx               sdet_img_edge.h
)
AUX_SOURCE_DIRECTORY(Templates sdet_sources)

ADD_LIBRARY(sdet ${sdet_sources})
INSTALL_TARGETS(/lib sdet)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/brl/bseg/sdet ${sdet_sources})

TARGET_LINK_LIBRARIES(sdet brip bsol btol bdgl gevd vdgl vtol vsol bil_algo vil vil_algo vil1 vgl_algo vgl vnl_algo vnl vul vbl)

IF(BUILD_TESTING)
  SUBDIRS(tests)
ENDIF(BUILD_TESTING)
