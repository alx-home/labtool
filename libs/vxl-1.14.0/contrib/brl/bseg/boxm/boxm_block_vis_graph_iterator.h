#ifndef boxm_block_vis_graph_iterator_h_
#define boxm_block_vis_graph_iterator_h_
//:
// \file
#include "boxm_block_vis_graph_node.h"
#include "boxm_block.h"
#include "boxm_scene.h"
#include <vcl_vector.h>
#include <vcl_map.h>

template <class T>
class boxm_block_vis_graph_iterator
{
 public:
  boxm_block_vis_graph_iterator(vpgl_camera_double_sptr cam, boxm_scene<T>* scene,
                                unsigned img_ni, unsigned img_nj, bool rev_iter=false);

  ~boxm_block_vis_graph_iterator(){}

  bool next();

  vcl_vector<boxm_block<T>*> frontier_blocks();

  vcl_vector<vgl_point_3d<int> > frontier_indices() const {return to_process_indices_; }

  void set_reverse_iter(bool reverse) { reverse_it_ = reverse; }

 private:

  typedef vcl_map<vgl_point_3d<int>, boxm_block_vis_graph_node<T>, vgl_point_3d_cmp<int> > vis_graph_type;

  //: visibility graph, indexed by the block indices
  vis_graph_type vis_graph_;

  //: blocks that can be seen by the camera unoccluded
  vcl_vector<typename vis_graph_type::iterator> curr_blocks_;

  vcl_vector<vgl_point_3d<int> > to_process_indices_;

  //: the camera
  vpgl_camera_double_sptr camera_;

  boxm_scene<T>* scene_;

  bool reverse_it_;
};

#endif
