// This is brl/bseg/boxm/pro/processes/boxm_describe_scene_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file
// \brief A process for describing the attributes of a scene
//
// \author J.L. Mundy
// \date January 24, 2010
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <boct/boct_tree.h>
#include <boxm/boxm_sample.h>
#include <boxm/boxm_scene_base.h>
#include <boxm/boxm_scene.h>
#include <boxm/boxm_compute_scene_statistics.h>
#include <boxm/boxm_apm_traits.h>
#include <bsta/bsta_histogram_sptr.h>
#include <bsta/io/bsta_io_histogram.h>

namespace boxm_describe_scene_process_globals
{
  const unsigned n_inputs_ = 1;
  const unsigned n_outputs_ = 4;
}

bool boxm_describe_scene_process_cons(bprb_func_process& pro)
{
  using namespace boxm_describe_scene_process_globals;
  //process takes 1 input
  //input[0]: scene binary file
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "boxm_scene_base_sptr";
  if (!pro.set_input_types(input_types_))
    return false;

  // process has 4 outputs:
  vcl_vector<vcl_string>  output_types_(n_outputs_);
  output_types_[0] = "bsta_histogram_sptr"; // Omega Histogram
  output_types_[1] = "bsta_histogram_sptr"; // Sigma Histogram
  output_types_[2] = "bsta_histogram_sptr"; // Level Histogram
  output_types_[3] = "unsigned";            // Number of leaves
  return true;
}
//
// This process produces four outputs
//  1) The distribution of "Omega" values where Omega = 1-e^( alpha x length )
//  2) The distribution of "Sigma" values where Sigma is the std_dev of
//     the appearance model. (currenly implemented only for simple grey)
//  3) The histogram of levels for leaves in the octree
//  4) The number of leaves in the tree
//
bool boxm_describe_scene_process(bprb_func_process& pro)
{
  using namespace boxm_describe_scene_process_globals;

  if ( !pro.verify_inputs() ) {
    vcl_cerr << pro.name() << ": invalid inputs\n";
    return false;
  }
  unsigned n_leaves = 0;
  //assign tree type
  boxm_scene_base_sptr scene_ptr = pro.get_input<boxm_scene_base_sptr>(0);
  if (scene_ptr->appearence_model() == BOXM_APM_MOG_GREY) {
    if (!scene_ptr->multi_bin())
    {
      vcl_cerr<<"boxm_describe_scene_process not yet implemented for Gaussian mixture\n";
      return false;//not implemented
    }
    else
    {
      vcl_cerr<<"boxm_describe_scene_process not yet implemented for multi-bin/Gaussian mixture\n";
      return false;
    }
  }
  else if (scene_ptr->appearence_model() == BOXM_APM_SIMPLE_GREY)
  {
    if (!scene_ptr->multi_bin()) {
      typedef boct_tree<short, boxm_sample<BOXM_APM_SIMPLE_GREY> > tree_type;
      boxm_scene<tree_type>* scene = dynamic_cast<boxm_scene<tree_type> *> (scene_ptr.as_pointer());

      bsta_histogram<float> omega_hist, sigma_hist, level_hist;
      if (!compute_scene_statistics(*scene, omega_hist, sigma_hist,
                                    level_hist, n_leaves))
        return false;
      vcl_cout << "Omega Hist\n";
      omega_hist.print_vals_prob();
      vcl_cout << "Sigma Hist\n";
      sigma_hist.print_vals_prob();
      vcl_cout << "Level Hist\n";
      level_hist.print_vals_prob();
      vcl_cout << "Number of Leaves " << n_leaves << '\n';
      pro.set_output_val<bsta_histogram_sptr>(0, brdb_value_t<bsta_histogram_sptr>(new bsta_histogram<float>(omega_hist)));
      pro.set_output_val<bsta_histogram_sptr>(1, brdb_value_t<bsta_histogram_sptr>(new bsta_histogram<float>(sigma_hist)));
      pro.set_output_val<bsta_histogram_sptr>(2, brdb_value_t<bsta_histogram_sptr>(new bsta_histogram<float>(level_hist)));
      pro.set_output_val<unsigned>(3, n_leaves);
    }
    else {
      vcl_cerr<<"boxm_describe_scene_process not yet implemented for multi-bin/simple_grey\n";
      return false;
    }
  }

  return true;
}
