# oxl/apps/glmovie/CMakeLists.txt

INCLUDE(${CMAKE_ROOT}/Modules/FindGLUT.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindOpenGL.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindMPEG2.cmake)

IF(BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
  ADD_EXECUTABLE( vobgetframe vobgetframe.cxx )
  TARGET_LINK_LIBRARIES( vobgetframe oxp vidl_vil1 vil1 vnl vul )

  IF(MPEG2_FOUND)
    TARGET_LINK_LIBRARIES( vobgetframe ${MPEG2_LIBRARIES} )
    ADD_DEFINITIONS(-DHAS_MPEG2)
  ENDIF(MPEG2_FOUND)

  IF(WIN32)
    TARGET_LINK_LIBRARIES( vobgetframe vfw32 )
  ENDIF(WIN32)

  IF(OPENGL_FOUND)
    INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIR} )

    IF(GLUT_FOUND)
      INCLUDE_DIRECTORIES( ${GLUT_INCLUDE_DIR} )
      ADD_EXECUTABLE( oxl_glmovie glmovie.cxx make_index.cxx )
      INSTALL_TARGETS( /bin oxl_glmovie )
      TARGET_LINK_LIBRARIES( oxl_glmovie oxp vidl_vil1 vil1 vnl vul ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} )
    ENDIF(GLUT_FOUND)

  ENDIF(OPENGL_FOUND)

ENDIF(BUILD_UNMAINTAINED_LIBRARIES OR BUILD_FOR_VXL_DASHBOARD)
