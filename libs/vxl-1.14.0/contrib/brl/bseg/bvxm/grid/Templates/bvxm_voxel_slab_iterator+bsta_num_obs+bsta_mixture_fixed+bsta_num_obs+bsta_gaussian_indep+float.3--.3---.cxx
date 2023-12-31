#include <bvxm/grid/bvxm_voxel_slab_iterator.txx>
#include <bsta/bsta_gaussian_indep.h>
#include <bsta/bsta_attributes.h>
#include <bsta/bsta_mixture_fixed.h>

typedef bsta_num_obs<bsta_gaussian_indep<float,3> > gauss_type;
typedef bsta_mixture_fixed<gauss_type, 3> mix_gauss;
typedef bsta_num_obs<mix_gauss> mix_gauss_type;

BVXM_VOXEL_SLAB_ITERATOR_INSTANTIATE(mix_gauss_type);
