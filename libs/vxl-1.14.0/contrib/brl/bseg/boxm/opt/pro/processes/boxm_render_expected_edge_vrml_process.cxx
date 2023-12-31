// This is brl/bseg/boxm/opt/pro/processes/boxm_render_expected_edge_vrml_process.cxx
#include <bprb/bprb_func_process.h>
//:
// \file
// \brief A class for obtaining roc curve from change detection results.
//
// \author Gamze Tunali
// \date Apr 14, 2009
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <boxm/boxm_scene_base.h>
#include <boxm/boxm_scene.h>
#include <boxm/boxm_render_image.h>
#include <boxm/boxm_apm_traits.h>
#include <boxm/boxm_sample.h>
#include <boxm/boxm_sample_multi_bin.h>
#include <boxm/boxm_inf_line_sample.h>
#include <bvrml/bvrml_write.h>
#include <vil/vil_image_view.h>
#include <vgl/vgl_point_3d.h>
#include <vgl/vgl_intersection.h>
#include <vcl_fstream.h>

namespace boxm_render_expected_edge_vrml_process_globals
{
  const unsigned n_inputs_ = 5;
  const unsigned n_outputs_ = 0;
}

bool boxm_render_expected_edge_vrml_process_cons(bprb_func_process& pro)
{
  using namespace boxm_render_expected_edge_vrml_process_globals;
  //process takes 5 inputs
  //input[0]: scene binary file
  //input[1]: camera
  //input[2]: the path for vrml file
  //input[3]: threshold
  //input[4]: s (to write every s cell)
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "boxm_scene_base_sptr";
  input_types_[1] = "vpgl_camera_double_sptr";
  input_types_[2] = "vcl_string";
  input_types_[3] = "float";
  input_types_[4] = "int";
  if (!pro.set_input_types(input_types_))
    return false;

  // process has no output:
  vcl_vector<vcl_string>  output_types_(n_outputs_);

  return true;
}

bool boxm_render_expected_edge_vrml_process(bprb_func_process& pro)
{
  using namespace boxm_render_expected_edge_vrml_process_globals;

  if ( pro.n_inputs() < n_inputs_ ) {
    vcl_cerr << pro.name() << ": The input number should be " << n_inputs_<< vcl_endl;
    return false;
  }

  //get the inputs
  unsigned i = 0;
  boxm_scene_base_sptr scene_ptr = pro.get_input<boxm_scene_base_sptr>(i++);
  vpgl_camera_double_sptr camera = pro.get_input<vpgl_camera_double_sptr>(i++);
  vcl_string path = pro.get_input<vcl_string>(i++);
  float threshold = pro.get_input<float>(i++);
  int s = pro.get_input<int>(i++);

  vcl_ofstream stream(path.c_str());

  if (scene_ptr->appearence_model() == BOXM_EDGE_LINE) {
    if (!scene_ptr->multi_bin())
    {
      typedef boct_tree<short, boxm_inf_line_sample<float> > type;
      boxm_scene<type>* scene = dynamic_cast<boxm_scene<type>*> (scene_ptr.as_pointer());
      if (!scene) {
        vcl_cout << "boxm_render_expected_edge_process: the scene is not of expected type" << vcl_endl;
        return false;
      }
      bvrml_write::write_vrml_header(stream);
      vgl_point_3d<double> origin(450.0,450.0,0.0);
      vgl_vector_3d<double> dirx(1,0,0);
      vgl_vector_3d<double> diry(0,1,0);
      vgl_vector_3d<double> dirz(0,0,1);
      bvrml_write::write_vrml_line(stream,origin,dirx,3,1,0,0);
      bvrml_write::write_vrml_line(stream,origin,diry,3,0,1,0);
      bvrml_write::write_vrml_line(stream,origin,dirz,3,0,0,1);

      // for each block
      boxm_block_iterator<type> iter(scene);
      iter.begin();
      while (!iter.end())
      {
        scene->load_block(iter.index());
        boxm_block<type>* block = *iter;
        type* tree = block->get_tree();
        vcl_vector<boct_tree_cell<short,boxm_inf_line_sample<float> >*> cells = tree->leaf_cells();
        
        // iterate over cells
        for (unsigned i=0; i<cells.size(); ++i)
        {
          boct_tree_cell<short,boxm_inf_line_sample<float> >* cell = cells[i];
          boxm_inf_line_sample<float> data = cell->data();
          vgl_infinite_line_3d<float> line = data.line_;
          // TODO: revise with segment length
          vgl_vector_3d<double> dir(line.direction().x(), line.direction().y(), line.direction().z());
          if (line.x0().x()!=0 && line.x0().y()!=0) {
            vgl_point_3d<double> p0,p1;
            vgl_box_3d<double> bb = tree->cell_bounding_box(cell);
            // convert to line type (from float to double)
            vgl_vector_2d<double> x0(line.x0().x(), line.x0().y());
            vgl_infinite_line_3d<double> dline(x0,dir);
            if (vgl_intersection<double>(bb, dline, p0, p1)) {
              vgl_vector_3d<double> dir(p1-p0);
              double length=dir.length();
              dir/=length;
              bvrml_write::write_vrml_line(stream, p0,dir,length,1.f,0.f,0.f);
            }
          }
        }
        iter++;
      }
    }
    else
    {
      vcl_cerr << "Ray tracing version not yet implemented\n";
      return false;
    }
  } else {
    vcl_cerr << "boxm_render_expected_edge_vrml_process: undefined APM type\n";
    return false;
  }

  // no output
  return true;
}
