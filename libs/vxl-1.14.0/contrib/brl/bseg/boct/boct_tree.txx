#ifndef boct_tree_txx_
#define boct_tree_txx_
//:
// \file
#include "boct_tree.h"
#include <vcl_cmath.h>
#include <vcl_iostream.h>
#include <vgl/vgl_box_3d.h>
#include <vgl/io/vgl_io_box_3d.h>

//: Construct an empty tree from maximum number of levels and levels, to initialize
template <class T_loc,class T_data>
boct_tree<T_loc,T_data>::boct_tree(short num_levels, short init_levels): num_levels_(num_levels), root_level_(num_levels-1), max_val_((double)(1 << root_level_)), root_(0)
{
  // root is allocated at (max_level_-1) with code [0,0,0]
  boct_loc_code<T_loc> code;
  if (init_levels>0)
  {
    code.set_code(0,0,0);
    code.set_level(root_level_);
    root_=new boct_tree_cell<T_loc,T_data>( code);
  }
  init_levels--;
  while (init_levels > 0) {
    vcl_vector<boct_tree_cell<T_loc,T_data>*> cells;
    cells = leaf_cells();
    for (unsigned i=0; i<cells.size(); i++) {
      boct_tree_cell<T_loc,T_data>* c = static_cast<boct_tree_cell<T_loc,T_data>*>(cells[i]);
      c->split();
    }
    init_levels--;
  }
}

template <class T_loc,class T_data>
boct_tree<T_loc,T_data>::boct_tree(T_data data,short num_levels, short init_levels): num_levels_(num_levels), root_level_(num_levels-1), max_val_((double)(1 << root_level_)), root_(0)
{
  // root is allocated at (max_level_-1) with code [0,0,0]
  boct_loc_code<T_loc> code;
  if (init_levels>0)
  {
    code.set_code(0,0,0);
    code.set_level(root_level_);
    root_=new boct_tree_cell<T_loc,T_data>( code);
  }
  init_levels--;
  while (init_levels > 0) {
    vcl_vector<boct_tree_cell<T_loc,T_data>*> cells;
    cells = leaf_cells();
    for (unsigned i=0; i<cells.size(); i++) {
      boct_tree_cell<T_loc,T_data>* c = static_cast<boct_tree_cell<T_loc,T_data>*>(cells[i]);
#if 1 // temporarily commented out? Now, "data" is an unused parameter!
      T_data newdata=data;
      c->set_data(newdata);
#endif
      c->split();
    }
    init_levels--;
  }
}


//: Construct from bounding box, maximum number of levels and levels to initialize
template <class T_loc,class T_data>
boct_tree<T_loc,T_data>::boct_tree(vgl_box_3d<double>  bbox,short num_levels, short init_levels)
: num_levels_(num_levels), root_level_(num_levels-1), max_val_((double)(1 << root_level_)),global_bbox_(bbox)
{
  // root is allocated at (max_level_-1) with code [0,0,0]
  boct_loc_code<T_loc> code;
  if (num_levels_>0)
  {
    code.set_code(0,0,0);
    code.set_level(root_level_);
    root_=new boct_tree_cell<T_loc,T_data>( code);
  }
  init_levels--;
  while (init_levels > 0) {
    vcl_vector<boct_tree_cell<T_loc,T_data>*> cells;
    cells = leaf_cells();
    for (unsigned i=0; i<cells.size(); i++) {
      boct_tree_cell<T_loc,T_data>* c = static_cast<boct_tree_cell<T_loc,T_data>*>(cells[i]);
      c->split();
    }
    init_levels--;
  }
}

