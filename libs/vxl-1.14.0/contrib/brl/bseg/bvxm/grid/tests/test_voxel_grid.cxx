#include <testlib/testlib_test.h>
#include <vcl_iostream.h>
#include <vcl_vector.h>
#include <vul/vul_file.h>

#include <vgl/vgl_vector_3d.h>

#include "../bvxm_voxel_grid.h"
#include "../bvxm_voxel_storage.h"
#include "../bvxm_voxel_storage_disk.h"
#include "../bvxm_voxel_slab.h"


static void test_voxel_grid()
{
  // we need temporary disk storage for this test.
  vcl_string storage_fname("bvxm_voxel_grid_test_temp.vox");
  vcl_string storage_cached_fname("bvxm_voxel_grid_cached_test_temp.vox");
  // remove file if exists from previous test.
  if (vul_file::exists(storage_fname.c_str())) {
    vul_file::delete_file_glob(storage_fname.c_str());
  }
  if (vul_file::exists(storage_cached_fname.c_str())) {
    vul_file::delete_file_glob(storage_cached_fname.c_str());
  }

  vgl_vector_3d<unsigned> grid_size(300,300,120);
  unsigned max_cache_size = grid_size.x()*grid_size.y()*18;

  // try test with all types of underlying storage.
  vcl_vector<bvxm_voxel_grid<float>* > grids;
  vcl_vector<vcl_string> grid_types; // for labeling tests
  grids.push_back(new bvxm_voxel_grid<float>(storage_fname,grid_size)); // disk storage;
  grid_types.push_back("disk_storage");
  grids.push_back(new bvxm_voxel_grid<float>(grid_size)); // memory storage;
  grid_types.push_back("memory storage");
  grids.push_back(new bvxm_voxel_grid<float>(storage_cached_fname,grid_size,max_cache_size)); // cached disk storage
  grid_types.push_back("disk_cached_storage");

  vcl_string test_name;

  for (unsigned i=0; i<grids.size(); i++) {

    bvxm_voxel_grid<float> *grid = grids[i];

    // check num_observations
    unsigned nobs = grid->num_observations();
    test_name = grid_types[i] + ": number of observations initially == 0";
    TEST(test_name.c_str(),nobs,0);

    // fill with test data
    float init_val = 0.5f;
    grid->initialize_data(init_val);
    bool init_check = true;
    bool write_read_check = true;

    nobs = grid->num_observations();
    test_name = grid_types[i] + ": number of observations == 0 after init";
    TEST(test_name.c_str(),nobs,0);

    grid->increment_observations();
    nobs = grid->num_observations();
    test_name = grid_types[i] + ": number of observations == 1 after increment";
    TEST(test_name.c_str(),nobs,1);

    // read in each slice, check that init_val was set, and fill with new value
    unsigned count = 0;
    vcl_cout << "read/write: ";
    bvxm_voxel_grid<float>::iterator slab_it;
    for (slab_it = grid->begin(); slab_it != grid->end(); ++slab_it) {
      vcl_cout << '.';
      bvxm_voxel_slab<float>::iterator vit;
      for (vit = slab_it->begin(); vit != slab_it->end(); vit++, count++) {
        if (*vit != init_val) {
          vcl_cerr << "error: read in value does not match init value! count = " << count << vcl_endl;
          init_check = false;
        }
        // write new value
        *vit = static_cast<float>(count);
      }
    }
    vcl_cout << "done." << vcl_endl;

    test_name = grid_types[i] + ": Initialization correctly set voxel values?";
    TEST(test_name.c_str(),init_check,true);

    grid->increment_observations();
    nobs = grid->num_observations();
    test_name = grid_types[i] + ": number of observations == 2 after increment";
      TEST(test_name.c_str(),nobs,2);

    // read in each slice, check that written value is set. use const iterators.
    count = 0;
    vcl_cout << "read: ";
    bvxm_voxel_grid<float>::const_iterator slab_it_const;
    for (slab_it_const = grid->begin(); slab_it_const != grid->end(); ++slab_it_const) {
      vcl_cout << '.';
      bvxm_voxel_slab<float>::const_iterator vit;
      for (vit = slab_it_const->begin(); vit != slab_it_const->end(); vit++, count++) {
        if (*vit != static_cast<float>(count)) {
          vcl_cerr << "error: read in value does not match written value! count = " << count << vcl_endl;
          write_read_check = false;
        }
      }
    }
    vcl_cout << "done." << vcl_endl;

    test_name = grid_types[i] + ": Read in voxel values match written values?";
    TEST(test_name.c_str(),write_read_check,true);
  }

  // delete grids
  for (unsigned i=0; i<grids.size(); i++) {
    delete grids[i];
  }

  // remove temporary file
  vul_file::delete_file_glob(storage_fname.c_str());
}

TESTMAIN( test_voxel_grid );
