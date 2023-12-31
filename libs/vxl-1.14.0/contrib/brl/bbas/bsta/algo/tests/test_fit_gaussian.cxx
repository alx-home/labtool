#include <testlib/testlib_test.h>

#include <bsta/bsta_mixture_fixed.h>
#include <bsta/bsta_gaussian_indep.h>
#include <bsta/bsta_gaussian_sphere.h>
#include <bsta/algo/bsta_fit_gaussian.h>

#include <vcl_string.h>

#include <vnl/vnl_random.h>


MAIN( test_fit_gaussian)
{
  START ("test_fit_gaussian");
  vnl_random rand_gen;

  {
    vcl_cout << "Testing 1D Gaussian (spherical)" << vcl_endl;
    // Test the fitting of spherical gaussian
    // 1D
    float mean = 2.3f;
    float var = 0.2f;
    float sigma = vcl_sqrt(var);

    const unsigned int n_samples = 500;

    bsta_gaussian_sphere<float,1> gauss_est;

    // generate samples
    vcl_vector<float> samples;
    vcl_vector<float> weights;
    for (unsigned int n=0; n<n_samples; ++n) {  
      float sample = mean + sigma*(float)rand_gen.normal();
      float weight = (float)rand_gen.drand32(0.0, 1.0);
      weights.push_back(weight);
      samples.push_back(sample);
    }
    bsta_fit_gaussian(samples, weights, gauss_est);

    TEST_NEAR("1D: Estimated mean is correct" ,gauss_est.mean(), mean, 0.1);
    TEST_NEAR("1D: Estimated variance is correct", gauss_est.var(), var, 0.05);
  }
  {
    vcl_cout << "Testing 3D Gaussian (spherical)" << vcl_endl;
    // Test the fitting of spherical gaussian
    // 3D
    vnl_vector_fixed<float,3> mean(2.5f, 1.2f, -0.85f);
    float var = 0.25f;

    float sigma = vcl_sqrt(var);

    const unsigned int n_samples = 500;

    bsta_gaussian_sphere<float,3> gauss_est;

    // generate samples
    vcl_vector<vnl_vector_fixed<float,3> > samples;
    vcl_vector<float> weights;
    for (unsigned int n=0; n<n_samples; ++n) {  
      vnl_vector_fixed<float,3> sample;
      for (unsigned int d=0; d<3; ++d) {
        sample[d] = mean[d] + sigma*(float)rand_gen.normal();
      }
      float weight = (float)rand_gen.drand32(0.0, 1.0);
      weights.push_back(weight);
      samples.push_back(sample);
    }
    bsta_fit_gaussian(samples, weights, gauss_est);
    vcl_cout << "mean = " << mean << vcl_endl;
    vcl_cout << "estimated mean = " << gauss_est.mean() << vcl_endl;
    vcl_cout << "variance = " << var << vcl_endl;
    vcl_cout << "estimated variance = " << gauss_est.covar() << vcl_endl;
    TEST_NEAR("3D spherical: Estimated mean maximum error is small" ,(gauss_est.mean() - mean).max_value(), 0, 0.1);

    TEST_NEAR("3D spherical: Estimated variance is correct", gauss_est.covar(), var, 0.1);
  }
  {
    vcl_cout << "Testing 3D Gaussian (independant)" << vcl_endl;
    // Test the fitting of independant gaussian
    vnl_vector_fixed<float,3> mean(2.5f, 1.2f, -0.85f);
    vnl_vector_fixed<float,3> covar_diag(0.3f, 0.09f, 0.55f);

    vnl_vector_fixed<float,3> sigmas(vcl_sqrt(covar_diag[0]),vcl_sqrt(covar_diag[1]),vcl_sqrt(covar_diag[2]));

    const unsigned int n_samples = 500;

    bsta_gaussian_indep<float,3> gauss_est;
    // generate samples
    vcl_vector<vnl_vector_fixed<float,3> > samples;
    vcl_vector<float> weights;
    for (unsigned int n=0; n<n_samples; ++n) {  
      vnl_vector_fixed<float,3> sample;
      for (unsigned int d=0; d<3; ++d) {
        sample[d] = mean[d] + sigmas[d]*(float)rand_gen.normal();
      }
      float weight = (float)rand_gen.drand32(0.0, 1.0);
      weights.push_back(weight);
      samples.push_back(sample);
    }
    bsta_fit_gaussian(samples, weights, gauss_est);

    vcl_cout << "mean = " << mean << vcl_endl;
    vcl_cout << "estimated mean = " << gauss_est.mean() << vcl_endl;
    vcl_cout << "variance = " << covar_diag << vcl_endl;
    vcl_cout << "estimated variance = " << gauss_est.covar() << vcl_endl;
    TEST_NEAR("3D indep: Estimated mean maximum error is small" ,(gauss_est.mean() - mean).max_value(), 0, 0.1);
    TEST_NEAR("3D indep: Estimated covariance maximum error is small" ,(gauss_est.covar() - covar_diag).max_value(), 0, 0.1);

  }
  {
    vcl_cout << "Testing 3D Gaussian (full covariance matrix)" << vcl_endl;
    // Test the fitting of independant gaussian
    vnl_vector_fixed<float,3> mean(5.5f, -2.2f, 0.25f);
    vnl_matrix_fixed<float,3,3> A(0.0f); // lower triangular matrix used to construct covariance
    A(0,0) = 1.5f; A(1,0) = 0.05f; A(1,1) = 1.1f; A(2,0) = 0.08f; A(2,1) = -0.10f; A(2,2) = 0.7f;
    vnl_matrix_fixed<float,3,3> covar = A * A.transpose();

    const unsigned int n_samples = 4000;

    bsta_gaussian_full<float,3> gauss_est;
    // generate samples
    vcl_vector<vnl_vector_fixed<float,3> > samples;
    vcl_vector<float> weights;
    for (unsigned int n=0; n<n_samples; ++n) {  
      vnl_vector_fixed<float,3> sample;
      vnl_vector_fixed<float,3> unit_rand;
      for (unsigned int d=0; d<3; ++d) {
        unit_rand[d] = (float)rand_gen.normal();
      }
      sample = mean + A * unit_rand;
      float weight = (float)rand_gen.drand32(0.0, 1.0);
      weights.push_back(weight);
      samples.push_back(sample);
    }
    bsta_fit_gaussian(samples, weights, gauss_est);
    vnl_matrix_fixed<float,3,3> covar_est = gauss_est.covar();

    vcl_cout << "mean = " << mean << vcl_endl;
    vcl_cout << "estimated mean = " << gauss_est.mean() << vcl_endl;
    vcl_cout << "covar = " << vcl_endl << covar << vcl_endl;
    vcl_cout << "estimated covar = " << vcl_endl << covar_est << vcl_endl;

    TEST_NEAR("3D full: Estimated mean maximum error is small" ,(gauss_est.mean() - mean).max_value(), 0, 0.1);

    float total_error = (covar - covar_est).absolute_value_max();
    TEST_NEAR("  Estimated covariance matrix is error is small", total_error, 0.0f, 0.25);
  }
  {
    // test EM fitting. 
    // TODO
    bsta_gaussian_sphere<float,1> gauss_est;
    vcl_vector<float> samples;
    vcl_vector<float> sample_prob;
    vcl_vector<float> alt_prob_density;
    float min_var = 0.01f;
    bsta_fit_gaussian(samples,sample_prob,alt_prob_density,gauss_est,min_var);
  }
    {
      // TODO
    bsta_gaussian_indep<float,3> gauss_est;
    vcl_vector<vnl_vector_fixed<float,3> > samples;
    vcl_vector<float> sample_prob;
    vcl_vector<float> alt_prob_density;
    vnl_vector_fixed<float,3> min_covar(0.01f);
    bsta_fit_gaussian(samples,sample_prob,alt_prob_density,gauss_est, min_covar);

  }
  {
      // TODO
    bsta_gaussian_full<float,3> gauss_est;
    vcl_vector<vnl_vector_fixed<float,3> > samples;
    vcl_vector<float> sample_prob;
    vcl_vector<float> alt_prob_density;
    vnl_matrix_fixed<float,3,3> min_covar(0.0f);
    min_covar(0,0) = 0.01f; min_covar(1,1) = 0.01f; min_covar(2,2) = 0.01f;
    bsta_fit_gaussian(samples,sample_prob,alt_prob_density,gauss_est, min_covar);

  }

  SUMMARY();
}