template <class T_loc,class T_data>
boct_tree_cell<T_loc,T_data>* boct_tree<T_loc,T_data>::construct_tree(vcl_vector<boct_tree_cell<T_loc, T_data> >& leaf_nodes,
                                                                      short num_levels)
{
  // create an empty tree
  boct_loc_code<T_loc> code;
  boct_tree_cell<T_loc,T_data>* root;
  if (num_levels>0) {
    code.set_code(0,0,0);
    code.set_level(num_levels-1);
    root=new boct_tree_cell<T_loc,T_data>( code);
  }
  else {
    vcl_cerr << "boct_tree: the tree max level is 0, cannot create a tree!\n";
    return 0;
  }

  for (unsigned i=0; i<leaf_nodes.size(); i++)
  {
    boct_tree_cell<T_loc, T_data>& cell = leaf_nodes[i];
    boct_loc_code<T_loc> loccode=cell.code_;
    int level=loccode.level;

    // temporary pointer to traverse
    boct_tree_cell<T_loc,T_data>* curr_cell=root;
    short curr_level=num_levels-1;

    while (curr_level>level)
    {
      if (curr_cell->is_leaf()) {
        curr_cell->split();
      }
      short child_index=loccode.child_index(curr_level);
      if (child_index < 0)
        vcl_cout << "ERROR 1: child_index is " << child_index << vcl_endl;
      curr_cell=curr_cell->children()+child_index;
      --curr_level;
    }

    if (curr_cell->code_.isequal(&loccode))
      // the place of the cell is found, put the data in
      curr_cell->set_data(cell.data());
    else
      vcl_cerr << "WRONG ERROR CODE OR CELL FOUND!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
  }
  return root;
}


//: Destructor. Deleted all cells
template <class T_loc,class T_data>
boct_tree<T_loc,T_data>::~boct_tree()
{
  if (root_)
  {
    if (root_->is_leaf()) {
      delete root_;
    }
    else {
      root_->delete_children();
      delete root_;
    }
  }
}

//: Clones with the same data
template <class T_loc,class T_data>
boct_tree<T_loc,T_data>* boct_tree<T_loc,T_data>::clone()
{
  boct_tree_cell<T_loc, T_data>* root = root_->clone(0);
  boct_tree<T_loc,T_data>* tree = new boct_tree<T_loc,T_data>(root,num_levels_);
  return tree;
}

//: Clone a subtree determined by the root
template <class T_loc,class T_data>
boct_tree<T_loc, T_data>* boct_tree<T_loc,T_data>::clone_subtree(boct_tree_cell<T_loc, T_data>* subtree_root, short parent_tree_root_level)
{
  //Create root cell with location code corresponding to the subtree
  boct_loc_code<T_loc> shift_code;

  short shift_level = parent_tree_root_level - subtree_root->level();
  if (shift_level>0)
  {
    shift_code.set_code(((1<<(parent_tree_root_level - subtree_root->level()) )-1), ((1<<(parent_tree_root_level - subtree_root->level()) )-1), ((1<<(parent_tree_root_level - subtree_root->level()) )-1));
    boct_tree_cell<T_loc, T_data>* root = subtree_root->clone(0, &shift_code);
    boct_tree<T_loc,T_data>* tree = new boct_tree<T_loc,T_data>(root, subtree_root->level() +1 );
    return tree;
  } else if(shift_level == 0)
  {
    boct_tree_cell<T_loc, T_data>* root = subtree_root->clone(0);
    boct_tree<T_loc,T_data>* tree = new boct_tree<T_loc,T_data>(root, subtree_root->level() +1 );
    return tree;
  }
  else {
    vcl_cerr << "Error in boct_tree<T_loc,T_data>::clone_subtree \n";
    return NULL;
  }
}

//: Clones(from a root) the part of the subtree that intesects the bounding region
template <class T_loc,class T_data>
boct_tree<T_loc, T_data>* boct_tree<T_loc,T_data>::clone_and_intersect(boct_tree_cell<T_loc, T_data>* subtree_root,
                                                                       short parent_tree_root_level,
                                                                       vgl_box_3d<double> local_crop_box)
{
  //Create root cell with location code corresponding to the subtree
  boct_loc_code<T_loc> shift_code;

  short shift_level = parent_tree_root_level - subtree_root->level();
  if (shift_level>0)
  {
    shift_code.set_code(((1<<(subtree_root->level()))-1), ((1<<(subtree_root->level()))-1), ((1<<(subtree_root->level()))-1));
    boct_tree_cell<T_loc, T_data>* root = subtree_root->clone_and_intersect(0, &shift_code,local_crop_box, parent_tree_root_level);
    boct_tree<T_loc,T_data>* tree = new boct_tree<T_loc,T_data>(root, subtree_root->level() +1 );
    return tree;
  } else if(shift_level == 0)
  {
    boct_tree_cell<T_loc, T_data>* root = subtree_root->clone_and_intersect(0,local_crop_box, parent_tree_root_level);
    boct_tree<T_loc,T_data>* tree = new boct_tree<T_loc,T_data>(root, subtree_root->level() +1 );
    return tree;
  }
  else {
    vcl_cerr << "Error in boct_tree<T_loc,T_data>::clone_subtree \n";
    return NULL;
  }
}


