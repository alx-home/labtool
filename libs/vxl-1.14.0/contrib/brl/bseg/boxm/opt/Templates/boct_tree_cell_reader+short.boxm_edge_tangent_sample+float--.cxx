#include <boct/boct_tree_cell_reader.txx>
#include <boxm/boxm_edge_tangent_sample.h>

typedef boxm_edge_tangent_sample<float> aux_sample;
BOCT_TREE_CELL_READER_INSTANTIATE(short,aux_sample);
