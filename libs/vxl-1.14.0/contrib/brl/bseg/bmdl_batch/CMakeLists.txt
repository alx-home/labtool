# contrib/brl/bseg/bmdl_batch/CMakeLists.txt
INCLUDE( ${VXL_CMAKE_DIR}/NewCMake/FindPython.cmake )
IF( PYTHON_FOUND )
  INCLUDE( ${BRL_MODULE_PATH}/FindEXPAT.cmake )
  IF( EXPAT_FOUND )
    INCLUDE(${MODULE_PATH}/FindTIFF.cmake)
    IF(TIFF_FOUND)
      INCLUDE( ${MODULE_PATH}/FindGEOTIFF.cmake)
      IF(GEOTIFF_FOUND)
        INCLUDE( ${MODULE_PATH}/FindZLIB.cmake )
        IF(ZLIB_FOUND)
          INCLUDE_DIRECTORIES( ${ZLIB_INCLUDE_DIR} )
          INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/b3p )
        ENDIF(ZLIB_FOUND)
        INCLUDE_DIRECTORIES( ${PYTHON_INCLUDE_PATH} )
        INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR} )
        INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bpro )
        INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bpro/core )
        
        INCLUDE_DIRECTORIES( ${VXLCORE_INCLUDE_DIR} )
        INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR}/mrc )
        INCLUDE_DIRECTORIES( ${MUL_INCLUDE_DIR} )
        INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/bseg/bmdl )
      
        INCLUDE_DIRECTORIES( ${TIFF_INCLUDE_DIR} ) 
        INCLUDE_DIRECTORIES( ${GEOTIFF_INCLUDE_DIR} ) 
    
        SET(bmdl_batch_sources
          reg_bmdl.cxx          reg_bmdl.h
        )
     
        ADD_LIBRARY(bmdl_batch MODULE ${bmdl_batch_sources})

        IF(WIN32)
          #library has to have different name depending on debug or release version.
          SET_TARGET_PROPERTIES(bmdl_batch PROPERTIES OUTPUT_NAME bmdl_batch DEBUG_POSTFIX _d SUFFIX .pyd)
        ENDIF(WIN32)
        SET_TARGET_PROPERTIES(bmdl_batch PROPERTIES PREFIX "")

        TARGET_LINK_LIBRARIES(bmdl_batch bprb brdb bpro_batch bmdl_pro vbl vpgl_io vpgl_pro vil_io vil_pro) 
      
        IF (PYTHON_DEBUG_LIBRARIES)
          TARGET_LINK_LIBRARIES( bmdl_batch debug ${PYTHON_DEBUG_LIBRARY})
        ENDIF(PYTHON_DEBUG_LIBRARIES )

        IF(PYTHON_LIBRARIES)
          TARGET_LINK_LIBRARIES( bmdl_batch optimized ${PYTHON_LIBRARY})
        ENDIF(PYTHON_LIBRARIES)
    ENDIF(GEOTIFF_FOUND )
   ENDIF(TIFF_FOUND ) 
  ENDIF( EXPAT_FOUND ) 
ENDIF( PYTHON_FOUND )
