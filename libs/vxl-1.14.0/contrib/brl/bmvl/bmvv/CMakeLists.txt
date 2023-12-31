# view library for multi-view gui
# brl/bmvl/bmvv/CMakeLists.txt

doxygen_add_library(contrib/brl/bmvl/bmvv
  DEPENDS
    contrib/brl/bmvl/brct
    contrib/brl/bbas/bgui
    contrib/brl/bbas/bxml
  PACKAGE contrib/brl
  )

INCLUDE_DIRECTORIES( ${OXL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bmvl )
INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR}/mrc )
INCLUDE_DIRECTORIES( ${RPL_INCLUDE_DIR} )

# determines if vgui is built and opengl is available
INCLUDE( ${MODULE_PATH}/UseVGUI.cmake )

IF(HAS_VGUI)
IF(BUILD_RPL) # bmvv_f_manager.cxx needs rpl/rrel

 # sources that depend on xerces and vgui  being present
 SET(bmvv_sources
    dll.h

    #bmvv_multiview_manager.cxx     bmvv_multiview_manager.h
    #bmvv_tomography_manager.cxx    bmvv_tomography_manager.h  # used btom library
     bmvv_recon_manager.cxx         bmvv_recon_manager.h
     bmvv_cal_manager.cxx           bmvv_cal_manager.h
    #bmvv_menus.cxx                 bmvv_menus.h
    #bmvv_tomg_menus.cxx            bmvv_tomg_menus.h
     bmvv_recon_menus.cxx           bmvv_recon_menus.h
     bmvv_cal_menus.cxx             bmvv_cal_menus.h
     bmvv_f_manager.cxx             bmvv_f_manager.h
     bmvv_f_menus.cxx               bmvv_f_menus.h
    )

 ADD_LIBRARY(bmvv ${bmvv_sources})
 INSTALL_TARGETS(/lib bmvv)
 INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/brl/bmvl/bmvv ${bmvv_sources})

 TARGET_LINK_LIBRARIES(bmvv brct sdet brip bdgl mvl vpgl vpgl_algo vtol vdgl bgui vgui vsol vgl_algo vgl vnl vil vil1 vul)
 #TARGET_LINK_LIBRARIES(bmvv btom) # when compiling bmvv_tomography_manager.cxx

 # the main executable
 SUBDIRS(mvbin)

ENDIF(BUILD_RPL)
ENDIF(HAS_VGUI)
