#include "bvpl_direction_to_color_map.h"
//:
// \file
#include <vnl/vnl_random.h>
#include <vnl/vnl_float_4.h>
#include <vgl/vgl_vector_3d.h>
#include <vgl/vgl_line_3d_2_points.h>
#include <vgl/vgl_distance.h>
#include <vgl/vgl_closest_point.h>
#include <vil/algo/vil_colour_space.h>

//: project a unit radius sphere onto the cube circumscribing it using gnomonic projection
void bvpl_direction_to_color_map::project_sphereical_samples_to_cubes(vcl_vector<vgl_point_3d<double> > & proj_on_cube)
{
  vcl_vector<vgl_vector_3d<double> > normals;
  normals.push_back(vgl_vector_3d<double>(1,0,0));  // X high
  normals.push_back(vgl_vector_3d<double>(0,1,0));  // Y high
  normals.push_back(vgl_vector_3d<double>(0,0,1));  // Z high
  normals.push_back(vgl_vector_3d<double>(-1,0,0)); // X low
  normals.push_back(vgl_vector_3d<double>(0,-1,0)); // Y low
  normals.push_back(vgl_vector_3d<double>(0,0,-1)); // Z low

  // iterate over all the spherical samples
  for (unsigned i=0;i<samples_.size();++i)
  {
    //find the face which has a normal closest to the sample direction.
    double tmax=-10.0;int jmax=-1;
    for (unsigned j=0;j<normals.size();++j)
    {
      double t=samples_[i].x()*normals[j].x()+
               samples_[i].y()*normals[j].y()+
               samples_[i].z()*normals[j].z();
      if (t>tmax || j==0)
      {
        tmax=t; jmax=j;
      }
    }
    // find intersection with appropriate plane
    switch (jmax) {
      case 0:
        proj_on_cube.push_back(vgl_point_3d<double>
                               (1.0,samples_[i].y()/samples_[i].x(),samples_[i].z()/samples_[i].x()));
        break;
      case 1:
        proj_on_cube.push_back(vgl_point_3d<double>
                               (samples_[i].x()/samples_[i].y(),1.0,samples_[i].z()/samples_[i].y()));
        break;
      case 2:
        proj_on_cube.push_back(vgl_point_3d<double>
                               (samples_[i].x()/samples_[i].z(),samples_[i].y()/samples_[i].z(),1.0));
        break;
      case 3:
        proj_on_cube.push_back(vgl_point_3d<double>
                               (-1.0,-samples_[i].y()/samples_[i].x(),-samples_[i].z()/samples_[i].x()));
        break;
      case 4:
        proj_on_cube.push_back(vgl_point_3d<double>
                               (-samples_[i].x()/samples_[i].y(),-1.0,-samples_[i].z()/samples_[i].y()));
        break;
      case 5:
        proj_on_cube.push_back(vgl_point_3d<double>
                               (-samples_[i].x()/samples_[i].z(),-samples_[i].y()/samples_[i].z(),-1.0));
        break;
    }
  }
}


vcl_vector< float>
bvpl_direction_to_color_map::find_closest_points_from_cube_to_peano_curve(vcl_vector<vgl_point_3d<double> > peano_curve,
                                                                          vcl_vector<vgl_point_3d<double> > proj_on_cube)
{
  // store indices of the directions in (0,1) range
  vcl_vector<float> indices_of_cube_projs;
  vcl_map<int,float> index_to_length;
  for (unsigned j=0;j<peano_curve.size();++j)
  {
    if (j==0)
      index_to_length[j]=0;
    else
      index_to_length[j]=index_to_length[j-1]+float((peano_curve[j]-peano_curve[j-1]).length());
  }
  for (unsigned i=0;i<proj_on_cube.size();++i)
  {
    double dmin=1e5;
    int indexj=-1;
    // find the closest index point
    for (unsigned j=0;j<peano_curve.size();++j)
    {
      double d=vgl_distance<double>(proj_on_cube[i],peano_curve[j]);
      if (d<dmin || j==0)
      {
        dmin=d;
        indexj=j;
      }
    }
    // find the closest point on the two line segments emanating from the index point

    if (indexj==0) // first point
    {
      vgl_line_3d_2_points<double> l1(peano_curve[indexj],peano_curve[indexj+1]);
      double t1=vgl_closest_point_t(l1,proj_on_cube[i]);
      if (t1<0) t1=0;
      double length=(peano_curve[indexj+1]-peano_curve[indexj]).length();
      indices_of_cube_projs.push_back(float(index_to_length[indexj]+t1/length));
    }
    else if (unsigned(indexj+1)==proj_on_cube.size()) // last point
    {
      vgl_line_3d_2_points<double> l2(peano_curve[indexj-1],peano_curve[indexj]);
      double t2=vgl_closest_point_t(l2,proj_on_cube[i]);
      if (t2>0)t2=0;
      double length=index_to_length[indexj]-index_to_length[indexj-1];
      indices_of_cube_projs.push_back(float(index_to_length[indexj]+t2/length));
    }
    else // rest of the points
    {
      vgl_line_3d_2_points<double> l1(peano_curve[indexj],peano_curve[indexj+1]);
      vgl_line_3d_2_points<double> l2(peano_curve[indexj-1],peano_curve[indexj]);

      double t1=vgl_closest_point_t(l1,proj_on_cube[i]);
      double t2=vgl_closest_point_t(l2,proj_on_cube[i]);

      if (vcl_fabs(t1)<vcl_fabs(t2))
      {
        //if (t1<0)t1=0;
        double length=(peano_curve[indexj+1]-peano_curve[indexj]).length();
        indices_of_cube_projs.push_back(float(index_to_length[indexj]+t1/length));
      }
      else
      {
        //if (t2<0)t2=0;
        double length=(peano_curve[indexj-1]-peano_curve[indexj]).length();
        indices_of_cube_projs.push_back(float(index_to_length[indexj-1]+t2/length));
      }
    }
  }

  for (unsigned j=0;j<indices_of_cube_projs.size();++j)
  {
      vcl_cout<<indices_of_cube_projs[j]<<' ';
      indices_of_cube_projs[j]/=index_to_length[index_to_length.size()-1];
  }

  return indices_of_cube_projs;
}


