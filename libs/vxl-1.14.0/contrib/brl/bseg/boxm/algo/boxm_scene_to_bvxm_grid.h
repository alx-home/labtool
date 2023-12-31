// This is brl/bseg/boxm/algo/boxm_scene_to_bvxm_grid.h
#ifndef boxm_scene_to_bvxm_grid_h
#define boxm_scene_to_bvxm_grid_h
//:
// \file
// \brief Set of functions that convert a boxm_scene to a bvxm grid
// \author Isabel Restrepo mir@lems.brown.edu
// \date  Jan 15, 2009
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <boxm/boxm_scene.h>
#include <bvxm/grid/bvxm_voxel_grid.h>
#include <bvxm/grid/bvxm_voxel_grid_basic_ops.h>
#include <vcl_iostream.h>
#include <boxm/boxm_cell_data_traits.h>

template <class T_loc, class T_data>
bvxm_voxel_grid<T_data>* boxm_scene_to_bvxm_grid(boxm_scene<boct_tree<T_loc, T_data > > &scene,
                                                 vcl_string input_path,
                                                 unsigned int resolution_level,
                                                 bool enforce_level = false )
{
  //Print a little reminder that no inter/extra-polation happens in this function
  vcl_cout << "Convertion boxm_scene to bvxm_grid\n"
  << "Current resolution level: " << resolution_level << "\n"
  << "Enforcing only level cells ? " << enforce_level << "\n"
  << "Is grid saving internal nodes? " <<scene.save_internal_nodes() << vcl_endl;
  
  typedef boct_tree<T_loc, T_data > tree_type;

  // create an array for each block, and save in a binary file
  boxm_block_iterator<tree_type> iter(&scene);

  unsigned int finest_level=100000;
  // find the finest levels in the blocks
  while (!iter.end()) {
    vgl_point_3d<int> idx = iter.index();
    scene.load_block(idx);
    boxm_block<tree_type>* block = scene.get_block(idx);
    vgl_box_3d<double> block_bb = block->bounding_box();
    tree_type* tree = block->get_tree();
    if (tree->finest_level() < int(finest_level)) {
      finest_level = tree->finest_level();
    }
    iter++;
  }

  // do not make the resolution smaller than finest level
  if (resolution_level < finest_level)
    resolution_level=finest_level;


  // make sure the resolution level for all trees is the same
  iter.begin();
  short root_level = 0;
  {
    vgl_point_3d<int> idx = iter.index();
    scene.load_block(idx);
    boxm_block<tree_type>* block = scene.get_block(idx);
    tree_type* tree = block->get_tree();
    root_level = tree->root_level();
  }

  // make sure root level is the same for all the trees
  while (!iter.end()) {
    vgl_point_3d<int> idx = iter.index();
    scene.load_block(idx);
    boxm_block<tree_type>* block = scene.get_block(idx);
    tree_type* tree = block->get_tree();
    if (tree->root_level() != root_level)
    {
      vcl_cerr << "Error converting boxm_scene to bvxm_grid: blocks have different root level\n";
    }
    iter++;
  }

  // number of cells for each block should be the same, because they have the
  // same tree max_level definitions
  unsigned int ncells = 1 << (root_level - (int)resolution_level);
  
  vcl_cout << "Number of cells per grid side: " << ncells << "\n";

  //create the regular grid
  vgl_vector_3d<unsigned> dim = scene.world_dim(); //number of blocks in the scene
  unsigned dimx = dim.x()*ncells; // total number of cells in the scene x-dim
  unsigned dimy = dim.y()*ncells;
  unsigned dimz = dim.z()*ncells;
  bvxm_voxel_grid<T_data> *grid = new bvxm_voxel_grid<T_data>(input_path,vgl_vector_3d<unsigned>(dimx,dimy,dimz));
  T_data data_init(boxm_zero_val<T_loc, T_data>());
  grid->initialize_data(data_init);
  
  vcl_cout << "Grid Size: " << vgl_vector_3d<unsigned>(dimx,dimy,dimz) << "\n";
  vcl_cout << "In boxm_scene_to_bxm_grid, default voxel value for the grid is: " << data_init << vcl_endl;

  //iterate through grid, locate corresponding position in the octree
  typename bvxm_voxel_grid<T_data>::iterator grid_it=grid->begin();

  //locate point in the tree, for now assume ONLY ONE BLOCK
  iter.begin();
  vgl_point_3d<int> idx = iter.index();
  scene.load_block(idx);
  boxm_block<tree_type>* block = scene.get_block(idx);
  vgl_box_3d<double> block_bb = block->bounding_box();
  tree_type* tree = block->get_tree();

  // assume that bounding box is a cube
  //const double step_len = ((block_bb.max_x() - block_bb.min_x())/double(ncells));

  for (unsigned z=0; z<dimz; ++grid_it, ++z)
  {
    bvxm_voxel_slab<T_data> slab = (*grid_it);
    vcl_cout << '.' <<vcl_flush ;
    for (unsigned y=0; y<dimy;++y)
    {
      for (unsigned x=0; x<dimx; ++x)
      {
        vgl_point_3d<double> p(((double)x/(double)dimx), ((double)y/(double)dimy), (0.99 - (double)z/(double)dimz));
        //locate the cell containing the point closest to the specified level
        boct_tree_cell<T_loc,T_data>* this_cell = tree->locate_point_at_level(p, resolution_level,true);
        
        if (!this_cell) {
          vcl_cerr << "In boxm_scene_to_bvxm_grid: cell out of bounds\n";
          continue;
        }
      
        unsigned int level = this_cell->get_code().level;
        T_data cell_val = this_cell->data();
        
        if(level < resolution_level)
          vcl_cerr << "In boxm_scene_to_bvxm_grid: current level smaller than target level\n";

        //if enfoce level is true, there is no iter/extrapolation
        if((enforce_level)&& (level != resolution_level))
          continue;
        
        // just copy value to output grid
        slab(x,y) = cell_val;
        
      }
    }
  }
  vcl_cout << '\n';
  return grid;
}
#endif
