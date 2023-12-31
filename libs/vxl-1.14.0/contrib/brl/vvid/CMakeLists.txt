# brl/vvid/CMakeLists.txt

doxygen_add_library(contrib/brl/vvid
  DEPENDS contrib/brl/bbas/bgui contrib/brl/bseg/strk
  PACKAGE contrib/brl
  )

INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR})

# determines if vgui is built and opengl is available
INCLUDE( ${MODULE_PATH}/UseVGUI.cmake )

IF(HAS_VGUI)
 # sources that don't depend on the camera being present
 SET(vvid_sources
     vvid_frame_trail.cxx          vvid_frame_trail.h
 )
 IF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
  # source files depending on vidl1 or vidl_vil1
  SET(vvid_sources ${vvid_sources}
      vvid_file_manager.cxx         vvid_file_manager.h
      vvid_vil_file_manager.cxx     vvid_vil_file_manager.h
      vvid_command_line_player.cxx  vvid_command_line_player.h
  )
 ENDIF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)

 # find the path to the cmu camera libraries and includes
 INCLUDE( ${vxl_SOURCE_DIR}/contrib/brl/bmods/find_cmu_camera.cmake )

 # sources that do depend on the camera being present

 IF(HAS_CMU1394CAMERA)
  ADD_DEFINITIONS(-DHAS_CMU1394CAMERA)
  SET(cmu_camera_sources
      cmu_1394_camera_params.cxx   cmu_1394_camera_params.h
      cmu_1394_camera.cxx          cmu_1394_camera.h
      vvid_live_video_tableau.cxx  vvid_live_video_tableau.h
                                   vvid_live_video_tableau_sptr.h
      vvid_live_video_manager.cxx  vvid_live_video_manager.h
      vvid_live_stereo_manager.cxx vvid_live_stereo_manager.h
  )
 ENDIF(HAS_CMU1394CAMERA)

 # check if we have the camera libraries and assemble accordingly
 IF(HAS_CMU1394CAMERA)
  ADD_LIBRARY(vvid ${vvid_sources} ${cmu_camera_sources})  
 ELSE(HAS_CMU1394CAMERA)
  ADD_LIBRARY(vvid ${vvid_sources})
 ENDIF(HAS_CMU1394CAMERA)

 INSTALL_TARGETS(/lib vvid)
 INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/brl/vvid ${vvid_sources})

 TARGET_LINK_LIBRARIES(vvid vpro strk sdet btol bsol vtol vsol brip bgui vgui vul vil vil1)
 IF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
   TARGET_LINK_LIBRARIES(vvid vidl1 vidl_vil1)
 ENDIF (BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)

 # the main executables
 SUBDIRS(bin)

ENDIF(HAS_VGUI)
