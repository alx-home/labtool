// This is brl/bseg/bvxm/grid/pro/processes/bvxm_multiply_grids_process.cxx

//:
// \file
// \brief A process for multiplying two grids. Assumes floating point grids
// \author Isabel Restrepo
// \date May 5, 2009
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <vcl_string.h>
#include <bprb/bprb_func_process.h>
#include <bvxm/grid/bvxm_voxel_grid_basic_ops.h>
#include <bvxm/grid/bvxm_voxel_slab.h>


//: set input and output types
bool bvxm_multiply_grids_process_cons(bprb_func_process& pro)
{
  // Inputs
  // 0. Path to grid1
  // 1. Path to grid2
  // 2. Path to output grid

  vcl_vector<vcl_string> input_types_(3);
  input_types_[0] = "vcl_string";
  input_types_[1] = "vcl_string";
  input_types_[2] = "vcl_string";


  // No outputs to the database. The resulting grid is stored on disk
  vcl_vector<vcl_string> output_types_(0);

  if (!pro.set_input_types(input_types_))
    return false;

  if (!pro.set_output_types(output_types_))
    return false;

  return true;
}


//: Execute the process
bool bvxm_multiply_grids_process(bprb_func_process& pro)
{
  // check number of inputs
  if (pro.n_inputs() != 3)
  {
    vcl_cout << pro.name() << "The number of inputs should be " << 3<< vcl_endl;
    return false;
  }

  vcl_string path1 = pro.get_input<vcl_string>(0);
  vcl_string path2 = pro.get_input<vcl_string>(1);
  vcl_string output_path = pro.get_input<vcl_string>(2);


  //get  and create the grids
  typedef float datatype;

  bvxm_voxel_grid_base_sptr grid1 = new bvxm_voxel_grid<datatype>(path1);
  bvxm_voxel_grid_base_sptr grid2 = new bvxm_voxel_grid<datatype>(path2);

  if (grid1->grid_size()!=grid2->grid_size()){
    vcl_cerr << "Imput grids must be of same size\n";
    return false;
  }

  bvxm_voxel_grid_base_sptr grid_out = new bvxm_voxel_grid<datatype>(output_path, grid1->grid_size());

  //multipy
  bvxm_voxel_grid_multiply<float>(grid1, grid2, grid_out);
  return true;
}
