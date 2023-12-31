#include <boxm/boxm_scene.txx>
#include <boct/boct_tree.h>
#include <boxm/boxm_edge_tangent_sample.h>
#include <boxm/boxm_inf_line_sample.h>

typedef boct_tree<short,boxm_edge_tangent_sample<float> > aux_tree;
BOXM_SCENE_INSTANTIATE(aux_tree);

typedef boct_tree<short,boxm_inf_line_sample<float> > tree;
BOXM_SCENE_INSTANTIATE(tree);
