#ifndef boxm_generate_edge_tangent_sample_functor_h
#define boxm_generate_edge_tangent_sample_functor_h
//:
// \file
#include <boxm/boxm_apm_traits.h>
#include <boxm/opt/boxm_raytrace_function.h>
#include <boxm/boxm_edge_tangent_sample.h>
#include <boxm/boxm_inf_line_sample.h>
#include <boxm/boxm_plane_obs.h>
#include <boxm/boxm_mog_grey_processor.h>
#include <boxm/boxm_simple_grey_processor.h>
#include <vgl/vgl_homg_plane_3d.h>
#include <vil/vil_math.h>
#include <vil/vil_save.h>
#include <vcl_iostream.h>

template <class T, class T_aux>
class boxm_generate_edge_tangent_sample_functor
{
 public:
  boxm_generate_edge_tangent_sample_functor(vil_image_view<float> &observation,
                                            unsigned int /*ni*/=0, unsigned /*nj*/=0)
    : obs_(observation)
  {
    scene_read_only_=true;
    is_aux_=true;
    // make sure that the image has 4 planes ((a,b,c,d) params of a plane ax+by+cz=d )
    if (observation.nplanes() != 4)
      vcl_cerr << "boxm_generate_edge_tangent_sample_functor: the image does not have 4 planes\n";
  }

  inline bool step_cell(unsigned int i, unsigned int j,
                        vgl_point_3d<double> s0, vgl_point_3d<double> s1,
                        T &cell_value,
                        T_aux &aux_val)
  {
    const float seg_len = (float)(s1 - s0).length();
    float a = obs_(i,j,0);
    float b = obs_(i,j,1);
    float c = obs_(i,j,2);
    float d = obs_(i,j,3);
  
    if (a||b||c||d){
      vgl_homg_plane_3d<float> p(a,b,c,d);
      boxm_plane_obs<float> observation(p,seg_len);
      aux_val.insert(observation);
    }
    return true;
  }

 public:
  bool scene_read_only_;
  bool is_aux_;

 private:
  vil_image_view<float> &obs_;
};

template <class T_loc, class T_data>
void boxm_generate_edge_tangent_sample_rt(boxm_scene<boct_tree<T_loc, T_data > > &scene,
                                          vpgl_camera_double_sptr cam,
                                          vil_image_view<float> &obs,
                                          vcl_string iname)
{
    typedef boxm_edge_tangent_sample<float> aux_datatype;
    boxm_aux_scene<T_loc, T_data, aux_datatype> aux_scene(&scene,iname, boxm_aux_scene<T_loc,T_data,aux_datatype>::CLONE);
    typedef boxm_generate_edge_tangent_sample_functor<boxm_inf_line_sample<float>,aux_datatype> func;
    boxm_raytrace_function<func,T_loc, T_data, aux_datatype> raytracer(scene,aux_scene,cam.ptr(),obs.ni(),obs.nj());
    vcl_cerr << "PROCESSING EDGE IMAGE\n";
    func functor(obs,obs.ni(),obs.nj());
    raytracer.run(functor);

    //aux_scene.clean_scene();
    vcl_cerr << "DONE.\n";
}

#endif // boxm_generate_edge_tangent_sample_functor_h
