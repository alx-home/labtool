# core/vil/CMakeLists.txt

doxygen_add_library(core/vil
  DEPENDS core/vnl core/vsl
  PACKAGE core
  DESCRIPTION "Core image library"
  )

# avoid undefined macro in subsequent SETs:
SET( vil_sources vil_config.h.in )

INCLUDE(${MODULE_PATH}/FindPNG.cmake)
IF(PNG_FOUND)
  INCLUDE_DIRECTORIES( ${PNG_INCLUDE_DIR})
  ADD_DEFINITIONS( ${PNG_DEFINITIONS} )
  SET( HAS_PNG 1 )
  SET( vil_sources ${vil_sources}
    file_formats/vil_png.cxx file_formats/vil_png.h
  )
ELSE(PNG_FOUND)
  SET( HAS_PNG 0 )
ENDIF(PNG_FOUND)

INCLUDE(${MODULE_PATH}/FindJPEG.cmake)
IF(JPEG_FOUND)
  INCLUDE_DIRECTORIES( ${JPEG_INCLUDE_DIR} )
  SET( HAS_JPEG 1 )
  SET( vil_sources ${vil_sources}
    file_formats/vil_jpeglib.h
    file_formats/vil_jpeg.cxx                 file_formats/vil_jpeg.h
    file_formats/vil_jpeg_source_mgr.cxx      file_formats/vil_jpeg_source_mgr.h
    file_formats/vil_jpeg_decompressor.cxx    file_formats/vil_jpeg_decompressor.h
    file_formats/vil_jpeg_destination_mgr.cxx file_formats/vil_jpeg_destination_mgr.h
    file_formats/vil_jpeg_compressor.cxx      file_formats/vil_jpeg_compressor.h
  )
ELSE(JPEG_FOUND)
  SET( HAS_JPEG 0 )
ENDIF(JPEG_FOUND)

################################
# JPEG 2000
################################
INCLUDE( ${MODULE_PATH}/NewCMake/FindECW.cmake )
IF(ECW_FOUND)
  SET( vil_sources ${vil_sources}
    file_formats/vil_j2k_image.h           file_formats/vil_j2k_image.cxx
    file_formats/NCSJPCVilIOStream.h       file_formats/NCSJPCVilIOStream.cxx 
    file_formats/vil_j2k_nitf2_pyramid_image_resource.h
    file_formats/vil_j2k_nitf2_pyramid_image_resource.cxx
    file_formats/vil_j2k_pyramid_image_resource.h
    file_formats/vil_j2k_pyramid_image_resource.cxx)
  INCLUDE_DIRECTORIES(${ECW_INCLUDE_DIR})
  SET( HAS_J2K 1 )
ELSE(ECW_FOUND)
  SET( HAS_J2K 0 )
ENDIF(ECW_FOUND)

SET( HAS_TIFF 0 )
SET( HAS_GEOTIFF 0 )
INCLUDE(${MODULE_PATH}/FindTIFF.cmake)
IF(TIFF_FOUND)
  INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIR}) 
  SET( HAS_TIFF 1 )
  SET( vil_sources ${vil_sources}
    file_formats/vil_tiff.cxx file_formats/vil_tiff.h
    file_formats/vil_tiff_header.cxx file_formats/vil_tiff_header.h
  ) 

  INCLUDE( ${MODULE_PATH}/FindGEOTIFF.cmake)
  IF(GEOTIFF_FOUND)
    #ADD_DEFINITIONS( -DHAS_GEOTIFF )
    SET (HAS_GEOTIFF 1 )
    INCLUDE_DIRECTORIES(${GEOTIFF_INCLUDE_DIR}) 
    SET( vil_sources ${vil_sources}
      file_formats/vil_geotiff_header.cxx file_formats/vil_geotiff_header.h
    )
  ENDIF(GEOTIFF_FOUND)
ENDIF(TIFF_FOUND)

INCLUDE(${MODULE_PATH}/FindDCMTK.cmake)
IF(DCMTK_FOUND)
  INCLUDE_DIRECTORIES(${DCMTK_INCLUDE_DIR})
  SET( HAS_DCMTK 1 )
  SET( vil_sources ${vil_sources}
    file_formats/vil_dicom.cxx        file_formats/vil_dicom.h
    file_formats/vil_dicom_stream.cxx file_formats/vil_dicom_stream.h
    file_formats/vil_dicom_header.cxx file_formats/vil_dicom_header.h
  )
