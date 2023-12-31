// This is brl/bseg/bvpl/bvpl_octree/pro/processes/bvpl_scene_vector_operator_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file
// \brief A class for successively running a kernel(of a vector), applying non-max suppression and combining with previous result
// \author Isabel Restrepo
// \date December 2, 2009
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <bvpl/bvpl_octree/bvpl_scene_vector_operator.h>
#include <bvpl/bvpl_octree/bvpl_octree_vector_operator_impl.h>
#include <bvpl/bvpl_octree/bvpl_octree_sample.h>
#include <bvpl/bvpl_kernel_factory.h>
#include <bvpl/bvpl_edge_geometric_mean_functor.h>
#include <bvpl/bvpl_gauss_convolution_functor.h>
#include <bprb/bprb_parameters.h>
#include <brdb/brdb_value.h>

#include <boxm/boxm_scene.h>
#include <bsta/bsta_gauss_f1.h>
#include <bsta/bsta_attributes.h>

namespace bvpl_scene_vector_operator_process_globals
{
  const unsigned n_inputs_ = 6;
  const unsigned n_outputs_ = 1;
}

//: process takes 6 inputs and has 2 outputs.
// * input[0]: The boxm_scene
// * input[1]: The kernels; bvpl_kernel_vector_sptr
// * input[2]: The grid type:
//           - float
//           - opinion
//           - ...
// * input[3]: String identifying octree_vector_operator (e.g. max)
// * input[4]: String identifying functor type
// * input[5]: Output path to a dir where to store, id octree and response octree
//
// * output[0]: Output scene with response and kernel id



bool bvpl_scene_vector_operator_process_cons(bprb_func_process& pro)
{
  using namespace bvpl_scene_vector_operator_process_globals;
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "boxm_scene_base_sptr";
  input_types_[1] = "bvpl_kernel_vector_sptr";
  input_types_[2] = "vcl_string";
  input_types_[3] = "vcl_string";
  input_types_[4] = "vcl_string";
  input_types_[5] = "vcl_string";
  
  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[0] = "boxm_scene_base_sptr";
  
  return pro.set_input_types(input_types_) && pro.set_output_types(output_types_);
}

bool bvpl_scene_vector_operator_process(bprb_func_process& pro)
{
  using namespace bvpl_scene_vector_operator_process_globals;
  
  if (pro.n_inputs() < n_inputs_)
  {
    vcl_cout << pro.name() << ": the input number should be " << n_inputs_
    << " but instead it is " << pro.n_inputs() << vcl_endl;
    return false;
  }
  
  //get inputs:
  unsigned i = 0;
  boxm_scene_base_sptr scene_base = pro.get_input<boxm_scene_base_sptr>(i++);
  bvpl_kernel_vector_sptr kernel_vec = pro.get_input<bvpl_kernel_vector_sptr>(i++);
  vcl_string datatype = pro.get_input<vcl_string>(i++);
  vcl_string operator_name = pro.get_input<vcl_string>(i++);
  vcl_string functor_name = pro.get_input<vcl_string>(i++);
  vcl_string output_path = pro.get_input<vcl_string>(i++);
  short level = 0;
 
  //check input's validity
  if (!scene_base.ptr()) {
    vcl_cout <<  " :-- Grid is not valid!\n";
    return false;
  }
  
  if ( !kernel_vec ) {
    vcl_cout << pro.name() << " :-- Kernel is not valid!\n";
    return false;
  }
  
  boxm_scene_base_sptr scene_ptr=new boxm_scene_base();
  
  if (datatype == "float")
  {
    typedef boct_tree<short, float > tree_type;
    boxm_scene<tree_type> *scene_in = static_cast<boxm_scene<tree_type>* > (scene_base.as_pointer());
    
    //parameters of the output scene are the same as thos of the input scene
    boxm_scene<boct_tree<short, bvpl_octree_sample<float> > > *scene_out = 
    new boxm_scene<boct_tree<short, bvpl_octree_sample<float> > >(scene_in->lvcs(), scene_in->origin(), scene_in->block_dim(), scene_in->world_dim());
    scene_out->set_paths(output_path, "response_scene");
    scene_out->set_appearance_model(BVPL_SAMPLE_FLOAT);
    scene_out->write_scene("/response_scene.xml");
    if(operator_name == "max_vector_operator")
     {
       bvpl_max_vector_operator<float> max_oper;
       
       if (functor_name == "edge_geometric_mean") {
         bvpl_edge_geometric_mean_functor<float> functor;
         bvpl_scene_vector_operator scene_oper;
         scene_oper.operate(*scene_in, &max_oper, functor, kernel_vec, *scene_out, level);
         scene_ptr = scene_out;
         pro.set_output_val<boxm_scene_base_sptr>(0, scene_ptr);
         return true;
       }
     }
  }
  if (datatype == "bsta_gauss_f1")
  {
    typedef bsta_num_obs<bsta_gauss_f1> gauss_type;
    typedef boct_tree<short, gauss_type > tree_type;
    boxm_scene<tree_type> *scene_in = static_cast<boxm_scene<tree_type>* > (scene_base.as_pointer());
    
    //parameters of the output scene are the same as thos of the input scene
    boxm_scene<boct_tree<short, bvpl_octree_sample<gauss_type> > > *scene_out = 
    new boxm_scene<boct_tree<short, bvpl_octree_sample<gauss_type> > >(scene_in->lvcs(), scene_in->origin(), scene_in->block_dim(), scene_in->world_dim());
    scene_out->set_paths(output_path, "response_scene");
    scene_out->set_appearance_model(BVPL_SAMPLE_BSTA_GAUSS_F1);
    scene_out->write_scene("/response_scene.xml");
    if(operator_name == "max_vector_operator")
    {
      bvpl_max_vector_operator<gauss_type> max_oper;
      
      if (functor_name == "gauss_convolution") {
        bvpl_gauss_convolution_functor functor;
        bvpl_scene_vector_operator scene_oper;
        scene_oper.operate(*scene_in, &max_oper, functor, kernel_vec, *scene_out, level);
        scene_ptr = scene_out;
        pro.set_output_val<boxm_scene_base_sptr>(0, scene_ptr);
        return true;
      }
    }
  }
  
  else
    return false;
  
  return false;
}


