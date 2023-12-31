# mul/mfpf/tests/CMakeLists.txt

ADD_EXECUTABLE( mfpf_test_all
  test_driver.cxx
  test_edge_finder.cxx
  test_norm_corr1d.cxx
  test_norm_corr2d.cxx
  test_profile_pdf.cxx
  test_region_pdf.cxx
  test_region_finder.cxx
  test_pose.cxx
  test_mr_point_finder.cxx
  test_dp_snake.cxx
  test_patch_data.cxx
  test_pose_predictor.cxx
  )

TARGET_LINK_LIBRARIES( mfpf_test_all mfpf mipa vil_algo vil vgl testlib )

ADD_TEST( mfpf_test_edge_finder ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_edge_finder)
ADD_TEST( mfpf_test_norm_corr1d ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_norm_corr1d)
ADD_TEST( mfpf_test_norm_corr2d ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_norm_corr2d)
ADD_TEST( mfpf_test_profile_pdf ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_profile_pdf)
ADD_TEST( mfpf_test_region_pdf  ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_region_pdf)
ADD_TEST( mfpf_test_region_finder  ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_region_finder)
ADD_TEST( mfpf_test_pose        ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_pose)
ADD_TEST( mfpf_test_mr_point_finder  ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_mr_point_finder)
ADD_TEST( mfpf_test_patch_data  ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_patch_data)
ADD_TEST( mfpf_test_dp_snake    ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_dp_snake)
ADD_TEST( mfpf_test_pose_predictor    ${EXECUTABLE_OUTPUT_PATH}/mfpf_test_all test_pose_predictor)

ADD_EXECUTABLE( mfpf_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( mfpf_test_include mfpf mipa)