void bvpl_direction_to_color_map::make_svg_color_map(vcl_string outfile)
{
  bsvg_document doc(400, 400);

  vcl_map<vgl_point_3d<double>,float,point_3d_cmp>::iterator iter=colors_.begin();
  vcl_map<float,vgl_point_3d<double> > colors_ordered_by_index;
  for (;iter!=colors_.end();iter++)
  {
    colors_ordered_by_index[iter->second]=iter->first;
  }
  int i=0;  float r,g,b;
  vcl_map<float,vgl_point_3d<double> >::iterator iter1=colors_ordered_by_index.begin();
  for (;iter1!=colors_ordered_by_index.end();iter1++,i++)
  {
    float col=iter1->first*360;
    vil_colour_space_HSV_to_RGB<float>(col,1.0f,255.0f,&r,&g,&b);

    vcl_ostringstream os;
    os<<'#'<<vcl_setw(2)<<vcl_setfill('0')<<vcl_hex<<(int)r
      <<vcl_setw(2)<<vcl_setfill('0')<<vcl_hex<<(int)g
      <<vcl_setw(2)<<vcl_setfill('0')<<vcl_hex<<(int)b;

    vcl_ostringstream os_dir;
    os_dir.precision(2);
    os_dir<<'['<<vcl_setw(5)<<iter1->second.x()<<','<<vcl_setw(5)<<iter1->second.y()<<','<<vcl_setw(5)<<iter1->second.z()<<']';
    bsvg_text* t = new bsvg_text(os_dir.str());
    t->set_font_size(15);
    t->set_location(10.0f, 15.0f*(i+1));

    bsvg_ellipse* e1 = new bsvg_ellipse(25, 7);
    e1->set_location(250.0f, 15.0f*(i+1));
    e1->set_fill_color(os.str());
    doc.add_element(e1);
    doc.add_element(t);
  }

  bxml_write(outfile, doc);
}


bvpl_direction_to_color_map::bvpl_direction_to_color_map(vcl_vector<vgl_point_3d<double> > samples, vcl_string type)
{
  samples_=samples;
  vcl_vector<float> oneparam;
  if (type=="peano")
  {
    vcl_vector<vgl_point_3d<double> >  proj_on_cube;
    project_sphereical_samples_to_cubes(proj_on_cube);
    // level 2 peano curve
    vcl_vector<vgl_point_3d<double> > peano_curve=peano_curve_on_cube(2);
    // mapping of samples to 1-d curve between 0-1
    oneparam=find_closest_points_from_cube_to_peano_curve(peano_curve,proj_on_cube);
  }
  else if (type=="random")
  {
    vnl_random rand;
    for (unsigned i=0;i<samples_.size();i++)
      oneparam.push_back(float(rand.drand32(1.0)));
  }

  for (unsigned i=0;i<samples_.size();i++)
    colors_[samples[i]]=oneparam[i];
}


void bvpl_generate_direction_samples_from_kernels(bvpl_kernel_vector_sptr kernel_vector,
                                                  vcl_vector<vgl_point_3d<double> > & samples)
{
  vcl_vector< bvpl_kernel_sptr >::iterator iter;
  for (iter=kernel_vector->begin();iter!=kernel_vector->end();++iter)
    samples.push_back(vgl_point_3d<double>((*iter)->axis()[0], (*iter)->axis()[1], (*iter)->axis()[2]));
}


