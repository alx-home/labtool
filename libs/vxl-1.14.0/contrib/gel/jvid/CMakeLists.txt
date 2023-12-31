# gel/jvid/CMakeLists.txt

doxygen_add_library(contrib/gel/jvid
  DEPENDS core/vgui core/vidl_vil1
  PACKAGE contrib/gel
  )

INCLUDE( ${MODULE_PATH}/UseVGUI.cmake )

IF(HAS_VGUI)

  INCLUDE(${MODULE_PATH}/FindMPEG2.cmake)
  IF(MPEG2_FOUND)
    ADD_DEFINITIONS(-DHAS_MPEG2)
    INCLUDE_DIRECTORIES(${MPEG2_INCLUDE_DIR})
  ENDIF(MPEG2_FOUND)

  SET( jvid_sources
    jvx_manager.cxx jvx_manager.h
  )

  ADD_LIBRARY(jvid ${jvid_sources})
  INSTALL_TARGETS(/lib jvid)
  INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/gel/jvid ${jvid_sources})
  TARGET_LINK_LIBRARIES( jvid vgui vidl_vil1 vul vil1 )
  IF(MPEG2_FOUND)
    TARGET_LINK_LIBRARIES( jvid ${MPEG2_LIBRARIES} )
  ENDIF(MPEG2_FOUND)

  SUBDIRS(bin)

ENDIF(HAS_VGUI)
