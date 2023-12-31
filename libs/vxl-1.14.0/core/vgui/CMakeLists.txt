# core/vgui/CMakeLists.txt

PROJECT(vgui)

doxygen_add_library(core/vgui
  DEPENDS core/vgl core/vpl core/vbl core/vul core/vnl core/vil core/vil1
  PACKAGE core-L2
  DESCRIPTION "Multi-platform user-interface using OpenGL"
  )

# Default the dashboard builds to "YES" so that
# we have some clients that try to compile vgui
OPTION( BUILD_VGUI "Build VGUI" ${YES_FOR_DASHBOARD} )

# Flag that determines if we were able to successfully build vgui.
# Initialize to NO. Change below if yes.
SET( VGUI_FOUND "NO" CACHE INTERNAL "Was vgui successfully built?" )

IF( BUILD_VGUI )

INCLUDE(${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

# Build here only if OpenGL is available:
IF (OPENGL_FOUND)
 IF (OPENGL_GLU_FOUND)

  # For (not) reporting an error below
  SET( CAN_BUILD_VGUI "YES" )

  # Apple can use OpenGL either with or without X11
  # Finding X11 can cause problems when the native
  # Apple OpenGL is to be used.
  IF(APPLE)
    OPTION(VGUI_USE_X11 "Use OpenGL for X11" NO)
    IF(VGUI_USE_X11)
      INCLUDE(${CMAKE_ROOT}/Modules/FindX11.cmake)
    ENDIF(VGUI_USE_X11)
  ELSE(APPLE)
    INCLUDE(${CMAKE_ROOT}/Modules/FindX11.cmake)
  ENDIF(APPLE)
  # Qv needed by vrml only
  INCLUDE(${MODULE_PATH}/FindQv.cmake)
  # glut optionally used by vgui_text and by the glut toolkit
  # implementation
  INCLUDE(${CMAKE_ROOT}/Modules/FindGLUT.cmake)

  # The following are for the optional toolkit
  # implementations
  INCLUDE(${CMAKE_ROOT}/Modules/FindQt.cmake)
  INCLUDE(${CMAKE_ROOT}/Modules/FindGTK.cmake)
  INCLUDE(${MODULE_PATH}/NewCMake/FindGTK2.cmake)
  IF(NOT MINGW)
    # MFC is not available in MinGW.
    # This should be fixed in FindMFC.cmake and then this IF can be removed
    INCLUDE(${CMAKE_ROOT}/Modules/FindMFC.cmake)
  ENDIF(NOT MINGW)

  #SET(WXWIDGETS_USE_LIBS base core gl)
  #FIND_PACKAGE(wxWidgets)
  #INCLUDE(${MODULE_PATH}/NewCMake/FindwxWidgets.cmake)
  FIND_PACKAGE(wxWidgets COMPONENTS base core gl)

  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
  IF( GLUT_FOUND )
    INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})
  ENDIF( GLUT_FOUND )

