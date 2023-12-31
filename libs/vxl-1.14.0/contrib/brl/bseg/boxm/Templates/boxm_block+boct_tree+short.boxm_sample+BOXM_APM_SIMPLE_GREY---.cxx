#include <boxm/boxm_block.txx>
#include <boxm/boxm_apm_traits.h>
#include <boxm/boxm_sample.h>
#include <boct/boct_tree.h>

typedef boct_tree<short,boxm_sample<BOXM_APM_SIMPLE_GREY> >  tree_type;
BOXM_BLOCK_INSTANTIATE(tree_type);

// block with appearance
typedef boxm_apm_traits<BOXM_APM_SIMPLE_GREY>::apm_datatype apm_datatype;
typedef boct_tree<short,apm_datatype >  apm_tree_type;
BOXM_BLOCK_INSTANTIATE(apm_tree_type);
