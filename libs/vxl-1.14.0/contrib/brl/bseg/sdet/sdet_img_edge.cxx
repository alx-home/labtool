// This is brl/bseg/sdet/sdet_img_edge.cxx

#include "sdet_img_edge.h"

#include <sdet/sdet_detector.h>
#include <bsta/bsta_gaussian_sphere.h>
#include <brip/brip_vil_float_ops.h>
#include <vdgl/vdgl_digital_curve.h>
#include <vdgl/vdgl_edgel.h>
#include <vdgl/vdgl_edgel_chain.h>
#include <vdgl/vdgl_interpolator.h>
#include <vtol/vtol_edge_2d.h>
#include <bil/algo/bil_edt.h>
#include <vil/vil_convert.h>
#include <vnl/algo/vnl_gaussian_kernel_1d.h>
#include <vnl/algo/vnl_chi_squared.h>
#include <vnl/vnl_vector_fixed.h>
#include <vil/vil_new.h>
#include <vnl/vnl_math.h>
#include <vcl_iostream.h>
#include <vcl_fstream.h>
#include <vcl_cmath.h>
#include <vcl_string.h>
#include <vcl_vector.h>
#include <vcl_cassert.h>

vil_image_view<vxl_byte> sdet_img_edge::detect_edges(vil_image_view<vxl_byte> img,
                                                     double noise_multiplier,
                                                     double smooth,
                                                     bool automatic_threshold,
                                                     bool junctionp,
                                                     bool aggressive_junction_closure)
{
  if ( img.nplanes() >= 3 )
  {
    vil_image_view<vxl_byte> img_rgb;
    img_rgb.deep_copy(img);
    vil_convert_planes_to_grey(img_rgb,img);
  }

  // set parameters for the edge detector
  sdet_detector_params dp;
  dp.noise_multiplier = (float)noise_multiplier;
  dp.smooth = (float)smooth;
  dp.automatic_threshold = automatic_threshold;
  dp.junctionp = junctionp;
  dp.aggressive_junction_closure = aggressive_junction_closure;

  // detect edgels from the input image
  sdet_detector detector(dp);
  vil_image_resource_sptr img_res_sptr = vil_new_image_resource_of_view(img);
  detector.SetImage(img_res_sptr);
  detector.DoContour();
  vcl_vector<vtol_edge_2d_sptr> * edges = detector.GetEdges();

  // initialize the output edge image
  vil_image_view<vxl_byte> img_edge(img.ni(),img.nj(),1);
  img_edge.fill(0);

  // iterate over each connected edge component
  for (vcl_vector<vtol_edge_2d_sptr>::iterator eit = edges->begin(); eit != edges->end(); eit++)
  {
    vsol_curve_2d_sptr c = (*eit)->curve();
    vdgl_digital_curve_sptr dc = c->cast_to_vdgl_digital_curve();
    if (!dc)
      continue;
    vdgl_interpolator_sptr intp = dc->get_interpolator();
    vdgl_edgel_chain_sptr ec = intp->get_edgel_chain();

    // iterate over each point in the connected edge component
    for (unsigned j=0; j<ec->size(); j++) {
      vdgl_edgel curr_edgel = ec->edgel(j);
      int cr_x = (int)curr_edgel.x();
      int cr_y = (int)curr_edgel.y();

      // set the current edge pixel in the edge image
      img_edge(cr_x,cr_y) = 255;
    }
  }

  // Following loop removes the edges in the image boundary
  int temp_index = img_edge.nj()-1;
  for (unsigned i=0; i<img_edge.ni(); i++) {
    img_edge(i,0) = 0;
    img_edge(i,temp_index) = 0;
  }
  temp_index = img_edge.ni()-1;
  for (unsigned j=0; j<img_edge.nj(); j++) {
    img_edge(0,j) = 0;
    img_edge(temp_index,j) = 0;
  }

  return img_edge;
}

static double angle_0_360(double angle)
{
  double ang = angle;
  while (ang<0)
    ang += (2.0*vnl_math::pi);
  while (ang > 2.0*vnl_math::pi)
    ang -= (2.0*vnl_math::pi);
  return ang;
}

