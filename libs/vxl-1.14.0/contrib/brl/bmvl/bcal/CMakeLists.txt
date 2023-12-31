# multi-view camera library
# brl/bmvl/bcal/CMakeLists.txt

doxygen_add_library(contrib/brl/bmvl/bcal
  DEPENDS contrib/gel/vsol core/vcsl
  PACKAGE contrib/brl
  )

INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR}/bmvl)

SET(bcal_sources
    bcal_camera.h                   bcal_camera.cxx
    bcal_camera_node.h              bcal_camera_node.cxx
    bcal_euclidean_transformation.h bcal_euclidean_transformation.cxx
    bcal_camera_graph.h
    bcal_calibrate_object.h
    bcal_calibrate_plane.h          bcal_calibrate_plane.cxx
    bcal_zhang_camera_node.h        bcal_zhang_camera_node.cxx
    bcal_zhang_linear_calibrate.h   bcal_zhang_linear_calibrate.cxx
)

ADD_LIBRARY(bcal ${bcal_sources})
INSTALL_TARGETS(/lib bcal)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/brl/bmvl/bcal ${bcal_sources})
TARGET_LINK_LIBRARIES(bcal vgl_algo vnl_algo vnl vgl vcsl)

IF(BUILD_TESTING)
  SUBDIRS(tests)
ENDIF(BUILD_TESTING)
