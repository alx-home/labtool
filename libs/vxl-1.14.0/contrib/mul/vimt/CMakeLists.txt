# mul/vimt/CMakeLists.txt

doxygen_add_library(contrib/mul/vimt
  DEPENDS core/vil core/vnl core/vgl
  PACKAGE contrib/mul
  DESCRIPTION "Polymorphic image + transform library"
  )

SET(vimt_sources
    vimt_image.cxx                                vimt_image.h
    vimt_transform_2d.cxx                         vimt_transform_2d.h
    vimt_transform_util_2d.cxx                    vimt_transform_util_2d.h
    vimt_image_2d.h                               vimt_image_2d.cxx
    vimt_image_2d_of.txx                          vimt_image_2d_of.h
    vimt_crop.h
    vimt_convert.h
    vimt_dog_pyramid_builder_2d.txx               vimt_dog_pyramid_builder_2d.h
    vimt_image_pyramid.cxx vimt_image_pyramid.txx vimt_image_pyramid.h
    vimt_image_pyramid_builder.cxx                vimt_image_pyramid_builder.h
    vimt_gaussian_pyramid_builder_2d.txx          vimt_gaussian_pyramid_builder_2d.h
    vimt_gaussian_pyramid_builder_2d_general.txx  vimt_gaussian_pyramid_builder_2d_general.h
    vimt_scale_pyramid_builder_2d.txx             vimt_scale_pyramid_builder_2d.h
    vimt_sample_profile_bilin.txx                 vimt_sample_profile_bilin.h
    vimt_sample_grid_bilin.txx                    vimt_sample_grid_bilin.h
    vimt_sample_grid_bicub.txx                    vimt_sample_grid_bicub.h
    vimt_bilin_interp.h
    vimt_reflect.h
    vimt_resample_bilin.h
    vimt_load.h                                   vimt_load.cxx
    vimt_save.h                                   vimt_save.cxx
    vimt_vil_v2i.h                                vimt_vil_v2i.cxx
    vimt_add_all_binary_loaders.h                 vimt_add_all_binary_loaders.cxx
    vimt_fwd.h
)
AUX_SOURCE_DIRECTORY(Templates vimt_sources)

ADD_LIBRARY(vimt ${vimt_sources})
INSTALL_TARGETS(/lib vimt)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/mul/vimt ${vimt_sources})
TARGET_LINK_LIBRARIES(vimt mbl vil_algo vgl vnl vil )

SUBDIRS(algo)

IF(BUILD_EXAMPLES)
  SUBDIRS(examples)
ENDIF(BUILD_EXAMPLES)

IF (BUILD_TESTING)
  SUBDIRS(tests)
ENDIF (BUILD_TESTING)
