# This is core/vnl/algo/tests/CMakeLists.txt

INCLUDE( ${MODULE_PATH}/FindNetlib.cmake )

# MESSAGE( NETLIB_FOUND " is " ${NETLIB_FOUND} )
IF(NETLIB_FOUND)

  INCLUDE_DIRECTORIES( ${NETLIB_INCLUDE_DIR} )

  ADD_EXECUTABLE( vnl_algo_test_all
    # Driver source and utilities
    test_driver.cxx
    test_util.cxx       test_util.h

    # The tests
    test_algo.cxx
    test_amoeba.cxx
    test_cholesky.cxx
    test_complex_eigensystem.cxx
    test_convolve.cxx
    test_cpoly_roots.cxx
    test_determinant.cxx
    test_fft.cxx
    test_fft1d.cxx
    test_fft2d.cxx
    test_functions.cxx
    test_generalized_eigensystem.cxx
    test_ldl_cholesky.cxx
    test_levenberg_marquardt.cxx
    test_matrix_update.cxx
    test_minimizers.cxx
    test_powell.cxx
    test_qr.cxx
    test_qsvd.cxx
    test_rank.cxx
    test_real_eigensystem.cxx
    test_rnpoly_roots.cxx
    test_rpoly_roots.cxx
    test_sparse_matrix.cxx
    test_svd.cxx
    test_svd_fixed.cxx
    test_symmetric_eigensystem.cxx
    test_integral.cxx
    test_solve_qp.cxx
    test_sparse_lu.cxx
    test_bracket_minimum.cxx
    test_brent_minimizer.cxx
    test_sparse_lm.cxx
  )

  TARGET_LINK_LIBRARIES( vnl_algo_test_all vnl_algo vul testlib ${CMAKE_THREAD_LIBS} )


  ADD_TEST( vnl_test_algo                     ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_algo                    )
  ADD_TEST( vnl_test_amoeba                   ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_amoeba                  )
  ADD_TEST( vnl_test_cholesky                 ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_cholesky                )
  ADD_TEST( vnl_test_complex_eigensystem      ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_complex_eigensystem     )
  ADD_TEST( vnl_test_convolve                 ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_convolve                )
  ADD_TEST( vnl_test_cpoly_roots              ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_cpoly_roots             )
  ADD_TEST( vnl_test_determinant              ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_determinant             )
  ADD_TEST( vnl_test_fft                      ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_fft                     )
  ADD_TEST( vnl_test_fft1d                    ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_fft1d                   )
  ADD_TEST( vnl_test_fft2d                    ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_fft2d                   )
  ADD_TEST( vnl_test_functions                ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_functions               )
  ADD_TEST( vnl_test_generalized_eigensystem  ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_generalized_eigensystem )
  ADD_TEST( vnl_test_ldl_cholesky             ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_ldl_cholesky                )
  ADD_TEST( vnl_test_levenberg_marquardt      ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_levenberg_marquardt     )
  ADD_TEST( vnl_test_matrix_update            ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_matrix_update              )
  ADD_TEST( vnl_test_minimizers               ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_minimizers              )
  ADD_TEST( vnl_test_powell                   ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_powell                  )
  ADD_TEST( vnl_test_qr                       ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_qr                      )
  ADD_TEST( vnl_test_qsvd                     ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_qsvd                    )
  ADD_TEST( vnl_test_rank                     ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_rank                    )
  ADD_TEST( vnl_test_real_eigensystem         ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_real_eigensystem        )
  ADD_TEST( vnl_test_rnpoly_roots             ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_rnpoly_roots            )
  ADD_TEST( vnl_test_rpoly_roots              ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_rpoly_roots             )
  ADD_TEST( vnl_test_integral                 ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_integral                )
  ADD_TEST( vnl_test_solve_qp                 ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_solve_qp                )
  ADD_TEST( vnl_test_sparse_lu                ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_sparse_lu               )
  ADD_TEST( vnl_test_bracket_minimum          ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_bracket_minimum         )
  ADD_TEST( vnl_test_brent_minimizer          ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_brent_minimizer         )
  ADD_TEST( vnl_test_sparse_lm                ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_sparse_lm               )
  ADD_TEST( vnl_test_sparse_matrix            ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_sparse_matrix           )
  ADD_TEST( vnl_test_svd                      ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_svd                     )
  ADD_TEST( vnl_test_svd_fixed                ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_svd_fixed               )
  ADD_TEST( vnl_test_symmetric_eigensystem    ${EXECUTABLE_OUTPUT_PATH}/vnl_algo_test_all test_symmetric_eigensystem   )
ENDIF(NETLIB_FOUND)

# GCC 2.95 has problems when compiling test_algo.cxx with "-O2" flag.
# The solution is to turn off optimization for GCC < 3.0
IF(CMAKE_COMPILER_IS_GNUCXX)
  IF ( VNL_COMPILER_IS_GNUCXX_2XX MATCHES "VNL_COMPILER_IS_GNUCXX_2XX")
    EXEC_PROGRAM(${CMAKE_CXX_COMPILER} ARGS --version OUTPUT_VARIABLE CMAKE_CXX_COMPILER_VERSION)
    IF(CMAKE_CXX_COMPILER_VERSION MATCHES ".*2\\.9[0-9]\\.[0-9].*")
      SET ( VNL_COMPILER_IS_GNUCXX_2XX 1 CACHE INTERNAL "Are we using an version of gcc < 3.0")
    ELSE(CMAKE_CXX_COMPILER_VERSION MATCHES ".*2\\.9[0-9]\\.[0-9].*")
      SET ( VNL_COMPILER_IS_GNUCXX_2XX 0 CACHE INTERNAL "Are we using an version of gcc < 3.0")
    ENDIF(CMAKE_CXX_COMPILER_VERSION MATCHES ".*2\\.9[0-9]\\.[0-9].*")
  ENDIF ( VNL_COMPILER_IS_GNUCXX_2XX MATCHES "VNL_COMPILER_IS_GNUCXX_2XX")

  IF(VNL_COMPILER_IS_GNUCXX_2XX)
    # We only need to remove "-O2" flag from test_algo.cxx.
    # But it is much easier to do it for all
    FOREACH(var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_MINSIZEREL)
      STRING(REGEX REPLACE "-O2" "" "${var}" "${${var}}")
    ENDFOREACH(var)
  ENDIF(VNL_COMPILER_IS_GNUCXX_2XX)
ENDIF ( CMAKE_COMPILER_IS_GNUCXX )

ADD_EXECUTABLE( vnl_algo_test_include test_include.cxx )
TARGET_LINK_LIBRARIES( vnl_algo_test_include vnl_algo )
