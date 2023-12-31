// This is brl/bseg/bvxm/pro/processes/bvxm_report_statistics_point_cloud_process.h
#ifndef bvxm_report_statistics_point_cloud_process_h_
#define bvxm_report_statistics_point_cloud_process_h_
//:
// \file
// \brief A class for update process of a voxel world.
//
// \author Vishal JAin
// \date Nov 11, 2009
// \verbatim
// \endverbatim

#include <bprb/bprb_func_process.h>

//: global variables
namespace bvxm_report_statistics_point_cloud_process_globals
{
  const unsigned n_inputs_ = 1;
  const unsigned n_outputs_ = 0;
}

bool bvxm_report_statistics_point_cloud_process_cons(bprb_func_process& pro);

bool bvxm_report_statistics_point_cloud_process(bprb_func_process& pro);

#endif // bvxm_report_statistics_point_cloud_process_h_