SET(vgui_sources
  vgui_fwd.h
  vgui_config.h.in

  # basic classes
  vgui.cxx                      vgui.h
  vgui_toolkit.cxx              vgui_toolkit.h
  vgui_tag.cxx                  vgui_tag.h
  vgui_window.cxx               vgui_window.h
  vgui_adaptor.cxx              vgui_adaptor.h
  vgui_tableau.cxx              vgui_tableau.h    vgui_tableau_sptr.h
  vgui_parent_child_link.cxx    vgui_parent_child_link.h
  vgui_key.cxx                  vgui_key.h
  vgui_button.cxx               vgui_button.h
  vgui_modifier.cxx             vgui_modifier.h
  vgui_event.cxx                vgui_event.h
  vgui_command.cxx              vgui_command.h    vgui_command_sptr.h
  vgui_menu.cxx                 vgui_menu.h
  vgui_popup_params.h
  vgui_message.h
  vgui_observer.cxx             vgui_observer.h
  vgui_observable.cxx           vgui_observable.h
  vgui_satellite_tableau.txx vgui_satellite_tableau.h
  vgui_font.cxx                 vgui_font.h       vgui_font_sptr.h
  vgui_font_bitmap.cxx          vgui_font_bitmap.h
  vgui_font_textured.cxx        vgui_font_textured.h

  # utility
  vgui_find.cxx                 vgui_find.h
  vgui_utils.cxx                vgui_utils.h
  vgui_macro.cxx                vgui_macro.h
  vgui_color.cxx                vgui_color.h
  vgui_projection_inspector.cxx vgui_projection_inspector.h
  vgui_matrix_state.cxx         vgui_matrix_state.h
  vgui_text_graph.cxx           vgui_text_graph.h
  vgui_camera.cxx               vgui_camera.h
  vgui_event_condition.cxx      vgui_event_condition.h

  # images
  internals/vgui_rasterpos.cxx  internals/vgui_rasterpos.h
  vgui_pixel.cxx                vgui_pixel.h
  vgui_section_render.cxx       vgui_section_render.h
  vgui_section_buffer.cxx       vgui_section_buffer.h
  vgui_range_map_params.h       vgui_range_map_params_sptr.h
  vgui_range_map_params.cxx
  vgui_range_map.txx            vgui_range_map.h
  vgui_texture_hacks.cxx        vgui_texture_hacks.h
  vgui_cache_wizard.cxx         vgui_cache_wizard.h
  vgui_image_renderer.cxx       vgui_image_renderer.h
  vgui_vil_image_renderer.cxx   vgui_vil_image_renderer.h
  vgui_image_tableau.cxx        vgui_image_tableau.h      vgui_image_tableau_sptr.h
  vgui_blender_tableau.cxx      vgui_blender_tableau.h    vgui_blender_tableau_sptr.h

  # tableau mixins and miscellaneous
  vgui_wrapper_tableau.cxx      vgui_wrapper_tableau.h    vgui_wrapper_tableau_sptr.h
  vgui_deck_tableau.cxx         vgui_deck_tableau.h       vgui_deck_tableau_sptr.h
  vgui_composite_tableau.cxx    vgui_composite_tableau.h  vgui_composite_tableau_sptr.h
  vgui_poly_tableau.cxx         vgui_poly_tableau.h       vgui_poly_tableau_sptr.h
  vgui_grid_tableau.cxx         vgui_grid_tableau.h       vgui_grid_tableau_sptr.h
  vgui_drag_mixin.cxx           vgui_drag_mixin.h
  vgui_active_tableau.cxx       vgui_active_tableau.h     vgui_active_tableau_sptr.h
                                vgui_drag_tableau.h       vgui_drag_tableau_sptr.h
  vgui_clear_tableau.cxx        vgui_clear_tableau.h      vgui_clear_tableau_sptr.h
  vgui_debug_tableau.cxx        vgui_debug_tableau.h      vgui_debug_tableau_sptr.h
  vgui_quit_tableau.cxx         vgui_quit_tableau.h       vgui_quit_tableau_sptr.h
  vgui_tview_launcher_tableau.cxx vgui_tview_launcher_tableau.h vgui_tview_launcher_tableau_sptr.h
  vgui_shell_tableau.cxx        vgui_shell_tableau.h      vgui_shell_tableau_sptr.h
  vgui_text_put.cxx             vgui_text_put.h
  vgui_text_tableau.cxx         vgui_text_tableau.h       vgui_text_tableau_sptr.h
  vgui_blackbox_tableau.cxx     vgui_blackbox_tableau.h   vgui_blackbox_tableau_sptr.h
  vgui_enhance_tableau.cxx      vgui_enhance_tableau.h    vgui_enhance_tableau_sptr.h
  vgui_tview_tableau.cxx        vgui_tview_tableau.h      vgui_tview_tableau_sptr.h
  vgui_function_tableau.cxx     vgui_function_tableau.h   vgui_function_tableau_sptr.h
  vgui_roi_tableau.cxx          vgui_roi_tableau.h        vgui_roi_tableau_sptr.h
  vgui_rubberband_tableau.cxx   vgui_rubberband_tableau.h vgui_rubberband_tableau_sptr.h
  vgui_loader_tableau.cxx       vgui_loader_tableau.h     vgui_loader_tableau_sptr.h
  vgui_color_text.cxx           vgui_color_text.h
  vgui_event_server.cxx         vgui_event_server.h
  vgui_error_dialog.cxx         vgui_error_dialog.h

  vgui_soview.cxx               vgui_soview.h
  vgui_soview2D.cxx             vgui_soview2D.h
  vgui_soview3D.cxx             vgui_soview3D.h
  vgui_style.cxx                vgui_style.h                vgui_style_sptr.h
  vgui_displaybase_tableau.cxx  vgui_displaybase_tableau.h  vgui_displaybase_tableau_sptr.h
  vgui_displaylist2D_tableau.cxx  vgui_displaylist2D_tableau.h vgui_displaylist2D_tableau_sptr.h
  vgui_displaylist3D_tableau.cxx  vgui_displaylist3D_tableau.h vgui_displaylist3D_tableau_sptr.h
  vgui_easy2D_tableau.cxx       vgui_easy2D_tableau.h       vgui_easy2D_tableau_sptr.h
  vgui_easy3D_tableau.cxx       vgui_easy3D_tableau.h       vgui_easy3D_tableau_sptr.h
  vgui_listmanager2D_tableau.cxx  vgui_listmanager2D_tableau.h  vgui_listmanager2D_tableau_sptr.h
  vgui_viewer2D_tableau.cxx vgui_viewer2D_tableau.h         vgui_viewer2D_tableau_sptr.h
  vgui_viewer3D_tableau.cxx vgui_viewer3D_tableau.h         vgui_viewer3D_tableau_sptr.h
  internals/trackball.c              internals/trackball.h

  vgui_slider_tableau.cxx       vgui_slider_tableau.h       vgui_slider_tableau_sptr.h

  # dialog classes
  vgui_dialog.cxx                    vgui_dialog.h
  vgui_dialog_extensions.cxx         vgui_dialog_extensions.h
  internals/vgui_dialog_impl.cxx     internals/vgui_dialog_impl.h
  internals/vgui_dialog_extensions_impl.cxx     internals/vgui_dialog_extensions_impl.h
  internals/vgui_dialog_field.h
  internals/vgui_simple_field.h      internals/vgui_simple_field.cxx
  internals/vgui_string_field.h
  internals/vgui_file_field.h

  # statusbar classes
  vgui_statusbuf.cxx            vgui_statusbuf.h
  vgui_statusbar.h

  # extra header files
  dll.h
  vgui_gl.h
  vgui_glu.h
  vgui_glx.h

  # internals
  internals/vgui_invert_homg4x4.cxx  internals/vgui_invert_homg4x4.h
  internals/vgui_back_project.cxx    internals/vgui_back_project.h
  internals/vgui_un_project.cxx      internals/vgui_un_project.h
  internals/vgui_adaptor_tableau.cxx internals/vgui_adaptor_tableau.h
  internals/vgui_parent_child_link_data.h
  internals/vgui_adaptor_mixin.h
  internals/vgui_overlay_helper.cxx  internals/vgui_overlay_helper.h
  internals/vgui_multiply_4x4.cxx    internals/vgui_multiply_4x4.h
  internals/vgui_transpose_4x4.cxx   internals/vgui_transpose_4x4.h
  internals/vgui_draw_line.cxx       internals/vgui_draw_line.h
  # Mesa-X11-mfc accelerated functions using Hermes
  internals/vgui_accelerate.cxx      internals/vgui_accelerate.h
  internals/vgui_accelerate_tag.cxx
  internals/vgui_gl_selection_macros.h
)

