#include "bwm_observer_mgr.h"
//:
// \file
#include "algo/bwm_utils.h"
#include "bwm_world.h"
#include <vgl/vgl_point_2d.h>
#include <vgl/vgl_vector_2d.h>
#include <vgl/vgl_point_3d.h>
#include <vgl/vgl_plane_3d.h>
#include <vpgl/algo/vpgl_adjust_rational_trans_onept.h>
#include <vsl/vsl_basic_xml_element.h>
#include <vgui/vgui_dialog.h>

#include <vcl_iostream.h>

bwm_observer_cam* bwm_observer_mgr::BWM_MASTER_OBSERVER = 0;
bwm_observer_cam* bwm_observer_mgr::BWM_EO_OBSERVER = 0;
bwm_observer_cam* bwm_observer_mgr::BWM_OTHER_MODE_OBSERVER = 0;

bwm_observer_mgr* bwm_observer_mgr::instance_ = 0;

bwm_observer_mgr* bwm_observer_mgr::instance()
{
  if (!instance_)
    instance_ = new bwm_observer_mgr();
  return bwm_observer_mgr::instance_;
}

void bwm_observer_mgr::clear()
{
  corr_mode_ = IMAGE_TO_IMAGE;
  n_corrs_ = SINGLE_PT_CORR;
  corr_type_ = FEATURE_CORR;
  start_corr_ = false;
  corr_list_.clear();
}

vcl_vector<bwm_observer_cam*> bwm_observer_mgr::observers_cam()
{
  vcl_vector<bwm_observer_cam*> v;
  for (unsigned i=0; i< observers_.size(); i++) {
    if (observers_[i]->type_name().compare("bwm_observer_cam") == 0)
      v.push_back(static_cast<bwm_observer_cam*> (observers_[i]));
    if (observers_[i]->type_name().compare("bwm_observer_rat_cam") == 0)
      v.push_back(static_cast<bwm_observer_cam*> (observers_[i]));
    if (observers_[i]->type_name().compare("bwm_observer_proj_cam") == 0)
      v.push_back(static_cast<bwm_observer_cam*> (observers_[i]));
    if (observers_[i]->type_name().compare("bwm_observer_video") == 0)
      v.push_back(static_cast<bwm_observer_cam*> (observers_[i]));
  }
  return v;
}

vcl_vector<bwm_observer_rat_cam*> bwm_observer_mgr::observers_rat_cam()
{
  vcl_vector<bwm_observer_rat_cam*> v;

  for (unsigned i=0; i< observers_.size(); i++) {
    if (observers_[i]->type_name().compare("bwm_observer_rat_cam") == 0)
      v.push_back(static_cast<bwm_observer_rat_cam*> (observers_[i]));
  }

  return v;
}

void bwm_observer_mgr::add(bwm_observer* o)
{
  observers_.push_back(o);

  // make the connection between this observer and the available observables
  vcl_vector<bwm_observable_sptr> objects = bwm_world::instance()->objects();
#if 0
  vgui_message msg;
  msg.data = "new";
#endif
  for (unsigned i=0; i<objects.size(); i++) {
    bwm_observable_sptr obj = objects[i];
    if (!obj)
      vcl_cerr << "ERROR: world has an invalid (NULL) object!\n";
    else {
      obj->attach(o);
      o->add_new_obj(obj);
    }
  }
}

void bwm_observer_mgr::attach(bwm_observable_sptr obs)
{
  for (unsigned i=0; i<observers_.size(); i++)
    obs->attach(observers_[i]);
}

void bwm_observer_mgr::remove(bwm_observer* observer)
{
  for (unsigned i=0; i<observers_.size(); i++)
    if (observers_[i] == observer)
      observers_.erase(observers_.begin()+i);
}

bool bwm_observer_mgr::comp_avg_camera_center(vgl_point_3d<double> &cam_center)
{
  unsigned num = 0;
  double x=0, y=0, z=0;
  vgl_point_3d<double> c;

  // go through the camera observers and compute a camera center
  for (unsigned i=0; i<observers_.size(); i++) {
    if (observers_[i]->type_name().compare("bwm_observer_rat_cam") == 0) {
      bwm_observer_rat_cam* obs = static_cast<bwm_observer_rat_cam*> (observers_[i]);
      obs->camera_center(c);
      vgl_point_3d<double> temp(c);
      x += temp.x();
      y += temp.y();
      z += temp.z();
      num++;
    }
  }

  if (num == 0)
    return false;

  cam_center.set(x/num, y/num, z/num);
  return true;
}

