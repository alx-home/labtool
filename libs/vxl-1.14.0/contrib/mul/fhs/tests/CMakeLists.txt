# This is mul/fhs/tests/CMakeLists.txt

ADD_EXECUTABLE( fhs_test_all
  test_driver.cxx

  test_arc.cxx
  test_searcher.cxx
)
TARGET_LINK_LIBRARIES( fhs_test_all fhs vgl testlib )

ADD_TEST( fhs_test_arc                  ${EXECUTABLE_OUTPUT_PATH}/fhs_test_all test_arc )
ADD_TEST( fhs_test_searcher             ${EXECUTABLE_OUTPUT_PATH}/fhs_test_all test_searcher )

ADD_EXECUTABLE( fhs_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( fhs_test_include fhs )