void bvpl_convert_grid_to_hsv_grid(bvxm_voxel_grid<vnl_float_4> *grid,
                                   bvxm_voxel_grid<vnl_float_4> *out_grid,
                                   bvpl_direction_to_color_map & color_map)
{
  bvxm_voxel_grid<vnl_float_4 >::iterator grid1_it = grid->begin();
  bvxm_voxel_grid<vnl_float_4>::iterator grid2_it = out_grid->begin();

  //calculate max response and normalize the range from 0-1
  float min = vcl_numeric_limits<float>::max();
  float max = vcl_numeric_limits<float>::min();
  for (; grid1_it != grid->end(); ++grid1_it)
  {
    bvxm_voxel_slab<vnl_float_4>::iterator slab1_it = (*grid1_it).begin();
    for (; slab1_it!=(*grid1_it).end(); ++slab1_it )
    {
     if ((*slab1_it)[3] > max)
       max = (*slab1_it)[3];
     if ((*slab1_it)[3] < min)
       min = (*slab1_it)[3];
    }
  }

  vcl_cout << "Maximum response: " << max << " Minimun response: " << min << vcl_endl;

  //reset iterator
  grid1_it = grid->begin();

  //convert to hsv grid
  float r,g,b;
  float col;
  for (; grid1_it != grid->end(); ++grid1_it, ++grid2_it)
  {
    bvxm_voxel_slab<vnl_float_4>::iterator slab1_it = (*grid1_it).begin();
    bvxm_voxel_slab<vnl_float_4>::iterator slab2_it = (*grid2_it).begin();
    for (; slab1_it!=(*grid1_it).end(); ++slab1_it ,++slab2_it)
    {
      vgl_point_3d<double> v((*slab1_it)[0],(*slab1_it)[1],(*slab1_it)[2]);
      col=color_map.get_color(v)*360;
      vil_colour_space_HSV_to_RGB<float>(col,1.0f,255.0f,&r,&g,&b);
      vnl_float_4 this_feature(r,g,b,(((*slab1_it)[3]-min)/(max - min))*255.0f);
      (*slab2_it)=this_feature;
    }
  }
}


void bvpl_convert_id_grid_to_hsv_grid(bvxm_voxel_grid<int> *id_grid,
                                      bvxm_voxel_grid<float> *response_grid,
                                      bvxm_voxel_grid<vnl_float_4> *out_grid,
                                      vcl_vector<float> colors)
{
  bvxm_voxel_grid<float>::iterator response_grid_it = response_grid->begin();
   //calculate max response and normalize the range from 0-1
  float min = *(response_grid_it->begin());
  float max = *(response_grid_it->begin());
  for (; response_grid_it != response_grid->end(); ++response_grid_it)
  {
    bvxm_voxel_slab<float>::iterator response_slab_it = (*response_grid_it).begin();
    for (; response_slab_it!=(*response_grid_it).end(); ++response_slab_it )
    {
     if ((*response_slab_it) > max)
       max = (*response_slab_it);
     if ((*response_slab_it) < min)
       min = (*response_slab_it);
    }
  }

  vcl_cout << "Maximum response: " << max << " Minimun response: " << min << vcl_endl;

  //reset iterator
  bvxm_voxel_grid<vnl_float_4>::iterator out_grid_it = out_grid->begin();
  bvxm_voxel_grid<int>::iterator id_grid_it = id_grid->begin();
  response_grid_it = response_grid->begin();

  //convert to hsv grid
  float r,g,b;
  float col;
  for (; id_grid_it != id_grid->end(); ++id_grid_it, ++response_grid_it, ++out_grid_it)
  {
    bvxm_voxel_slab<int>::iterator id_slab_it = (*id_grid_it).begin();
    bvxm_voxel_slab<float>::iterator response_slab_it = (*response_grid_it).begin();
    bvxm_voxel_slab<vnl_float_4>::iterator out_slab_it = (*out_grid_it).begin();
    for (; id_slab_it!=(*id_grid_it).end(); ++id_slab_it ,++response_slab_it, ++ out_slab_it)
    {
      if (*id_slab_it<0) {//negative ids are unitialized voxels
        (*out_slab_it)=vnl_float_4(0,0,0,0);
      }
      else {
         col=colors[*id_slab_it]*360.0f;
        vil_colour_space_HSV_to_RGB<float>(col,1.0f,255.0f,&r,&g,&b);
        float alpha;
        if (max -min < 1e-15)
          alpha = (*response_slab_it)/max *255.0;
        else
          alpha=(((*response_slab_it)-min)/(max - min))*255.0f;

       //  alpha = (*response_slab_it) > 1e-15 ? 255.0f:0.0f;
        //vnl_float_4 this_feature(r,g,b,alpha);
        (*out_slab_it)=vnl_float_4(r,g,b,alpha);
      }
    }
  }
}