IF( GLUT_FOUND )
  SET(vgui_sources ${vgui_sources}
    vgui_glut.cxx                    vgui_glut.h
  )
ENDIF( GLUT_FOUND )

AUX_SOURCE_DIRECTORY(Templates vgui_sources)

IF (QV_FOUND)
  INCLUDE_DIRECTORIES(${QV_INCLUDE_DIR})
  SET(vgui_sources ${vgui_sources}
    vrml/vgui_vrml_draw_visitor.cxx  vrml/vgui_vrml_draw_visitor.h
    vrml/vgui_vrml_tableau.cxx       vrml/vgui_vrml_tableau.h
    vrml/vgui_vrml_texture_map.cxx   vrml/vgui_vrml_texture_map.h
  )
ENDIF (QV_FOUND)

IF (MFC_FOUND)
  #SET(vgui_sources ${vgui_sources}
  #  internals/vgui_accelerate_mfc.cxx internals/vgui_accelerate_mfc.h
  #)
ENDIF (MFC_FOUND)

IF (X11_FOUND)
  INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})
  SET(vgui_sources ${vgui_sources}
    internals/vgui_accelerate_x11.cxx internals/vgui_accelerate_x11.h
  )
ENDIF (X11_FOUND)

IF (MFC_FOUND)
  # add stuff to use MFC in this executable
  ADD_DEFINITIONS( "-D_AFXDLL" )
  SET(CMAKE_MFC_FLAG 2)
