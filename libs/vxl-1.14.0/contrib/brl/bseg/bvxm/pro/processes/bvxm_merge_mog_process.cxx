// This is brl/bseg/bvxm/pro/processes/bvxm_merge_mog_process.cxx
#include "bvxm_merge_mog_process.h"
//:
// \file

#include <vcl_string.h>
#include <bvxm/algo/bvxm_merge_mog.h>
#include <bvxm/grid/bvxm_voxel_grid_base.h>
#include <bvxm/grid/bvxm_voxel_grid.h>

#include <bsta/bsta_gauss_f1.h>

//: set input and output types
bool bvxm_merge_mog_process_cons(bprb_func_process& pro)
{
  // Inputs
  // 0. Path to input grid(the one with gaussian mixtures)
  // 1. Path to univariate gaussian grid
  vcl_vector<vcl_string> input_types_(2);
  input_types_[0] = "vcl_string";
  input_types_[1] = "vcl_string";


  // No outputs to the database. The resulting grid is stored on disk
  vcl_vector<vcl_string> output_types_(0);

  if (!pro.set_input_types(input_types_))
    return false;

  return pro.set_output_types(output_types_);
}


//: Execute the process
bool bvxm_merge_mog_process(bprb_func_process& pro)
{
  // check number of inputs
  if (pro.n_inputs() != 2)
  {
    vcl_cout << pro.name() << "The number of inputs should be " << 2 << vcl_endl;
    return false;
  }

  vcl_string apm_path = pro.get_input<vcl_string>(0);
  vcl_string output_path = pro.get_input<vcl_string>(1);

  //get the grids
  typedef bsta_num_obs<bsta_gauss_f1> gauss_type;
  typedef bsta_mixture_fixed<gauss_type, 3> mix_gauss;
  typedef bsta_num_obs<mix_gauss> mix_gauss_type;

  bvxm_voxel_grid_base_sptr apm_base = new bvxm_voxel_grid<mix_gauss_type>(apm_path);

  bvxm_voxel_grid_base_sptr output_base = new bvxm_voxel_grid<gauss_type>(output_path, apm_base->grid_size());

  //merge mixtures
  bvxm_merge_mog::kl_merge_grid(apm_base, output_base);

  return true;
}

