# brl/bseg/bbgm/tests/CMakeLists.txt
# Tests for bbgm library

ADD_EXECUTABLE( bbgm_test_all
  test_driver.cxx
  test_bg_model_speed.cxx
  test_measure.cxx
)

TARGET_LINK_LIBRARIES( bbgm_test_all bbgm bsta_algo bsta vnl vil vul testlib )

ADD_TEST( bbgm_test_bg_model_speed ${EXECUTABLE_OUTPUT_PATH}/bbgm_test_all test_bg_model_speed )
ADD_TEST( bbgm_test_measure ${EXECUTABLE_OUTPUT_PATH}/bbgm_test_all test_measure )

ADD_EXECUTABLE( bbgm_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( bbgm_test_include bbgm)
