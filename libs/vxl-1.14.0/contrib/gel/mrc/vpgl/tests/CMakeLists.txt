ADD_EXECUTABLE( vpgl_test_all
  test_driver.cxx

  test_proj_camera.cxx
  test_perspective_camera.cxx
  test_affine_camera.cxx
  test_fundamental_matrix.cxx
  test_essential_matrix.cxx
  test_calibration_matrix.cxx
  test_camera_io.cxx
  test_poly_radial_distortion.cxx
  test_rational_camera.cxx
  test_local_rational_camera.cxx
)

TARGET_LINK_LIBRARIES( vpgl_test_all bgeo vpgl vgl_algo vgl vnl vpl testlib )

ADD_TEST( vpgl_test_proj_camera                ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_proj_camera )
ADD_TEST( vpgl_test_perspective_camera         ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_perspective_camera)
ADD_TEST( vpgl_test_affine_camera              ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_affine_camera)
ADD_TEST( vpgl_test_calibration_matrix         ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_calibration_matrix)
ADD_TEST( vpgl_test_camera_io                  ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_camera_io)
ADD_TEST( vpgl_test_poly_radial_distortion     ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_poly_radial_distortion)
ADD_TEST( vpgl_test_fundamental_matrix         ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_fundamental_matrix)
ADD_TEST( vpgl_test_essential_matrix           ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_essential_matrix)
ADD_TEST( vpgl_test_rational_camera            ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_rational_camera)
ADD_TEST( vpgl_test_local_rational_camera      ${EXECUTABLE_OUTPUT_PATH}/vpgl_test_all test_local_rational_camera)

SET( HAS_GEOTIFF 0 )
INCLUDE( ${MODULE_PATH}/FindGEOTIFF.cmake)
IF(GEOTIFF_FOUND)
  SET (HAS_GEOTIFF 1 )
  INCLUDE_DIRECTORIES(${GEOTIFF_INCLUDE_DIR})
ENDIF(GEOTIFF_FOUND)

ADD_EXECUTABLE( vpgl_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( vpgl_test_include vpgl )
