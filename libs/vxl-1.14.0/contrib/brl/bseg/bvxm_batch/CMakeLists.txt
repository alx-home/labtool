# contrib/brl/bseg/bvxm_batch/CMakeLists.txt
INCLUDE( ${VXL_CMAKE_DIR}/NewCMake/FindPython.cmake )
IF( PYTHON_FOUND )
  INCLUDE( ${BRL_MODULE_PATH}/FindEXPAT.cmake )
  IF( EXPAT_FOUND )
    INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_PATH} )
    INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR} )
    INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bpro )
    INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bpro/core )

    INCLUDE_DIRECTORIES( ${VXLCORE_INCLUDE_DIR} )
    INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR}/mrc )
    INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR}/mrc/vpgl )
    INCLUDE_DIRECTORIES( ${MUL_INCLUDE_DIR} )
    INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bseg/bvxm )
    INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bseg/brec )

     SET(bvxm_batch_sources
       reg_bvxm.h   reg_bvxm.cxx
     )

    ADD_LIBRARY(bvxm_batch MODULE ${bvxm_batch_sources})

    #library has to have different name depending on debug or release version.
    IF(WIN32)
      SET_TARGET_PROPERTIES(bvxm_batch PROPERTIES OUTPUT_NAME bvxm_batch DEBUG_POSTFIX _d SUFFIX .pyd)
    ENDIF(WIN32)
    SET_TARGET_PROPERTIES(bvxm_batch PROPERTIES PREFIX "")


    TARGET_LINK_LIBRARIES(bvxm_batch bprb brdb bpro_batch vbl bvxm bvxm_pro bvxm_io bvxm_grid_io bvxm_grid_pro vpgl_io vpgl_pro vil_io vil_pro sdet_pro)
  
    IF (PYTHON_DEBUG_LIBRARIES)
      TARGET_LINK_LIBRARIES( bvxm_batch debug ${PYTHON_DEBUG_LIBRARY})
    ENDIF(PYTHON_DEBUG_LIBRARIES )

    IF(PYTHON_LIBRARIES)
      TARGET_LINK_LIBRARIES( bvxm_batch optimized ${PYTHON_LIBRARY})
    ENDIF(PYTHON_LIBRARIES)
  ENDIF( EXPAT_FOUND ) 
ENDIF( PYTHON_FOUND )

INCLUDE( ${MODULE_PATH}/NewCMake/FindDirectShow.cmake )
IF(DIRECTSHOW_FOUND)
  ADD_DEFINITIONS(-DHAS_DIRECTSHOW)
ENDIF(DIRECTSHOW_FOUND)