//: Initialize all cells with a value
template <class T_loc,class T_data>
void boct_tree<T_loc,T_data>::init_cells(T_data val)
{
  vcl_vector<boct_tree_cell<T_loc,T_data>*> cells = leaf_cells();
  for (unsigned i=0; i<cells.size(); i++) {
    cells[i]->set_data(val);
  }
}

//: Returns the leaf cell that contains the 3d point specified in octree-coordinates i.e. [0,1)x[0,1)x[0,1)
template <class T_loc,class T_data>
boct_tree_cell<T_loc,T_data>* boct_tree<T_loc,T_data>::locate_point(const vgl_point_3d<double>& p, bool check_out_of_bounds)
{
  short curr_level=root_level_;
  // convert point to location code.
  boct_loc_code<T_loc>* loccode_=new boct_loc_code<T_loc>(p, root_level_,max_val_);

  if (check_out_of_bounds)
  {
    if ((loccode_->x_loc_ >> root_level_)^ 0)
      return 0;
    if ((loccode_->y_loc_ >> root_level_)^ 0)
      return 0;
    if ((loccode_->y_loc_ >> root_level_)^ 0)
      return 0;
  }

#if 0
  // check to see if point is contained in the octree
  if (!root_->code_.isequal(loccode_,curr_level))
    return 0;
#endif

  // temporary pointer to traverse
  boct_tree_cell<T_loc,T_data>* curr_cell=root_;

  while (curr_cell->children()&& curr_level>0)
  {
    short index_child=loccode_->child_index(curr_level);
    if (index_child >7)
      vcl_cout << "ERROR 2: child_index is " << index_child << vcl_endl;
    curr_cell=curr_cell->children()+index_child;
    --curr_level;
  }
  // delete the location code constructed
  delete loccode_;
  return curr_cell;
}

//: Returns the leaf cell that contains the 3d point specified in global coordinates
template <class T_loc,class T_data>
boct_tree_cell<T_loc,T_data>* boct_tree<T_loc,T_data>::locate_point_global(const vgl_point_3d<double>& p)
{
  short curr_level=root_level_;
  vgl_point_3d<double> norm_p((p.x()-global_bbox_.min_x())/global_bbox_.width(),
                              (p.y()-global_bbox_.min_y())/global_bbox_.height(),
                              (p.z()-global_bbox_.min_z())/global_bbox_.depth());


#if 0
  // make sure that coordinates of norm_p lie between 0 (inclusive) and 1 (exclusive)
  if (norm_p.x()>=1.0||norm_p.y()>=1.0||norm_p.z()>=1.0||
      norm_p.x() <0.0||norm_p.y() <0.0||norm_p.z() <0.0)
    return 0;
#endif // 0
  // convert point to location code.
  boct_loc_code<T_loc>* loccode_=new boct_loc_code<T_loc>(norm_p, root_level_, max_val_);
#if 0
  // check to see if point is contained in the octree
  if (!root_->code_.isequal(loccode_,curr_level))
    return 0;
#endif
  // temporary pointer to traverse
  boct_tree_cell<T_loc,T_data>* curr_cell=root_;

  while (curr_cell->children()&& curr_level>0)
  {
    short index_child=loccode_->child_index(curr_level);
    if (index_child >7) {
      vcl_cout << loccode_ << vcl_endl
               << "ERROR 3: child_index is " << index_child << vcl_endl;
    }
    curr_cell=curr_cell->children()+index_child;
    --curr_level;
  }
  // delete the location code constructed
  delete loccode_;
  return curr_cell;
}

