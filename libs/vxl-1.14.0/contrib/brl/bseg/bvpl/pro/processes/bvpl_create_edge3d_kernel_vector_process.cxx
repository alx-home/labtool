// This is brl/bseg/bvpl/pro/processes/bvpl_create_edge3d_kernel_vector_process.cxx

//:
// \file
// \brief A class for creating a vector of 3D edge kernels
//
// \author Vishal Jain (copied the code from brl/bseg/bvpl/pro/processes/bvpl_create_edge2d_kernel_vector_process.cxx)
// created by Isabel Restrepo
// \date 6/29/09
// \verbatim
//  Modifications
//  06/29/09 replaced 2d by 3d 
// \endverbatim 

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_parameters.h>

#include <brdb/brdb_value.h>

#include <bvpl/bvpl_edge3d_kernel_factory.h>
#include <bvpl/bvpl_create_directions.h>



namespace bvpl_create_edge3d_kernel_vector_process_globals
{
  const unsigned n_inputs_ = 6;
  const unsigned n_outputs_ = 1;
}


bool bvpl_create_edge3d_kernel_vector_process_cons(bprb_func_process& pro)
{
  using namespace bvpl_create_edge3d_kernel_vector_process_globals;
  //process takes 3inputs
  //input[0]-input[5]: Min and max coordinates of kernel


  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "int";
  input_types_[1] = "int";
  input_types_[2] = "int";
  input_types_[3] = "int";
  input_types_[4] = "int";
  input_types_[5] = "int";

  if (!pro.set_input_types(input_types_))
    return false;
  
  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[0] = "bvpl_kernel_vector_sptr";
  if (!pro.set_output_types(output_types_))
    return false;

  return true;
}

bool bvpl_create_edge3d_kernel_vector_process(bprb_func_process& pro)
{
  using namespace bvpl_create_edge3d_kernel_vector_process_globals;
  
  if (pro.n_inputs() < n_inputs_)
  {
    vcl_cout << pro.name() << " The input number should be " << n_inputs_<< vcl_endl;
    return false;
  }
  
  //get inputs:
  unsigned i = 0;
  int min_x = pro.get_input<int>(i++);
  int max_x = pro.get_input<int>(i++);
  int min_y = pro.get_input<int>(i++);
  int max_y = pro.get_input<int>(i++);
  int min_z = pro.get_input<int>(i++);
  int max_z = pro.get_input<int>(i++);
    
  //Create the factory and get the vector of kernels
  bvpl_edge3d_kernel_factory factory(min_x, max_x,min_y,max_y,min_z,max_z);
  bvpl_create_directions_c dir;
  bvpl_kernel_vector_sptr kernels = factory.create_kernel_vector(dir);
  pro.set_output_val<bvpl_kernel_vector_sptr>(0, kernels);
  
  
  return true;
}

