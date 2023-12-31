// This is brl/bseg/bvxm/grid/pro/processes/bvxm_save_grid_raw_process.cxx

//:
// \file
// \brief A process that saves a scalar grid in binary format readable by the Drishti volume rendering program
//        (http://anusf.anu.edu.au/Vizlab/drishti/)
//
// \author Isabel Restrepo
// \date Jun 19, 2009
// \verbatim
//  Modifications
//   Jun 25, 2009  Gamze Tunali
//       Added the type bvxm_opinion for grid  
// \endverbatim


#include <bprb/bprb_func_process.h>
#include <bvxm/grid/io/bvxm_io_voxel_grid.h>
#include <bvxm/grid/bvxm_opinion.h>
#include <bsta/bsta_attributes.h>
#include <bsta/bsta_gauss_f1.h>

namespace bvxm_save_grid_raw_process_globals
{
  const unsigned n_inputs_ = 2;
  const unsigned n_outputs_ = 0;
}

bool bvxm_save_grid_raw_process_cons(bprb_func_process& pro)
{
  using namespace bvxm_save_grid_raw_process_globals;
  // process takes 2 inputs:
  //input[0]: The voxel_grid
  //input[1]: The filename to write to
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "bvxm_voxel_grid_base_sptr";
  input_types_[1] = "vcl_string";
  if (!pro.set_input_types(input_types_))
    return false;

  return true;
}

bool bvxm_save_grid_raw_process(bprb_func_process& pro)
{
  using namespace bvxm_save_grid_raw_process_globals;

  // check number of inputs
  if (pro.n_inputs() != n_inputs_)
  {
    vcl_cout << pro.name() << "The number of inputs should be " << n_inputs_ << vcl_endl;
    return false;
  }
  bvxm_voxel_grid_base_sptr grid_base = pro.get_input<bvxm_voxel_grid_base_sptr>(0);
  vcl_string volume_path = pro.get_input<vcl_string>(1);
  
  // create the grid from in memory file and save
  if ( bvxm_voxel_grid<float > *grid = dynamic_cast<bvxm_voxel_grid<float >* >(grid_base.ptr())) {    
    bvxm_grid_save_raw(grid,volume_path);
    return true;
  }
  else if ( bvxm_voxel_grid<bvxm_opinion > *grid = dynamic_cast<bvxm_voxel_grid<bvxm_opinion >* >(grid_base.ptr())) {
     bvxm_grid_save_raw(grid,volume_path);
    return true;
  }
  else if ( bvxm_voxel_grid<unsigned> *grid = dynamic_cast<bvxm_voxel_grid<unsigned>* >(grid_base.ptr())) {
    bvxm_grid_save_raw(grid,volume_path);
    return true;
  }
  else if ( bvxm_voxel_grid<bsta_num_obs<bsta_gauss_f1> > *grid = dynamic_cast<bvxm_voxel_grid<bsta_num_obs<bsta_gauss_f1> >* >(grid_base.ptr())) {
    bvxm_grid_save_raw<bsta_num_obs<bsta_gauss_f1> >(grid,volume_path);
    return true;
  }
  else
    vcl_cerr << "Grid type not supportted yet, but you can add one!\n";
  return false;
}
