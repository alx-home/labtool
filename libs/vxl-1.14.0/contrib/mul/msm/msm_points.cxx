#include "msm_points.h"
//:
// \file
// \brief Set of 2D points, stored in a vnl_vector (x0,y0,x1,y1...)
// \author Tim Cootes

#include <vcl_iostream.h>
#include <vsl/vsl_indent.h>
#include <vsl/vsl_binary_io.h>
#include <vnl/io/vnl_io_vector.h>
#include <vgl/vgl_point_2d.h>
#include <vcl_cstdlib.h>  // for vcl_atoi() & vcl_abort()


//=======================================================================
// Dflt ctor
//=======================================================================

msm_points::msm_points()
{
}

//=======================================================================
// Destructor
//=======================================================================

msm_points::~msm_points()
{
}

//: Set this to be equal to supplied points
void msm_points::set_points(const vcl_vector<vgl_point_2d<double> >& pts)
{
  unsigned n=pts.size();
  v_.set_size(2*n);
  double* v=v_.data_block();
  vcl_vector<vgl_point_2d<double> >::const_iterator p = pts.begin();
  for (;p!=pts.end();v+=2,++p)
  {
    v[0] = p->x();
    v[1] = p->y();
  }
}

//: Copy points into pts
void msm_points::get_points(vcl_vector<vgl_point_2d<double> >& pts) const
{
  pts.resize(size());
  const double* v=v_.data_block();
  vcl_vector<vgl_point_2d<double> >::iterator p = pts.begin();
  for (;p!=pts.end();v+=2,++p)
  {
    p->x()=v[0];
    p->y()=v[1];
  }
}

//: Return centre of gravity of points
vgl_point_2d<double> msm_points::cog() const
{
  const double* v=v_.data_block();
  unsigned n=size();
  const double* end_v=v+2*n;
  double cx=0.0,cy=0.0;
  for (;v!=end_v;v+=2) { cx+=v[0]; cy+=v[1]; }
  if (n>0) { cx/=n; cy/=n; }
  return vgl_point_2d<double>(cx,cy);
}

//: Return RMS of distance of points to CoG.
double msm_points::scale() const
{
  vgl_point_2d<double> c;
  double s;
  get_cog_and_scale(c,s);
  return s;
}

//: Compute centre of gravity and RMS distance to CoG
void msm_points::get_cog_and_scale(vgl_point_2d<double>& cog, double& scale) const
{
  unsigned n=size();
  if (n==0) { cog=vgl_point_2d<double>(0,0); scale=0; return; }

  const double* v=v_.data_block();
  const double* end_v=v+2*n;

  // compute sum and sum of squares of elements
  double sx=0.0,s2x=0.0,sy=0.0,s2y=0.0;
  for (;v!=end_v;v+=2)
  {
    sx+=v[0];  s2x+=v[0]*v[0];
    sy+=v[1];  s2y+=v[1]*v[1];
  }

  double cx=sx/n, cy=sy/n;
  double L2=(s2x+s2y)/n-cx*cx-cy*cy;
  scale = 0.0;
  if (L2>0) scale=vcl_sqrt(L2);
  cog=vgl_point_2d<double>(cx,cy);
}

//: Scale current points by s about the origin
void msm_points::scale_by(double s)
{
  if (s==1.0) return;
  v_*=s;
}

//: Translate current points by (tx,ty)
void msm_points::translate_by(double tx, double ty)
{
  if (tx==0.0 && ty==0.0) return;
  double* v=v_.data_block();
  double* end_v=v+2*size();
  for (;v!=end_v;v+=2)
  {
    v[0]+=tx;
    v[1]+=ty;
  }
}

//: Transform current points with t
void msm_points::transform_by(const vimt_transform_2d& t)
{
  double* v=v_.data_block();
  double* end_v=v+2*size();
  for (;v!=end_v;v+=2)
  {
    vgl_point_2d<double> p = t(v[0],v[1]);
    v[0]=p.x(); v[1]=p.y();
  }
}

//: Bounding box of points
void msm_points::get_bounds(vgl_point_2d<double>& b_lo,
                            vgl_point_2d<double>& b_hi) const
{
  if (size()==0)
  {
    b_lo=vgl_point_2d<double>(0,0);
    b_hi=vgl_point_2d<double>(0,0);
    return;
  }

  const double* v=v_.data_block();
  const double* end_v=v+2*size();
  b_lo=vgl_point_2d<double>(v[0],v[1]);
  b_hi=b_lo;
  for (;v!=end_v;v+=2)
  {
    if (v[0]<b_lo.x()) b_lo.x()=v[0];
    if (v[0]>b_hi.x()) b_hi.x()=v[0];
    if (v[1]<b_lo.y()) b_lo.y()=v[1];
    if (v[1]>b_hi.y()) b_hi.y()=v[1];
  }
}

//: Equality test
bool msm_points::operator==(const msm_points& points)
{
  if (points.v_.size()!=v_.size()) return false;
  if (size()==0) return true;
  double ssd=vnl_vector_ssd(points.v_,v_);
  return (vcl_fabs(ssd/size())<1e-3);
}

