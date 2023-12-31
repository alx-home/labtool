// This is brl/bseg/bvxm/grid/pro/processes/bvxm_grid_to_image_stack_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file
// \brief A process for writing a grid as a stack of images.
// \author Isabel Restrepo
// \date June 30, 2009
//
// \verbatim
//  Modifications
//  <none yet>
// \endverbatim

#include <vcl_string.h>
#include <bprb/bprb_parameters.h>
#include <bvxm/grid/bvxm_voxel_grid_base.h>
#include <bvxm/grid/bvxm_voxel_grid.h>

#include <bvxm/grid/io/bvxm_grid_to_image_stack.h>

namespace bvxm_grid_to_image_stack_process_globals
{
  const unsigned n_inputs_ = 3;
  const unsigned n_outputs_ = 0;
}


//: set input and output types
bool bvxm_grid_to_image_stack_process_cons(bprb_func_process& pro)
{
  using namespace bvxm_grid_to_image_stack_process_globals;
  //This process has no inputs nor outputs only parameters
  vcl_vector<vcl_string> input_types_(n_inputs_);
  unsigned i=0;
  input_types_[i++]="bvxm_voxel_grid_base_sptr"; //the inpud grid
  input_types_[i++]="vcl_string"; //the datatype e.g. "float","double", "vnl_vector_fixed_float_3"...
  input_types_[i++]="vcl_string"; //output directory

  vcl_cout<<input_types_.size();
  if (!pro.set_input_types(input_types_))
    return false;

  return true;
}


//: Execute the process
bool bvxm_grid_to_image_stack_process(bprb_func_process& pro)
{
  using namespace bvxm_grid_to_image_stack_process_globals;
  // check number of inputs
  if (pro.input_types().size() != n_inputs_)
  {
    vcl_cout << pro.name() << "The number of inputs should be " << n_inputs_ << vcl_endl;
    return false;
  }

  bvxm_voxel_grid_base_sptr grid_base = pro.get_input<bvxm_voxel_grid_base_sptr>(0);
  vcl_string datatype =  pro.get_input<vcl_string>(1);
  vcl_string output_dir = pro.get_input<vcl_string>(2);

  if (!grid_base.ptr())  {
    vcl_cerr << "In bvxm_grid_to_image_stack_process -- input grid is not valid!\n";
    return false;
  }
  //This is temporary. What should happen is that we can read the type from the file header.
  //Also the header should be such that we can check if the file is not currupt
  if (datatype == "float"){
    bvxm_voxel_grid<float> *grid = dynamic_cast< bvxm_voxel_grid<float>* > (grid_base.ptr());
    bvxm_grid_to_image_stack::write_grid_to_image_stack<float>(grid, output_dir);

    return true;
  }
  else if (datatype == "vnl_float_3"){
      bvxm_voxel_grid<vnl_float_3> *grid = dynamic_cast< bvxm_voxel_grid<vnl_float_3>* > (grid_base.ptr());
      bvxm_grid_to_image_stack::write_grid_to_image_stack<vnl_float_3>(grid, output_dir);
    return true;
  }
  else if (datatype == "vnl_float_4"){
      bvxm_voxel_grid<vnl_float_4> *grid = dynamic_cast< bvxm_voxel_grid<vnl_float_4>* > (grid_base.ptr());
      bvxm_grid_to_image_stack::write_grid_to_image_stack<vnl_float_4>(grid, output_dir);
    return true;
  }
  else {
    vcl_cerr << "datatype not supported\n";
  }

  return false;
}
