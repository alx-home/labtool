#include <testlib/testlib_test.h>

#include <bvpl/bvpl_edge2d_kernel_factory.h>
#include <bvpl/bvpl_edge3d_kernel_factory.h>
#include <bvpl/bvpl_edge_algebraic_mean_functor.h>
#include <bvpl/bvpl_edge_geometric_mean_functor.h>
#include <bvpl/bvpl_opinion_functor.h>
#include <bvpl/bvpl_neighb_operator.h>
#include <bvpl/bvpl_vector_operator.h>
#include <bvpl/bvpl_discriminative_non_max_suppression.h>
#include <bvpl/bvpl_create_directions.h>

#include <bvxm/grid/bvxm_opinion.h>
#include <bvxm/grid/bvxm_voxel_grid_basic_ops.h>
#include <bvxm/grid/bvxm_voxel_grid_opinion_basic_ops.h>
#include <bvxm/grid/io/bvxm_io_voxel_grid.h>

#include <vnl/vnl_float_3.h>
#include <vul/vul_file.h>
#include <vcl_sstream.h>
#include <vcl_iostream.h>
#include <vcl_iomanip.h>

void create_grid(vcl_string grid_filename)
{
  if (vul_file_exists(grid_filename))
    vul_file::delete_file_glob(grid_filename);

  bvxm_voxel_grid<bvxm_opinion> surface_grid(grid_filename,vgl_vector_3d<unsigned int>(32,32,32));
  bvxm_opinion bnonsurf(0.9f,0.1f);
  surface_grid.initialize_data(bnonsurf);

  vcl_vector<vgl_point_3d<double> > poly_points;
  poly_points.push_back(vgl_point_3d<double>(10.0,10.0,10.0));
  poly_points.push_back(vgl_point_3d<double>(10.0,20.0,10.0));
  poly_points.push_back(vgl_point_3d<double>(20.0,20.0,10.0));
  poly_points.push_back(vgl_point_3d<double>(20.0,10.0,10.0));

  bvxm_opinion bsurf(0.1f,0.9f);
  bvxm_load_polygon_into_grid<bvxm_opinion>(&surface_grid,poly_points,bsurf);
}

void fill_in_data(bvxm_voxel_grid<float> *grid, float min_p, float max_p, vnl_float_3 axis, int margin)
{
  vgl_vector_3d<unsigned> grid_dim = grid->grid_size();
  grid->initialize_data(0.01f);
  unsigned ni=grid_dim.x();
  unsigned nj=grid_dim.y();
  unsigned nk=grid_dim.z();

  float ci=ni*0.5f;
  float cj=nj*0.5f;
  float ck=nk*0.5f;

  unsigned slab_idx = 0;
  bvxm_voxel_grid<float>::iterator grid_it = grid->slab_iterator(slab_idx,nk);
  for (unsigned i=margin;i<ni-margin;i++)
  {
    for (unsigned j=margin;j<nj-margin;j++)
    {
      for (unsigned k=margin;k<nk-margin;k++)
      {
        if ((i-ci)*axis[0]+(j-cj)*axis[1]+(k-ck)*axis[2]>=0)
          (*grid_it)(i,j,k)=max_p;
        else
          (*grid_it)(i,j,k)=min_p;
      }
    }
  }
}

bool check_data(bvxm_voxel_grid<int> *grid, vnl_float_3 axis, int id, int margin)
{
  vgl_vector_3d<unsigned> grid_dim = grid->grid_size();
  unsigned ni=grid_dim.x();
  unsigned nj=grid_dim.y();
  unsigned nk=grid_dim.z();

  float ci=ni*0.5f;
  float cj=nj*0.5f;
  float ck=nk*0.5f;

  bool result = true;

  unsigned slab_idx = 0;
  bvxm_voxel_grid<int>::iterator grid_it = grid->slab_iterator(slab_idx,nk);
  for (unsigned i=margin;i<ni-margin;i++)
  {
    for (unsigned j=margin;j<nj-margin;j++)
    {
      for (unsigned k=margin;k<nk-margin;k++)
      {
        if (((i-ci)*axis[0]+(j-cj)*axis[1]+(k-ck)*axis[2]>-1) && ((i-ci)*axis[0]+(j-cj)*axis[1]+(k-ck)*axis[2] <1))
        {
          result = result && (*grid_it)(i,j,k)==id;
          vcl_cout << "id at center " << i << j << k << " is " <<(*grid_it)(i,j,k) << vcl_endl;

        }
      }
    }
  }
  return result;
}

