FIND_PACKAGE(VXL)

IF(VXL_FOUND)
  INCLUDE(${VXL_CMAKE_DIR}/UseVXL.cmake)
ENDIF(VXL_FOUND)

INCLUDE_DIRECTORIES( ${VXL_VNL_INCLUDE_DIR} )

get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include("${SELF_DIR}/gmmreg_apiTargets.cmake")

get_filename_component(gmmreg_api_INCLUDE_DIRS "${SELF_DIR}/../../../include" ABSOLUTE)

set(gmmreg_api_LIBRARIES gmmreg_api)

include_directories("${gmmreg_api_INCLUDE_DIRS}")