#ifndef bwm_observer_vgui_h
#define bwm_observer_vgui_h
//:
// \file

#include "bwm_observer.h"
#include "bwm_observer_img.h"
#include "bwm_observable_sptr.h"
#include "algo/bwm_soview2D_cross.h"
#include "algo/bwm_soview2D_vertex.h"

#include <vcl_vector.h>
#include <vcl_utility.h>

#include <vgui/vgui_easy2d_tableau.h>
#include <vgui/vgui_style.h>
#include <bgui/bgui_image_tableau.h>

#include <vgl/vgl_point_2d.h>
#include <vgl/vgl_point_3d.h>
#include <vgl/vgl_vector_3d.h>

#include <vsol/vsol_point_3d_sptr.h>
#include <vsol/vsol_point_3d.h>
#include <vsol/vsol_polygon_2d_sptr.h>
#include <vsol/vsol_polygon_3d_sptr.h>

#include <vpgl/vpgl_camera.h>

class bwm_observer_vgui : public bwm_observer_img, public bwm_observer
{
 public:

  typedef bwm_observer_img base;

  bwm_observer_vgui(bgui_image_tableau_sptr const& img);

  virtual ~bwm_observer_vgui() {}

  bool handle(const vgui_event &);

  virtual vcl_string type_name() const { return "bwm_observer_vgui"; }

  void add_new_obj(bwm_observable_sptr observable);

  void handle_update(vgui_message const& msg, bwm_observable_sptr observable);

  void show_vertices(bool);

  void update_all();

  void translate(vgl_vector_3d<double> T, bwm_observable_sptr object=0);

  void delete_object();

  void delete_all();

  void connect_inner_face(vsol_polygon_2d_sptr poly);

  void create_interior();

  bwm_observable_sptr selected_face(unsigned& face_id);

  //:select a given observable
  void select_object(bwm_observable_sptr const& obj);

  void label_roof();

  void label_wall();

  void intensity_profile(float start_col, float start_row,
                         float end_col, float end_row);

  virtual void proj_poly(vsol_polygon_3d_sptr poly3d,
                         vsol_polygon_2d_sptr& poly2d) = 0;

  virtual void proj_line(vsol_line_3d_sptr line_3d,
                         vsol_line_2d_sptr &line_2d)=0;

  virtual void proj_point(vgl_point_3d<double> world_pt,
                          vgl_point_2d<double> &image_pt) = 0;

  virtual void backproj_poly(vsol_polygon_2d_sptr poly2d,
                             vsol_polygon_3d_sptr& poly3d) = 0;

  //: move the correspondence location and replace the cross soview
  void set_corr(float x, float y);

  //: the current location of the correspondence point
  void corr_image_pt(float& x, float& y);

  //: the current location of the correspondence point, if corr is valid
  bool corr_image_pt(vgl_point_2d<double>& pt);


  //: remove the cross soview and set its pointer to null
  void remove_corr_pt();

  void record_corr_pt() { corr_valid_ = false; }

  //: display a cross soview at the specified location
  void add_cross(float x, float y, float r);

 protected:
  //allows children to take some action if a correspondence is set
  virtual void correspondence_action() {}

  bwm_observer_vgui() { show_vertices_ = true; }

  enum BWM_DRAW_MODE mode_;

  vgui_style_sptr mesh_style_;
  vgui_style_sptr vertex_style_;
  vgui_style_sptr select_style_;
  vgui_style_sptr terrain_style_;

  bool show_vertices_;
  bool corr_valid_;

  //: the current correspondence point
  vcl_vector<vcl_pair<vgl_point_2d<double>, bwm_soview2D_cross * > > corr_;

  //: objects are kept as a triple (bwm_observable *, face_id, bgui_vsol_soview2D_polygon*)
  vcl_map<bwm_observable_sptr, vcl_map<unsigned, bgui_vsol_soview2D* > > objects_;

  //: vertices are kept as a pair (bwm_observable *, vector<bwm_soview2D_vertex*> )
  vcl_map<bwm_observable_sptr, vcl_vector<bwm_soview2D_vertex* > > object_verts_;
  vcl_map<bwm_observable_sptr, vcl_vector<vsol_point_2d_sptr> > object_verts_xy_;

  vcl_map<unsigned, vsol_point_3d_sptr> vertex_3d_map_;

  bwm_observable_sptr moving_face_;

  bwm_observable_sptr find_object(unsigned soview2d_id, unsigned &face_id);

  unsigned get_selected_3d_vertex_index(unsigned poly_id);

  vsol_point_3d_sptr selected_vertex();

  void print_selected_vertex();

#if 0
  //: makes the polygon a little smaller to prevent the face edges overlapping
  vsol_polygon_2d_sptr shrink_face(vsol_polygon_2d_sptr poly);
#endif

  void draw_mesh(bwm_observable_sptr observable,
                 vcl_map<unsigned, bgui_vsol_soview2D* > &poly_list,
                 vcl_vector<bwm_soview2D_vertex*> &vertx_list,
                 vcl_vector<vsol_point_2d_sptr> &vertx_xy_list);

  void draw_vertices(bwm_observable_sptr observable,
                     vcl_map<unsigned, bgui_vsol_soview2D* > list,
                     bool selectable,
                     vcl_vector<bwm_soview2D_vertex*> &vertx_list,
                     vcl_vector<vsol_point_2d_sptr> &vertx_xy_list);
};

#endif // bwm_observer_vgui_h
