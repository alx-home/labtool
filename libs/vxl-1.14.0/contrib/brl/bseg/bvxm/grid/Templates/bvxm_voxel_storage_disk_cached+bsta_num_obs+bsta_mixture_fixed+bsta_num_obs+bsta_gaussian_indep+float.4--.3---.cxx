#include <bvxm/grid/bvxm_voxel_storage_disk_cached.txx>
#include <bsta/bsta_gaussian_indep.h>
#include <bsta/bsta_attributes.h>
#include <bsta/bsta_mixture_fixed.h>

typedef bsta_num_obs<bsta_gaussian_indep<float,4> > gauss_type;
typedef bsta_mixture_fixed<gauss_type, 3> mix_gauss;
typedef bsta_num_obs<mix_gauss> mix_gauss_type;

BVXM_VOXEL_STORAGE_DISK_CACHED_INSTANTIATE(mix_gauss_type);
