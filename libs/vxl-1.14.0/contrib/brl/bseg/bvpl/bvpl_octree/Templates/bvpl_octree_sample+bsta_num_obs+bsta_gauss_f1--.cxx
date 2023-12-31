#include <bvpl/bvpl_octree/bvpl_octree_sample.txx>
#include <bsta/bsta_gauss_f1.h>
#include <bsta/io/bsta_io_attributes.h>
#include <bsta/io/bsta_io_gaussian_sphere.h>

typedef bsta_num_obs<bsta_gauss_f1> gauss_type;
BVPL_OCTREE_SAMPLE_INSTANTIATE(gauss_type);
