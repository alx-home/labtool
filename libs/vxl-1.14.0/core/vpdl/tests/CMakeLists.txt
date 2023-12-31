# core/vpdl/tests/CMakeLists.txt
# Tests for vpdl library

ADD_EXECUTABLE( vpdl_test_all
  test_driver.cxx
  test_eigen_sym_matrix.cxx
  test_gaussian_sphere.cxx
  test_gaussian_indep.cxx
  test_gaussian.cxx
  test_update_gaussian.cxx
  test_mixture.cxx
  test_mixture_of.cxx
  test_update_mog.cxx
  test_kernel_gaussian_sfbw.cxx
)

TARGET_LINK_LIBRARIES( vpdl_test_all vpdl vnl_algo vnl testlib)

ADD_TEST( vpdl_test_eigen_sym_matrix      vpdl_test_all test_eigen_sym_matrix )
ADD_TEST( vpdl_test_gaussian_sphere       vpdl_test_all test_gaussian_sphere )
ADD_TEST( vpdl_test_gaussian_indep        vpdl_test_all test_gaussian_indep )
ADD_TEST( vpdl_test_gaussian              vpdl_test_all test_gaussian )
ADD_TEST( vpdl_test_update_gaussian       vpdl_test_all test_update_gaussian )
ADD_TEST( vpdl_test_mixture               vpdl_test_all test_mixture )
ADD_TEST( vpdl_test_mixture_of            vpdl_test_all test_mixture_of )
ADD_TEST( vpdl_test_update_mog            vpdl_test_all test_update_mog )
ADD_TEST( vpdl_test_kernel_gaussian_sfbw  vpdl_test_all test_kernel_gaussian_sfbw )

ADD_EXECUTABLE( vpdl_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( vpdl_test_include vpdl )
