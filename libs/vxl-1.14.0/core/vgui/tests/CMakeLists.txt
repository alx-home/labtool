# This is core/vgui/test/CMakeLists.txt

PROJECT( vgui_tests )

INCLUDE( ${MODULE_PATH}/UseVGUI.cmake )

IF( HAS_VGUI )

  # No need to do FindGLUT since the parent CMakeLists.txt did it for
  # us...

  LINK_LIBRARIES( vgui )

  ADD_EXECUTABLE( vgui_test_popup test_popup.cxx )
  #ADD_TEST( vgui_test_popup ${EXECUTABLE_OUTPUT_PATH}/vgui_test_popup )
  ADD_EXECUTABLE( vgui_test_timer test_timer.cxx )
  #ADD_TEST( vgui_test_timer ${EXECUTABLE_OUTPUT_PATH}/vgui_test_timer )
  ADD_EXECUTABLE( vgui_test_events test_events.cxx )
  #ADD_TEST( vgui_test_events ${EXECUTABLE_OUTPUT_PATH}/vgui_test_events )
  ADD_EXECUTABLE( vgui_test_front_back test_front_back.cxx )
  #ADD_TEST( vgui_test_front_back ${EXECUTABLE_OUTPUT_PATH}/vgui_test_front_back )

  IF(X11_FOUND)
    ADD_EXECUTABLE( vgui_test_drawpix_speed test_drawpix_speed.cxx )
    #ADD_TEST( vgui_test_drawpix_speed ${EXECUTABLE_OUTPUT_PATH}/vgui_test_drawpix_speed )
    ADD_EXECUTABLE( vgui_test_acceleration test_acceleration.cxx )
    #ADD_TEST( vgui_test_acceleration ${EXECUTABLE_OUTPUT_PATH}/vgui_test_acceleration )
  ENDIF(X11_FOUND)

  ADD_EXECUTABLE( vgui_test_all
    test_driver.cxx

    test_displaybase.cxx
    test_pixels.cxx
    test_image_tableau.cxx
    test_range_map.cxx
  )
  TARGET_LINK_LIBRARIES( vgui_test_all vgui vul vbl testlib )

  ADD_TEST( vgui_test_displaybase         ${EXECUTABLE_OUTPUT_PATH}/vgui_test_all test_displaybase )
  ADD_TEST( vgui_test_pixels              ${EXECUTABLE_OUTPUT_PATH}/vgui_test_all test_pixels )
  ADD_TEST( vgui_test_image_tableau       ${EXECUTABLE_OUTPUT_PATH}/vgui_test_all test_image_tableau ${CMAKE_CURRENT_SOURCE_DIR}/test_image.ppm )
  ADD_TEST( vgui_test_range_map ${EXECUTABLE_OUTPUT_PATH}/vgui_test_all test_range_map)
  ADD_EXECUTABLE( vgui_test_include test_include.cxx )
  TARGET_LINK_LIBRARIES( vgui_test_include vgui )

  ADD_EXECUTABLE( vgui_test_drawpix_speed2 test_drawpix_speed2.cxx )

  ADD_EXECUTABLE( vgui_test_rubberband_dialog test_rubberband_dialog.cxx )

ENDIF( HAS_VGUI )