ELSE(DCMTK_FOUND)
  SET( HAS_DCMTK 0 )
ENDIF(DCMTK_FOUND)


OPTION(VIL_CONFIG_ENABLE_SSE2_ROUNDING
  "Enable Streaming SIMD Extensions 2 implementation of rounding (hardware dependant)."
  ${VXL_HAS_SSE2_HARDWARE_SUPPORT} )
IF( VIL_CONFIG_ENABLE_SSE2_ROUNDING )
  IF( NOT VXL_HAS_SSE2_HARDWARE_SUPPORT )
    IF( VXL_SSE2_HARDWARE_SUPPORT_POSSIBLE )
      MESSAGE( ${VXL_SSE2_HARDWARE_SUPPORT_POSSIBLE_HELP} )
    ENDIF( VXL_SSE2_HARDWARE_SUPPORT_POSSIBLE )
    MESSAGE( SEND_ERROR "Cannot have VIL_CONFIG_ENABLE_SSE2_ROUNDING because"
                        " there is no SSE2 hardware or no compiler support enabled" )
    SET(VIL_CONFIG_ENABLE_SSE2_ROUNDING 0)
  ENDIF( NOT VXL_HAS_SSE2_HARDWARE_SUPPORT )
ENDIF( VIL_CONFIG_ENABLE_SSE2_ROUNDING )


IF(VIL_CONFIG_ENABLE_SSE2_ROUNDING)
  SET(VIL_CONFIG_ENABLE_SSE2_ROUNDING 1)
ELSE(VIL_CONFIG_ENABLE_SSE2_ROUNDING)
  SET(VIL_CONFIG_ENABLE_SSE2_ROUNDING 0)
ENDIF(VIL_CONFIG_ENABLE_SSE2_ROUNDING)


# Store the external library configurations in to the config file
CONFIGURE_FILE( ${vxl_SOURCE_DIR}/core/vil/vil_config.h.in
                ${vxl_BINARY_DIR}/core/vil/vil_config.h @ONLY IMMEDIATE )

