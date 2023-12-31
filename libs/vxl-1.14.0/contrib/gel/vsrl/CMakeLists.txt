# gel/vsrl/CMakeLists.txt

doxygen_add_library(contrib/gel/vsrl
  DEPENDS
    contrib/brl/bseg/sdet
    contrib/gel/vgel
    contrib/tbl/vepl
    core/vgui
    core/vil1
    contrib/rpl/rsdl
  PACKAGE contrib/gel
  DESCRIPTION "Dense image matcher"
  )

INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR})

SET(vsrl_sources
 vsrl_3d_output.cxx             vsrl_3d_output.h
                                vsrl_dense_matcher.h
 vsrl_diffusion.cxx             vsrl_diffusion.h
 vsrl_dynamic_program.cxx       vsrl_dynamic_program.h
 vsrl_image_correlation.cxx     vsrl_image_correlation.h
 vsrl_intensity_token.cxx       vsrl_intensity_token.h
 vsrl_null_token.cxx            vsrl_null_token.h
 vsrl_parameters.cxx            vsrl_parameters.h
 vsrl_raster_dp_setup.cxx       vsrl_raster_dp_setup.h
 vsrl_results_dense_matcher.cxx vsrl_results_dense_matcher.h
 vsrl_saliency_diffusion.cxx    vsrl_saliency_diffusion.h
 vsrl_step_diffusion.cxx        vsrl_step_diffusion.h
 vsrl_stereo_dense_matcher.cxx  vsrl_stereo_dense_matcher.h
                                vsrl_token.h
 vsrl_token_saliency.cxx        vsrl_token_saliency.h
 vsrl_window_accumulator.cxx    vsrl_window_accumulator.h
 vsrl_region_disparity.cxx      vsrl_region_disparity.h
)

# vsrl_manager depends on vgui, on tbl/vepl and on brl/bseg/sdet
# vsrl_menus and vsrl_point_picker depend on vgui
INCLUDE( ${MODULE_PATH}/UseVGUI.cmake )

IF (HAS_VGUI)
 INCLUDE_DIRECTORIES(${VXLCORE_INCLUDE_DIR})

 SET(vsrl_sources ${vsrl_sources}
  vsrl_point_picker.cxx         vsrl_point_picker.h    vsrl_point_picker_sptr.h
  vsrl_menus.h vsrl_menus.cxx
 )
 IF (BUILD_TBL)
 IF (BUILD_BRL)
 IF (BUILD_RPL)
   INCLUDE_DIRECTORIES(${TBL_INCLUDE_DIR})
   INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR}/bseg)
   INCLUDE_DIRECTORIES(${RPL_INCLUDE_DIR}) # rsdl is in rpl
   SET(vsrl_sources ${vsrl_sources}
    vsrl_manager.cxx              vsrl_manager.h
   )
 ENDIF (BUILD_RPL)
 ENDIF (BUILD_BRL)
 ENDIF (BUILD_TBL)
ENDIF (HAS_VGUI)

ADD_LIBRARY(vsrl ${vsrl_sources})
INSTALL_TARGETS(/lib vsrl)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/gel/vsrl ${vsrl_sources})

IF (HAS_VGUI)
 IF (BUILD_BRL)
#  TARGET_LINK_LIBRARIES(vsrl sdet jseg)
# remove missing jseg error
  TARGET_LINK_LIBRARIES(vsrl sdet)
 ENDIF (BUILD_BRL)
 TARGET_LINK_LIBRARIES(vsrl vgui)
 IF (BUILD_TBL)
  TARGET_LINK_LIBRARIES(vsrl vepl)
 ENDIF (BUILD_TBL)
 IF (BUILD_RPL)
  TARGET_LINK_LIBRARIES(vsrl rsdl)
 ENDIF (BUILD_RPL)
ENDIF (HAS_VGUI)

TARGET_LINK_LIBRARIES(vsrl vtol vdgl vgl vil1 vnl vgel)

# vgel uses mvl from oxl
INCLUDE_DIRECTORIES(${OXL_INCLUDE_DIR})

IF (BUILD_EXAMPLES)
  SUBDIRS(examples)
ENDIF (BUILD_EXAMPLES)