vil_image_view<float>
sdet_img_edge::detect_edge_tangent(vil_image_view<vxl_byte> img,
                                   double noise_multiplier,
                                   double smooth,
                                   bool automatic_threshold,
                                   bool junctionp,
                                   bool aggressive_junction_closure)
{
  // set parameters for the edge detector
  sdet_detector_params dp;
  dp.noise_multiplier = (float)noise_multiplier;
  dp.smooth = (float)smooth;
  dp.automatic_threshold = automatic_threshold;
  dp.junctionp = junctionp;
  dp.aggressive_junction_closure = aggressive_junction_closure;

  // detect edgels from the input image
  sdet_detector detector(dp);
  vil_image_resource_sptr img_res_sptr = vil_new_image_resource_of_view(img);
  detector.SetImage(img_res_sptr);
  detector.DoContour();
  vcl_vector<vtol_edge_2d_sptr> * edges = detector.GetEdges();

  // initialize the output edge image
  vil_image_view<float> edge_img(img.ni(),img.nj(),3);
  edge_img.fill(-1.0f);

  // iterate over each connected edge component
  for (vcl_vector<vtol_edge_2d_sptr>::iterator eit = edges->begin(); eit != edges->end(); eit++)
  {
    vsol_curve_2d_sptr c = (*eit)->curve();
    vdgl_digital_curve_sptr dc = c->cast_to_vdgl_digital_curve();
    if (!dc)
      continue;
    vdgl_interpolator_sptr intp = dc->get_interpolator();
    vdgl_edgel_chain_sptr ec = intp->get_edgel_chain();
    unsigned n = ec->size();
    if (n<3) continue; //can't estimate edge tangent on short chains
    //special case at start
    vdgl_edgel e0 = ec->edgel(0);
    vdgl_edgel e1 = ec->edgel(1);
    double e0x  = e0.x(), e0y = e0.y();
    double e1x  = e1.x(), e1y = e0.y();
    if (e0x<0||e0y<0) continue;
    double ang = angle_0_360(vcl_atan2(e1y-e0y, e1x-e0x));
    unsigned x0 = static_cast<unsigned>(e0x);
    unsigned y0 = static_cast<unsigned>(e0y);
    edge_img(x0, y0, 0) = static_cast<float>(e0x);
    edge_img(x0, y0, 1) = static_cast<float>(e0y);
    edge_img(x0, y0, 2) = static_cast<float>(ang);
    //special case at end of chain
    vdgl_edgel enm2 = ec->edgel(n-2);
    vdgl_edgel enm1 = ec->edgel(n-1);
    double enm2x  = enm2.x(), enm2y = enm2.y();
    double enm1x  = enm1.x(), enm1y = enm1.y();
    if (enm1x<0||enm1y<0) continue;
    double angnm1 = angle_0_360(vcl_atan2(enm1y-enm2y, enm1x-enm2x));
    unsigned xnm1 = static_cast<unsigned>(enm1x);
    unsigned ynm1 = static_cast<unsigned>(enm1y);
    edge_img(xnm1, ynm1, 0) = static_cast<float>(enm1x);
    edge_img(xnm1, ynm1, 1) = static_cast<float>(enm1y);
    edge_img(xnm1, ynm1, 2) = static_cast<float>(angnm1);
    // the general case
    for (unsigned j=1; j<n-1; j++) {
      vdgl_edgel pe = ec->edgel(j-1);
      vdgl_edgel ce = ec->edgel(j);
      vdgl_edgel ne = ec->edgel(j+1);
      double pex  = pe.x(), pey = pe.y();
      double cex  = ce.x(), cey = ce.y();
      double nex  = ne.x(), ney = ne.y();
      if (cex<0||cey<0) continue;
      double angle = angle_0_360(vcl_atan2(ney-pey, nex-pex));
      unsigned xc = static_cast<unsigned>(cex);
      unsigned yc = static_cast<unsigned>(cey);
      // set the current edge pixel in the edge image
      edge_img(xc, yc, 0) = static_cast<float>(cex);
      edge_img(xc, yc, 1) = static_cast<float>(cey);
      edge_img(xc, yc, 2) = static_cast<float>(angle);
    }
  }

  // Following loop removes the edges in the image boundary
  int temp_index = edge_img.nj()-1;
  for (unsigned i=0; i<edge_img.ni(); i++) {
    edge_img(i,0,0) = -1;     edge_img(i,0,1) = -1;
    edge_img(i,temp_index,0) = -1;
    edge_img(i,temp_index,1) = -1;
  }
  temp_index = edge_img.ni()-1;
  for (unsigned j=0; j<edge_img.nj(); j++) {
    edge_img(0,j,0) = -1;     edge_img(0,j,1) = -1;
    edge_img(temp_index,j,0) = -1;
    edge_img(temp_index,j,1) = -1;
  }
  return edge_img;
}