SET( vil_sources ${vil_sources}

  # basic things
  vil_memory_chunk.cxx                  vil_memory_chunk.h
  vil_image_view_base.h
  vil_chord.h
  vil_image_view.h                      vil_image_view.txx
  vil_image_resource.cxx                vil_image_resource.h
                                        vil_image_resource_sptr.h
  vil_blocked_image_resource.cxx        vil_blocked_image_resource.h
                                        vil_blocked_image_resource_sptr.h
  vil_blocked_image_facade.cxx          vil_blocked_image_facade.h
  vil_file_format.cxx                   vil_file_format.h
  vil_memory_image.cxx                  vil_memory_image.h
  vil_block_cache.cxx                   vil_block_cache.h
  vil_cached_image_resource.cxx         vil_cached_image_resource.h
  vil_pyramid_image_resource.cxx        vil_pyramid_image_resource.h
                                        vil_pyramid_image_resource_sptr.h
  vil_image_list.cxx                    vil_image_list.h
  # file format readers/writers (see above for conditional ones)


  file_formats/vil_pnm.cxx              file_formats/vil_pnm.h

  file_formats/vil_bmp_file_header.cxx  file_formats/vil_bmp_file_header.h
  file_formats/vil_bmp_core_header.cxx  file_formats/vil_bmp_core_header.h
  file_formats/vil_bmp_info_header.cxx  file_formats/vil_bmp_info_header.h
  file_formats/vil_bmp.cxx              file_formats/vil_bmp.h

  file_formats/vil_ras.cxx              file_formats/vil_ras.h

  file_formats/vil_iris.cxx             file_formats/vil_iris.h

  file_formats/vil_mit.cxx              file_formats/vil_mit.h


  file_formats/vil_viff.cxx             file_formats/vil_viff.h
  file_formats/vil_viffheader.cxx       file_formats/vil_viffheader.h

  ################################
  # NITF 2.0 and 2.1 reading code
  ################################
  # The actual vil_image_resource subclass
  file_formats/vil_nitf2_image.h                    file_formats/vil_nitf2_image.cxx

  # For reading the NITF file headers as well as the image headers
  file_formats/vil_nitf2_header.h                   file_formats/vil_nitf2_header.cxx
  file_formats/vil_nitf2_image_subheader.h          file_formats/vil_nitf2_image_subheader.cxx
  file_formats/vil_nitf2_des.h                      file_formats/vil_nitf2_des.cxx

  # Stuff shared by all NITF2 classes
  file_formats/vil_nitf2.h                          file_formats/vil_nitf2.cxx

  # Generic framework for reading NITF tagged record extensions (TREs)
  file_formats/vil_nitf2_array_field.h              file_formats/vil_nitf2_array_field.cxx
  file_formats/vil_nitf2_classification.h           file_formats/vil_nitf2_classification.cxx
  file_formats/vil_nitf2_compound_field_value.h     file_formats/vil_nitf2_compound_field_value.cxx
  file_formats/vil_nitf2_data_mask_table.h          file_formats/vil_nitf2_data_mask_table.cxx
  file_formats/vil_nitf2_field.h                    file_formats/vil_nitf2_field.cxx
  file_formats/vil_nitf2_field_definition.h         file_formats/vil_nitf2_field_definition.cxx
  file_formats/vil_nitf2_field_formatter.h          file_formats/vil_nitf2_field_formatter.cxx
  file_formats/vil_nitf2_field_functor.h            file_formats/vil_nitf2_field_functor.cxx
  file_formats/vil_nitf2_field_sequence.h           file_formats/vil_nitf2_field_sequence.cxx
  file_formats/vil_nitf2_index_vector.h
  file_formats/vil_nitf2_scalar_field.h             file_formats/vil_nitf2_scalar_field.cxx
  file_formats/vil_nitf2_tagged_record.h            file_formats/vil_nitf2_tagged_record.cxx
  file_formats/vil_nitf2_tagged_record_definition.h file_formats/vil_nitf2_tagged_record_definition.cxx
  file_formats/vil_nitf2_typed_array_field.h
  file_formats/vil_nitf2_typed_scalar_field.h
  file_formats/vil_nitf2_typed_field_formatter.h    file_formats/vil_nitf2_typed_field_formatter.cxx

  file_formats/vil_pyramid_image_list.h             file_formats/vil_pyramid_image_list.cxx
  # image operations
  vil_crop.cxx                          vil_crop.h
  vil_clamp.cxx                         vil_clamp.h
  vil_transpose.cxx                     vil_transpose.h
  vil_flip.cxx                          vil_flip.h
  vil_plane.cxx                         vil_plane.h
  vil_math.cxx                          vil_math.h
  vil_view_as.h
  vil_convert.h
  vil_fill.h
  vil_transform.h
  vil_decimate.cxx                      vil_decimate.h
  vil_load.cxx                          vil_load.h
  vil_save.cxx                          vil_save.h
  vil_copy.txx       vil_copy.cxx       vil_copy.h
  vil_new.cxx                           vil_new.h
  vil_print.cxx                         vil_print.h
  vil_warp.h
  vil_flatten.h
  
  # Bilinear Sampling Operations
  vil_bilin_interp.h
  vil_sample_profile_bilin.txx          vil_sample_profile_bilin.h
  vil_sample_grid_bilin.txx             vil_sample_grid_bilin.h
  vil_resample_bilin.txx                vil_resample_bilin.h
  vil_rotate.txx                        vil_rotate.h

  # Bicubic Sampling Operations
  vil_bicub_interp.txx                  vil_bicub_interp.h
  vil_sample_profile_bicub.txx          vil_sample_profile_bicub.h
  vil_sample_grid_bicub.txx             vil_sample_grid_bicub.h
  vil_resample_bicub.txx                vil_resample_bicub.h

  # Nearest Neighbour Sampling Operations
  vil_nearest_interp.h
  vil_resample_nearest.txx              vil_resample_nearest.h

  # Stuff
  vil_border.h
  vil_smart_ptr.txx                     vil_smart_ptr.h
  vil_property.h
  vil_pixel_format.cxx                  vil_pixel_format.h
  vil_exception.h
  vil_rgb.txx                           vil_rgb.h
  vil_rgba.txx                          vil_rgba.h
  vil_color_table.h
  vil_fwd.h
  vil_round.h
  
  # Streams
  vil_stream.cxx                        vil_stream.h
  vil_stream_fstream.cxx                vil_stream_fstream.h
  vil_stream_core.cxx                   vil_stream_core.h
  vil_stream_section.cxx                vil_stream_section.h
  vil_open.cxx                          vil_open.h
  vil_stream_read.cxx                   vil_stream_read.h
  vil_stream_write.cxx                  vil_stream_write.h

  # Plugin for image loading
  vil_image_resource_plugin.cxx         vil_image_resource_plugin.h
)

