# vxl/vbl/CMakeLists.txt

doxygen_add_library(core/vbl
  DEPENDS core/vsl
  PACKAGE core
  DESCRIPTION "Basic Template Library"
  )

SET( vbl_sources
  vbl_fwd.h

  vbl_bool_ostream.cxx        vbl_bool_ostream.h
  vbl_smart_ptr.txx           vbl_smart_ptr.h
                              vbl_shared_pointer.h
                              vbl_scoped_ptr.h
                              vbl_checked_delete.h
  vbl_sort.txx                vbl_sort.h           vbl_sort.cxx
  vbl_qsort.cxx               vbl_qsort.h

  vbl_array_1d.txx            vbl_array_1d.h
  vbl_array_2d.txx            vbl_array_2d.h
  vbl_array_3d.txx            vbl_array_3d.h
  vbl_bit_array_2d.cxx        vbl_bit_array_2d.h
  vbl_bit_array_3d.cxx        vbl_bit_array_3d.h
  vbl_sparse_array_base.txx   vbl_sparse_array_base.h
  vbl_sparse_array_1d.txx     vbl_sparse_array_1d.h
  vbl_sparse_array_2d.txx     vbl_sparse_array_2d.h
  vbl_sparse_array_3d.txx     vbl_sparse_array_3d.h
  vbl_big_sparse_array_3d.txx vbl_big_sparse_array_3d.h

                              vbl_ref_count.h
  vbl_bounding_box.txx        vbl_bounding_box.h

  vbl_triple.txx              vbl_triple.h
  vbl_quadruple.txx           vbl_quadruple.h
)

AUX_SOURCE_DIRECTORY(Templates vbl_sources)

ADD_LIBRARY(vbl ${vbl_sources})
TARGET_LINK_LIBRARIES( vbl vcl )

INSTALL_TARGETS(/lib vbl)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/core/vbl ${vbl_sources})

IF( BUILD_EXAMPLES )
  SUBDIRS( examples )
ENDIF( BUILD_EXAMPLES )

IF( BUILD_TESTING )
  SUBDIRS(tests)
ENDIF( BUILD_TESTING )
