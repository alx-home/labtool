# brl/bbas/bwm/reg/tests/CMakeLists.txt
INCLUDE_DIRECTORIES( ${VXLCORE_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${GEL_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${BRL_INCLUDE_DIR})

ADD_EXECUTABLE(bwm_reg_test_all
  test_driver.cxx
  test_champher.cxx
  test_matcher.cxx
  test_processor.cxx
)
TARGET_LINK_LIBRARIES(bwm_reg_test_all bwm_reg vsol vnl vil vgl testlib)

ADD_TEST(bwm_reg_test_matcher   ${EXECUTABLE_OUTPUT_PATH}/bwm_reg_test_all test_champher)
ADD_TEST(bwm_reg_test_matcher   ${EXECUTABLE_OUTPUT_PATH}/bwm_reg_test_all test_matcher)
ADD_TEST(bwm_reg_test_processor ${EXECUTABLE_OUTPUT_PATH}/bwm_reg_test_all test_processor)

ADD_EXECUTABLE(bwm_reg_test_include test_include.cxx)
TARGET_LINK_LIBRARIES(bwm_reg_test_include bwm_reg)