ENDIF (MFC_FOUND)


######################################################################
# TOOLKIT IMPLEMENTATIONS
######################################################################

##################################################
# glut
##################################################

# Build here only if GLUT is available:
IF (GLUT_FOUND)

  OPTION(VGUI_USE_GLUT "Should Glut support be compiled into vgui?" YES)

  IF(VGUI_USE_GLUT)

    INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})

    SET(vgui_glut_sources
      impl/glut/vgui_glut_adaptor.cxx    impl/glut/vgui_glut_adaptor.h
      impl/glut/vgui_glut_tag.cxx
      impl/glut/vgui_glut_popup_impl.cxx impl/glut/vgui_glut_popup_impl.h
      impl/glut/vgui_glut_window.cxx     impl/glut/vgui_glut_window.h
      impl/glut/vgui_glut_impl.cxx       impl/glut/vgui_glut_impl.h

      impl/glut/menu_hack.h
    )
    IF (X11_FOUND AND NOT APPLE)
      INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})
     # FreeGLUT does not support this menu hack
      IF(EXISTS ${GLUT_INCLUDE_DIR}/GL/freeglut.h)
        SET(vgui_glut_sources ${vgui_glut_sources}
          impl/glut/menu_hack_none.cxx
        )
      ELSE(EXISTS ${GLUT_INCLUDE_DIR}/GL/freeglut.h)
        SET(vgui_glut_sources ${vgui_glut_sources}
          impl/glut/menu_hack_X11.cxx
        )
      ENDIF(EXISTS ${GLUT_INCLUDE_DIR}/GL/freeglut.h)
    ELSE (X11_FOUND AND NOT APPLE)
      SET(vgui_glut_sources ${vgui_glut_sources}
        impl/glut/menu_hack_none.cxx
      )
    ENDIF (X11_FOUND AND NOT APPLE)

    SET( vgui_sources ${vgui_sources} ${vgui_glut_sources} )

  ENDIF(VGUI_USE_GLUT)

ENDIF (GLUT_FOUND)

##################################################
# Qt
##################################################

