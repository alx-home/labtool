// This is brl/bpro/core/vpgl_pro/processes/vpgl_create_local_rational_camera_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file

#include <bprb/bprb_parameters.h>
#include <vcl_iostream.h>
#include <vpgl/vpgl_camera.h>
#include <vpgl/vpgl_rational_camera.h>
#include <vpgl/vpgl_local_rational_camera.h>
#include <bgeo/bgeo_lvcs.h>
#include <bgeo/bgeo_lvcs_sptr.h>

//: initialization
bool vpgl_create_local_rational_camera_process_cons(bprb_func_process& pro)
{
  //this process takes one input: the filename
  bool ok=false;
  vcl_vector<vcl_string> input_types;
  input_types.push_back("vcl_string"); 
  input_types.push_back("vcl_string");
  ok = pro.set_input_types(input_types);
  if (!ok) return ok;

  vcl_vector<vcl_string> output_types;
  output_types.push_back("vpgl_camera_double_sptr");  
  ok = pro.set_output_types(output_types);
  if (!ok) return ok;
  
  return true;

}

//: Execute the process
bool vpgl_create_local_rational_camera_process(bprb_func_process& pro)
{
  if (pro.n_inputs() != 2) {
    vcl_cout << "vpgl_create_local_rational_camera_process: The number of inputs should be 2" << vcl_endl;
    return false;
  }

  // get the inputs
  vcl_string camera_filename = pro.get_input<vcl_string>(0);
  vcl_string lvcs_filename = pro.get_input<vcl_string>(1);

  //vpgl_rational_camera<double>* ratcam = read_local_rational_camera<double>(camera_filename);

  //if ( ratcam ) {
  //  vcl_cerr << "Error: rational camera is already local! Use load_rational_camera" << vcl_endl;
  //  return false;
  //}
  
  vpgl_rational_camera<double>* ratcam = read_rational_camera<double>(camera_filename);
  if ( !ratcam ) {
    vcl_cerr << "Failed to load rational camera from file" << camera_filename << vcl_endl;
    return false;
  }

  if (dynamic_cast<vpgl_local_rational_camera<double>*>(ratcam)) {
    vcl_cerr << "Error: rational camera is already local! Use load_rational_camera" << vcl_endl;
    return false;
  }

  bgeo_lvcs lvcs; 
  vcl_ifstream ifs(lvcs_filename.c_str());
  if(!ifs.good()) {
    vcl_cerr << "Error opening lvcs filename " << lvcs_filename << vcl_endl;
    return false;
  }
  
  lvcs.read(ifs);
  vpgl_camera_double_sptr local_ratcam = new vpgl_local_rational_camera<double>(lvcs, *ratcam);

  pro.set_output_val<vpgl_camera_double_sptr>(0, local_ratcam);

  return true;
}

