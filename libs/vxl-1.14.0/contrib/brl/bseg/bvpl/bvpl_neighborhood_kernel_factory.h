// This is brl/bseg/bvpl/bvpl_neighborhood_kernel_factory.h
#ifndef bvpl_neighborhood_kernel_factory_h
#define bvpl_neighborhood_kernel_factory_h
//:
// \file
// \brief
// \author Isabel Restrepo mir@lems.brown.edu
// \date  October 6, 2009
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include "bvpl_kernel_factory.h"

class bvpl_neighborhood_kernel_factory : public bvpl_kernel_factory
{
 public:

  //:Default Constructor
  bvpl_neighborhood_kernel_factory();

  //: Constructs a kernel form three values, lenght, widht and thickness
  bvpl_neighborhood_kernel_factory(int min_lenght, int max_lenght,
                                   int min_width, int max_width,
                                   int min_thickness, int max_thickness);

  virtual ~bvpl_neighborhood_kernel_factory() {}

 private:

  //:Creates a 2d edge kernel
  virtual void create_canonical();

  int min_length_;
  int max_length_;
  int min_width_;
  int max_width_;
  int min_thickness_;
  int max_thickness_;

  static const unsigned max_size_ = 71;
};

#endif