//: Returns the cell containing "p", at the closest level available to "level"
template <class T_loc,class T_data>
boct_tree_cell<T_loc,T_data>* boct_tree<T_loc,T_data>::locate_point_at_level(const vgl_point_3d<double>& p, short level, bool check_out_of_bounds)
{
  short curr_level=root_level_;
  // convert point to location code.
  boct_loc_code<T_loc>* loccode_=new boct_loc_code<T_loc>(p, root_level_, max_val_);

  if (check_out_of_bounds)
  {
    if ((loccode_->x_loc_ >> root_level_)^ 0)
      return 0;
    if ((loccode_->y_loc_ >> root_level_)^ 0)
      return 0;
    if ((loccode_->y_loc_ >> root_level_)^ 0)
      return 0;
  }
  // temporary pointer to traverse
  boct_tree_cell<T_loc,T_data>* curr_cell=root_;

  while (curr_cell->children()&& curr_level>level)
  {
    short child_index=loccode_->child_index(curr_level);
    curr_cell=curr_cell->children()+child_index;
    --curr_level;
  }
  // delete the location code constructed
  delete loccode_;
  return curr_cell;
}

//: Returns the smallest cell that entirely contains a 3d regionin octree coordinates [0,1)x[0,1)x[0,1)
template <class T_loc,class T_data>
boct_tree_cell<T_loc,T_data>* boct_tree<T_loc,T_data>::locate_region(const vgl_box_3d<double>& r, bool check_out_of_bounds)
{
  boct_loc_code<T_loc>* mincode=new boct_loc_code<T_loc>(r.min_point(), root_level_, max_val_);
  boct_loc_code<T_loc>* maxcode=new boct_loc_code<T_loc>(r.max_point(), root_level_, max_val_);

  boct_loc_code<T_loc>* xorcode=mincode->XOR(maxcode);

  short level_x=root_level_;
  short level_y=root_level_;
  short level_z=root_level_;
  while (!(xorcode->x_loc_&(1<<level_x))&& level_x) level_x--;
  while (!(xorcode->y_loc_&(1<<level_y))&& level_y>level_x) level_y--;
  while (!(xorcode->z_loc_&(1<<level_z))&& level_z>level_y) level_z--;

  level_z++;
  return locate_point_at_level(r.min_point(),level_z, check_out_of_bounds);
}

//: Returns the smallest cell that entirely contains a 3d region in global coordinates
template <class T_loc,class T_data>
boct_tree_cell<T_loc,T_data>* boct_tree<T_loc,T_data>::locate_region_global(const vgl_box_3d<double>& r, bool check_out_of_bounds)
{
  vgl_point_3d<double> min_point((r.min_x()-global_bbox_.min_x())/global_bbox_.width(),
                                 (r.min_y()-global_bbox_.min_y())/global_bbox_.height(),
                                 (r.min_z()-global_bbox_.min_z())/global_bbox_.depth());

  vgl_point_3d<double> max_point((r.max_x()-global_bbox_.min_x())/global_bbox_.width(),
                                 (r.max_y()-global_bbox_.min_y())/global_bbox_.height(),
                                 (r.max_z()-global_bbox_.min_z())/global_bbox_.depth());

  vgl_box_3d<double> r_local(min_point, max_point);
  return locate_region(r_local, check_out_of_bounds);
}

//: Split the tree
template <class T_loc,class T_data>
bool boct_tree<T_loc,T_data>::split()
{
  return root_->split();
}

//: Returns a vector of all leaf cells of the tree
template <class T_loc,class T_data>
vcl_vector<boct_tree_cell<T_loc,T_data>*> boct_tree<T_loc,T_data>::leaf_cells()
{
  vcl_vector<boct_tree_cell<T_loc,T_data>*> v;
  if (root_)
  {
    if (root_->is_leaf()) {
      v.push_back(root_);
    }
    else {
      root_->leaf_children(v);
    }
  }
  return v;
}

//: Returns the total number of leaf nodes in the tree
template <class T_loc, class T_data>
unsigned int boct_tree<T_loc, T_data>::size()
{
  // Note: There should be a more efficient way to do this -DEC
  vcl_vector<boct_tree_cell<T_loc, T_data>*> leaves = leaf_cells();
  return leaves.size();
}

//: Returns all leaf cells at a specified level of the tree
template <class T_loc,class T_data>
vcl_vector<boct_tree_cell<T_loc,T_data>*> boct_tree<T_loc,T_data>::leaf_cells_at_level(short level)
{
  vcl_vector<boct_tree_cell<T_loc,T_data>*> v;
  if (root_)
  {
    if (root_->is_leaf()) {
      if (root_->level() == level)
        v.push_back(root_);
    }
    else {
      root_->leaf_children_at_level(v, level);
    }
  }
  return v;
}