#if 0
//Set a world point to be used in correspondences from world to image
void bwm_observer_mgr::set_world_pt(vgl_point_3d<double> world_pt)
{
  corr_world_pt_ = world_pt;
  world_point_valid_ = true;
}
#endif
//Set the correspodence mode which is either image_to_image or world_to_image
//The world_to_image mode is only possible if there is a world point available
//The existence of a valid world point is defined by the flag
// world_point_valid_
void bwm_observer_mgr::set_corr_mode()
{
  vgui_dialog params ("Correspondence Mode");
  vcl_string empty="";
  vcl_vector<vcl_string> modes;
  int mode = bwm_observer_mgr::instance()->corr_mode();
  modes.push_back("Image to Image");
  modes.push_back("World to Image");

  vcl_vector<vcl_string> n_corrs;
  int n = bwm_observer_mgr::instance()->n_corrs();
  n_corrs.push_back("Single Correspondence ");
  n_corrs.push_back("Multiple Correspondence ");

  vcl_vector<vcl_string> types;
  int t = bwm_observer_mgr::instance()->corr_type();
  types.push_back("Feature Correspondence ");
  types.push_back("Terrain Correspondence ");

  vcl_string name, type;
  params.choice("Correspondence Mode", modes, mode);
  params.choice("Correspondence Type ", types, t);
  params.choice("Number of Correspondences ", n_corrs, n);

  if (!params.ask())
    return;
  if (mode ==bwm_observer_mgr::WORLD_TO_IMAGE)
    if (bwm_world::instance()->world_pt_valid()) {
      corr_mode_ =  bwm_observer_mgr::WORLD_TO_IMAGE;
      return;
    }
    else {
      vcl_cout << "In bwm_observer_mgr::set_corr_mode() -\n"
               << " can't use WORLD_TO_IMAGE mode since the 3-d world"
               << " point is not defined\n";
    }

  if (t == bwm_observer_mgr::FEATURE_CORR) {
    corr_type_ = bwm_observer_mgr::FEATURE_CORR;
  }
  else if (t == bwm_observer_mgr::TERRAIN_CORR) {
    corr_type_ = bwm_observer_mgr::TERRAIN_CORR;
  }
  else
    vcl_cout << "In bwm_observer_mgr::set_corr_mode() Undefined TYPE -\n" ;


  corr_mode_ = bwm_observer_mgr::IMAGE_TO_IMAGE;

  n_corrs_ = (BWM_N_CORRS) n;
}

void bwm_observer_mgr::collect_corr()
{
  bwm_corr_sptr corr = new bwm_corr();
  vgl_point_2d<double> pt;

  // set mode
  if (corr_mode_ == IMAGE_TO_IMAGE)
    corr->set_mode(true);
  else if (corr_mode_ == WORLD_TO_IMAGE) {
    vgl_point_3d<double> wpt;
    if (!bwm_world::instance()->world_pt(wpt))
    {
      vcl_cerr << " In bwm_observer_mgr::collect_corr() -"
               << " Can't do world to image, world pt invalid\n";
      return;
    }
    corr->set_mode(false);
    corr->set_world_pt(wpt);
  }
  else
    vcl_cerr << "Unknown correspondence mode!\n";

  bool found = false;
  vcl_vector<bwm_observer_cam*> obs_cam = this->observers_cam();
  for (unsigned i=0; i< obs_cam.size(); i++) {
    bwm_observer_cam* obs = obs_cam[i];
    if (obs->corr_pt(pt)) {
      corr->set_match(obs, pt.x(), pt.y());
      obs->record_corr_pt();
      found = true;
    }
  }

  if (found)
  {
    if (n_corrs_==MULTIPLE_CORRS) {
      if (corr_type_ == FEATURE_CORR)
        corr_list_.push_back(corr);
      else if (corr_type_ == TERRAIN_CORR)
        terrain_corr_list_.push_back(corr);
      return;
    }
    else if (n_corrs_==SINGLE_PT_CORR) // in this case there can be only one
    {
      if (corr_type_ == FEATURE_CORR) {
        corr_list_.clear();
        corr_list_.push_back(corr);
      }
      else if (corr_type_ == TERRAIN_CORR) {
        terrain_corr_list_.clear();
        terrain_corr_list_.push_back(corr);
      }
      return;
    }
  }
  vcl_cerr << "No Correspondence SET yet!!\n";
}

void bwm_observer_mgr::set_corr(bwm_corr_sptr corr)
{
  if (corr->num_matches() > 0)
    if (corr_type_ == FEATURE_CORR) {
      corr_list_.push_back(corr);
    }
    else if (corr_type_ == TERRAIN_CORR) {
      terrain_corr_list_.push_back(corr);
    }
}

