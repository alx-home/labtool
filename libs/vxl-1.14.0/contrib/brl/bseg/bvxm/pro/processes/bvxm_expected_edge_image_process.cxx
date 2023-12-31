// This is brl/bseg/bvxm/pro/processes/bvxm_expected_edge_image_process.cxx
#include "bvxm_expected_edge_image_process.h"
//:
// \file

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_parameters.h>
#include <brdb/brdb_value.h>
#include <bvxm/bvxm_voxel_world.h>
#include <bvxm/bvxm_image_metadata.h>
#include <bvxm/bvxm_edge_ray_processor.h>
#include <brip/brip_vil_float_ops.h>
#include <vpgl/algo/vpgl_backproject.h>
#include <vcl_cstdio.h>

//: set input and output types
bool bvxm_expected_edge_image_process_cons(bprb_func_process& pro)
{
  using namespace bvxm_expected_edge_image_process_globals;

  // process takes 4 inputs:
  //input[0]: The voxel world
  //input[1]: The current camera
  //input[2]: An image specifying the size of the expected edge image
  //input[3]: Scale of the image

  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "bvxm_voxel_world_sptr";
  input_types_[1] = "vpgl_camera_double_sptr";
  input_types_[2] = "vil_image_view_base_sptr";
  input_types_[3] = "unsigned";
  if (!pro.set_input_types(input_types_))
    return false;

  // process has 2 outputs:
  // output[0]: Expected edge image (probabilities between 0 and 1, float)
  // output[1]: Expected edge image (normalized for display purposes, vxl_byte)
  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[0] = "vil_image_view_base_sptr";
  output_types_[1] = "vil_image_view_base_sptr";
  return pro.set_output_types(output_types_);
}

//:  optimizes rpc camera parameters based on edges
bool bvxm_expected_edge_image_process(bprb_func_process& pro)
{
  using namespace bvxm_expected_edge_image_process_globals;

  //check number of inputs
  if ( !pro.verify_inputs()) {
    vcl_cout << pro.name() << " - invalid inputs " << vcl_endl;
    return false;
  }

  // get the inputs
  // voxel world
  bvxm_voxel_world_sptr vox_world = pro.get_input<bvxm_voxel_world_sptr>(0);
  // camera
  vpgl_camera_double_sptr camera_inp = pro.get_input<vpgl_camera_double_sptr>(1);
  bvxm_edge_ray_processor edge_proc(vox_world);

  vil_image_view_base_sptr size_image_sptr = pro.get_input<vil_image_view_base_sptr>(2);
  unsigned ni = size_image_sptr->ni();
  unsigned nj = size_image_sptr->nj();

  // scale of image
  unsigned scale = pro.get_input<unsigned>(3);

  int num_observations = vox_world->num_observations<EDGES>(0,scale);
  vcl_cout << "Number of observations in curren edge world: " << num_observations << '\n';

  float n_normal = vox_world->get_params()->edges_n_normal();

  // render the expected edge image
  vil_image_view_base_sptr dummy_img;
  bvxm_image_metadata camera_metadata_inp(dummy_img,camera_inp);
  vil_image_view<float> *img_eei_f = new vil_image_view<float>(ni,nj,1);
  vil_image_view_base_sptr img_eei_f_sptr = img_eei_f;

  edge_proc.expected_edge_image(camera_metadata_inp,img_eei_f_sptr,n_normal,scale);

  vil_image_view<vxl_byte> *img_eei_vb = new vil_image_view<vxl_byte>(ni,nj,1);
  float min_val, max_val;
  vil_math_value_range(*img_eei_f, min_val, max_val);
  float min_max_diff = max_val - min_val;
  if(min_max_diff > 0.0f){
    for(unsigned i=0; i<ni; i++){
      for(unsigned j=0; j<nj; j++){
        (*img_eei_vb)(i,j) = (vxl_byte)(255.0f*((*img_eei_f)(i,j)-min_val)/(min_max_diff));
      }
    }
  }

  pro.set_output_val<vil_image_view_base_sptr>(0, img_eei_f);
  pro.set_output_val<vil_image_view_base_sptr>(1, img_eei_vb);

  return true;
}
