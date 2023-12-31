// This is brl/bseg/bvxm/pro/processes/bvxm_update_process.cxx
#include "bvxm_update_process.h"
//:
// \file
#include <bprb/bprb_func_process.h>
#include <bprb/bprb_parameters.h>

#include <brdb/brdb_value.h>

#include <vil/vil_image_view_base.h>
#include <vpgl/vpgl_camera.h>

#include <bvxm/bvxm_voxel_world.h>
#include <bvxm/bvxm_image_metadata.h>
#include <bvxm/bvxm_mog_grey_processor.h>

bool bvxm_update_process_cons(bprb_func_process& pro)
{
  using namespace bvxm_update_process_globals;
  //process takes 4inputs
  //input[0]: The observation image
  //input[1]: The camera of the observation
  //input[2]: The voxel world
  //input[3]: The apperance model type, the supported strings are:
  //          -apm_mog_grey
  //          -apm_mog_rgb
  //          -apm_mog_mc_2_3
  //          -apm_mog_mc_3_3
  //          -apm_mog_mc_4_3
  //input[4]: The bin index to be updatet
  //input[5]: The scale index  of the voxel world to be updated (default is 0)
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "vil_image_view_base_sptr";
  input_types_[1] = "vpgl_camera_double_sptr";
  input_types_[2] = "bvxm_voxel_world_sptr";
  input_types_[3] = "vcl_string";
  input_types_[4] = "unsigned";
  input_types_[5] = "unsigned";
  if (!pro.set_input_types(input_types_))
    return false;

  //output has 1 output
  //output[0] : The updated probability map
  //output[1] : The mask of image pixels used in update
  unsigned j = 0;
  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[j++] = "vil_image_view_base_sptr";
  output_types_[j++] = "vil_image_view_base_sptr";
  return pro.set_output_types(output_types_);
}

bool bvxm_update_process(bprb_func_process& pro)
{
  using namespace bvxm_update_process_globals;

  if (pro.n_inputs() < n_inputs_)
  {
    vcl_cout << pro.name() << " The input number should be " << n_inputs_<< vcl_endl;
    return false;
  }

  //get inputs:
  unsigned i = 0;
  vil_image_view_base_sptr img = pro.get_input<vil_image_view_base_sptr>(i++);
  vpgl_camera_double_sptr camera = pro.get_input<vpgl_camera_double_sptr>(i++);
  bvxm_voxel_world_sptr world = pro.get_input<bvxm_voxel_world_sptr>(i++);
  vcl_string voxel_type = pro.get_input<vcl_string>(i++);
  unsigned bin_index = pro.get_input<unsigned>(i++);
  unsigned curr_scale = pro.get_input<unsigned>(i++);

  //check input's validity
  i = 0;
  if ( !img ){
      vcl_cout << pro.name() << " :-- Input " << i++ << " is not valid!\n";
      return false;
  }

  if ( !camera ){
      vcl_cout << pro.name() << " :-- Input " << i++ << " is not valid!\n";
      return false;
  }

  if ( !world ){
      vcl_cout << pro.name() << " :-- Input " << i++ << " is not valid!\n";
      return false;
  }


  //create metadata:
  bvxm_image_metadata observation(img,camera);
  unsigned max_scale = world->get_params()->max_scale();

  //update
  vcl_vector<vil_image_view<float> > prob_map_vec;
  vcl_vector<vil_image_view<bool> >mask_vec;


  for (unsigned scale = curr_scale;scale < max_scale;scale++)
  {
    vil_image_view<float> prob_map(img->ni(),img->nj(),1);
    vil_image_view<bool> mask(img->ni(),img->nj(),1);

    if (scale!=curr_scale)
    {
      img=bvxm_util::downsample_image_by_two(img);
      camera=bvxm_util::downsample_camera( camera, scale);
      prob_map.set_size(img->ni(),img->nj());
      mask.set_size(img->ni(),img->nj());
    }
    bvxm_image_metadata observation(img,camera);

    bool result = true;

    if (voxel_type == "apm_mog_grey")
      result = world->update<APM_MOG_GREY>(observation, prob_map, mask, bin_index,scale);
    else if (voxel_type == "apm_mog_rgb")
      result = world->update<APM_MOG_RGB>(observation, prob_map, mask, bin_index,scale);
    else if (voxel_type == "apm_mog_mc_2_3")
    {
      if (observation.img->nplanes()!= 2)
      {
        vcl_cerr << "appereance model type" << voxel_type << "does not support images with " << observation.img->nplanes()
                 << " planes\n";
        return false;
      }

      result = world->update<APM_MOG_MC_3_3>(observation, prob_map, mask, bin_index,scale);
    }
    else if (voxel_type == "apm_mog_mc_3_3")
      result = world->update<APM_MOG_MC_3_3>(observation, prob_map, mask, bin_index,scale);
    else if (voxel_type == "apm_mog_mc_4_3")
    {
      if (observation.img->nplanes()!= 4)
      {
        vcl_cerr << "appereance model type" << voxel_type << "does not support images with " << observation.img->nplanes()
                 << " planes\n";
        return false;
      }
      result = world->update<APM_MOG_MC_4_3>(observation, prob_map, mask, bin_index,scale);
    }
    else
      vcl_cerr << "Error in: bvxm_update_processor: Unsuppported appereance model\n";

    vcl_cout<<"update done ";
    vcl_cout.flush();

    prob_map_vec.push_back(prob_map);
    mask_vec.push_back(mask);
    if (!result){
      vcl_cerr << "error bvxm_update_process: failed to update observation\n";
      return false;
    }
  }

  //store output
  pro.set_output_val<vil_image_view_base_sptr>(0, new vil_image_view<float>(prob_map_vec[0]));
  pro.set_output_val<vil_image_view_base_sptr>(1, new vil_image_view<bool>(mask_vec[0]));

  return true;
}
