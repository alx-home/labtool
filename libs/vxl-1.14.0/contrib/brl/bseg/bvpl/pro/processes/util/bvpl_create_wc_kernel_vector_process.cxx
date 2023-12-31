// This is brl/bseg/bvpl/pro/processes/util/bvpl_create_wc_kernel_vector_process.cxx
#include <bvpl/bvpl_weighted_cube_kernel_factory.h>
//:
// \file
// \brief A class for creating a vector of 3D cube kernels
//
// \author Isabel Restrepo
// \date September 29, 2009
// \verbatim
//  Modifications
//  <none yet>
// \endverbatim

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_parameters.h>
#include <brdb/brdb_value.h>
#include <bvpl/bvpl_create_directions.h>
#include <bvpl/bvpl_neighborhood_kernel_factory.h>


namespace bvpl_create_wc_kernel_vector_process_globals
{
  const unsigned n_inputs_ = 7;
  const unsigned n_outputs_ = 1;
}


bool bvpl_create_wc_kernel_vector_process_cons(bprb_func_process& pro)
{
  using namespace bvpl_create_wc_kernel_vector_process_globals;
  //process takes 3inputs
  // *input[0]: min length
  // *input[1]: max length
  // *input[2]: min width
  // *input[3]: max width
  // *input[4]: min thickness
  // *input[5]: max thickness
  // *input[6]: string identifying a set of directions

  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "int";
  input_types_[1] = "int";
  input_types_[2] = "int";
  input_types_[3] = "int";
  input_types_[4] = "int";
  input_types_[5] = "int";
  input_types_[6] = "vcl_string";

  if (!pro.set_input_types(input_types_))
    return false;

  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[0] = "bvpl_kernel_vector_sptr";
  if (!pro.set_output_types(output_types_))
    return false;

  return true;
}

bool bvpl_create_wc_kernel_vector_process(bprb_func_process& pro)
{
  using namespace bvpl_create_wc_kernel_vector_process_globals;

  if (pro.n_inputs() < n_inputs_)
  {
    vcl_cout << pro.name() << " The input number should be " << n_inputs_<< vcl_endl;
    return false;
  }

  //get inputs:
  int min_length = 0, max_length=0 ;
  min_length = pro.get_input<int>(0);
  max_length = pro.get_input<int>(1);
  int min_width = 0, max_width=0;
  min_width = pro.get_input<int>(2);
  max_width = pro.get_input<int>(3);
  int min_thickness = 0, max_thickness=0;
  min_thickness = pro.get_input<int>(4);
  max_thickness = pro.get_input<int>(5);
  vcl_string dir_type = pro.get_input<vcl_string>(6);

  //Create the factory and get the vector of kernels
  bvpl_neighborhood_kernel_factory factory(min_length, max_length,
                                           min_width, max_width,
                                           min_thickness, max_thickness);
  
  if (dir_type == "main_corners") {
    bvpl_main_corner_dirs dir;
    bvpl_kernel_vector_sptr kernels = factory.create_kernel_vector(dir);
    pro.set_output_val<bvpl_kernel_vector_sptr>(0, kernels);
  }
  if (dir_type == "main_plane") {
    bvpl_main_plane_corner_dirs dir;
    bvpl_kernel_vector_sptr kernels = factory.create_kernel_vector(dir);
    pro.set_output_val<bvpl_kernel_vector_sptr>(0, kernels);
  }
  if (dir_type == "all_corners") {
    bvpl_all_corner_dirs dir;
    bvpl_kernel_vector_sptr kernels = factory.create_kernel_vector(dir);
    pro.set_output_val<bvpl_kernel_vector_sptr>(0, kernels);
  }
  if(dir_type == "pi_over_2_corners"){
    bvpl_pi_over_2_corner_dirs dir;
    bvpl_kernel_vector_sptr kernels = factory.create_kernel_vector(dir);
    pro.set_output_val<bvpl_kernel_vector_sptr>(0, kernels);
  }

  return true;
}
