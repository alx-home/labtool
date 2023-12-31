// This is brl/bseg/boxm/algo/boxm_vrml_util.h
#ifndef boxm_vrml_util_h
#define boxm_vrml_util_h
//:
// \file
// \brief  Set of utilities to save a boxm_scene as vrml files
// \author Isabel Restrepo mir@lems.brown.edu
// \date  Dec 9, 2009
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <boxm/boxm_scene.h>
#include <boxm/boxm_cell_data_traits.h>

#include <vcl_fstream.h>
#include <bvrml/bvrml_write.h>

class boxm_vrml_util
{
 public:

  //Writes the values in the scene above the treshold as vrml dots
  template <class T_data>
  static void write_vrml_scene(vcl_ofstream& str, boxm_scene<boct_tree<short,T_data> > *scene,
                               const float threshold= 0.0f);
#if 0 // not yet working?
  static void write_vrml_scene(vcl_ofstream& str, bvxm_voxel_scene<bsta_num_obs<bsta_gauss_f1> > *scene,
                               const float threshold);
  static void write_vrml_scene_as_spheres(vcl_ofstream& str, bvxm_voxel_scene<float> *scene, float threshold);
  static void write_vrml_scene_as_spheres(vcl_ofstream& str, bvxm_voxel_scene<vnl_float_4> *scene, float threshold, int s=1);
  static void write_vrml_scene_as_pointers(vcl_ofstream& str, bvxm_voxel_scene<vnl_float_4> *scene, float threshold, int s=1);
#endif // 0
};


template <class T_data>
void boxm_vrml_util::write_vrml_scene(vcl_ofstream& str, boxm_scene<boct_tree<short,T_data> > *scene, float /*threshold*/)
{
  typedef boct_tree<short, T_data> tree_type;
  typedef boct_tree_cell<short, T_data> cell_type;
  vcl_ofstream temp_stream("temp.txt");

  bvrml_write::write_vrml_header(str);

  str << "Shape {\n"
      << "  appearance NULL\n"
      << "    geometry PointSet {\n"
      << "      color Color{\n"
      << "        color[\n";
  //write the colors
  //iterate through the scene
  boxm_block_iterator<tree_type > iter= scene->iterator();
  iter.begin();

  for (; !iter.end(); iter++) {
    scene->load_block(iter.index());
    tree_type  *tree = (*iter)->get_tree();

    // iterate through the tree
    vcl_vector<cell_type*> cells = tree->leaf_cells();

    for (unsigned i = 0; i < cells.size(); i++)
    {
      str <<"        0.5 0.2 0.8\n";
      vgl_point_3d<double> coord = tree->global_origin(cells[i]);
      temp_stream <<"        " << (int)coord.x() << ' ' <<(int)coord.y() << ' ' << (int)coord.z() <<  '\n';
    }
  }
  temp_stream.close();

  str << "        ]\n     }\n"
      << "      coord Coordinate{\n"
      << "        point[\n";

  // write the coordinates.
  vcl_ifstream fin;  // file in
  vcl_filebuf *fb;   // file buffer
  fb = fin.rdbuf();
  fb->open ("temp.txt",vcl_ios::in);
  if (fb->is_open() )
  {
    while (fb->sgetc()!=EOF)
    {
      vcl_string temp_str;
      vcl_istream isbf(fb);
      vcl_getline(isbf, temp_str);
      str << temp_str << '\n';
    }
  }
  else
    vcl_cerr << "file is not open.\n";

  fin.close();
  str << "        ]\n     }\n   }\n}\n";
}

#if 0 // not yet working?
void bvxm_vrml_voxel_grid::write_vrml_grid(vcl_ofstream& str, bvxm_voxel_grid<bsta_num_obs<bsta_gauss_f1> > *grid, float threshold)
{
  bvxm_voxel_grid<bsta_num_obs<bsta_gauss_f1> >::iterator grid_it = grid->begin();

  str << "Shape {\n"
      << "  appearance NULL\n"
      << "    geometry PointSet {\n"
      << "      color Color{\n"
      << "        color[\n";
  //write the colors
  for (unsigned k=0; grid_it != grid->end(); ++grid_it, ++k) {
    for (unsigned i=0; i<(*grid_it).nx(); ++i){
      for (unsigned j=0; j < (*grid_it).ny(); ++j) {
        if ((((*grid_it)(i,j)).mean() > threshold))
          str <<"        " << ((*grid_it)(i,j)).mean() << ' '<< ((*grid_it)(i,j)).mean() << ' '<< ((*grid_it)(i,j)).mean() << '\n';
      }
    }
  }
  str << "        ]\n     }\n"
      << "      coord Coordinate{\n"
      << "        point[\n";

  //write the coordinates
  grid_it = grid->begin();
  for (unsigned k=0; grid_it != grid->end(); ++grid_it, ++k) {
    vcl_cout << '.';
    for (unsigned i=0; i<(*grid_it).nx(); ++i) {
      for (unsigned j=0; j < (*grid_it).ny(); ++j) {
        if (((*grid_it)(i,j)).mean() > threshold)
          str<<"        " << i << ' ' <<j << ' ' << k <<  '\n';
      }
    }
  }
  str << "        ]\n     }\n   }\n}\n";
}


