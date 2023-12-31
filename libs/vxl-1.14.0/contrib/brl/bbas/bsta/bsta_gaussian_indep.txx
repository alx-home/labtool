// This is brl/bbas/bsta/bsta_gaussian_indep.txx
#ifndef bsta_gaussian_indep_txx_
#define bsta_gaussian_indep_txx_
//:
// \file

#include "bsta_gaussian_indep.h"
#include <vcl_limits.h>
#include <vnl/vnl_erf.h>

namespace
{
  //: Unrol the mahalanobis distance calculation
  template <class T, unsigned n, unsigned index>
  struct compute_sqr_mahalanobis
  {
    static inline T value(const vnl_vector_fixed<T,n>& d,
                          const vnl_vector_fixed<T,n>& covar)
    {
      return d[index-1]*d[index-1]/covar[index-1]
        + compute_sqr_mahalanobis<T,n,index-1>::value(d,covar);
    }
  };

  //: base case
  //  This is partial specialization: expect MSVC6 to complain
  template <class T, unsigned n>
  struct compute_sqr_mahalanobis<T,n,0>
  {
    static inline T value(const vnl_vector_fixed<T,n>& d,
                          const vnl_vector_fixed<T,n>& covar)
    { return 0; }
  };


  //: Unrol the determinant calculation
  template <class T, unsigned n, unsigned index>
  struct determinant
  {
    static inline T value(const vnl_vector_fixed<T,n>& covar)
    {
      return covar[index-1]*determinant<T,n,index-1>::value(covar);
    }
  };

  //: base case
  //  This is partial specialization: expect MSVC6 to complain
  template <class T, unsigned n>
  struct determinant<T,n,0>
  {
    static inline T value(const vnl_vector_fixed<T,n>& /*covar*/)
    { return 1; }
  };
};


//: The squared Mahalanobis distance to this point
template <class T, unsigned int n>
T
bsta_gaussian_indep<T,n>::sqr_mahalanobis_dist(const vnl_vector_fixed<T,n>& pt) const
{
  if (det_covar_<=T(0))
    return vcl_numeric_limits<T>::infinity();
  vnl_vector_fixed<T,n> d = bsta_gaussian<T,n>::mean_-pt;
  return compute_sqr_mahalanobis<T,n,n>::value(d,diag_covar_);
}


//: The determinant of the covariance matrix
template <class T, unsigned int n>
void
bsta_gaussian_indep<T,n>::compute_det()
{
  det_covar_ = determinant<T,n,n>::value(diag_covar_);
}

//: Unrol the compute probability calculation
//  The general induction step
template <class T, unsigned n, unsigned index>
struct compute_probability_box
{
  static inline T value(const vnl_vector_fixed<T,n>& min_minus_mean,
                        const vnl_vector_fixed<T,n>& max_minus_mean,
                        const vnl_vector_fixed<T,n>& covar
                       )
  {
    if (covar[index]<=T(0))
      return vcl_numeric_limits<T>::infinity();
    double sigma_sq_2 = 2.0*static_cast<double>(covar[index]);
    double s2 = 1/vcl_sqrt(sigma_sq_2);
    double temp = vnl_erf(max_minus_mean[index]*s2);
    temp -= vnl_erf(min_minus_mean[index]*s2);
    T res = static_cast<T>(0.5*temp);
    res *= compute_probability_box<T,n,index-1>::value(min_minus_mean,
                                                       max_minus_mean,
                                                       covar);
    return res;
  }
};

//: base case
//  This is partial specialization: expect MSVC6 to complain
template <class T, unsigned n>
struct compute_probability_box<T,n,0>
{
  static inline T value(const vnl_vector_fixed<T,n>& min_minus_mean,
                        const vnl_vector_fixed<T,n>& max_minus_mean,
                        const vnl_vector_fixed<T,n>& covar)
  {
    if (covar[0]<=T(0))
      return vcl_numeric_limits<T>::infinity();
    double sigma_sq_2 = 2.0*static_cast<double>(covar[0]);
    double s2 = 1/vcl_sqrt(sigma_sq_2);
    double temp = vnl_erf(max_minus_mean[0]*s2);
    temp -= vnl_erf(min_minus_mean[0]*s2);
    return static_cast<T>(0.5*temp);
  };
};

//: The probability that a sample lies inside a n-d bounding box
//  \note min_pt and max_pt are the corners of the box
template <class T, unsigned int n>
T bsta_gaussian_indep<T,n>::probability(const vnl_vector_fixed<T,n>& min_pt,
                                        const vnl_vector_fixed<T,n>& max_pt) const
{
  vnl_vector_fixed<T,n> min_minus_mean = min_pt-bsta_gaussian<T,n>::mean_;
  vnl_vector_fixed<T,n> max_minus_mean = max_pt-bsta_gaussian<T,n>::mean_;
  return compute_probability_box<T, n, n-1>::value(min_minus_mean,
                                                   max_minus_mean,
                                                   diag_covar_);
}


#define BSTA_GAUSSIAN_INDEP_INSTANTIATE(T,n) \
template class bsta_gaussian_indep<T,n >


#endif // bsta_gaussian_indep_txx_