IF (WIN32 AND VXL_USE_LFS AND NOT CMAKE_CL_64)
#This is a hack since win32 doesn't have transparent Large File Support.
  ADD_DEFINITIONS( -DVIL_USE_FSTREAM64 )
  SET( vil_sources ${vil_sources}
    vil_stream_fstream64.cxx        vil_stream_fstream64.h )
ENDIF (WIN32 AND VXL_USE_LFS AND NOT CMAKE_CL_64)

AUX_SOURCE_DIRECTORY(Templates vil_sources)

# Some versions of Solaris (at least 5.8) has a brain-dead mechanism
# for implementing DNS services, where the user of a library that uses
# gethostbyname should link to -lnsl *before* linking to the
# library. This creates a kind of "pre-dependency" that the CMake
# dependency analysis is not equipped to handle. We cope by isolating
# the offending code into its own library vil_network (under Solaris
# only, of course). We can then control the dependencies of vil to
# link nsl before this vil_network.
#
# This workaround also occurs in vul
#
SET( vil_network_sources
  # load image from URL
  vil_stream_url.cxx vil_stream_url.h
)

IF(NOT SOLARIS)
  ADD_LIBRARY(vil ${vil_sources} ${vil_network_sources})
  INSTALL_TARGETS(/lib vil)
ELSE(NOT SOLARIS)
  ADD_LIBRARY(vil ${vil_sources})
  ADD_LIBRARY(vil_network ${vil_network_sources})
  INSTALL_TARGETS(/lib vil vil_network)
ENDIF(NOT SOLARIS)

IF(JPEG_FOUND)
  TARGET_LINK_LIBRARIES( vil ${JPEG_LIBRARIES} )
ENDIF(JPEG_FOUND)
IF(TIFF_FOUND)
  TARGET_LINK_LIBRARIES( vil ${TIFF_LIBRARIES}) 
ENDIF(TIFF_FOUND)
IF(HAS_GEOTIFF)
  TARGET_LINK_LIBRARIES( vil ${GEOTIFF_LIBRARIES}) 
ENDIF(HAS_GEOTIFF)
IF(PNG_FOUND)
  TARGET_LINK_LIBRARIES( vil ${PNG_LIBRARIES} )
ENDIF(PNG_FOUND)
IF(DCMTK_FOUND)
  TARGET_LINK_LIBRARIES( vil ${DCMTK_LIBRARIES} )
ENDIF(DCMTK_FOUND)

TARGET_LINK_LIBRARIES( vil vcl )

IF (NOT UNIX)
  TARGET_LINK_LIBRARIES( vil ws2_32 )
ENDIF (NOT UNIX)

IF (SOLARIS)
  TARGET_LINK_LIBRARIES( vil nsl vil_network socket )
ENDIF (SOLARIS)

INSTALL_NOBASE_HEADER_FILES(/include/vxl/core/vil
  ${vil_sources}
  ${vil_network_sources}
)

IF(ECW_FOUND)
  TARGET_LINK_LIBRARIES( vil ${ECW_LIBRARIES} )
ENDIF(ECW_FOUND)

IF( BUILD_EXAMPLES )
  SUBDIRS( examples )
ENDIF( BUILD_EXAMPLES )
IF( BUILD_TESTING )
  SUBDIRS(tests)
ENDIF( BUILD_TESTING )
