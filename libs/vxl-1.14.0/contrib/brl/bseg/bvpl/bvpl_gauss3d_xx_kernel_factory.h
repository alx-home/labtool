// This is brl/bseg/bvpl/bvpl_gauss3d_xx_kernel_factory.h
#ifndef bvpl_gauss3d_xx_kernel_factory_h
#define bvpl_gauss3d_xx_kernel_factory_h

#include "bvpl_kernel_factory.h"

//:
// \file
// \brief: A factory of the kernel of type "xx derivative of 3d gaussian" 
//
// \author Isabel Restrepo mir@lems.brown.edu
//
// \date  8/6/09
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

//: A class to generate kernels of the xx second derivative of gaussian. i.e. the first entry of the Hessian 
// This kernel can be constructed from 2 sigma values or 3 sigma values. In the fisrt case the kernel
// will be an spheroid because 2 of the radii are equal. In such case the kernel is completely 
// decribed by a axis of rotation(wich is aligned with the non-equal radii) and two variance parameters, sigma1 and sigma2
// In the second case when all 3 sigmas are different then the gaussian kernel is a "triaxial ellipsoide" and it is 
// determined by axis of rotation, angle of rotation about such axis, sigma1, sigma2, sigma3.
// The case of an isotropic has not been implemented becuase is it not needed at the moment, but the code is reusable for such case
class bvpl_gauss3d_xx_kernel_factory : public bvpl_kernel_factory
{
 public:
  
  //:Default Constructor
  bvpl_gauss3d_xx_kernel_factory();

 //: Constructs a kernel form gaussian spheroid with sigma parameters s1 and s2. i.e. Cov is diagonal with entries s1, s2, s2
  bvpl_gauss3d_xx_kernel_factory(float s1, float s2);
  
  //: Constructs a kernel form gaussian ellipsoid with sigma parameters s1, s2 and s3. i.e. Cov is diagonal with entries s1, s2,s3
  bvpl_gauss3d_xx_kernel_factory(float s1, float s2, float s3);
  
  virtual ~bvpl_gauss3d_xx_kernel_factory() {}
   
  /******************Batch Methods ***********************/
  ////: Creates a vector of kernels with azimuthal and elevation resolutio equal to pi/4. And angle of rotation= angular_resolution_
  //virtual bvpl_kernel_vector_sptr create_kernel_vector();
  //
  ////: Creates a vector of kernels according to given  azimuthal and elevation resolutio, and angle of rotation= angular_resolution_
  //virtual bvpl_kernel_vector_sptr create_kernel_vector(float pi, float phi);
  //
  ////: Creates a vector of kernels  according to given azimuthal, levation resolutio and angle_res
  //virtual bvpl_kernel_vector_sptr create_kernel_vector(float pi, float phi, float angular_res);
  
private:
  
  //:Creates a 2d edge kernel
  virtual void create_canonical();
  
  float sigma1_;
  float sigma2_;
  float sigma3_;
 
  static const unsigned max_size_ = 71;
  
  
};


#endif
