// This is brl/bseg/bvpl/bvpl_edge3d_kernel_factory.h
#ifndef bvpl_edge3d_kernel_h_
#define bvpl_edge3d_kernel_h_
//:
// \file
// \brief A class to construct a 3d edge kernel
// \author Vishal Jain
// \date  August, 2009
//
// \verbatim
//  Modifications
//   9/30/09 Isabel Restrepo: Changed coordinate system to match that of kernels.
//           Within a subgrid the centroid is placed at the origin. The maximum
//           and minimum position are as shown below. The methods in this class must take care
//           of retrieving the appropiate index of the big grid (where z is inverted).
// \endverbatim
//  \verbatim
//                            Canonical Axis
//                                  (max_x, max_y, max_z)
//                       O-----------O
//                      /___________/|
//                     /           /||---->"-" Minus region
//                    O-----------O ||
//                    |           | ||
//                    |  +    +   |---->"+" Plus region (including Z=0 plane)   |
//                    |  +    +   | |O
//     Z              |  +    +   | /
//     |              |           |/
//     |              O-----------O
//     |       (min_x,min_y,min_z)
//     O-----Y
//    /
//   /
//  X - Canonical Axis
// \endverbatim

#include "bvpl_kernel_factory.h"
#include <vcl_iostream.h>


class bvpl_edge3d_kernel_factory : public bvpl_kernel_factory
{
 public:
  //:Default Constructor
  bvpl_edge3d_kernel_factory();

  //: Constructs constructor from min and max positions on each axis
  bvpl_edge3d_kernel_factory(int min_x, int max_x, int min_y, int max_y, int min_z, int max_z);

  virtual ~bvpl_edge3d_kernel_factory() {}

 private:

  //:Creates a 2d edge kernel
  virtual void create_canonical();

  int min_x_;
  int max_x_;
  int min_y_;
  int max_y_;
  int min_z_;
  int max_z_;

  static const unsigned max_size_ = 71;
};

#endif