void bwm_observer_mgr::update_corr(bwm_observer_cam* obs,
                                   vgl_point_2d<double> old_pt,
                                   vgl_point_2d<double> new_pt)
{
  for (unsigned i=0; i< corr_list_.size(); i++) {
    if (corr_type_ == FEATURE_CORR) {
      bwm_corr_sptr corr = corr_list_[i];
      if (corr->update_match(obs, old_pt, new_pt))
       return;
    }
    else if (corr_type_ == TERRAIN_CORR) {
      bwm_corr_sptr corr = terrain_corr_list_[i];
      if (corr->update_match(obs, old_pt, new_pt))
       return;
    }
  }
}

//: finds out if that observer involved with any of the correspondences
bool bwm_observer_mgr::obs_in_corr(bwm_observer_cam *obs)
{
  for (unsigned i=0; i<corr_list_.size(); i++) {
    vgl_point_2d<double> c;
    if (corr_list_[i]->obs_in(obs, c))
      return true;
  }
  return false;
}

//: returns the list correspondence points of a given observer
vcl_vector<vgl_point_2d<double> >
bwm_observer_mgr::get_corr_points(bwm_observer_cam *obs)
{
  vcl_vector<vgl_point_2d<double> > corr_list;
  for (unsigned i=0; i<corr_list_.size(); i++) {
    vgl_point_2d<double> corr;
    if (corr_list_[i]->obs_in(obs, corr)) {
      corr_list.push_back(corr);
    }
  }
  return corr_list;
}

void bwm_observer_mgr::save_corr(vcl_ostream& s)
{
  if (corr_list_.size() == 0)
    vcl_cerr << "No correspondences to save yet!\n";
  else
  {
    vcl_string fname = bwm_utils::select_file();
    vcl_ofstream s(fname.data());

#if 0
    s << "Cameras:" << vcl_endl;
#endif
    // first write down the camera info
    vcl_map<bwm_observer_cam*, unsigned> camera_map;
    for (unsigned i=0; i< observers_.size(); i++)
    {
      if ((observers_[i]->type_name().compare("bwm_observer_rat_cam") == 0) ||
          (observers_[i]->type_name().compare("bwm_observer_cam_proj") == 0))
      {
        bwm_observer_cam* obs = static_cast<bwm_observer_cam *> (observers_[i]);

        // check if that camera is involved with any of the correspondences
        if (obs_in_corr(obs)) {
          s << "CAM_TAB: " << i << vcl_endl
            << "IMAGE: " << obs->image_tableau()->file_name() << vcl_endl
            << "CAMERA_TYPE: " ;
          if (observers_[i]->type_name().compare("bwm_observer_rat_cam") == 0)
            s << "rational" << vcl_endl;
          else if (observers_[i]->type_name().compare("bwm_observer_cam_proj") == 0)
            s << "projective" << vcl_endl;
          s << "CAMERA_PATH: " << obs->camera_path() << vcl_endl << vcl_endl;
          camera_map[obs] = i;
        }
      }
    }

    s << "CORRESPONDENCES: " << corr_list_.size() << vcl_endl
      << "CORR_MODE: ";
    if (corr_mode_ == IMAGE_TO_IMAGE)
      s << "IMAGE_TO_IMAGE" << vcl_endl;
    else
      s << "WORLD_TO_IMAGE" << vcl_endl;
    for (unsigned i=0; i< corr_list_.size(); i++)
    {
      bwm_corr_sptr corr = corr_list_[i];
      s << "C: " << corr->num_matches() << vcl_endl;

      vcl_vector<bwm_observer_cam*> obs = corr->observers();
#if 0
      s << obs.size() << vcl_endl;
#endif
      if (! corr->mode()) { // WORLD TO IMAGE
        s << "WORLD_POINT: " << corr->world_pt().x() << ' ' << corr->world_pt().y()
          << ' ' << corr->world_pt().z() << vcl_endl;
      }
      for (unsigned j=0; j< obs.size(); j++) {
        vgl_point_2d<double> p;
        if (corr->match(obs[j], p))
          s << camera_map[obs[j]] << ' ' << p.x() << ' ' << p.y() << vcl_endl;
      }
    }
    s << "END" << vcl_endl;
  }
}

