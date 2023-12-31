#include "bwm_world.h"
#include "bwm_observer_mgr.h"
#include "algo/bwm_shape_file.h"
#include "algo/bwm_algo.h"
#include "algo/bwm_utils.h"

#include <vcl_iostream.h>
#include <vcl_sstream.h>

#include <vul/vul_file.h>
#include <vgl/vgl_vector_3d.h>
#include <vgui/vgui_dialog.h>

#include "bwm_observable.h"
#include "bwm_observable_textured_mesh.h"

bwm_world* bwm_world::instance_ = 0;

bwm_world* bwm_world::instance()
{
  if (!instance_)
    instance_ = new bwm_world();
  return bwm_world::instance_;
}


void  bwm_world::set_world_pt(vgl_point_3d<double> const& pt)
{
  world_pt_ = pt;
  vgl_vector_3d<double> normal(0, 0, 1);//z axis
  world_plane_ = vgl_plane_3d<double>(normal, pt);
  world_pt_valid_ = true;
}

// removes an observable from the world
bool bwm_world::remove(bwm_observable_sptr obj)
{
  // find the object
  vcl_vector<bwm_observable_sptr>::iterator it = objects_.begin();
  while (it != objects_.end()) {
    if (*it == obj) {
      objects_.erase(it, it+1);
      return true;
    }
    it++;
  }
  return true;
}

void bwm_world::set_lvcs(double lat, double lon, double elev)
{
  // clean up the olde one, if any
  lvcs_ = bgeo_lvcs(lat, lon, elev);
  lvcs_valid_ = true;
}

bool bwm_world::get_lvcs(bgeo_lvcs &lvcs)
{
  vgl_point_3d<double> center;

#if 0 // commented out
  // if lvcs is set get that
  if (lvcs_valid_) {
    lvcs = lvcs_;
    return true;
  }

  // else, create from the world point
  else if (world_pt_valid_) {
    lvcs = bgeo_lvcs(world_pt_.x(), world_pt_.y(), world_pt_.z());
    return true;
  }

  // get from the tableau mgr, as the avg of the camera centers
  else if (bwm_observer_mgr::instance()->comp_avg_camera_center(center)) {
    lvcs = bgeo_lvcs(center.x(), center.y(), center.z());
    return true;
  }
#endif // 0

  // else, request from user
  double lat, lon, elev;
  vgui_dialog lvcs_dialog("Set LVCS");
  lvcs_dialog.message("Please Enter and LVCS origin:");
  lvcs_dialog.field("Latitude:", lat);
  lvcs_dialog.field("Longitude:", lon);
  lvcs_dialog.field("Elevation:", elev);
  if (!lvcs_dialog.ask())
    return false;
  lvcs = bgeo_lvcs(lat, lon, elev);
  return true;
}

void bwm_world::load_shape_file()
{
  vcl_string file = bwm_utils::select_file();
  bwm_shape_file sfile;
  if (sfile.load(file)) {
    // "#define SHPT_POLYGONZ 15" in shapefil.h
    if (sfile.shape_type() == 15) {
      vcl_vector<vcl_vector<vsol_point_3d_sptr> > polys = sfile.vertices();
      for (unsigned i=0; i<polys.size(); i++) {
        bwm_observable_mesh_sptr mesh = new bwm_observable_mesh();
        bwm_observer_mgr::instance()->attach(mesh);
        vsol_polygon_3d_sptr poly3d = bwm_algo::move_points_to_plane(polys[i]);
        mesh->set_object(poly3d);
      }
    }
  }
}

