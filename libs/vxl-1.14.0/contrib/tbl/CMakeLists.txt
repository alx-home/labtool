PROJECT( tbl )

doxygen_add_book(contrib/tbl "The Image Processing Library")

doxygen_add_package(contrib/tbl "Image Processing Libraries")

SET( TBL_INCLUDE_DIR ${tbl_SOURCE_DIR} CACHE STATIC "TB package include files" )
SET( TBL_INSTALL_INCLUDE_DIR
  ${CMAKE_INSTALL_PREFIX}/include/vxl/contrib/tbl
  CACHE INTERNAL "TB package include files"
)

INCLUDE_DIRECTORIES(${VXLCORE_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${TBL_INCLUDE_DIR})

SUBDIRS(vipl vepl vepl2)