// ===============================================================
// ========= Text IO =============================================

//: Write out points to named text file
//  Returns true if successful.
bool msm_points::write_text_file(const vcl_string& path) const
{
  vcl_ofstream afs(path.c_str(),vcl_ios_out);
  if (!afs) return false;

  unsigned n = size();
  const double* v = v_.data_block();
  afs << "version: 1\nn_points: " << n << "\n{" << '\n';
  for (unsigned i=0;i<n;++i)
  {
    // Write out elements of point on a single line
    afs << v[2*i] << ' ' << v[2*i+1] << '\n';
  }
  afs << '}' << '\n';

  afs.close();

  return true;
}

static bool read_points(vcl_istream& afs,
                        vnl_vector<double>& vec, unsigned n)
{
  if (n>999999)
  {
    vcl_cerr << "msm_points read_points() :\n"
             << "Bizarre number of points specified : " << n << vcl_endl;
    return false;
  }

  vec.set_size(2*n);
  double* v = vec.data_block();
  for (unsigned i=0;i<n;i++,v+=2)
  {
    if (afs.eof())
    {
      vcl_cerr << "msm_points read_points() :\n"
               << "EOF reached after reading "
               << i << " of " << n << " points.\n";
      return false;
    }
    afs>>v[0]>>v[1];
  }

  return true;
}

//: Read in points from named text file
//  Returns true if successful.
bool msm_points::read_text_file(const vcl_string& path)
{
  vcl_ifstream afs( path.c_str(), vcl_ios_in );
  if (!afs) return false;

  vnl_vector<double> vec;  // New data
  vcl_string label;
  afs >> label;
  if (label != "version:")
  {
    // Attempt to load in old format
    int n = vcl_atoi(label.c_str());
    if (n>0)
    {
      return read_points(afs, v_, n);
    }

    vcl_cerr << "Expecting <version:> got <" << label << vcl_endl;
    return false;
  }

  int ver;
  afs >> ver;
  if (ver!=1)
  {
    vcl_cerr << "msm_points::read_text_file() :\n"
             << "Cannot cope with version number " << ver << vcl_endl;
    return false;
  }

  // Possible extra data - ignore it
  int image_nx, image_ny, image_nz;
  int n = -1;

  afs >> label;
  while (!afs.eof()  && label != "}")
  {
    if (label.size()>=2 && label[0]=='/' && label[1]=='/')
    {
      // Comment: Read to the end of the line
      char buf[256];
      afs.get(buf,256);
    }
    else
    if (label=="image_size_x:")
      afs>>image_nx;
    else if (label=="image_size_y:")
      afs>>image_ny;
    else if (label=="image_size_z:")
      afs>>image_nz;
    else if (label=="n_points:")
      afs>>n;
    else if (label=="{")
    {
      if (!read_points(afs, v_, n))
        return false;
    }
    else
    {
      vcl_cerr << "Unexpected label: <" << label << vcl_endl;
      return false;
    }

    afs>>label;
  }

  return true;
}


//=======================================================================
// Method: version_no
//=======================================================================

short msm_points::version_no() const
{
  return 1;
}

//=======================================================================
// Method: is_a
//=======================================================================

vcl_string msm_points::is_a() const
{
  return vcl_string("msm_points");
}

//=======================================================================
// Method: print
//=======================================================================

  // required if data is present in this class
void msm_points::print_summary(vcl_ostream& os) const
{
  os << size() << " pts: ";
  for (unsigned i=0;i<size();++i)
    os << '(' << v_[2*i] << ',' << v_[2*i+1] << ')';
}

//=======================================================================
// Method: save
//=======================================================================

  // required if data is present in this class
void msm_points::b_write(vsl_b_ostream& bfs) const
{
  vsl_b_write(bfs,version_no());
  vsl_b_write(bfs,v_);
}

//=======================================================================
// Method: load
//=======================================================================

  // required if data is present in this class
void msm_points::b_read(vsl_b_istream& bfs)
{
  short version;
  vsl_b_read(bfs,version);
  switch (version)
  {
    case (1):
      vsl_b_read(bfs,v_);
      break;
    default:
      vcl_cerr << "msm_points::b_read() :\n"
               << "Unexpected version number " << version << vcl_endl;
      vcl_abort();
  }
}


//=======================================================================
// Associated function: operator<<
//=======================================================================

void vsl_b_write(vsl_b_ostream& bfs, const msm_points& b)
{
  b.b_write(bfs);
}

//=======================================================================
// Associated function: operator>>
//=======================================================================

void vsl_b_read(vsl_b_istream& bfs, msm_points& b)
{
  b.b_read(bfs);
}

//=======================================================================
// Associated function: operator<<
//=======================================================================

vcl_ostream& operator<<(vcl_ostream& os,const msm_points& b)
{
  os << b.is_a() << ": ";
  vsl_indent_inc(os);
  b.print_summary(os);
  vsl_indent_dec(os);
  return os;
}

//: Stream output operator for class reference
void vsl_print_summary(vcl_ostream& os,const msm_points& b)
{
 os << b;
}