IF (QT_FOUND)

  OPTION(VGUI_USE_QT "Should Qt support be compiled into vgui?" YES)
  IF(QT3_INSTALLED AND QT4_INSTALLED)
    OPTION(VGUI_USE_QT4 "Specify QT version" YES)
  ELSE(QT3_INSTALLED AND QT4_INSTALLED)
     IF(QT4_INSTALLED)
          SET(VGUI_USE_QT4 YES)
     ELSE(QT4_INSTALLED)
         SET(VGUI_USE_QT4 NO)
     ENDIF(QT4_INSTALLED)
  ENDIF(QT3_INSTALLED AND QT4_INSTALLED)
  IF(VGUI_USE_QT)
    IF(QT4_INSTALLED AND VGUI_USE_QT4)
    INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR} ${QT_QT_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTOPENGL_INCLUDE_DIR})
        ADD_DEFINITIONS(-DQT3_SUPPORT_WARNINGS ${QT_DEFINITIONS} ${QT_USE_QTOPENGL})
    SET(QT_SRCS_DIR impl/qt4)
    ELSE(QT4_INSTALLED AND VGUI_USE_QT4)
    INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})
    ADD_DEFINITIONS(${QT_DEFINITIONS})
    SET(QT_SRCS_DIR impl/qt)
    ENDIF(QT4_INSTALLED AND VGUI_USE_QT4)

    SET(vgui_qt_sources
      ${QT_SRCS_DIR}/vgui_qt.cxx             ${QT_SRCS_DIR}/vgui_qt.h
      ${QT_SRCS_DIR}/vgui_qt_tag.cxx
      ${QT_SRCS_DIR}/vgui_qt_window.cxx      ${QT_SRCS_DIR}/vgui_qt_window.h
      ${QT_SRCS_DIR}/vgui_qt_adaptor.cxx     ${QT_SRCS_DIR}/vgui_qt_adaptor.h
      ${QT_SRCS_DIR}/vgui_qt_statusbar.cxx   ${QT_SRCS_DIR}/vgui_qt_statusbar.h
      ${QT_SRCS_DIR}/vgui_qt_dialog_impl.cxx ${QT_SRCS_DIR}/vgui_qt_dialog_impl.h
      ${QT_SRCS_DIR}/vgui_qt_menu.cxx        ${QT_SRCS_DIR}/vgui_qt_menu.h
    )

    QT_WRAP_CPP(vgui vgui_qt_moc_files
      ${QT_SRCS_DIR}/vgui_qt_adaptor.h
      ${QT_SRCS_DIR}/vgui_qt_dialog_impl.h
      ${QT_SRCS_DIR}/vgui_qt_menu.h
      ${QT_SRCS_DIR}/vgui_qt_statusbar.h
    )

    SET( vgui_sources ${vgui_sources} ${vgui_qt_sources} ${vgui_qt_moc_files} )

    IF(CMAKE_COMPILER_IS_GNUCXX)
      SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/moc_vgui_qt_adaptor.cxx GENERATED PROPERTIES COMPILE_FLAGS -O0)
    ENDIF(CMAKE_COMPILER_IS_GNUCXX)

  ENDIF(VGUI_USE_QT)

ENDIF (QT_FOUND)

##################################################
# MFC
##################################################

IF (MFC_FOUND)

  OPTION(VGUI_USE_MFC "Should MFC support be compiled into vgui?" YES)

  IF(VGUI_USE_MFC)

    SET(vgui_mfc_sources
      impl/mfc/vgui_mfc.cxx             impl/mfc/vgui_mfc.h
      impl/mfc/vgui_mfc_adaptor.cxx     impl/mfc/vgui_mfc_adaptor.h
      impl/mfc/vgui_mfc_app.cxx         impl/mfc/vgui_mfc_app.h
      impl/mfc/vgui_mfc_app_init.cxx    impl/mfc/vgui_mfc_app_init.h
      impl/mfc/vgui_mfc_dialog_impl.cxx impl/mfc/vgui_mfc_dialog_impl.h
      impl/mfc/vgui_mfc_dialog_extensions_impl.cxx impl/mfc/vgui_mfc_dialog_extensions_impl.h
      impl/mfc/vgui_mfc_doc.cxx         impl/mfc/vgui_mfc_doc.h
      impl/mfc/vgui_mfc_mainfrm.cxx     impl/mfc/vgui_mfc_mainfrm.h
      impl/mfc/vgui_mfc_statusbar.cxx   impl/mfc/vgui_mfc_statusbar.h
      impl/mfc/vgui_mfc_tag.cxx
      impl/mfc/vgui_mfc_utils.cxx       impl/mfc/vgui_mfc_utils.h
      impl/mfc/vgui_mfc_view.cxx        impl/mfc/vgui_mfc_view.h
      impl/mfc/vgui_mfc_window.cxx      impl/mfc/vgui_mfc_window.h
      impl/mfc/vgui_dir_dialog.cxx      impl/mfc/vgui_dir_dialog.h
    )

    SET( vgui_sources ${vgui_sources} ${vgui_mfc_sources} )

  ENDIF(VGUI_USE_MFC)

ENDIF (MFC_FOUND)

##################################################
# GTK
##################################################