void sdet_img_edge::edge_distance_transform(vil_image_view<vxl_byte>& inp_image, vil_image_view<float>& out_edt)
{
  vil_image_view<vxl_byte> edge_image_negated(inp_image);
  vil_math_scale_and_offset_values<vxl_byte,double>(edge_image_negated,-1.0,255.0);

  unsigned ni = edge_image_negated.ni();
  unsigned nj = edge_image_negated.nj();

  vil_image_view<vxl_uint_32> curr_image_edt(ni,nj,1);
  for (unsigned i=0; i<ni; i++) {
    for (unsigned j=0; j<nj; j++) {
      curr_image_edt(i,j) = edge_image_negated(i,j);
    }
  }

  bil_edt_maurer(curr_image_edt);

  out_edt.set_size(ni,nj,1);
  for (unsigned i=0; i<ni; i++) {
    for (unsigned j=0; j<nj; j++) {
      out_edt(i,j) = vcl_sqrt((float)curr_image_edt(i,j));
    }
  }
}


/************************************************************************/
/* Functions related to estimating edge probability given an edge image */
/************************************************************************/

vil_image_view<float> sdet_img_edge::multiply_image_with_gaussian_kernel(vil_image_view<float> img, double gaussian_sigma)
{
  vil_image_view<float> ret_img(img.ni(),img.nj(),1);

  vnl_gaussian_kernel_1d gaussian(gaussian_sigma);

  for (unsigned i=0; i<img.ni(); i++) {
    for (unsigned j=0; j<img.nj(); j++) {
      ret_img(i,j) = (float)gaussian.G((double)img(i,j));
    }
  }

  return ret_img;
}

vbl_array_2d<float> sdet_img_edge::get_spherical_gaussian_kernel(const int size, const float sigma)
{
  assert(size>=3 && size%2==1);

  vbl_array_2d<float> kernel(size,size,0.0f);

  vnl_vector_fixed<float,2> mean(0.0f);
  float variance = (sigma*sigma);
  bsta_gaussian_sphere<float,2> gaussian(mean,variance);

  int center = (size-1)/2;

  vnl_vector_fixed<float,2> min_pt;
  vnl_vector_fixed<float,2> max_pt;
  for (int i=0; i<size; i++) {
    for (int j=0; j<size; j++) {
      min_pt[0] = ((float)(i-center))-0.5f;
      min_pt[1] = ((float)(j-center))-0.5f;
      max_pt[0] = ((float)(i-center))+0.5f;
      max_pt[1] = ((float)(j-center))+0.5f;
      kernel(i,j) = gaussian.probability(min_pt,max_pt);
    }
  }

  return kernel;
}

void sdet_img_edge::estimate_edge_prob_image(const vil_image_view<vxl_byte>& img_edge, vil_image_view<float>& img_edgeness, const int mask_size, const float mask_sigma)
{
  vbl_array_2d<float> kernel = get_spherical_gaussian_kernel(mask_size,mask_sigma);

  for (unsigned i=0; i<kernel.rows(); i++) {
    for (unsigned j=0; j<kernel.columns(); j++) {
      kernel(i,j) = vcl_log(1.0f - kernel(i,j));
    }
  }

  vil_convert_cast<vxl_byte,float>(img_edge,img_edgeness);
  vil_math_scale_values<float>(img_edgeness,1.0/255.0);
  img_edgeness = brip_vil_float_ops::convolve(img_edgeness,kernel);

  for (unsigned i=0; i<img_edgeness.ni(); i++) {
    for (unsigned j=0; j<img_edgeness.nj(); j++) {
      img_edgeness(i,j) = 1.0f - vcl_exp(img_edgeness(i,j));
    }
  }
}


float sdet_img_edge::convert_edge_statistics_to_probability(float edge_statistic, float n_normal, int dof)
{
  if (dof<1) {
    return edge_statistic;
  }

  if ((edge_statistic-n_normal)>0.0f) {
    double chi_sq_stat = (double)vnl_math_sqr((edge_statistic-n_normal))/n_normal;
    return (float)vnl_chi_squared_cumulative(chi_sq_stat,dof);
  }

  return 0.0f;
}