#if 0
void bwm_world::save_all()
{
  if (objects_.size() == 0) {
    vgui_dialog error ("Error");
    error.message ("There is no object to save..." );
    error.ask();
    return;
  }

  vgui_dialog_extensions save("Save 3D objects");
  vcl_vector<vcl_string> file_types;
  file_types.push_back("ply");
  file_types.push_back("gml");
  file_types.push_back("kml");
  file_types.push_back("kml collada");
  file_types.push_back("x3d");

  vcl_string ext, file_path;
  unsigned t = 0;
  save.dir("Path:", ext, file_path);
  save.choice("File Type", file_types, t);
  //save.line_break();

  if (!save.ask())
    return;

  // what if they choose a dir instead of a file name
  if (vul_file::is_directory(file_path)) {
   // for (unsigned i=0; i<objects_.size(); i++) {
    //  vcl_string path = file_path + "\\objects";

      if (file_types[t].compare("ply") == 0)
        save_ply(path); // HOW ABOUT LVCS, do we use world point to create one

      else if (file_types[t].compare("gml") == 0)
        save_gml(path);

      else if (file_types[t].compare("kml") == 0)
        bwm_file_io::save_kml(objects_[i], path+".kml");

      else if (file_types[t].compare("kml collada") == 0)
        bwm_file_io::save_kml_collada(objects_[i], path+".kml");  // ??what is the extension of kml collada??

      else if (file_types[t].compare("x3d") == 0)
        bwm_file_io::save_x3d(objects_[i], path+".x3d");
    }
  }
}
#endif // 0

void bwm_world::save_ply()  // how about use lvcs??
{
  vgui_dialog params("File Save");
  vcl_string ext, list_name, empty="";
  bool use_lvcs = false;

  params.file ("Filename...", ext, list_name);
  params.checkbox("Use LVCS", use_lvcs);

  if (!params.ask())
    return;

  if (list_name == "") {
    vgui_dialog error ("Error");
    error.message ("Please specify a filename." );
    error.ask();
    return;
  }

  vcl_string directory_name = vul_file::dirname(list_name);

  vcl_ofstream list_out(list_name.data());
  if (!list_out.good()) {
    vcl_cerr << "error opening file "<< list_name <<vcl_endl;
    return;
  }

  for (unsigned idx=0; idx<objects_.size(); idx++) {
    vcl_ostringstream objname;
    vcl_ostringstream fullpath;
    objname << "obj" << idx <<".ply";
    fullpath << directory_name << '/' << objname.str();

    list_out << objname.str() << vcl_endl;
    bwm_observable_sptr o = objects_[idx];
    // figure out the lvcs here

    o->save(fullpath.str().data(),&lvcs_);
  }
}

void bwm_world::save_gml()
{
#if 0
  if (!lvcs_) {
    vcl_cerr << "Error: lvcs not defined.\n";
    return;
  }
#endif // 0

  vgui_dialog params("File Save (.gml) ");
  vcl_string ext, gml_filename, empty="";
  vcl_string model_name;

  params.field("model name", model_name);

  params.file("Save...", ext, gml_filename);
  if (!params.ask())
    return;

  if (gml_filename == "") {
    vcl_cerr << "Error: no filename selected.\n";
    return;
  }

  vcl_ofstream os(gml_filename.c_str());

  os << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n"
     << "<CityModel xmlns=\"http://www.citygml.org/citygml/1/0/0\" xmlns:gml=\"http://www.opengis.net/gml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.citygml.org/citygml/1/0/0 http://www.citygml.org/citygml/1/0/0/CityGML.xsd\">\n"
     << "<gml:description>" << model_name.c_str() << "</gml:description>\n"
     << "<gml:name>" << model_name.c_str() << "</gml:name>\n";

  int obj_count = 0;
  for (unsigned idx=0; idx<objects_.size(); idx++) {
    bwm_observable_sptr obj = objects_[idx];
    if (obj->type_name().compare("bwm_observable_textured_mesh") == 0) {
      bwm_observable_textured_mesh* tm_obj = static_cast<bwm_observable_textured_mesh*>(obj.as_pointer());
      tm_obj->save_gml(os, obj_count, &lvcs_);
      os << "   </Building>"
         << "  </cityObjectMember>";
    }
  }
  os << " </CityModel>";
  os.close();
}

