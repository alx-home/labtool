ADD_EXECUTABLE( bvxm_algo_test_all
  test_driver.cxx
  test_merge_mog.cxx
  test_mog_norm.cxx
)

TARGET_LINK_LIBRARIES( bvxm_algo_test_all bvxm_algo bvxm_grid testlib bsta)

ADD_TEST( bvxm_test_merge_mog    ${EXECUTABLE_OUTPUT_PATH}/bvxm_algo_test_all   test_merge_mog )
ADD_TEST( bvxm_test_mog_norm     ${EXECUTABLE_OUTPUT_PATH}/bvxm_algo_test_all   test_mog_norm )

ADD_EXECUTABLE( bvxm_algo_test_include test_include.cxx )

TARGET_LINK_LIBRARIES( bvxm_algo_test_include bvxm_algo)
