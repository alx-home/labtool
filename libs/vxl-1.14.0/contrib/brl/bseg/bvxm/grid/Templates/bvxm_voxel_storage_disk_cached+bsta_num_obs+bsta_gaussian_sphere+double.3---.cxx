#include <bvxm/grid/bvxm_voxel_storage_disk_cached.txx>
#include <bsta/bsta_attributes.h>
#include <bsta/bsta_mixture_fixed.h>
#include <bsta/bsta_gaussian_sphere.h>
#include <bsta/io/bsta_io_attributes.h>
#include <bsta/io/bsta_io_gaussian_sphere.h>

typedef bsta_num_obs<bsta_gaussian_sphere<double,3> > gauss_type;
BVXM_VOXEL_STORAGE_DISK_CACHED_INSTANTIATE(gauss_type);