bool check_non_max(bvxm_voxel_grid<float> *grid, int margin)
{
  vgl_vector_3d<unsigned> grid_dim = grid->grid_size();
  unsigned ni=grid_dim.x();
  unsigned nj=grid_dim.y();
  unsigned nk=grid_dim.z();

  float ci=ni*0.5f;
  float cj=nj*0.5f;
  float ck=nk*0.5f;

  bool result = true;

  unsigned slab_idx = 0;
  bvxm_voxel_grid<float>::iterator grid_it = grid->slab_iterator(slab_idx,nk);
  for (unsigned i=margin;i<ni-margin;i++)
  {
    for (unsigned j=margin;j<nj-margin;j++)
    {
      for (unsigned k=margin;k<nk-margin;k++)
      {
       if ( i == (unsigned int)ci && j == (unsigned int)cj && k == (unsigned int)ck)
        {
          vcl_cout << "Response at center " << i << j << k << "is " << (*grid_it)(i,j,k) << vcl_endl;
          result = result && ((*grid_it)(i,j,k) > 1e-2);
        }
        else if (!((*grid_it)(i,j,k) < 1e-2) )
        {
          result = false;
          //vcl_cout <<  "Response at " << i << j << k << "is " << (*grid_it)(i,j,k) << vcl_endl;
        }
      }
    }
  }
  return result;
}


void test_vector_operator()
{
  vcl_string grid_filename="grid_plane.vox";
  create_grid(grid_filename);
  bvxm_voxel_grid<bvxm_opinion>* grid = new bvxm_voxel_grid<bvxm_opinion>(grid_filename);
  vcl_string grid_expectation_filename="grid_plane_expectation.vox";
  // output to verify if the digitization of the plane is correct.
  bvxm_voxel_grid<float> * surface_grid_expectation
  =new bvxm_voxel_grid<float>(grid_expectation_filename,vgl_vector_3d<unsigned int>(32,32,32));

  bvxm_expectation_opinion_voxel_grid(grid,surface_grid_expectation);

  bvxm_grid_save_raw<float>(surface_grid_expectation,"grid_plane_expectation.raw");
  // get vector of kernel
  bvpl_edge3d_kernel_factory kernels_3d(-2,2,-2,2,-2,2);
  bvpl_create_directions_a dir;
  bvpl_kernel_vector_sptr kernel_vec = kernels_3d.create_kernel_vector(dir);

  vcl_string out_grid_path="out_grid.vox";
  vcl_string id_grid_path="orientation_grid.vox";
  vcl_string out_grid_expectation_path="out_grid_expectation.vox";

  bvxm_voxel_grid<bvxm_opinion> *grid_out=new bvxm_voxel_grid<bvxm_opinion>(out_grid_path, grid->grid_size());
  bvxm_voxel_grid<int > *id_grid
  =new bvxm_voxel_grid<int >(id_grid_path, grid->grid_size());
  bvpl_opinion_functor func;
  bvpl_neighb_operator<bvxm_opinion, bvpl_opinion_functor> oper(func);
  bvpl_vector_operator vector_oper;
  vector_oper.apply_and_suppress(grid,kernel_vec,&oper,grid_out, id_grid);

  bvxm_voxel_grid<float> *out_grid_expectation=new bvxm_voxel_grid<float>(out_grid_expectation_path,grid->grid_size());
  bvxm_expectation_opinion_voxel_grid(grid_out,out_grid_expectation);
  bvxm_grid_save_raw<float>(out_grid_expectation,"grid_out_expectation.raw");
}