void bwm_observer_mgr::save_corr_XML()
{
  if (corr_list_.size() == 0)
    vcl_cerr << "No correspondences to save yet!\n";
  else
  {
    vcl_string fname = bwm_utils::select_file();
    vcl_ofstream s(fname.data());

    s << "<BWM_CONFIG>" << vcl_endl
      << "<TABLEAUS>" << vcl_endl;
    // first write down the camera info
    vcl_map<bwm_observer_cam*, unsigned> camera_map;
    for (unsigned i=0; i< observers_.size(); i++)
    {
      if ((observers_[i]->type_name().compare("bwm_observer_rat_cam") == 0) ||
          (observers_[i]->type_name().compare("bwm_observer_cam_proj") == 0))
      {
        bwm_observer_cam* obs = static_cast<bwm_observer_cam *> (observers_[i]);

        // check if that camera is involved with any of the correspondences
        if (obs_in_corr(obs))
        {
          vsl_basic_xml_element tab("CameraTableau");
          tab.add_attribute("name", obs->tab_name());
          tab.x_write_open(s);

          vsl_basic_xml_element img_path("imagePath");
          img_path.append_cdata(obs->image_tableau()->file_name());
          img_path.x_write(s);

          vcl_string type;
          if (observers_[i]->type_name().compare("bwm_observer_rat_cam") == 0)
            type = "rational";
          else if (observers_[i]->type_name().compare("bwm_observer_cam_proj") == 0)
            type = "projective";

          vsl_basic_xml_element cam_path("cameraPath");
          cam_path.add_attribute("type", type);
          cam_path.append_cdata(obs->camera_path());
          cam_path.x_write(s);
          camera_map[obs] = i;
          tab.x_write_close(s);
        }
      }
    }
    s << "</TABLEAUS>" << vcl_endl;

    // write out the correspondence list
    vcl_string m = "";
    if (corr_mode_ == IMAGE_TO_IMAGE)
      m = "IMAGE_TO_IMAGE";
    else
      m = "WORLD_TO_IMAGE";
    vsl_basic_xml_element xml_element("correspondences");
    xml_element.add_attribute("mode", m);

    vcl_string n = "";
    if (n_corrs_==MULTIPLE_CORRS)
      n = "MULTIPLE";
    else
      n = "SINGLE";
    xml_element.add_attribute("type", n);
    xml_element.x_write_open(s);


    for (unsigned i=0; i< corr_list_.size(); i++) {
      bwm_corr_sptr corr = corr_list_[i];
      vcl_cout << corr->num_matches() << vcl_endl;
      corr->x_write(s);
    }
    xml_element.x_write_close(s);
    s << "</BWM_CONFIG>" << vcl_endl;
  }
}

void bwm_observer_mgr::delete_last_corr()
{
  unsigned i = corr_list_.size();
  if (i > 0) {
    // first notify the observer to delete the corr point on the screen
    bwm_corr_sptr corr = corr_list_[i-1];
    vcl_vector<bwm_observer_cam*> obs = corr->observers();
    for (unsigned i=0; i<obs.size(); i++) {
      obs[i]->remove_corr_pt();
      obs[i]->post_redraw();
    }
    corr_list_.pop_back();  // removes the last element
  }
}

void bwm_observer_mgr::delete_all_corr()
{
  while (corr_list_.size() > 0) {
    delete_last_corr();
  }
}

void bwm_observer_mgr::print_observers()
{
  for (unsigned i=0; i< observers_.size(); i++) {
    vcl_cout <<  i << " - " << observers_[i]->type_name() << vcl_endl;
  }
}

void bwm_observer_mgr::move_to_corr()
{
  if (!corr_list_.size())
  {
    vcl_cerr << "In bwm_observer_mgr::move_to_corr() -"
             << " no correspondences to move to\n";
    return;
  }
  bwm_corr_sptr corr = corr_list_[0];
  vcl_vector<bwm_observer_cam*> obs = corr->observers();
  for (vcl_vector<bwm_observer_cam*>::iterator oit = obs.begin();
       oit != obs.end(); ++oit)
  {
    vgl_point_2d<double> p;
    //observer has a match so can zoom
    if (corr->match(*oit, p))
    {
      float x = static_cast<float>(p.x());
      float y = static_cast<float>(p.y());
      (*oit)->move_to_point(x, y);
    }
  }
}

