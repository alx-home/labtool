// This is brl/bseg/boxm/opt/pro/processes/boxm_generate_edge_samples_process.cxx
//:
// \file
// \brief Process to update the scene from an image and camera pair
//
// \author Gamze Tunali
// \date Sep 15, 2009
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_parameters.h>

#include <vcl_fstream.h>

#include <boxm/boxm_scene_base.h>
#include <boxm/boxm_scene.h>
#include <boxm/opt/boxm_generate_edge_sample_functor.h>
#include <boxm/opt/boxm_generate_edge_tangent_sample_functor.h>
#include <boxm/boxm_edge_sample.h>
#include <boxm/boxm_inf_line_sample.h>

#include <vil/vil_convert.h>
#include <vil/vil_image_view_base.h>
#include <vil/vil_image_view.h>

#include <sdet/sdet_img_edge.h>

namespace boxm_generate_edge_samples_process_globals
{
  const unsigned n_inputs_ = 5;
  const unsigned n_outputs_ = 1;
}

bool boxm_generate_edge_samples_process_cons(bprb_func_process& pro)
{
  using namespace boxm_generate_edge_samples_process_globals;
  //process takes 4 inputs
  //input[0]: The cropped edge image
  //input[1]: The camera of the observation
  //input[2]: The scene
  //input[3]: image name for saving scene
  //input[4]: n_normal
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "vil_image_view_base_sptr";
  input_types_[1] = "vpgl_camera_double_sptr";
  input_types_[2] = "boxm_scene_base_sptr";
  input_types_[3] = "vcl_string";
  input_types_[4] = "float";
  if (!pro.set_input_types(input_types_))
    return false;

  //output
  unsigned j = 0;
  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[j++] = "float"; // new n_normal value
  if (!pro.set_output_types(output_types_))
    return false;
  return true;
}

bool boxm_generate_edge_samples_process(bprb_func_process& pro)
{
  using namespace boxm_generate_edge_samples_process_globals;

  if ( pro.n_inputs() < n_inputs_ ){
    vcl_cout << pro.name() << "boxm_generate_edge_samples_process: The input number should be " << n_inputs_<< vcl_endl;
    return false;
  }

  //get inputs:
  unsigned i = 0;
  vil_image_view_base_sptr edge_image = pro.get_input<vil_image_view_base_sptr>(i++);
  vpgl_camera_double_sptr camera = pro.get_input<vpgl_camera_double_sptr>(i++);
  boxm_scene_base_sptr scene = pro.get_input<boxm_scene_base_sptr>(i++);
  vcl_string img_name =  pro.get_input<vcl_string>(i++);
  float n_normal = pro.get_input<float>(i++);

  // get parameters
  int edge_prob_mask_size = 21;
  pro.parameters()->get_value("edge_prob_mask_size",edge_prob_mask_size);
  float edge_prob_mask_sigma = 1.0f;
  pro.parameters()->get_value("edge_prob_mask_sigma",edge_prob_mask_sigma);

  // check the input validity
  if ((edge_image == 0) || (camera == 0) || (scene == 0)) {
     vcl_cout << "boxm_generate_edge_samples_process: null input value, cannot run" << vcl_endl;
     return false;
  }

  float new_n_normal=0.0;
  

  if (scene->appearence_model() == BOXM_EDGE_FLOAT) {
    vil_image_view<float> edge_prob_image;
    sdet_img_edge::estimate_edge_prob_image(edge_image, edge_prob_image, edge_prob_mask_size, edge_prob_mask_sigma);
    float edge_prob_image_mean;
    vil_math_mean(edge_prob_image_mean,edge_prob_image,0);
    vil_image_view<float> img(edge_prob_image);
    new_n_normal = n_normal + edge_prob_image_mean;
    if (!scene->multi_bin())
    {
      typedef boct_tree<short, boxm_edge_sample<float> > tree_type;
      boxm_scene<tree_type> *s = static_cast<boxm_scene<tree_type>*> (scene.as_pointer());
      boxm_generate_edge_sample_rt<short,boxm_edge_sample<float> > (*s, camera, img, img_name);
    }
    else
    {
      vcl_cout<<"boxm_generate_edge_samples_process: Multibin -- Not yet implemented"<<vcl_endl;
    }
  }
  if (scene->appearence_model() == BOXM_EDGE_LINE) {
    // get the edges as an image with 3 planes (a,b,c)
    if (!scene->multi_bin())
    {
      typedef boxm_inf_line_sample<float> sample_type;
      typedef boct_tree<short, sample_type> tree_type;
      boxm_scene<tree_type> *s = static_cast<boxm_scene<tree_type>*> (scene.as_pointer());
      // for this case, the image should be with 4 planes, representing plane definitions
      vil_image_view<float> img(edge_image);
      boxm_generate_edge_tangent_sample_rt<short,sample_type> (*s, camera, img, img_name);
    }
    else
    {
      vcl_cout<<"boxm_generate_edge_samples_process: Multibin -- Not yet implemented"<<vcl_endl;
    }
  }
  else {
    vcl_cout << "boxm_generate_edge_samples_process: undefined APM type" << vcl_endl;
    return false;
  }
  vcl_cout << " New n_normal======>" << new_n_normal << vcl_endl;
  pro.set_output_val<float>(0, float(new_n_normal));
  return true;
}
