# brl/bseg/strk/tests/CMakeLists.txt

ADD_EXECUTABLE( strk_test_all
  test_driver.cxx
  test_tracking_face_2d.cxx
)

TARGET_LINK_LIBRARIES(strk_test_all strk brip btol vtol vsol vil1 vnl testlib)

ADD_TEST(strk_test_tracking_face_2d   ${EXECUTABLE_OUTPUT_PATH}/strk_test_all test_tracking_face_2d
         ${CMAKE_CURRENT_SOURCE_DIR}/image0005_left.bmp
         ${CMAKE_CURRENT_SOURCE_DIR}/image0005_right.bmp)

ADD_EXECUTABLE( strk_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( strk_test_include strk )