void bvxm_vrml_voxel_grid::write_vrml_grid_as_spheres(vcl_ofstream& str, bvxm_voxel_grid<float> *grid, float threshold)
{
  bvxm_voxel_grid<float>::iterator grid_it = grid->begin();
  vgl_vector_3d<unsigned> dim=grid->grid_size();
  unsigned s=3;
  //write the colors
  for (unsigned k=dim.z()-1; grid_it != grid->end(); ++grid_it, --k) {
    if (k%1==0)
    {
      for (unsigned i=0; i<(*grid_it).nx(); i+=s){
        for (unsigned j=0; j < (*grid_it).ny(); j+=s) {
          if (((*grid_it)(i,j) > threshold)) {
#ifdef DEBUG
            vgl_sphere_3d<float> sphere((float)i,(float)j,(float)k,0.5f);
            write_vrml_sphere(str, sphere, (*grid_it)(i,j),(*grid_it)(i,j),(*grid_it)(i,j),1-(*grid_it)(i,j));
#endif // DEBUG
            vgl_sphere_3d<float> sphere((float)i/s,(float)j/s,(float)k/s,0.4f);
            bvrml_write::write_vrml_sphere(str, sphere, 1,0,0,0);
          }
        }
      }
    }
  }
}

void bvxm_vrml_voxel_grid::write_vrml_grid_as_spheres(vcl_ofstream& str, bvxm_voxel_grid<vnl_float_4> *grid, float threshold, int s)
{
  bvxm_voxel_grid<vnl_float_4>::iterator grid_it = grid->begin();
  //write the colors
  for (unsigned k=0; grid_it != grid->end(); ++grid_it, ++k) {
    for (unsigned i=0; i<(*grid_it).nx(); ){
      for (unsigned j=0; j < (*grid_it).ny(); ) {
        if ((*grid_it)(i,j)[3]/255.0f > threshold) {
          vgl_sphere_3d<float> sphere((float)i/s,(float)j/s,(float)k/s,0.5f);
          bvrml_write::write_vrml_sphere(str, sphere, 1,0,0,0);
        }
      }
    }
  }
}


void bvxm_vrml_voxel_grid::write_vrml_grid_as_pointers(vcl_ofstream& str, bvxm_voxel_grid<vnl_float_4> *grid, float threshold, int s)
{
  bvxm_voxel_grid<vnl_float_4>::iterator grid_it = grid->begin();
  vgl_point_3d<double> origin(0.0,0.0,0.0);
  vgl_vector_3d<double> dirx(1,0,0);
  vgl_vector_3d<double> diry(0,1,0);
  vgl_vector_3d<double> dirz(0,0,1);
  bvrml_write::write_vrml_line(str,origin,dirx,1,1,0,0);
  bvrml_write::write_vrml_line(str,origin,diry,1,0,1,0);
  bvrml_write::write_vrml_line(str,origin,dirz,1,0,0,1);

  vgl_vector_3d<unsigned> dim=grid->grid_size();
  //write the colors
  for (unsigned k=dim.z()-1; grid_it != grid->end(); ++grid_it, --k) {
    if (k%s==0)
    {
      for (unsigned i=0; i<(*grid_it).nx(); i=i+s) {
        for (unsigned j=0; j < (*grid_it).ny(); j=j+s) {
          if (((*grid_it)(i,j)[3] > threshold)){
            vgl_vector_3d<double> dir((*grid_it)(i,j)[0],(*grid_it)(i,j)[1],(*grid_it)(i,j)[2]);
            vgl_point_3d<double> pt((double)i/s,(double)j/s,(double)k/s);
            bvrml_write::write_vrml_line(str, pt,dir,4*((*grid_it)(i,j)[3]-0.5f),1,0,0);
            bvrml_write::write_vrml_disk(str, pt,dir,2*((*grid_it)(i,j)[3]-0.5f),0,0.5f,0.0f);
          }
        }
      }
    }
  }
}
#endif // 0

#endif // boxm_vrml_util_h