void bvpl_convert_id_grid_to_hsv_grid(bvxm_voxel_grid<int> *id_grid,
                                      bvxm_voxel_grid<bsta_num_obs<bsta_gauss_f1> > *response_grid,
                                      bvxm_voxel_grid<vnl_float_4> *out_grid,
                                      vcl_vector<float> colors)
{
  bvxm_voxel_grid<bsta_num_obs<bsta_gauss_f1> >::iterator response_grid_it = response_grid->begin();
   //calculate max response and normalize the range from 0-1
  float min = ((*(response_grid_it->begin())).mean());
  float max = ((*(response_grid_it->begin())).mean());
  for (; response_grid_it != response_grid->end(); ++response_grid_it)
  {
    bvxm_voxel_slab<bsta_num_obs<bsta_gauss_f1> >::iterator response_slab_it = (*response_grid_it).begin();
    for (; response_slab_it!=(*response_grid_it).end(); ++response_slab_it )
    {
     if (((*response_slab_it).mean()) > max)
       max = ((*response_slab_it).mean());
     if (((*response_slab_it).mean())< min)
       min = ((*response_slab_it).mean());
    }
  }

  vcl_cout << "Maximum response: " << max << " Minimun response: " << min << vcl_endl;

  //reset iterator
  bvxm_voxel_grid<vnl_float_4>::iterator out_grid_it = out_grid->begin();
  bvxm_voxel_grid<int>::iterator id_grid_it = id_grid->begin();
  response_grid_it = response_grid->begin();

  //convert to hsv grid
  float r,g,b;
  float col;
  for (; id_grid_it != id_grid->end(); ++id_grid_it, ++response_grid_it, ++out_grid_it)
  {
    bvxm_voxel_slab<int>::iterator id_slab_it = (*id_grid_it).begin();
    bvxm_voxel_slab<bsta_num_obs<bsta_gauss_f1> >::iterator response_slab_it = (*response_grid_it).begin();
    bvxm_voxel_slab<vnl_float_4>::iterator out_slab_it = (*out_grid_it).begin();
    for (; id_slab_it!=(*id_grid_it).end(); ++id_slab_it ,++response_slab_it, ++ out_slab_it)
    {
      col=colors[*id_slab_it]*360.0f;
      vil_colour_space_HSV_to_RGB<float>(col,1.0f,255.0f,&r,&g,&b);
      //float alpha = vcl_abs((*response_slab_it).mean())>1e-15 ? 255.0f:0.0f;
      vnl_float_4 this_feature(r,g,b,255.0);
      //vnl_float_4 this_feature(r,g,b,((vcl_abs((*response_slab_it).mean())-min)/(max - min))*500.0f);
      (*out_slab_it)=this_feature;
    }
  }
}


void bvpl_write_colors_to_svg(bvpl_kernel_vector_sptr kernel_vector, vcl_vector<float> hue_vector, vcl_string outfile)
{
  bsvg_document doc(600, hue_vector.size()*20);

  vcl_vector<float>::iterator iter = hue_vector.begin();

  int i=0;  float r,g,b;
  for (;iter!=hue_vector.end();iter++,i++)
  {
    float col=(*iter)*360.0f;
    vil_colour_space_HSV_to_RGB<float>(col,1.0f,255.0f,&r,&g,&b);

    vcl_ostringstream os;
    os<<'#'<<vcl_setw(2)<<vcl_setfill('0')<<vcl_hex<<(int)r
      <<vcl_setw(2)<<vcl_setfill('0')<<vcl_hex<<(int)g
      <<vcl_setw(2)<<vcl_setfill('0')<<vcl_hex<<(int)b;

    vcl_ostringstream os_dir;
    os_dir.precision(2);
    os_dir<<'['<<i<<']'<< '['<<vcl_setw(2)<<kernel_vector->kernels_[i]->axis()<<']'<<'['<<vcl_setw(2)<<kernel_vector->kernels_[i]->angle()<<']' ;//<< '['<<(int)r << ',' << (int)g<< ',' << (int)b<<']';
    bsvg_text* t = new bsvg_text(os_dir.str());
    t->set_font_size(15);
    t->set_location(10.0f, 15.0f*(i+1));

    bsvg_ellipse* e1 = new bsvg_ellipse(25, 7);
    e1->set_location(400.0f, 15.0f*(i+1));
    e1->set_fill_color(os.str());
    doc.add_element(e1);
    doc.add_element(t);
  }

  bxml_write(outfile, doc);
}