void test_non_max_suppression()
{
  //Create vector of kernels
  bvpl_edge3d_kernel_factory kernels_3d(-1,0,-1,0,-1,0);
  bvpl_create_directions_a dir;
  bvpl_kernel_vector_sptr kernel_vec = kernels_3d.create_kernel_vector(dir);


  //Create an in memory grid and filled it with a plane
  bvxm_voxel_grid<float> *grid = new bvxm_voxel_grid<float> (vgl_vector_3d<unsigned>(4,4,4));
  int target_id = 9;
  vnl_float_3 target_axis = kernel_vec->kernels_[target_id]->axis();
  vcl_cout << "taget axis " << target_axis << vcl_endl;
  vcl_cout << "taget axis " << kernel_vec->kernels_[1]->axis() << vcl_endl;
  fill_in_data(grid, 0.01f, 0.99f, target_axis,0);

  //Run all the kernels
  bvxm_voxel_grid<float> *grid_out=new bvxm_voxel_grid<float>(grid->grid_size());
  bvxm_voxel_grid<int > *id_grid=new bvxm_voxel_grid<int >(grid->grid_size());
  id_grid->initialize_data(-1);
  bvpl_edge_geometric_mean_functor<float> func;
  bvpl_neighb_operator<float, bvpl_edge_geometric_mean_functor<float> > oper(func);
  bvpl_vector_operator vector_oper;
  vector_oper.apply_and_suppress(grid,kernel_vec,&oper,grid_out, id_grid);

  //along the plane the winner should be the target axis
  vcl_cout << vcl_endl;
  TEST("Directions", true,  check_data(id_grid, target_axis, target_id, 2));


  vector_oper.non_maxima_suppression(grid_out, id_grid, kernel_vec);

  //after non-maxima suppression the center voxel should be the winner
  vcl_cout << vcl_endl;
  TEST("Non-max suppression", true, check_non_max(grid_out,2));
}


void test_keep_top_responses()
{
  vgl_vector_3d<unsigned> grid_size(2,2,2);
  bvxm_voxel_grid<float> *grid1=new bvxm_voxel_grid<float>(grid_size);
  grid1->initialize_data(1.0f);
  bvxm_voxel_grid<float> *grid2=new bvxm_voxel_grid<float>(grid_size);
  grid2->initialize_data(2.0f);
  bvxm_voxel_grid<float> *grid3=new bvxm_voxel_grid<float>(grid_size);
  grid3->initialize_data(3.0f);
  bvxm_voxel_grid<float> *grid4=new bvxm_voxel_grid<float>(grid_size);
  grid4->initialize_data(4.0f);
  
  bvxm_voxel_grid<vnl_vector_fixed<float,3> > *resp = new bvxm_voxel_grid<vnl_vector_fixed<float,3> >(grid_size);
  bvxm_voxel_grid<vnl_vector_fixed<int,3> > *id_grid = new bvxm_voxel_grid<vnl_vector_fixed<int,3> >(grid_size);
  
  bvpl_discriminative_non_max_suppression vec_oper;
  vec_oper.keep_top_responses(resp, grid1,id_grid, 1);
  vec_oper.keep_top_responses(resp, grid2,id_grid, 2);
  vec_oper.keep_top_responses(resp, grid3,id_grid, 3);
  vec_oper.keep_top_responses(resp, grid4,id_grid, 4);
  
  //check top responses
  bvxm_voxel_grid<vnl_vector_fixed<float,3> >::iterator resp_it= resp->begin();
  bvxm_voxel_grid<vnl_vector_fixed<int,3> >::iterator id_it= id_grid->begin();
  bool result = true;
  vnl_vector_fixed<float,3> sample_resp(4.0f, 3.0f,2.0f);
  vnl_vector_fixed<int,3> sample_id(4,3,2);
  for(; resp_it!=resp->end(); ++resp_it, ++ id_it)
  {
    bvxm_voxel_slab<vnl_vector_fixed<float,3> >::iterator resp_slab_it= resp_it->begin();
    bvxm_voxel_slab<vnl_vector_fixed<int,3> >::iterator id_slab_it= id_it->begin();
    for(; resp_slab_it!=resp_it->end(); ++resp_slab_it, ++ id_slab_it)
    {
      result = result && (*resp_slab_it == sample_resp) && (*id_slab_it == sample_id);
    }
  }

  TEST("Keep top responses", true, result);
  
}




void test_local_non_max()
{

  
}

MAIN(test_bvpl_vector_operator)
{
  test_vector_operator();
  test_non_max_suppression();
  //test_keep_top_responses();
  test_local_non_max();
  return 0;
}
