#include "bvxm_merge_mog.h"
//:
// \file

#include <vcl_cmath.h>
#include <vcl_vector.h>
#include <bvxm/grid/bvxm_voxel_grid.h>

void bvxm_merge_mog::kl_merge(bvxm_merge_mog::mix_gauss_type const& mixture, bsta_gauss_f1 &gaussian)
{
  //When merging components of gaussian mixtures, we need to perform the followign calculations
  //1. find the normalizing weight of the new component. In this case this value is 1 because
  //   we are merging all the componets
  //2. find the mean
  //3. find the variance
  
  
  //Find mean and variance
  float mean = 0.0f;
  float var = 0.0f;
  
  //CAUTION: only mixtures of 3 modes are supported for now. The value is hardcoded, because when reading and writing the world
  //mixture.num_components becomes curropted
  
  //unsigned num_components = mixture.num_components();
  unsigned num_components = 3; 
  
  for (unsigned i = 0; i<num_components; i++) 
  {
    //note these equations ommit the weight of the final distribution
    // only becausee in this case it is 1
    mean = mean + mixture.weight(i)*mixture.distribution(i).mean();
    var = var +  mixture.weight(i)*mixture.distribution(i).var() +
      mixture.weight(i)*vcl_pow(mixture.distribution(i).mean(),2);
  }
  if(var <  vcl_pow(mean,2))
    vcl_cout<< mixture <<vcl_endl;
  var = var - vcl_pow(mean,2);

  gaussian.set_mean(mean);
  gaussian.set_var(var);
  return;
}

//: Merges the components of the gaussian mixtures at each voxel into a single gaussian
//  Thus the resulting grid contains unimodal gaussians
bool bvxm_merge_mog::kl_merge_grid(bvxm_voxel_grid_base_sptr apm_base,
                                   bvxm_voxel_grid_base_sptr gauss_base)
{
  //cast grids
  bvxm_voxel_grid< mix_gauss_type >* apm_grid = static_cast<bvxm_voxel_grid< mix_gauss_type>* >(apm_base.ptr());
  bvxm_voxel_grid< gauss_type >* gauss_grid = static_cast<bvxm_voxel_grid< gauss_type>* >(gauss_base.ptr());

  //iterate through the grid merging mixtures
  bvxm_voxel_grid< mix_gauss_type >::iterator apm_it = apm_grid->begin();
  bvxm_voxel_grid< gauss_type >::iterator gauss_it = gauss_grid->begin();

  for (unsigned z=0; z<apm_grid->grid_size().z(); ++z, ++apm_it, ++gauss_it)
  {
    bvxm_voxel_slab< mix_gauss_type >::iterator apm_slab_it = (*apm_it).begin();
    bvxm_voxel_slab< gauss_type >::iterator gauss_slab_it = (*gauss_it).begin();

    for (; apm_slab_it!=(*apm_it).end(); apm_slab_it++, gauss_slab_it++)
    {
      kl_merge(*apm_slab_it, *gauss_slab_it);
    }
  }
  return true;
}

//: Converts a mog grid into a most probable mode grid
bool bvxm_merge_mog::mpm_grid(bvxm_voxel_grid_base_sptr apm_base,
                                   bvxm_voxel_grid_base_sptr gauss_base)
{
  //cast grids
  bvxm_voxel_grid< mix_gauss_type >* apm_grid = static_cast<bvxm_voxel_grid< mix_gauss_type>* >(apm_base.ptr());
  bvxm_voxel_grid< gauss_type >* gauss_grid = static_cast<bvxm_voxel_grid< gauss_type>* >(gauss_base.ptr());
  
  //iterate through the grid merging mixtures
  bvxm_voxel_grid< mix_gauss_type >::iterator apm_it = apm_grid->begin();
  bvxm_voxel_grid< gauss_type >::iterator gauss_it = gauss_grid->begin();
  
  for (unsigned z=0; z<apm_grid->grid_size().z(); ++z, ++apm_it, ++gauss_it)
  {
    bvxm_voxel_slab< mix_gauss_type >::iterator apm_slab_it = (*apm_it).begin();
    bvxm_voxel_slab< gauss_type >::iterator gauss_slab_it = (*gauss_it).begin();
    
    for (; apm_slab_it!=(*apm_it).end(); apm_slab_it++, gauss_slab_it++)
    {
      //most probable mode
      *gauss_slab_it = (*apm_slab_it).distribution(0);
    }
  }
  return true;
}

