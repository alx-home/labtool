#include <boct/boct_tree_cell.txx>
#include "boxm/boxm_apm_traits.h"
#include "boxm/boxm_sample.h"

typedef boxm_sample<BOXM_APM_SIMPLE_GREY> boxm_sample_simple_grey;
BOCT_TREE_CELL_INSTANTIATE(short,boxm_sample_simple_grey );

// tree with appearance
typedef boxm_apm_traits<BOXM_APM_SIMPLE_GREY>::apm_datatype apm_datatype;
BOCT_TREE_CELL_INSTANTIATE(short, apm_datatype);