//: Returns all cells at a specified level of the tree (wheather or not they are leafs)
template <class T_loc,class T_data>
vcl_vector<boct_tree_cell<T_loc,T_data>*> boct_tree<T_loc,T_data>::cells_at_level(short level)
{
  vcl_vector<boct_tree_cell<T_loc,T_data>*> v;
  if (root_)
  {
    if (root_->level() == level)
      v.push_back(root_);
    else
      root_->children_at_level(v, level);
  }
  return v;
}

//: Returns all cells on the tree
template<class T_loc, class T_data>
vcl_vector<boct_tree_cell<T_loc,T_data>*>  boct_tree<T_loc,T_data>::all_cells()
{
  vcl_vector<boct_tree_cell<T_loc,T_data>*> v;
  if (root_)
  {
    v.push_back(root_);
    if (!root_->is_leaf())
      root_->all_children(v);
  }
  return v;

}

//: Fills inetermediade cells with the average of the children
template<class T_loc, class T_data>
void boct_tree<T_loc,T_data>::fill_with_average()
{
  if(root_)
    if(!root_->is_leaf())
      root_->set_data_to_avg_children();
  return;

}

//: Return the finest level the tree has been split down to (not necessarly 0)
template <class T_loc,class T_data>
short boct_tree<T_loc,T_data>::finest_level()
{
  short min_level = num_levels_;
  vcl_vector<boct_tree_cell<T_loc,T_data>*> cells = leaf_cells();
  for (unsigned i=0; i<cells.size(); i++) {
    if (cells[i]->code_.level < min_level)
      min_level = cells[i]->code_.level;
  }
  return min_level;
}

template <class T_loc,class T_data>
vgl_box_3d<double> boct_tree<T_loc,T_data>::cell_bounding_box(boct_tree_cell<T_loc,T_data>* const cell)
{
  double cellsize=(double)(1<<cell->level())/max_val_;
  vgl_point_3d<double> local_origin(cell->code_.x_loc_,cell->code_.y_loc_,cell->code_.z_loc_);
  vgl_point_3d<double> global_origin(global_bbox_.min_x()+local_origin.x()/max_val_*global_bbox_.width(),
                                     global_bbox_.min_y()+local_origin.y()/max_val_*global_bbox_.height(),
                                     global_bbox_.min_z()+local_origin.z()/max_val_*global_bbox_.depth());

  return vgl_box_3d<double>(global_origin,
                            cellsize*global_bbox_.width(),
                            cellsize*global_bbox_.height(),
                            cellsize*global_bbox_.depth(),
                            vgl_box_3d<double>::min_pos);
}

template <class T_loc,class T_data>
vgl_box_3d<double> boct_tree<T_loc,T_data>::cell_bounding_box_local(boct_tree_cell<T_loc,T_data>* const cell)
{
  double cellsize=(double)(1<<cell->level())/max_val_;
  vgl_point_3d<double> local_origin(cell->code_.x_loc_,cell->code_.y_loc_,cell->code_.z_loc_);

  vgl_point_3d<double> global_origin(local_origin.x()/max_val_*global_bbox_.width(),
                                     local_origin.y()/max_val_*global_bbox_.height(),
                                     local_origin.z()/max_val_*global_bbox_.depth());

  return vgl_box_3d<double>(global_origin,
                            cellsize*global_bbox_.width(),
                            cellsize*global_bbox_.height(),
                            cellsize*global_bbox_.depth(),
                            vgl_box_3d<double>::min_pos);
}

template <class T_loc,class T_data>
vgl_box_3d<double> boct_tree<T_loc,T_data>::cell_bounding_box_canonical(boct_tree_cell<T_loc,T_data>* const cell)
{
  double onebymaxval=1/max_val_;
  double cellsize=(double)(1<<cell->level())*onebymaxval;
  vgl_point_3d<double> local_origin(cell->code_.x_loc_*onebymaxval,cell->code_.y_loc_*onebymaxval,cell->code_.z_loc_*onebymaxval);

  return vgl_box_3d<double>(local_origin,cellsize,cellsize,cellsize,vgl_box_3d<double>::min_pos);
}

template <class T_loc,class T_data>
void boct_tree<T_loc,T_data>::print()
{
  vcl_cout << "Octree Max Number of Levels=" << num_levels_ << vcl_endl;
  root_->print();
}