void bwm_world::save_kml()
{
  bgeo_lvcs lvcs;
  if (!get_lvcs(lvcs)) {
    vcl_cerr << "Error: lvcs not defined.\n";
    return;
  }

  vgui_dialog params("File Save");
  vcl_string ext, kml_filename, empty="";
  vcl_string model_name;
  double ground_height = 0.0;
  double x_offset = 0.0;
  double y_offset = 0.0;

  params.field("model name",model_name);
  params.field("ground height",ground_height);
  params.field("x offset",x_offset);
  params.field("y offset",y_offset);

  params.file("Save...",ext,kml_filename);
  if (!params.ask())
    return;

  if (kml_filename == "") {
    vcl_cerr << "Error: no filename selected.\n";
    return;
  }

  vcl_ofstream os(kml_filename.c_str());

  os << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
     << "<kml xmlns=\"http://earth.google.com/kml/2.1\">\n"
     << "<Document>\n"
     << "  <name>" << vul_file::strip_directory(kml_filename.c_str()) << "</name>\n"
     << "  <open>1</open>\n"
     << "  <Placemark>\n"
     << "    <name>" << model_name.c_str() << "</name>\n"
     << "    <visibility>1</visibility>\n"
     << "    <MultiGeometry>\n";

  for (unsigned idx=0; idx<objects_.size(); idx++) {
    bwm_observable_sptr obj = objects_[idx];
    if (obj->type_name().compare("bwm_observable_textured_mesh") == 0) {
      bwm_observable_textured_mesh* tm_obj = static_cast<bwm_observable_textured_mesh*>(obj.as_pointer());
      tm_obj->save_kml(os, idx, &lvcs, ground_height, x_offset, y_offset);
    }
  }

  os << "    </MultiGeometry>\n"
     << "  </Placemark>\n"
     << "</Document>\n"
     << "</kml>\n";

  os.close();
}

void bwm_world::save_x3d()
{
  bgeo_lvcs lvcs;
  if (!get_lvcs(lvcs)) {
    vcl_cerr << "Error: lvcs not defined.\n";
    return;
  }

  vgui_dialog params("File Save");
  vcl_string ext, x3d_filename, empty="";

  params.file("Save...",ext,x3d_filename);
  if (!params.ask())
    return;

  if (x3d_filename == "") {
    vcl_cerr << "Error: no filename selected.\n";
    return;
  }

  vcl_ofstream os(x3d_filename.c_str());

  os << "#VRML V2.0 utf8\n"
     << "PROFILE Immersive\n\n";

  for (unsigned idx=0; idx<objects_.size(); idx++) {
    bwm_observable_sptr obj = objects_[idx];
    if (obj->type_name().compare("bwm_observable_textured_mesh") == 0) {
      bwm_observable_textured_mesh* tm_obj = static_cast<bwm_observable_textured_mesh*> (obj.as_pointer());
      tm_obj->save_x3d(os, &lvcs);
      os << "      ]\n\n"
         << "      solid TRUE\n"
         << "      convex FALSE\n"
         << "      creaseAngle 0\n"
         << "    }\n"
         << "  }\n"
         << "}\n\n\n";
    }
  }

  os.close();
  return;
}

