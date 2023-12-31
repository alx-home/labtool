// This is brl/bseg/bvpl/bvpl_octree/pro/processes/bvpl_scene_kernel_operator_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file
// \brief A class for running a kernel to a boxm_scene
// \author Isabel Restrepo
// \date January 29, 2010
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <bvpl/bvpl_octree/bvpl_scene_kernel_operator.h>
#include <bvpl/bvpl_octree/bvpl_octree_sample.h>
#include <bvpl/bvpl_edge_geometric_mean_functor.h>
#include <bvpl/bvpl_edge_algebraic_mean_functor.h>
#include <bvpl/bvpl_gauss_convolution_functor.h>
#include <bvpl/bvpl_positive_gauss_conv_functor.h>

#include <bprb/bprb_parameters.h>

#include <brdb/brdb_value.h>

#include <boxm/boxm_scene.h>

#include <bsta/bsta_gauss_f1.h>
#include <bsta/bsta_attributes.h>

namespace bvpl_scene_kernel_operator_process_globals
{
  const unsigned n_inputs_ = 5;
  const unsigned n_outputs_ = 1;
}

//: process takes 5 inputs and has 1 output.
// * input[0]: The boxm_scene
// * input[1]: The kernel
// * input[2]: The grid type:
//           - float
//           - opinion
//           - ...
// * input[3]: String identifying functor type
// * input[4]: Output path to a dir where to store, id octree and response octree
//
// * output[0]: Output scene with response and kernel id

bool bvpl_scene_kernel_operator_process_cons(bprb_func_process& pro)
{
  using namespace bvpl_scene_kernel_operator_process_globals;
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "boxm_scene_base_sptr";
  input_types_[1] = "bvpl_kernel_sptr";
  input_types_[2] = "vcl_string";
  input_types_[3] = "vcl_string";
  input_types_[4] = "vcl_string";

  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[0] = "boxm_scene_base_sptr";

  return pro.set_input_types(input_types_) && pro.set_output_types(output_types_);
}

bool bvpl_scene_kernel_operator_process(bprb_func_process& pro)
{
  using namespace bvpl_scene_kernel_operator_process_globals;

  if (pro.n_inputs() < n_inputs_)
  {
    vcl_cerr << pro.name() << ": the input number should be " << n_inputs_
             << " but instead it is " << pro.n_inputs() << vcl_endl;
    return false;
  }

  //get inputs:
  unsigned i = 0;
  boxm_scene_base_sptr scene_base = pro.get_input<boxm_scene_base_sptr>(i++);
  bvpl_kernel_sptr kernel = pro.get_input<bvpl_kernel_sptr>(i++);
  vcl_string datatype = pro.get_input<vcl_string>(i++);
  vcl_string functor_name = pro.get_input<vcl_string>(i++);
  vcl_string output_path = pro.get_input<vcl_string>(i++);
  short level = 0;

  //print inputs
  vcl_cout << "In bvpl_scene_kernel_operator:\n"
           << "Datatype:     " << datatype << vcl_endl
           << "Functor Name: " << functor_name << vcl_endl
           << "Resolution:   " << level << vcl_endl;

  //check input's validity
  if (!scene_base.ptr()) {
    vcl_cerr <<  " :-- Grid is not valid!\n";
    return false;
  }

  if ( !kernel ) {
    vcl_cerr << pro.name() << " :-- Kernel is not valid!\n";
    return false;
  }

  boxm_scene_base_sptr scene_ptr=new boxm_scene_base();

  if (datatype == "bsta_gauss_f1")
  {
    typedef bsta_num_obs<bsta_gauss_f1> gauss_type;
    typedef boct_tree<short, gauss_type > tree_type;
    boxm_scene<tree_type> *scene_in = static_cast<boxm_scene<tree_type>* > (scene_base.as_pointer());

    //parameters of the output scene are the same as those of the input scene
    boxm_scene<tree_type> *scene_out =
      new boxm_scene<tree_type>(scene_in->lvcs(), scene_in->origin(), scene_in->block_dim(), scene_in->world_dim());
    scene_out->set_paths(output_path, "response_scene");
    scene_out->set_appearance_model(BSTA_GAUSS_F1);
    scene_out->write_scene("/response_scene.xml");

    if (functor_name == "gauss_convolution") {
      bvpl_gauss_convolution_functor functor;
      bvpl_scene_kernel_operator scene_oper;
      //operate on scene
      scene_oper.operate(*scene_in, functor, kernel, *scene_out, level);
      scene_ptr = scene_out;
      pro.set_output_val<boxm_scene_base_sptr>(0, scene_ptr);
      return true;
    }
    else if(functor_name == "positive_gauss_convolution"){
      bvpl_positive_gauss_conv_functor functor;
      bvpl_scene_kernel_operator scene_oper;
      //operate on scene
      scene_oper.operate(*scene_in, functor, kernel, *scene_out, level);
      scene_ptr = scene_out;
      pro.set_output_val<boxm_scene_base_sptr>(0, scene_ptr);
      return true;
    }
      return false;
  }
  else if (datatype == "float")
  {
    typedef boct_tree<short, float > tree_type;
    boxm_scene<tree_type> *scene_in = static_cast<boxm_scene<tree_type>* > (scene_base.as_pointer());

    //parameters of the output scene are the same as those of the input scene
    boxm_scene<tree_type> *scene_out =
      new boxm_scene<tree_type>(scene_in->lvcs(), scene_in->origin(), scene_in->block_dim(), scene_in->world_dim());
    scene_out->set_paths(output_path, "response_scene");
    scene_out->set_appearance_model(FLOAT);
    scene_out->write_scene("/float_response_scene.xml");

    if (functor_name == "edge_algebraic_mean") {
      bvpl_edge_algebraic_mean_functor<float> functor;
      bvpl_scene_kernel_operator scene_oper;
      //operate on scene
      scene_oper.operate(*scene_in, functor, kernel, *scene_out, level);
      scene_ptr = scene_out;
      pro.set_output_val<boxm_scene_base_sptr>(0, scene_ptr);
      return true;
    }
    else
      return false;
  }
  else
    return false;
}