IF (GTK_GL_FOUND)

  OPTION(VGUI_USE_GTK "Should GTK support be compiled into vgui?" YES)

  IF(VGUI_USE_GTK)

    INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIR})

    SET(vgui_gtk_sources
      impl/gtk/vgui_gtk.cxx             impl/gtk/vgui_gtk.h
      impl/gtk/vgui_gtk_adaptor.cxx     impl/gtk/vgui_gtk_adaptor.h
      impl/gtk/vgui_gtk_dialog_impl.cxx impl/gtk/vgui_gtk_dialog_impl.h
      impl/gtk/vgui_gtk_statusbar.cxx   impl/gtk/vgui_gtk_statusbar.h
      impl/gtk/vgui_gtk_tag.cxx
      impl/gtk/vgui_gtk_utils.cxx       impl/gtk/vgui_gtk_utils.h
      impl/gtk/vgui_gtk_window.cxx      impl/gtk/vgui_gtk_window.h
    )

    SET( vgui_sources ${vgui_sources} ${vgui_gtk_sources} )

  ENDIF(VGUI_USE_GTK)

ENDIF (GTK_GL_FOUND)


##################################################
# GTK2
##################################################

IF (GTK2_FOUND)

  OPTION(VGUI_USE_GTK2 "Should GTK2 support be compiled into vgui?" YES)

  IF(VGUI_USE_GTK2)

    IF(VGUI_USE_GTK)
       MESSAGE(SEND_ERROR "You cannot build against both GTK1 and"
                           "GTK2 at the same time")
    ENDIF(VGUI_USE_GTK)


    # This puts the include directories and whatever compiler flags
    # are necessary for GTK2
    ADD_DEFINITIONS( ${GTK2_DEFINITIONS} )

    SET(vgui_gtk2_sources
      impl/gtk2/vgui_gtk2.cxx             impl/gtk2/vgui_gtk2.h
      impl/gtk2/vgui_gtk2_adaptor.cxx     impl/gtk2/vgui_gtk2_adaptor.h
      impl/gtk2/vgui_gtk2_dialog_impl.cxx impl/gtk2/vgui_gtk2_dialog_impl.h
      impl/gtk2/vgui_gtk2_statusbar.cxx   impl/gtk2/vgui_gtk2_statusbar.h
      impl/gtk2/vgui_gtk2_tag.cxx
      impl/gtk2/vgui_gtk2_utils.cxx       impl/gtk2/vgui_gtk2_utils.h
      impl/gtk2/vgui_gtk2_window.cxx      impl/gtk2/vgui_gtk2_window.h
    )

    SET( vgui_sources ${vgui_sources} ${vgui_gtk2_sources} )

  ENDIF(VGUI_USE_GTK2)

ENDIF (GTK2_FOUND)

##################################################
# wxWidgets
##################################################

IF (wxWidgets_FOUND)

  OPTION(VGUI_USE_WX "Should wxWidgets support be compiled into vgui?" NO)

  IF(VGUI_USE_WX)

    INCLUDE( ${wxWidgets_USE_FILE} )

    SET(vgui_wx_sources
      impl/wx/vgui_wx_tag.cxx
      impl/wx/vgui_wx.cxx             impl/wx/vgui_wx.h
      impl/wx/vgui_wx_adaptor.cxx     impl/wx/vgui_wx_adaptor.h
      impl/wx/vgui_wx_window.cxx      impl/wx/vgui_wx_window.h
      impl/wx/vgui_wx_dialog_impl.cxx impl/wx/vgui_wx_dialog_impl.h
      impl/wx/vgui_wx_menu.cxx        impl/wx/vgui_wx_menu.h
      impl/wx/vgui_wx_statusbar.cxx   impl/wx/vgui_wx_statusbar.h
    )

    SET( vgui_sources ${vgui_sources} ${vgui_wx_sources} )

    OPTION(BUILD_VGUI_WX "Build extras for VGUI use in wxWidgets apps" NO)
    IF(BUILD_VGUI_WX)
      SUBDIRS(wx)
    ENDIF(BUILD_VGUI_WX)

  ENDIF(VGUI_USE_WX)

ENDIF (wxWidgets_FOUND)

######################################################################
# END TOOLKIT IMPLEMENTATIONS
######################################################################