void bwm_world::save_kml_collada()
{
  bgeo_lvcs lvcs;
  if (!get_lvcs(lvcs)) {
    vcl_cerr << "Error: lvcs not defined.\n";
    return;
  }

  double origin_lat = 0,origin_lon = 0, origin_elev = 0;
  lvcs_.get_origin(origin_lat,origin_lon,origin_elev);

  vgui_dialog params("File Save");
  vcl_string ext, kmz_dir, empty="";

  // guess at ground height = lowest vertex
  double minz = 1e6;
  for (unsigned idx=0; idx<objects_.size(); idx++) {
    bwm_observable_sptr obj = objects_[idx];
    obj->global_to_local(&lvcs, minz);
  }

  double ground_height = minz;
  double lat_offset = 0.0;
  double lon_offset = 0.0;
  vcl_string model_name;

  params.field("model name",model_name);
  params.field("ground height",ground_height);
  params.field("lattitude offset",lat_offset);
  params.field("longitude offset",lon_offset);

  params.file("Save...",ext,kmz_dir);
  if (!params.ask())
    return;

  if (kmz_dir == "") {
    vcl_cerr << "Error: no filename selected.\n";
    return;
  }

  if (!vul_file::is_directory(kmz_dir)) {
    vcl_cerr << "Error: Select a directory name.\n";
    return;
  }

  vcl_ostringstream dae_fname;
  dae_fname << kmz_dir << "/models/mesh.dae";

  vcl_ofstream os (dae_fname.str().data());

  vcl_vector<vcl_string> image_names;
  vcl_vector<vcl_string> image_fnames;
  vcl_vector<vcl_string> material_ids;
  vcl_vector<vcl_string> material_names;
  vcl_vector<vcl_string> effect_ids;
  vcl_vector<vcl_string> surface_ids;
  vcl_vector<vcl_string> image_sampler_ids;
  vcl_vector<vcl_string> geometry_ids;
  vcl_vector<vcl_string> geometry_position_ids;
  vcl_vector<vcl_string> geometry_position_array_ids;
  vcl_vector<vcl_string> geometry_uv_ids;
  vcl_vector<vcl_string> geometry_uv_array_ids;
  vcl_vector<vcl_string> geometry_vertex_ids;
  vcl_vector<vcl_string> mesh_ids;

  int nobjects = 0;
  unsigned min_faces = 3;

  for (unsigned idx=0; idx<objects_.size(); idx++) {
    bwm_observable_sptr obj = objects_[idx];
    if ( obj->num_faces() <  min_faces)
      // single mesh face is probably ground plane, which we do not want to render
      continue;

    // check if object is texture mapped
    if (obj->type_name().compare("bwm_observable_textured_mesh") == 0)
    {
      bwm_observable_textured_mesh* mesh = static_cast<bwm_observable_textured_mesh*>(obj.as_pointer());
      vcl_string image_fname = vul_file::strip_directory(mesh->tex_map_uri()); // assume all faces have same texmap img
      vcl_string image_name = vul_file::strip_extension(image_fname);

      vcl_ostringstream image_path;
      image_path << "../images/" << image_fname;

      vcl_ostringstream objname;
      objname << "object_"<<nobjects;

      vcl_ostringstream material_id;
      material_id << objname.str() <<"_materialID";

      vcl_ostringstream material_name;
      material_name << objname.str() <<"_material";

      vcl_ostringstream effect_id;
      effect_id << objname.str() << "_effect";

      vcl_ostringstream surface_id;
      surface_id << objname.str() << "_surface";

      vcl_ostringstream image_sampler_id;
      image_sampler_id << objname.str() << "_sampler";

      vcl_ostringstream geometry_id;
      geometry_id << objname.str() << "_geometry";

      vcl_ostringstream geometry_position_id;
      geometry_position_id << objname.str() << "_geometry_position";

      vcl_ostringstream geometry_position_array_id;
      geometry_position_array_id << objname.str() <<"_geometry_position_array";

      vcl_ostringstream geometry_uv_id;
      geometry_uv_id << objname.str() << "_geometry_uv";

      vcl_ostringstream geometry_uv_array_id;
      geometry_uv_array_id << objname.str() << "_geometry_uv_array";

      vcl_stringstream geometry_vertex_id;
      geometry_vertex_id << objname.str() << "_geometry_vertex";

      mesh_ids.push_back(objname.str());
      image_names.push_back(image_name);
      image_fnames.push_back(image_path.str());
      material_names.push_back(material_name.str());
      material_ids.push_back(material_id.str());
      effect_ids.push_back(effect_id.str());
      surface_ids.push_back(surface_id.str());
      image_sampler_ids.push_back(image_sampler_id.str());
      geometry_ids.push_back(geometry_id.str());
      geometry_position_ids.push_back(geometry_position_id.str());
      geometry_position_array_ids.push_back(geometry_position_array_id.str());
      geometry_uv_ids.push_back(geometry_uv_id.str());
      geometry_uv_array_ids.push_back(geometry_uv_array_id.str());
      geometry_vertex_ids.push_back(geometry_vertex_id.str());

      nobjects++;
    }
  }

  os <<"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
     << "<COLLADA xmlns=\"http://www.collada.org/2005/11/COLLADASchema\" version=\"1.4.1\">\n"

     << "  <asset>\n"
     << "    <contributor>\n"
     << "      <authoring_tool> Brown University World Modeler </authoring_tool>\n"
     << "    </contributor>\n"
     << "    <unit name=\"meters\" meter=\"1\"/>\n"
     << "    <up_axis>Z_UP</up_axis>\n"
     << "  </asset>\n"
     << "  <library_images>\n";

  for (int i=0; i<nobjects; i++) {
    os << "    <image id=\"" << image_names[i].c_str() << "\" name=\"" << image_names[i].c_str() << "\">\n"
       << "      <init_from>" << image_fnames[i].c_str() << "</init_from>\n"
       << "    </image>\n";
  }
  os << "  </library_images>\n";

  os << "  <library_materials>\n";
  for (int i=0; i<nobjects; i++) {
    os << "    <material id=\"" << material_ids[i].c_str() << "\" name=\"" << material_names[i].c_str() << "\">\n"
       << "      <instance_effect url=\"#" << effect_ids[i].c_str() << "\"/>\n"
       << "    </material>\n";
  }
  os << "  </library_materials>\n";

  os << "  <library_effects>\n";
  for (int i=0; i<nobjects; i++)
  {
    os << "    <effect id=\"" << effect_ids[i].c_str() << "\" name=\"" << effect_ids[i].c_str() << "\">\n"
       << "      <profile_COMMON>\n"
       << "        <newparam sid=\"" << surface_ids[i].c_str() << "\">\n"
       << "          <surface type=\"2D\">\n"
       << "            <init_from>" << image_names[i].c_str() << "</init_from>\n"
       << "          </surface>\n"
       << "        </newparam>\n"
       << "        <newparam sid=\"" << image_sampler_ids[i].c_str() << "\">\n"
       << "          <sampler2D>\n"
       << "            <source>" << surface_ids[i].c_str() << "</source>\n"
       << "          </sampler2D>\n"
       << "        </newparam>\n"
       << "        <technique sid=\"COMMON\">\n"
       << "          <phong>\n"
       << "            <emission>\n"
       << "              <color>0.0 0.0 0.0 1</color>\n"
       << "            </emission>\n"
       << "            <ambient>\n"
       << "              <color>0.0 0.0 0.0 1</color>\n"
       << "            </ambient>\n"
       << "            <diffuse>\n"
       << "              <texture texture=\"" << image_sampler_ids[i].c_str() << "\" texcoord=\"UVSET0\"/>\n"
       << "            </diffuse>\n"
       << "            <specular>\n"
       << "              <color>0.33 0.33 0.33 1</color>\n"
       << "            </specular>\n"
       << "            <shininess>\n"
       << "              <float>20.0</float>\n"
       << "            </shininess>\n"
       << "            <reflectivity>\n"
       << "              <float>0.1</float>\n"
       << "            </reflectivity>\n"
       << "            <transparent>\n"
       << "              <color>1 1 1 1</color>\n"
       << "            </transparent>\n"
       << "            <transparency>\n"
       << "              <float>0.0</float>\n"
       << "            </transparency>\n"
       << "          </phong>\n"
       << "        </technique>\n"
       << "      </profile_COMMON>\n"
       << "    </effect>\n";
  }
  os << "  </library_effects>\n";

  os << "  <library_geometries>\n";

  for (unsigned idx=0; idx<objects_.size(); idx++) {
    bwm_observable_sptr obj = objects_[idx];
    // assume object is texture mapped
    //dbmsh3d_textured_mesh_mc* mesh = (dbmsh3d_textured_mesh_mc*)obj->get_object();
    if (obj->num_faces() < min_faces) {
      // single mesh face is probably ground plane, which we do not want to render
      continue;
    }

    if (obj->type_name().compare("bwm_observable_textured_mesh") == 0) {
      bwm_observable_textured_mesh* tm_obj = static_cast<bwm_observable_textured_mesh*>(obj.as_pointer());
      tm_obj->save_kml_collada(os, &lvcs, geometry_ids[idx],
                               geometry_position_ids[idx],
                               geometry_position_array_ids[idx],
                               geometry_uv_ids[idx],
                               geometry_uv_array_ids[idx],
                               geometry_vertex_ids[idx],
                               material_names[idx]);
    }

    os << "</p>\n"
       << "      </triangles>\n"
       << "    </mesh>\n"
       << "  </geometry>\n";
    idx++;
  }
  os << "</library_geometries>\n";

  os << "<library_nodes>\n";
  for (int i=0; i<nobjects; i++) {
    os << "  <node id=\"Component_" << i << "\" name=\"Component_" << i << "\">\n"
       << "    <node id=\"" << mesh_ids[i].c_str() << "\" name=\"" << mesh_ids[i].c_str() << "\">\n"
       << "      <instance_geometry url=\"#" << geometry_ids[i].c_str() << "\">\n"
       << "        <bind_material>\n"
       << "          <technique_common>\n"
       << "            <instance_material symbol=\"" <<material_names[i].c_str() << "\" target=\"#" << material_ids[i].c_str()<< "\">\n"
       << "              <bind_vertex_input semantic=\"UVSET0\" input_semantic=\"TEXCOORD\" input_set=\"0\"/>\n"
       << "            </instance_material>\n"
       << "          </technique_common>\n"
       << "        </bind_material>\n"
       << "      </instance_geometry>\n"
       << "    </node>\n"
       << "  </node>\n";
  }
  os << "</library_nodes>\n";

  os << "<library_visual_scenes>\n"
     << "  <visual_scene id=\"WorldModelerScene\" name=\"WorldModelerScene\">\n"
     << "    <node id=\"Model\" name=\"Model\">\n";
  for (int i=0; i<nobjects; i++) {
    os << "      <node id=\"Component_" << i << "_1\" name=\"Component_" << i << "_1\">\n"
       << "        <instance_node url=\"#Component_" << i << "\"/>\n"
       << "      </node>\n";
  }
  os << "    </node>\n"
     << "  </visual_scene>\n"
     << "</library_visual_scenes>\n";

  os << "<scene>\n"
     << "  <instance_visual_scene url=\"#WorldModelerScene\"/>\n"
     << "</scene>\n"
     << "</COLLADA>\n";

  os.close();

  vcl_ostringstream textures_fname;
  textures_fname << kmz_dir << "/textures.txt";

  vcl_ofstream ost(textures_fname.str().data());

  for (int i=0; i<nobjects; i++) {
    ost << '<' << image_fnames[i].c_str() << "> <" << image_fnames[i].c_str() << ">\n";
  }

  vcl_ostringstream kml_fname;
  kml_fname << kmz_dir << "/doc.kml";

  vcl_ofstream oskml(kml_fname.str().data());

  oskml << "<?xml version='1.0' encoding='UTF-8'?>\n"
        << "<kml xmlns='http://earth.google.com/kml/2.1'>\n"
        << "<Folder>\n"
        << "  <name>" << model_name.c_str() << "</name>\n"
        << "  <description><![CDATA[Created with <a href=\"http://www.lems.brown.edu\">CrossCut</a>]]></description>\n"
        << "  <DocumentSource>CrossCut 1.0</DocumentSource>\n"
        << "  <visibility>1</visibility>\n"
        << "  <LookAt>\n"
        << "    <heading>0</heading>\n"
        << "    <tilt>45</tilt>\n"
        << "    <longitude>" << origin_lon << "</longitude>\n"
        << "    <latitude>" << origin_lat << "</latitude>\n"
        << "    <range>200</range>\n"
        << "    <altitude>" << 0.0f << "</altitude>\n"
        << "  </LookAt>\n"
        << "  <Folder>\n"
        << "    <name>Tour</name>\n"
        << "    <Placemark>\n"
        << "      <name>Camera</name>\n"
        << "      <visibility>1</visibility>\n"
        << "    </Placemark>\n"
        << "  </Folder>\n"
        << "  <Placemark>\n"
        << "    <name>Model</name>\n"
        << "    <description><![CDATA[]]></description>\n"
        << "    <Style id='default'>\n"
        << "    </Style>\n"
        << "    <Model>\n"
        << "      <altitudeMode>relativeToGround</altitudeMode>\n"
        << "      <Location>\n"
        << "        <longitude>" << origin_lon + lon_offset << "</longitude>\n"
        << "        <latitude>" << origin_lat + lat_offset << "</latitude>\n"
        << "        <altitude>" << origin_elev - ground_height << "</altitude>\n"
        << "      </Location>\n"
        << "      <Orientation>\n"
        << "        <heading>0</heading>\n"
        << "        <tilt>0</tilt>\n"
        << "        <roll>0</roll>\n"
        << "      </Orientation>\n"
        << "      <Scale>\n"
        << "        <x>1.0</x>\n"
        << "        <y>1.0</y>\n"
        << "        <z>1.0</z>\n"
        << "      </Scale>\n"
        << "      <Link>\n"
        << "        <href>models/mesh.dae</href>\n"
        << "      </Link>\n"
        << "    </Model>\n"
        << "  </Placemark>\n"
        << "</Folder>\n"
        << "</kml>\n";
}

void bwm_world::clear()
{
  world_pt_valid_ = false;
  lvcs_valid_ = false;
  objects_.clear();
}
