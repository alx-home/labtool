#include <boct/boct_tree_cell_reader.txx>
#include "boxm/boxm_apm_traits.h"
#include "boxm/boxm_sample.h"

typedef boxm_sample<BOXM_APM_MOG_GREY> boxm_sample_mog_grey;
BOCT_TREE_CELL_READER_INSTANTIATE(short,boxm_sample_mog_grey);
