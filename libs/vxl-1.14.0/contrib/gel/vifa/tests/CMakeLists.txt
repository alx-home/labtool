# gel/vifa/tests/CMakeLists.txt

INCLUDE_DIRECTORIES(${GEL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BRL_INCLUDE_DIR})

ADD_EXECUTABLE( vifa_test_all
  test_ifa_factory.h
  test_ifa_factory.cxx
  test_driver.cxx
  test_coll_lines_params.cxx
  test_group_pgram_params.cxx
  test_norm_params.cxx
  test_parallel_params.cxx
  test_int_face_attr_common_params.cxx
  test_image_histogram.cxx
  test_region_proc.cxx
  test_int_face_attr.cxx
  test_int_faces_attr.cxx
  test_int_faces_adj_attr.cxx
)
TARGET_LINK_LIBRARIES( vifa_test_all vifa sdet vtol vdgl vil vil1 vgl testlib )

ADD_TEST(vifa_test_coll_lines_params  ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_coll_lines_params)
ADD_TEST(vifa_test_group_pgram_params ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_group_pgram_params)
ADD_TEST(vifa_test_norm_params        ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_norm_params)
ADD_TEST(vifa_test_parallel_params    ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_parallel_params)
ADD_TEST(vifa_test_int_face_attr_common_params ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_int_face_attr_common_params)
ADD_TEST(vifa_test_image_histogram    ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_image_histogram ${CMAKE_CURRENT_SOURCE_DIR}/cam0013.tif)
ADD_TEST(vifa_test_region_proc        ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_region_proc ${CMAKE_CURRENT_SOURCE_DIR}/testimg.tif)
ADD_TEST(vifa_test_int_face_attr      ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_int_face_attr ${CMAKE_CURRENT_SOURCE_DIR}/testimg.tif)
ADD_TEST(vifa_test_int_faces_attr     ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_int_faces_attr ${CMAKE_CURRENT_SOURCE_DIR}/testimg.tif)
ADD_TEST(vifa_test_int_faces_adj_attr ${EXECUTABLE_OUTPUT_PATH}/vifa_test_all test_int_faces_adj_attr ${CMAKE_CURRENT_SOURCE_DIR}/testimg.tif)

ADD_EXECUTABLE( vifa_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( vifa_test_include vifa )