template <class T_loc,class T_data>
void boct_tree<T_loc,T_data>::b_write(vsl_b_ostream & os, bool save_internal_nodes)
{
  //new version where we only save the leaf nodes
  short v = version_no(save_internal_nodes);
  vcl_cout << "Internal Nodes 1: " << save_internal_nodes << vcl_endl;

  vcl_cout << "Writing tree binary version: " << v << vcl_endl;

  if (v == 2) {
    vsl_b_write(os, v);
    vsl_b_write(os, num_levels_);
    vsl_b_write(os, global_bbox_);
    vcl_vector<boct_tree_cell<T_loc,T_data>*> cells = leaf_cells();
    vsl_b_write(os, cells.size());
    for (unsigned i=0; i<cells.size(); i++) {
      vsl_b_write(os, cells[i]->code_);
      vsl_b_write(os, cells[i]->data());
    }
  }
  // older version, the whole tree structure is written
  else if (v == 1) {
    vsl_b_write(os, v);
    vsl_b_write(os, num_levels_);
    vsl_b_write(os, global_bbox_);
    if (root_)
      vsl_b_write(os, *root_);
  }
  else
    vcl_cerr << "boct_tree<T_loc,T_data>::b_write -- undefined version number!\n";
}

template <class T_loc,class T_data>
void boct_tree<T_loc,T_data>::b_read(vsl_b_istream & is)
{
  // read header info
  if (!is) return;
  short v;
  vsl_b_read(is, v);

  switch (v)
  {
   case 1:
    vsl_b_read(is, num_levels_);
    vsl_b_read(is, global_bbox_);
    root_ = new boct_tree_cell<T_loc,T_data>();
    vsl_b_read(is, *root_, (boct_tree_cell<T_loc,T_data>*)0);
    this->root_level_ = num_levels_ -1;
    this->max_val_ = (double)(1<<root_level_);
    break;
   case 2:
    {
      vsl_b_read(is, num_levels_);
      vsl_b_read(is, global_bbox_);
      unsigned num_cells;
      vsl_b_read(is, num_cells);

      boct_loc_code<T_loc> code;
      T_data data;
      boct_tree_cell<T_loc,T_data>* root;
      if (num_levels_>0) {
          code.set_code(0,0,0);
          code.set_level(num_levels_-1);
          root=new boct_tree_cell<T_loc,T_data>( code);
      }
      else {
          vcl_cerr << "boct_tree: the tree max level is 0, cannot create a tree!\n";
          return ;
      }

      for (unsigned i=0; i<num_cells; i++) {
          vsl_b_read(is, code);
          vsl_b_read(is, data);

          // temporary pointer to traverse
          boct_tree_cell<T_loc,T_data>* curr_cell=root;
          short curr_level=num_levels_-1;
          short level=code.level;
          while (curr_level>level)
          {
              if (curr_cell->is_leaf()) {
                  curr_cell->split();
              }
              short child_index=code.child_index(curr_level);
              if (child_index < 0)
                  vcl_cout << "ERROR 1: child_index is " << child_index << vcl_endl;
              curr_cell=curr_cell->children()+child_index;
              --curr_level;
          }

          if (curr_cell->code_.isequal(&code))
              // the place of the cell is found, put the data in
              curr_cell->set_data(data);
          else
              vcl_cerr << "WRONG ERROR CODE OR CELL FOUND!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
      }

      this->root_=root;
      this->root_level_ = num_levels_ -1;
      this->max_val_ = (double)(1<<root_level_);
      break;
    }

   default:
    vcl_cerr << "I/O ERROR: vsl_b_read(vsl_b_istream&, boct_tree<T_loc,T_data>&)\n"
             << "           Unknown version number "<< v << '\n';
    is.is().clear(vcl_ios::badbit); // Set an unrecoverable IO error on stream
    return;
  }
}

#define BOCT_TREE_INSTANTIATE(T_loc,T_data) \
template class boct_tree<T_loc,T_data >; \
template void vsl_b_write(vsl_b_ostream & os,const bool save_internal_nodes, boct_tree<T_loc,T_data >&); \
template void vsl_b_read(vsl_b_istream & is, boct_tree<T_loc,T_data >&)

#endif
