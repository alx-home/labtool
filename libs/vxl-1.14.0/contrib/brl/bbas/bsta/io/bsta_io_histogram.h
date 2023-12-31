// This is brl/bbas/bsta/io/bsta_io_histogram.h
#ifndef bsta_io_histogram_h_
#define bsta_io_histogram_h_
//:
// \file
// \brief Binary I/O for bsta_histogram
// \author J.L. Mundy
// \date February 29, 2008
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <bsta/bsta_histogram.h>
#include <bsta/bsta_joint_histogram.h>
#include <bsta/bsta_histogram_sptr.h>
#include <bsta/bsta_joint_histogram_sptr.h>
#include <vsl/vsl_binary_io.h>
#include <vsl/vsl_vector_io.h>
#include <vbl/vbl_array_2d.h>
#include <vbl/io/vbl_io_array_2d.h>
//: Binary save bsta_histogram to stream.
template <class T>
void
vsl_b_write(vsl_b_ostream &os, const bsta_histogram<T>& h)
{
  const short io_version_no = 1;
  vsl_b_write(os, io_version_no);
  bsta_histogram_base::bsta_hist_type type = h.type_;
  int itype = static_cast<int>(type);
  int nbins = h.nbins();
  T min = h.min();
  T max = h.max();
  T min_prob = h.min_prob();
  vcl_vector<T> values = h.value_array();
  vcl_vector<T> counts = h.count_array();
  vsl_b_write(os, itype);
  vsl_b_write(os, nbins);
  vsl_b_write(os, min);
  vsl_b_write(os, max);
  vsl_b_write(os, min_prob);
  vsl_b_write(os, values);
  vsl_b_write(os, counts);
}

//: Binary load bsta_histogram from stream.
template <class T>
void
vsl_b_read(vsl_b_istream &is, bsta_histogram<T>& h, bool skip = false)
{
  short ver;
  int itype = 0;
  if (!skip){
  vsl_b_read(is, ver);
  if (ver != 1)
    return;
  vsl_b_read(is, itype);
  }
  int nbins;
  T min, max, min_prob;
  vcl_vector<T> values, counts;
  vsl_b_read(is, nbins);
  vsl_b_read(is, min);
  vsl_b_read(is, max);
  vsl_b_read(is, min_prob);
  vsl_b_read(is, values);
  vsl_b_read(is, counts);
  bsta_histogram<T> temp(min, max, nbins, min_prob);
  for (unsigned i = 0; i<static_cast<unsigned>(nbins); ++i)
    temp.upcount(values[i], counts[i]);
  h = temp;
}

//: Print summary
template <class T>
void
vsl_print_summary(vcl_ostream &os, const bsta_histogram<T>& h)
{
  os << "bsta_histogram\n";
  h.print(os);
}

//: Binary save bsta_joint_histogram to stream.
template <class T>
void
vsl_b_write(vsl_b_ostream &os, const bsta_joint_histogram<T>& h)
{
  int nbins_a = h.nbins_a();
  int nbins_b = h.nbins_b();
  T min_a = h.min_a();
  T max_a = h.max_a();
  T min_b = h.min_b();
  T max_b = h.max_b();
  T min_prob = h.min_prob();
  vbl_array_2d<T> counts = h.counts();
  const short io_version_no = 1;
  vsl_b_write(os, io_version_no);
  vsl_b_write(os, nbins_a);
  vsl_b_write(os, min_a);
  vsl_b_write(os, max_a);
  vsl_b_write(os, nbins_b);
  vsl_b_write(os, min_b);
  vsl_b_write(os, max_b);
  vsl_b_write(os, min_prob);
  vsl_b_write(os, counts);
}

//: Binary load bsta_joint_histogram from stream.
template <class T>
void
vsl_b_read(vsl_b_istream &is, bsta_joint_histogram<T>& h)
{
  short ver;
  vsl_b_read(is, ver);
  if (ver != 1)
    return;
  int nbins_a, nbins_b;
  T min_a, max_a, min_b, max_b, min_prob;
  vbl_array_2d<T> counts;
  vsl_b_read(is, nbins_a);
  vsl_b_read(is, min_a);
  vsl_b_read(is, max_a);
  vsl_b_read(is, nbins_b);
  vsl_b_read(is, min_b);
  vsl_b_read(is, max_b);
  vsl_b_read(is, min_prob);
  vsl_b_read(is, counts);
  bsta_joint_histogram<T> temp(min_a, max_a, nbins_a, min_b, max_b, nbins_b, min_prob);
  unsigned nr = counts.rows(), nc = counts.cols();
  for (unsigned r = 0; r<nr; ++r)
    for (unsigned c = 0; c<nc; ++c)
      temp.set_count(r, c, counts[r][c]);
  h = temp;
}

//: Print summary
template <class T>
void
vsl_print_summary(vcl_ostream &os, const bsta_joint_histogram<T>& h)
{
  os << "bsta_joint_histogram\n";
  h.print(os);
}

//: Implement for key basic types
void vsl_b_write(vsl_b_ostream &os, const bsta_histogram_sptr& hptr)
{
  bsta_histogram<float>* hf = dynamic_cast<bsta_histogram<float>*>(hptr.ptr());
  if (hf) { vsl_b_write(os, *hf); return; }
  bsta_histogram<double>* hd=dynamic_cast<bsta_histogram<double>*>(hptr.ptr());
  if (hd) { vsl_b_write(os, *hd); return; }
}

void vsl_b_read(vsl_b_istream &is, bsta_histogram_sptr& hptr)
{
  short ver;
  vsl_b_read(is, ver);
  if (ver != 1)
    return;
  hptr = 0;
  int itype = 0;
  vsl_b_read(is, itype);
  bsta_histogram_base::bsta_hist_type type =
    static_cast<bsta_histogram_base::bsta_hist_type>(itype);
  if (type == bsta_histogram_base::HIST_TYPE_UNKNOWN) return;
  if (type == bsta_histogram_base::HIST_TYPE_FLOAT)
  {
    bsta_histogram<float> h;
    vsl_b_read(is, h, true);
    hptr = new bsta_histogram<float>(h);
    return;
  }
  if (type == bsta_histogram_base::HIST_TYPE_DOUBLE)
  {
    bsta_histogram<double> h;
    vsl_b_read(is, h, true);
    hptr = new bsta_histogram<double>(h);
    return;
  }
}

void vsl_b_write(vsl_b_ostream &os, const bsta_joint_histogram_sptr& /*hptr*/);

void vsl_b_read(vsl_b_istream &is, bsta_joint_histogram_sptr& /*hptr*/);

#endif // bsta_io_histogram_h_
