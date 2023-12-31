# contrib/brl/bseg/boxm/CMakeLists.txt
INCLUDE( ${BRL_MODULE_PATH}/FindEXPAT.cmake )
IF(EXPAT_FOUND)

INCLUDE_DIRECTORIES( ${EXPAT_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR}/mrc )
INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR}/b3p/expatpp )

SET(boxm_sources
    boxm_block.txx                         boxm_block.h
    boxm_scene_base.cxx                    boxm_scene_base.h
    boxm_scene.txx                         boxm_scene.h
    boxm_scene_parser.cxx                  boxm_scene_parser.h
    boxm_sample.txx                        boxm_sample.h
    boxm_sample_multi_bin.txx              boxm_sample_multi_bin.h

    boxm_apm_traits.cxx                    boxm_apm_traits.h
    boxm_mog_grey_processor.cxx            boxm_mog_grey_processor.h
    boxm_simple_grey_processor.cxx         boxm_simple_grey_processor.h
    boxm_block_vis_graph_node.h
    boxm_block_vis_graph_iterator.txx      boxm_block_vis_graph_iterator.h
    boxm_cell_vis_graph_iterator.txx       boxm_cell_vis_graph_iterator.h
    boxm_utils.cxx                         boxm_utils.h
    boxm_render_image.h                    boxm_render_image_triangle.h
    boxm_depth_image_triangle.h
    boxm_update_triangle.h
    boxm_refine.h
    boxm_save_block_raw.h
    boxm_save_scene_raw.h
    boxm_quad_scan_iterator.h              boxm_quad_scan_iterator.cxx
    boxm_compute_volume_visibility.h
    boxm_triangle_interpolation_iterator.h  boxm_triangle_interpolation_iterator.txx
    boxm_triangle_scan_iterator.h          boxm_triangle_scan_iterator.cxx
    boxm_raytrace_operations.h             boxm_raytrace_operations.cxx

    boxm_rational_camera_utils.h           boxm_rational_camera_utils.cxx
    boxm_upload_mesh.h
    boxm_fill_in_mesh.h
    boxm_vis_implicit_sample.h
    boxm_update_sample.h
    boxm_mob_grey_processor.cxx            boxm_mob_grey_processor.h
    boxm_cell_data_traits.h                boxm_cell_data_traits.cxx
    boxm_edge_sample.h                     boxm_edge_sample.txx
    boxm_compute_scene_statistics.h
    boxm_edge_tangent_sample.txx           boxm_edge_tangent_sample.h
    boxm_plane_obs.txx                     boxm_plane_obs.h
    boxm_inf_line_sample.txx               boxm_inf_line_sample.h
    boxm_init_scene.h
    boxm_sigma_normalizer.cxx              boxm_sigma_normalizer.h
    boxm_line_samples.txx                  boxm_line_samples.h
)

AUX_SOURCE_DIRECTORY(Templates boxm_sources)

ADD_LIBRARY(boxm  ${boxm_sources})

TARGET_LINK_LIBRARIES(boxm boct vgl_io vgl_xio vpgl vpgl_algo vsol bgeo bsta bsta_algo imesh expatpp vgl_algo vnl_algo vnl vgl vul vil vbl vsl vpl vcl)

#processes
SUBDIRS(pro)

#io
SUBDIRS(io)

#tests
SUBDIRS(tests)

#opt
SUBDIRS(opt)

#basic algorithms involving scenes
SUBDIRS(algo)

ENDIF(EXPAT_FOUND)