# Store chosen configuration in to the config file. This allows files
# that depend on these configuration parameters to be automatically
# recompiled when the config changes.

CONFIGURE_FILE( ${vxl_SOURCE_DIR}/core/vgui/vgui_config.h.in
                ${vxl_BINARY_DIR}/core/vgui/vgui_config.h @ONLY IMMEDIATE )

# Register each toolkit that was compiled in.
SET( vgui_sources ${vgui_sources}
  vgui_register_all.cxx
)

ADD_LIBRARY(vgui ${vgui_sources})
INSTALL_TARGETS(/lib vgui)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/core/vgui ${vgui_sources})
SET( VGUI_FOUND "YES" CACHE INTERNAL "Was vgui successfully built?" )

# Dependencies on other vxl libraries
TARGET_LINK_LIBRARIES(vgui vnl vil1 vil vgl vpl vbl vul)

#imagehlp.dll is needed for directory browsing (vgui_dir_dialog)
IF(MFC_FOUND)
  TARGET_LINK_LIBRARIES(vgui imagehlp)
ENDIF(MFC_FOUND)

# Dependencies created by the toolkit implementations

IF (VGUI_USE_QT)
  IF(QT4_INSTALLED AND VGUI_USE_QT4)
    TARGET_LINK_LIBRARIES(vgui ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY})
  ELSE(QT4_INSTALLED AND VGUI_USE_QT4)
    TARGET_LINK_LIBRARIES(vgui ${QT_LIBRARIES})
  ENDIF(QT4_INSTALLED AND VGUI_USE_QT4)
ENDIF (VGUI_USE_QT)
IF (VGUI_USE_GTK)
  TARGET_LINK_LIBRARIES(vgui ${GTK_LIBRARIES})
ENDIF (VGUI_USE_GTK)
IF (VGUI_USE_GTK2)
  TARGET_LINK_LIBRARIES(vgui ${GTK2_LIBRARIES})
ENDIF (VGUI_USE_GTK2)
IF (VGUI_USE_WX)
  IF(wxWidgets_LINK_DIRECTORIES)
    LINK_DIRECTORIES(${wxWidgets_LINK_DIRECTORIES})
  ENDIF(wxWidgets_LINK_DIRECTORIES)

  IF(wxWidgets_LIBRARIES)
    TARGET_LINK_LIBRARIES(vgui ${wxWidgets_LIBRARIES})
  ENDIF(wxWidgets_LIBRARIES)
ENDIF (VGUI_USE_WX)

# Basic vgui dependencies.
# These should appear after the above, because most of
# the toolkits depend on OpenGL.

IF (VGUI_USE_GLUT)
  TARGET_LINK_LIBRARIES(vgui ${GLUT_LIBRARIES})
ENDIF (VGUI_USE_GLUT)
IF (QV_FOUND)
  TARGET_LINK_LIBRARIES(vgui ${QV_LIBRARIES})
ENDIF (QV_FOUND)

TARGET_LINK_LIBRARIES(vgui ${OPENGL_LIBRARIES})

IF (X11_FOUND)
  TARGET_LINK_LIBRARIES(vgui ${X11_LIBRARIES})
ENDIF (X11_FOUND)

IF (BUILD_EXAMPLES)
  SUBDIRS(examples)
ENDIF (BUILD_EXAMPLES)

IF (BUILD_TESTING)
  SUBDIRS(tests)
ENDIF (BUILD_TESTING)

ENDIF (OPENGL_GLU_FOUND)
ENDIF (OPENGL_FOUND)

IF( NOT CAN_BUILD_VGUI )
  # Dashboard builds will try to build vgui if possible,
  # so don't warn if we can't.
  IF( NOT BUILD_FOR_VXL_DASHBOARD )
    MESSAGE(SEND_ERROR "vgui could not be built.\n"
                       "Make sure the OpenGL libraries "
                       "(GL and GLU) are specified correctly,\n"
                       "or set BUILD_VGUI to OFF." )
  ENDIF( NOT BUILD_FOR_VXL_DASHBOARD )
ENDIF( NOT CAN_BUILD_VGUI )

ENDIF( BUILD_VGUI )
