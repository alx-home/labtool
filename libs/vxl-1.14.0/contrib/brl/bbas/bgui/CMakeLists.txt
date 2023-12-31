# basic vgui add-ons
# brl/bbas/bgui/CMakeLists.txt

doxygen_add_library(contrib/brl/bbas/bgui
  DEPENDS contrib/brl/bbas/btol core/vgui
  PACKAGE contrib/brl
  DESCRIPTION "Brown VGUI Augmentation"
  )

INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR}/bbas )
INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR} )

# determines if vgui is built and opengl is available
INCLUDE( ${MODULE_PATH}/UseVGUI.cmake )

IF(HAS_VGUI)
 SET(bgui_sources
     bgui_vsol_soview2D.cxx            bgui_vsol_soview2D.h
     bgui_vsol2D_tableau.cxx           bgui_vsol2D_tableau.h          bgui_vsol2D_tableau_sptr.h
     bgui_vtol2D_tableau.cxx           bgui_vtol2D_tableau.h          bgui_vtol2D_tableau_sptr.h
     bgui_vtol2D_rubberband_client.cxx bgui_vtol2D_rubberband_client.h
     bgui_vtol_soview2D.cxx            bgui_vtol_soview2D.h
     bgui_vsol_camera_tableau.cxx      bgui_vsol_camera_tableau.h     bgui_vsol_camera_tableau_sptr.h
     bgui_picker_tableau.cxx           bgui_picker_tableau.h          bgui_picker_tableau_sptr.h
     bgui_image_tableau.cxx            bgui_image_tableau.h           bgui_image_tableau_sptr.h
     bgui_histogram_tableau.cxx        bgui_histogram_tableau.h       bgui_histogram_tableau_sptr.h
     bgui_selector_tableau.cxx         bgui_selector_tableau.h        bgui_selector_tableau_sptr.h
     bgui_bargraph_clipon_tableau.cxx  bgui_bargraph_clipon_tableau.h bgui_bargraph_clipon_tableau_sptr.h
     bgui_range_adjuster_tableau.cxx   bgui_range_adjuster_tableau.h  bgui_range_adjuster_tableau_sptr.h
     bgui_graph_tableau.cxx            bgui_graph_tableau.h           bgui_graph_tableau_sptr.h
     bgui_image_utils.cxx              bgui_image_utils.h
 )
IF(HAS_BMRF)
 SET(bgui_sources ${bgui_sources}
   bgui_bmrf_soview2D.cxx            bgui_bmrf_soview2D.h
 )
ENDIF(HAS_BMRF)

 AUX_SOURCE_DIRECTORY(Templates bgui_sources)
 ADD_LIBRARY(bgui ${bgui_sources})
 INSTALL_TARGETS(/lib bgui)
 INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/brl/bbas/bgui ${bgui_sources})

 TARGET_LINK_LIBRARIES(bgui bsta vdgl vtol vsol vgui vgl_algo vgl vil_algo vil vil1 vnl vul vbl vcl)
 IF(HAS_BMRF)
  TARGET_LINK_LIBRARIES(bgui bmrf)
 ENDIF(HAS_BMRF)

 IF(BUILD_EXAMPLES)
   SUBDIRS(examples)
 ENDIF(BUILD_EXAMPLES)

 IF(BUILD_TESTING)
   SUBDIRS(tests)
 ENDIF(BUILD_TESTING)

ENDIF(HAS_VGUI)
