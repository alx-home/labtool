//This is brl/bseg/boxm/pro/processes/boxm_clean_scene_process.cxx
#include <boxm/boxm_scene_base.h>
#include <boxm/boxm_scene.h>
//:
// \file
// \brief A process for removing any previously created scene data from disk
//
// \author Daniel Crispell
// \date Feb 18, 2010
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_parameters.h>

#include <brdb/brdb_value.h>

#include <vpgl/bgeo/bgeo_lvcs.h>
#include <vpgl/bgeo/bgeo_lvcs_sptr.h>

#include <vcl_string.h>
#include <vcl_iostream.h>
#include <vcl_fstream.h>

#include <boxm/boxm_sample_multi_bin.h>
#include <boxm/boxm_scene_parser.h>
//#include <boxm/boxm_init_scene.h>

//:global variables
namespace boxm_clean_scene_process_globals
{
  //this process takes no inputs
  const unsigned int n_inputs_ = 1;
  const unsigned int n_outputs_ = 0;
}

//:sets input and output types
bool boxm_clean_scene_process_cons(bprb_func_process& pro)
{
  //set output types
  using namespace boxm_clean_scene_process_globals;
  //process takes 1 input
  //input[0]: The scene
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "boxm_scene_base_sptr";
  if (!pro.set_input_types(input_types_))
    return false;

  return true;
}

//: removes data previously associated with scene
bool boxm_clean_scene_process(bprb_func_process& pro)
{
  using namespace boxm_clean_scene_process_globals;

  if ( pro.n_inputs() < n_inputs_ ){
    vcl_cout << pro.name() << "boxm_clean_scene_process: The input number should be " << n_inputs_<< vcl_endl;
    return false;
  }

  //get inputs:
  unsigned i = 0;
  boxm_scene_base_sptr scene = pro.get_input<boxm_scene_base_sptr>(i++);

  // check the input validity
  if (scene == 0) {
    vcl_cout << "boxm_clean_scene_process: scene is null, cannot run" << vcl_endl;
    return false;
  }

  switch (scene->appearence_model())
  {
  case BOXM_APM_MOG_GREY:
    {
      typedef boct_tree<short, boxm_sample<BOXM_APM_MOG_GREY> > tree_type;
      boxm_scene<tree_type> *s = static_cast<boxm_scene<tree_type>*> (scene.as_pointer());
      s->clean_scene();
      break;
    }
  case BOXM_APM_SIMPLE_GREY:
    {
      typedef boct_tree<short, boxm_sample<BOXM_APM_SIMPLE_GREY> > tree_type;
      boxm_scene<tree_type> *s = static_cast<boxm_scene<tree_type>*> (scene.as_pointer());
      s->clean_scene();
      break;
    }
  case BOXM_APM_MOB_GREY:
    {
      typedef boct_tree<short, boxm_sample<BOXM_APM_MOB_GREY> > tree_type;
      boxm_scene<tree_type> *s = static_cast<boxm_scene<tree_type>*> (scene.as_pointer());
      s->clean_scene();
      break;
    }
  default:
    {
      vcl_cout << "boxm_clean_scene_process: undefined APM type" << vcl_endl;
      return false;
    }
  }
  return true;
}