void bwm_observer_mgr::adjust_camera_offsets()
{
  if (!corr_list_.size())
    return;
  bwm_corr_sptr corr = corr_list_[0];
  vcl_vector<bwm_observer_cam*> obs = corr->observers();
  vcl_vector<vpgl_rational_camera<double> > rcams;
  vcl_vector<vgl_point_2d<double> > cpoints;
  for (vcl_vector<bwm_observer_cam*>::iterator oit = obs.begin();
       oit != obs.end(); ++oit)
  {
    if ((*oit)->type_name() != "bwm_observer_rat_cam")
      continue;
    bwm_observer_rat_cam* obscr =
      static_cast<bwm_observer_rat_cam*>(*oit);
    rcams.push_back(obscr->camera());
    vgl_point_2d<double> p;
    if (corr->match(*oit, p))
      cpoints.push_back(p);
  }
  if (cpoints.size()!=rcams.size())
  {
    vcl_cerr << "In bwm_observer_mgr::adjust_image_offsets - "
             << " inconsistent number of points and cameras\n";
    return;
  }

  vcl_cout << "Executing adjust image offsets\n";
  vcl_vector<vgl_vector_2d<double> > cam_trans;
  vgl_point_3d<double> intersection;
  if (!vpgl_adjust_rational_trans_onept::adjust(rcams, cpoints, cam_trans,
                                                intersection))
  {
    vcl_cerr << "In bwm_observer_rat_cam::adjust_image_offsets - "
             << " adjustment failed\n";
    return;
  }

  vgl_plane_3d<double> world_plane(0,0,1,-intersection.z());
  vcl_vector<vgl_vector_2d<double> >::iterator ti = cam_trans.begin();
  vcl_vector<bwm_observer_cam*>::iterator oit = obs.begin();
  for (; oit != obs.end() && ti != cam_trans.end(); ++oit, ++ti)
  {
    if ((*oit)->type_name() != "bwm_observer_rat_cam")
      continue;
    bwm_observer_rat_cam* obsrc =
      static_cast<bwm_observer_rat_cam*>(*oit);
    vcl_cout << "Shifting camera[" << obsrc->camera_path() <<  "]:\n("
             << (*ti).x() << ' ' << (*ti).y() << "):\n point_3d("
             << intersection.x() << ' ' << intersection.y()
             << ' ' << intersection.z() << ")\n";
    obsrc->shift_camera((*ti).x(), (*ti).y());
    // here is where we would set the terrain plane an maybe not
    // do anything to the projection plane of each observer.
    // but this approach works for now.
    obsrc->set_proj_plane(world_plane);
    obsrc->update_all();
  }

  //send the objects in the world the fact that they need to redisplay
  vcl_vector<bwm_observable_sptr> objs = bwm_world::instance()->objects();
  for (vcl_vector<bwm_observable_sptr>::iterator oit = objs.begin();
       oit != objs.end(); ++oit)
    (*oit)->send_update();

  //
  // now that the 3-d intersection is available, the correspondence mode
  // should be changed to "world_to_image." The mode should only be
  // chanaged back to "image_to_image" if a new image is added to the
  // site and the intersection point is re-computed
  //
  for (vcl_vector<bwm_corr_sptr>::iterator cit = corr_list_.begin();
       cit != corr_list_.end(); ++cit)
  {
    (*cit)->set_mode(false); //mode is set to world_to_image
    (*cit)->set_world_pt(intersection);
  }

  bwm_world::instance()->set_world_pt(intersection);
  this->set_corr_mode(bwm_observer_mgr::WORLD_TO_IMAGE);
}

void bwm_observer_mgr::find_terrain_points(vcl_vector<vgl_point_3d<double> >& points)
{
  if (!terrain_corr_list_.size())
    return;

  for (unsigned i=0; i<terrain_corr_list_.size(); i++) {
    bwm_corr_sptr corr = terrain_corr_list_[i];
    vcl_vector<bwm_observer_cam*> obs = corr->observers();
    vcl_vector<vpgl_rational_camera<double> > rcams;
    vcl_vector<vgl_point_2d<double> > cpoints;
    for (vcl_vector<bwm_observer_cam*>::iterator oit = obs.begin();
         oit != obs.end(); ++oit)
    {
      if ((*oit)->type_name() != "bwm_observer_rat_cam")
        continue;
      bwm_observer_rat_cam* obscr =
        static_cast<bwm_observer_rat_cam*>(*oit);
      rcams.push_back(obscr->camera());
      vgl_point_2d<double> p;
      if (corr->match(*oit, p))
        cpoints.push_back(p);
    }
    if (cpoints.size()!=rcams.size())
    {
      vcl_cerr << "In bwm_observer_mgr::adjust_image_offsets - "
               << " inconsistent number of points and cameras\n";
      return;
    }

    vcl_cout << "Executing adjust image offsets\n";
    vcl_vector<vgl_vector_2d<double> > cam_trans;
    vgl_point_3d<double> intersection;
    if (!vpgl_adjust_rational_trans_onept::adjust(rcams, cpoints, cam_trans,
                                                  intersection))
    {
      vcl_cerr << "In bwm_observer_rat_cam::find_terrain_points - "
               << " adjustment failed\n";
      return;
    }
    points.push_back(intersection);
  }
  terrain_corr_list_.clear();
}
