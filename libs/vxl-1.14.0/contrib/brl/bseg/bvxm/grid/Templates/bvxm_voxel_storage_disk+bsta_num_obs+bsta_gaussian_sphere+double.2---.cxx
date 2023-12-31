#include <bvxm/grid/bvxm_voxel_storage_disk.txx>
#include <bsta/bsta_attributes.h>
#include <bsta/io/bsta_io_attributes.h>
#include <bsta/io/bsta_io_gaussian_sphere.h>

typedef bsta_num_obs<bsta_gaussian_sphere<double, 2> > gauss_type;
BVXM_VOXEL_STORAGE_DISK_INSTANTIATE(gauss_type);
