#ifndef mbl_sample_stats_1d_h_
#define mbl_sample_stats_1d_h_
//:
// \file
// \brief Provides simple statistics on a 1D variable and stores the samples
// \author Graham Vincent

#include <vcl_stdexcept.h>
#include <vcl_iostream.h>
#include <vcl_vector.h>
#include <vnl/vnl_vector.h>
#include <vsl/vsl_fwd.h>
#include <mbl/mbl_stats_1d.h>

//: Provides simple statistics on a 1D variable and stores the samples
class mbl_sample_stats_1d
{
  vcl_vector<double> samples_;
  mbl_stats_1d stats_1d_;
  bool use_mvue_;

 public:

  //! Default ctor
  mbl_sample_stats_1d();

  //! ctor with a vcl_vector of samples
  mbl_sample_stats_1d(const vcl_vector<double> &samples);

  //! ctor with a vnl_vector of samples
  mbl_sample_stats_1d(const vnl_vector<double> &samples);

  ~mbl_sample_stats_1d();

  //: Sets type of variance normalistation
  // \param mvue if true (the dafault) the variance uses the "minimum variance unbiased estimator" which normalises by n_samples()-1
  //             else will normalise the variance by n_samples()
  void set_use_mvue(bool b) { use_mvue_=b; }

  //: Remove all data
  void clear();

  //: Add given observation
  void add_sample(double v);

  //: Number of samples
  unsigned n_samples() const;

  //! vector of samples
  const vcl_vector<double>& samples() const { return samples_; }

  //: Mean of current samples
  double mean() const ;

  //: Mean of absolutes current samples
  double mean_of_absolutes() const ;

  //: Median of current samples
  // Take care. if there are no samples, this method returns maxmimum double (a very large number)
  // Always check number of samples first
  double median() const;

  //: The last value within the n_th percentile of the distribution.
  // \note If there are no samples, this method returns maxmimum double (a very large number).
  // \sa quantile().
  double nth_percentile(int n) const;

  //: Calculate a value at a specified quantile \a q.
  // \param q Required quantile 0.0 <= q <= 1.0 
  // \note Linearly interpolates between the 2 sample values bracketing the specified quantile position.
  double quantile(double q) const;

  //: Standard deviation of current samples
  double sd() const;

  //: Standard error (i.e. sd of estimate of the mean)
  double stdError() const;

  //: Variance of current samples
  double variance() const;

  //: Returns the skewness of the samples
  double skewness() const;

  //: Returns the kurtosis of ths samples
  double kurtosis() const;

  //: Min of current samples
  // Take care. if there are no samples, this method returns maxmimum double
  // Always check number of samples first
  double min() const;

  //: Max of current samples
  // Take care. if there are no samples, this method returns -ve maximum double
  // Always check number of samples first
  double max() const;

  //: Sum of current samples
  double sum() const;

  //: Sum of squares of current samples
  double sum_squares() const;

  //: root mean square of current samples
  double rms() const;

  //: Add statistics together
  mbl_sample_stats_1d& operator+=(const mbl_sample_stats_1d& s1);

  //: Print summary of data
  void print_summary(vcl_ostream& os) const;

  //: Print all data.
  // \param delim Separate each value with this character/string.
  void print_all(vcl_ostream& os,
    const vcl_string& delim="\n") const;

  //: Version number for I/O
  short version_no() const;
  void b_write(vsl_b_ostream& bfs) const;
  void b_read(vsl_b_istream& bfs);

  //: Test for equality
  bool operator==(const mbl_sample_stats_1d& s) const;

  friend
    mbl_sample_stats_1d operator+(const mbl_sample_stats_1d& s1, const mbl_sample_stats_1d& s2);
};

///////////////////////////////////////////////////////////////////
// Some functions which are convenient when using the stats object
///////////////////////////////////////////////////////////////////

// Create a vector of doubles from the values in sample where the
// corresponding value in mask is greater than zero
template <class S, class M>
vcl_vector<double> mbl_apply_mask(const S &sample, const M &mask)
{
  if (sample.size()==0 || sample.size()!=mask.size()) throw vcl_runtime_error("Mask should be the same size as the sample and not empty\n");
  mbl_sample_stats_1d stats;
  typename S::const_iterator sit=sample.begin();
  typename M::const_iterator mit=mask.begin();
  vcl_vector<double> ret;
  for ( ; sit!=sample.end(); ++sit, ++mit)
  {
    if ((*mit))
    {
      ret.push_back(*sit);
    }
  }
  return ret;
}

//: Binary file stream output operator for class reference
void vsl_b_write(vsl_b_ostream& bfs, const mbl_sample_stats_1d& b);

//: Binary file stream input operator for class reference
void vsl_b_read(vsl_b_istream& bfs, mbl_sample_stats_1d& b);

//: Stream output operator for class reference
vcl_ostream& operator<<(vcl_ostream& os,const mbl_sample_stats_1d& stats);

//: Stream output operator for class reference
void vsl_print_summary(vcl_ostream& os,const mbl_sample_stats_1d& stats);

//: Print all data
void vsl_print_all(vcl_ostream& os, const mbl_sample_stats_1d& stats);

#endif // mbl_sample_stats_1d_h_
