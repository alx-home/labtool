#ifndef mfpf_grad_corr2d_h_
#define mfpf_grad_corr2d_h_
//:
// \file
// \brief Searches over a grid using normalised correllation
// \author Tim Cootes

#include <mfpf/mfpf_point_finder.h>
#include <vgl/vgl_fwd.h>
#include <vcl_iosfwd.h>

//: Searches over a grid using normalised correllation.
class mfpf_grad_corr2d : public mfpf_point_finder
{
 private:
  //: Kernel reference point (in kni_ x knj_ grid)
  double ref_x_;
  //: Kernel reference point (in kni_ x knj_ grid)
  double ref_y_;

  //: Relative size of region used for estimating overlap
  //  If 0.5, then overlap requires pt inside central 50% of region.
  double overlap_f_;

  //: Filter x-gradient kernel to search with
  vil_image_view<double> kernel_x_;

  //: Filter y-gradient kernel to search with
  vil_image_view<double> kernel_y_;

  //: Define default values
  void set_defaults();

    //: Compute gradient image around a patch
  void diff_image(const vimt_image_2d_of<float>& image,
                  const vgl_point_2d<double>& p,
                  const vgl_vector_2d<double>& u,
                  vil_image_view<double>& grad_x,
                  vil_image_view<double>& grad_y,
                  int search_ni=0, int search_nj=0);

 public:

  // Dflt ctor
  mfpf_grad_corr2d();

  // Destructor
  virtual ~mfpf_grad_corr2d();

  //: Define filter kernel to search with.
  //  Reference point set to the centre
  void set(const vil_image_view<double>& kx, const vil_image_view<double>& ky);

  //: Define filter kernel to search with
  void set(const vil_image_view<double>& kx, const vil_image_view<double>& ky,
           double ref_x, double ref_y);

  //: Define filter kernel to search with, expressed as a vector
  virtual bool set_model(const vcl_vector<double>& v);

  //: Number of dimensions in the model
  virtual unsigned model_dim();

  //: Relative size of region used for estimating overlap
  //  If 0.5, then overlap requires pt inside central 50% of region.
  void set_overlap_f(double);

  //: Filter x-gradient kernel to search with
  const vil_image_view<double>& kernel_x() const { return kernel_x_; }

  //: Filter y-gradient kernel to search with
  const vil_image_view<double>& kernel_y() const { return kernel_y_; }

  //: Filter kernel to search with, expressed as a vector
  void get_kernel_vector(vcl_vector<double>& v) const;

  //: Get sample of region around specified point in image
  virtual void get_sample_vector(const vimt_image_2d_of<float>& image,
                                 const vgl_point_2d<double>& p,
                                 const vgl_vector_2d<double>& u,
                                 vcl_vector<double>& v);

  //: Radius of circle containing modelled region
  virtual double radius() const;

  //: Evaluate match at p, using u to define scale and orientation
  // Returns -1*edge strength at p along direction u
  virtual double evaluate(const vimt_image_2d_of<float>& image,
                          const vgl_point_2d<double>& p,
                          const vgl_vector_2d<double>& u);

  //: Evaluate match at in a region around p
  // Returns a qualtity of fit at a set of positions.
  // response image (whose size and transform is set inside the
  // function), indicates the points at which the function was
  // evaluated.  response(i,j) is the fit at the point
  // response.world2im().inverse()(i,j).  The world2im() transformation
  // may be affine.
  virtual void evaluate_region(const vimt_image_2d_of<float>& image,
                               const vgl_point_2d<double>& p,
                               const vgl_vector_2d<double>& u,
                               vimt_image_2d_of<double>& response);

  //: Search given image around p, using u to define scale and angle
  //  On exit, new_p defines position of the best nearby match.
  //  Returns a qualtity of fit measure at that
  //  point (the smaller the better).
  virtual double search_one_pose(const vimt_image_2d_of<float>& image,
                                 const vgl_point_2d<double>& p,
                                 const vgl_vector_2d<double>& u,
                                 vgl_point_2d<double>& new_p);

  // Returns true if p is inside region at given pose
  // Actually only checks if p is inside bounding box,
  // scaled by a factor f about the reference point.
  bool is_inside(const mfpf_pose& pose,
                 const vgl_point_2d<double>& p,
                 double f=1.0) const;

  //: Return true if modelled regions at pose1 and pose2 overlap
  //  Checks if reference point of one is inside region of other
  virtual bool overlap(const mfpf_pose& pose1,
                       const mfpf_pose& pose2) const;

  //: Generate points in ref frame that represent boundary
  //  Points of a contour around the shape.
  //  Used for display purposes.
  virtual void get_outline(vcl_vector<vgl_point_2d<double> >& pts) const;

  //: Return an image of the kernel
  virtual void get_image_of_model(vimt_image_2d_of<vxl_byte>& image) const;

  //: Version number for I/O
  short version_no() const;

  //: Name of the class
  virtual vcl_string is_a() const;

  //: Create a copy on the heap and return base class pointer
  virtual mfpf_point_finder* clone() const;

  //: Print class to os
  virtual void print_summary(vcl_ostream& os) const;

  //: Save class to binary file stream
  virtual void b_write(vsl_b_ostream& bfs) const;

  //: Load class from binary file stream
  virtual void b_read(vsl_b_istream& bfs);

  //: Test equality
  bool operator==(const mfpf_grad_corr2d& nc) const;
};

#endif
