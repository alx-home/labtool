#include <testlib/testlib_test.h>
#include <bsta/bsta_gaussian_full.h>
#include <vcl_string.h>
#include <vcl_limits.h>
#include <vnl/vnl_math.h>
#include <vnl/vnl_inverse.h>
#include <vcl_iostream.h>

template <class T>
void test_gaussian_full_type(T epsilon, const vcl_string& type_name)
{
  bsta_gaussian_full<T,3> df_gauss;

  TEST(("dimension <"+type_name+">").c_str(),
       (bsta_gaussian_full<T,3>::dimension), 3);
  TEST(("det(null covar) <"+type_name+">").c_str(),
       df_gauss.det_covar(), T(0));

  vnl_vector_fixed<T,3> mean(T(1.0), T(2.0), T(4.0));
  vnl_matrix_fixed<T,3,3> covar(T(0));

  covar(0,0) = (T)0.5; covar(0,1) = (T)0.2; covar(0,2) = (T)0.1;
  covar(1,0) = (T)0.2; covar(1,1) = (T)0.3; covar(1,2) = (T)0.1;
  covar(2,0) = (T)0.1; covar(2,1) = (T)0.1; covar(2,2) = (T)0.4;

  bsta_gaussian_full<T,3> gauss(mean, covar);

  TEST(("mean <"+type_name+">").c_str(), gauss.mean(), mean);
  TEST(("covar <"+type_name+">").c_str(), gauss.covar(), covar);

  TEST_NEAR(("det(covar) <"+type_name+">").c_str(),
            gauss.det_covar(), T(0.04), epsilon);

  vnl_vector_fixed<T,3> test_pt(T(1.5), T(3.0), T(3.0));
  vnl_vector_fixed<T,3> d = mean - test_pt;

  T sqr_mah_dist = dot_product(d,(vnl_inverse(covar)*d));

  TEST_NEAR(("Mahalanobis dist <"+type_name+">").c_str(),
            gauss.sqr_mahalanobis_dist(test_pt), sqr_mah_dist, epsilon);

  T two_pi = T(2*vnl_math::pi);
  T prob = T(1.0/vcl_sqrt(two_pi*two_pi*two_pi*gauss.det_covar()) * vcl_exp(-sqr_mah_dist/2));
  TEST_NEAR(("probability density <"+type_name+">").c_str(),
            gauss.prob_density(test_pt), prob, epsilon);

  bsta_gaussian_full<T,3> zero_var_gauss;
  TEST(("zero var Mahalanobis dist <"+type_name+">").c_str(),
       zero_var_gauss.sqr_mahalanobis_dist(test_pt),
       vcl_numeric_limits<T>::infinity());

  TEST(("zero var probability density <"+type_name+">").c_str(),
       zero_var_gauss.prob_density(test_pt), T(0));

  // test stream
  vcl_cout << "testing stream operator\n"
           << gauss << '\n';
}

static void test_gaussian_full()
{
  test_gaussian_full_type(1e-5f,"float");
  test_gaussian_full_type(1e-14,"double");
}

TESTMAIN(test_gaussian_full);
