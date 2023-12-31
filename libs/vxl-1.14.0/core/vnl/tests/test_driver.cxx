#include <testlib/testlib_register.h>

DECLARE( test_bignum );
DECLARE( test_complex );
DECLARE( test_inverse );
DECLARE( test_diag_matrix );
DECLARE( test_diag_matrix_fixed );
DECLARE( test_file_matrix );
DECLARE( test_finite );
DECLARE( test_math );
DECLARE( test_na );
DECLARE( test_matlab );
DECLARE( test_matrix );
DECLARE( test_matrix_exp );
DECLARE( test_matrix_fixed );
DECLARE( test_matrix_fixed_ref );
DECLARE( test_na );
DECLARE( test_numeric_traits );
DECLARE( test_power );
DECLARE( test_quaternion );
DECLARE( test_rational );
DECLARE( test_real_polynomial );
DECLARE( test_real_npolynomial );
DECLARE( test_resize );
DECLARE( test_rotation_matrix );
DECLARE( test_sample );
DECLARE( test_sym_matrix );
DECLARE( test_transpose );
DECLARE( test_fastops );
DECLARE( test_vector );
DECLARE( test_vector_fixed_ref );
DECLARE( test_gamma );
DECLARE( test_random );
DECLARE( test_arithmetic );
DECLARE( test_alignment );
DECLARE( test_hungarian_algorithm );
DECLARE( test_integrant );
DECLARE( test_bessel );
DECLARE( test_crs_index );
DECLARE( test_sparse_lst_sqr_function );
DECLARE( test_sparse_matrix );

void
register_tests()
{
  REGISTER( test_bignum );
  REGISTER( test_complex );
  REGISTER( test_inverse );
  REGISTER( test_diag_matrix );
  REGISTER( test_diag_matrix_fixed );
  REGISTER( test_file_matrix );
  REGISTER( test_finite );
  REGISTER( test_math );
  REGISTER( test_matlab );
  REGISTER( test_matrix );
  REGISTER( test_matrix_exp );
  REGISTER( test_matrix_fixed );
  REGISTER( test_matrix_fixed_ref );
  REGISTER( test_na );
  REGISTER( test_numeric_traits );
  REGISTER( test_power );
  REGISTER( test_quaternion );
  REGISTER( test_rational );
  REGISTER( test_real_polynomial );
  REGISTER( test_real_npolynomial );
  REGISTER( test_resize );
  REGISTER( test_rotation_matrix );
  REGISTER( test_sample );
  REGISTER( test_sym_matrix );
  REGISTER( test_transpose );
  REGISTER( test_fastops );
  REGISTER( test_vector );
  REGISTER( test_vector_fixed_ref );
  REGISTER( test_gamma );
  REGISTER( test_random );
  REGISTER( test_arithmetic );
  REGISTER( test_alignment );
  REGISTER( test_hungarian_algorithm );
  REGISTER( test_integrant );
  REGISTER( test_bessel );  
  REGISTER( test_crs_index );
  REGISTER( test_sparse_lst_sqr_function );
  REGISTER( test_sparse_matrix );
}

DEFINE_MAIN;
