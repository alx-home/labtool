// This is core/vil/tests/test_blocked_image_resource.cxx
#include <testlib/testlib_test.h>
#include <vcl_iostream.h>
#include <vcl_string.h>
#include <vil/vil_new.h>
#include <vil/vil_load.h>
#include <vil/vil_property.h>
#include <vpl/vpl.h> // vpl_unlink()
#include <vil/vil_image_view.h>
#include <vil/vil_blocked_image_resource.h>
#include <vil/vil_block_cache.h>


static vcl_string image_file;
static void test_blocked_image_resource()
{
  vcl_cout << "************************************\n"
           << " Testing vil_blocked_image_resource\n"
           << "************************************\n";
  // Test Resource
  const unsigned int ni = 73;
  const unsigned int nj = 43;
  vil_image_view<unsigned short> image;
  image.set_size(ni,nj);
  for (unsigned i = 0; i<ni; ++i)
    for (unsigned j = 0; j<nj; ++j)
      image(i,j) = (unsigned short)(i + ni*j);
  vil_image_resource_sptr ir = vil_new_image_resource_of_view(image);

  vcl_string path("test_blocked_tiff.tif");
  unsigned sbi = 16, sbj = 32;
  unsigned nbi = (ni+sbi-1)/sbi, nbj = (nj+sbj-1)/sbj;
  vcl_cout << "Creating new blocked resource " << path << '\n';
  { // scope for resource
    vil_blocked_image_resource_sptr bir =
      vil_new_blocked_image_resource(path.c_str(),
                                     ir->ni(), ir->nj(),
                                     ir->nplanes(),
                                     ir->pixel_format(),
                                     sbi, sbj,
                                     "tiff");
    if (bir)
    {
      bool put_view_worked = bir->vil_image_resource::put_view(image);
      TEST("Put view to tiff blocked resource", put_view_worked, true);
    }
    else
      TEST("Put view to tiff blocked resource", false, true);
  }// delete resource by going out of scope
  vil_image_resource_sptr lir = vil_load_image_resource(path.c_str());
  vil_blocked_image_resource_sptr bir = blocked_image_resource(lir);
  if (bir) {
    vcl_cout << "Blocked Image Parameters\n"
             << "ni = " << bir->ni() << " nj = " << bir->nj()
             << " nplanes = "  << bir->nplanes() << '\n'
             << "size_block_i = " << bir->size_block_i()
             << "   size_block_j = " << bir->size_block_j()
             << "   n_block_i = " << bir->n_block_i()
             << "   n_block_j = " << bir->n_block_j() << '\n';
    bool success = sbi == bir->size_block_i() && sbj == bir->size_block_j();
    success = success && nbi == bir->n_block_i() && nbj == bir->n_block_j();
    TEST("Load blocked image resource", success, true);
  }
  else
  {
    TEST("Load blocked image resource", true, false);
  }

  if (bir)
  {
    vil_image_view<unsigned short> lview =
        bir->get_block(bir->n_block_i()-1, bir->n_block_j()-1);
#if 0
    for (unsigned j = 0; j<lview.nj(); ++j)
    {
      for (unsigned i = 0; i<lview.ni(); ++i)
        vcl_cout << lview(i,j) << ' ' ;
      vcl_cout << '\n';
    }
    vcl_cout << '\n';
#endif
    // value in upper left corner of last block
    unsigned last_block_val = ni*(nbj-1)*sbj+(nbi-1)*sbi;
    TEST("Last Block Value", lview(0,0)==last_block_val, true);
  }
  else
  {
    TEST("Last Block Value", false, true);
  }

  ///////-------- ----- Test Copying Blocks -------------------------///////
  vcl_cout << "Start test for copying blocks\n";
  vcl_string path2("test_blocked_tiff2.tif");
  bool good_copy = true;
  { // scope to close bir2
    vil_blocked_image_resource_sptr bir2 =
      vil_new_blocked_image_resource(path2.c_str(),
                                     bir->ni(), bir->nj(),
                                     bir->nplanes(),
                                     bir->pixel_format(),
                                     bir->size_block_i(), bir->size_block_j(),
                                     "tiff");  //
    if (bir2)
    {
      for (unsigned j = 0; j<bir2->n_block_j()&&good_copy; ++j)
        for (unsigned i = 0; i<bir2->n_block_i()&&good_copy; ++i)
        {
          vil_image_view_base_sptr blk = bir->get_block(i,j);
          if (!blk)
            good_copy = false;
#if 0
          if (blk)
          {
            vil_image_view<unsigned short> bv = blk;
            vcl_cout << "Block from resource(" << i << ' ' << j << ")["
                     <<  bv.ni() << ' ' << bv.nj() <<  "]\n";
            for (unsigned bj = 0; bj<bv.nj(); ++bj)
            {
              for (unsigned bi = 0; bi<bv.ni(); ++bi)
              {
                vcl_cout << bv(bi,bj) << ' ';
              }
              vcl_cout << '\n';
            }
          }
          vcl_cout << '\n';
#endif
          if (!bir2->put_block(i, j, *blk))
            good_copy = false;
        }
      TEST("Copy blocks", good_copy, true);
    }
    else
      TEST("Copy blocks", false, true);
  } // end of bir2 scope

  vcl_cout << "Loading resource from " << path2 << '\n';
  vil_image_resource_sptr bir2 = vil_load_image_resource(path2.c_str());
  if (bir2&&good_copy)
  {
    vil_image_view<unsigned short> v = bir->get_view();
    vil_image_view<unsigned short> v2 = bir2->get_view();
    for (unsigned i = 0; i<bir->ni(); ++i)
      for (unsigned j = 0; j<bir->nj(); ++j)
      {
        good_copy = good_copy && v(i,j)==v2(i,j);
        if (v(i,j)!=v2(i,j))
          vcl_cout << "v(" << i << ' ' << j <<  ") = " << v(i,j)
                   << "vs. " << v2(i,j) << '\n';
      }
  }
  else
  {
    TEST("Copy blocks to resource", false, true);
  }
  TEST("Copy blocks to resource", good_copy, true);
  //
  /////////---------------Test the facade -----------------------///////
  //
  vcl_cout << "Start testing the facade\n";
  vil_blocked_image_resource_sptr bif =
    vil_new_blocked_image_facade(ir, sbi, sbj);
  if (bif)
  {
    vcl_cout << "Blocked Image Parameters\n"
             << "ni = " << bif->ni() << " nj = " << bif->nj()
             << " nplanes = "  << bif->nplanes() << '\n'
             << "size_block_i = " << bif->size_block_i()
             << "   size_block_j = " << bif->size_block_j()
             << "   n_block_i = " << bif->n_block_i()
             << "   n_block_j = " << bif->n_block_j() << '\n';
    nbi = bif->n_block_i(); nbj = bif->n_block_j();
    TEST("Test blocking parameters", (nbi==(ni+bif->size_block_i()-1)/sbi)&&
         (nbj==(nj+bif->size_block_j()-1)/sbj), true);
    vil_image_view<unsigned short> block = bif->get_block(nbi-1, nbj-1);
    unsigned slbi = ni-(nbi-1)*sbi, slbj = nj-(nbj-1)*sbj;
    bool good = true;
    for (unsigned j = 0; j<slbj; ++j)
    {
      for (unsigned i = 0; i<slbi; ++i)
      {
        good = good && block(i,j)==image((nbi-1)*sbi+i, (nbj-1)*sbj +j);
        vcl_cout << block(i,j) << ' ';
      }
      vcl_cout << '\n';
    }
    TEST("Test lower right corner block", good, true);
  }
  vcl_cout << "Test copying from one facade to another\n";
  vil_image_view<unsigned short> dest;
  image.set_size(ni,nj);
  unsigned dsbi = 3, dsbj = 7;
  vil_image_resource_sptr dir = vil_new_image_resource_of_view(image);
  vil_blocked_image_resource_sptr dbif =
    vil_new_blocked_image_facade(dir, dsbi, dsbj);
  if (dbif)
  {
    vcl_cout << "Destination Blocked Image Parameters\n"
             << "size_block_i = " << dbif->size_block_i()
             << "   size_block_j = " << dbif->size_block_j()
             << "   n_block_i = " << dbif->n_block_i()
             << "   n_block_j = " << dbif->n_block_j() << '\n';

    vil_blocked_image_resource_sptr sbif =
      vil_new_blocked_image_facade(ir, dsbi, dsbj);

    if (sbif) {
      for (unsigned bi = 0; bi<dbif->n_block_i(); ++bi)
        for (unsigned bj = 0; bj<dbif->n_block_j(); ++bj)
        {
          vil_image_view_base_sptr v = sbif->get_block(bi, bj);
          dbif->put_block(bi, bj,*v);
        }
      bool valid = true;
      vil_image_view<unsigned short> out = dbif->get_view();
      for (unsigned i = 0; i<ni; ++i)
        for (unsigned j = 0; j<nj; ++j)
          valid = valid && out(i,j)==image(i,j);
      TEST("Full destination resource equality", valid , true);
    }
    else
    {
      TEST("Full destination resource equality", false , true);
    }
  }
  // test vil_new
  vil_blocked_image_resource_sptr flbir = blocked_image_resource(lir);
  vil_blocked_image_resource_sptr fabir = vil_new_blocked_image_facade(ir,sbi, sbj);
  if (flbir&&fabir)
  {
    vil_image_view<unsigned short> flview = flbir->get_block(0,0);
    vil_image_view<unsigned short> faview = fabir->get_block(0,0);
    bool valid = true;
    for (unsigned i = 0; i<sbi; ++i)
      for (unsigned j = 0; j<sbj; ++j)
        valid = valid && flview(i,j)==faview(i,j);
    TEST("vil_new for file and facade", valid , true);
  }
  else
    TEST("vil_new for file and facade", false , true);

  //
  /////////---------------Test the cache -----------------------///////
  //
  sbi = 16, sbj = 16;
  vil_block_cache cache(2);
  // add two blocks
  vil_image_view_base_sptr blk1;
  for (unsigned bi = 0; bi<3; ++bi)
  {
    vil_image_view_base_sptr blk = ir->get_view(bi*sbi, sbi, 0, sbj);
    if (bi==1)
      blk1 = blk;
    cache.add_block(bi, 0, blk);
  }
  // get block 1
  vil_image_view_base_sptr old_blk;
  bool got_b1 = cache.get_block(1, 0, old_blk);
  bool the_same = old_blk==blk1;
  // get block 0 -- should not be in the queue
  bool got_b0 = cache.get_block(0, 0, old_blk);
  TEST("test store and retrieve", got_b1&&the_same&&!got_b0 , true);
  // At this point the cache content (in age order)
  //  [1,0] [2,0] - since [1,0] was accessed and is now the youngest
  // get a new block and put it in the cache
  vil_image_view_base_sptr blk = ir->get_view(3*sbi, sbi, 0, sbj);
  cache.add_block(3, 0, blk);
  // now the cache content should be
  //  [3,0] [1,0]
  bool got_b3 = cache.get_block(3,0,old_blk);
  got_b1 = cache.get_block(1,0,old_blk);
  bool got_b2 = cache.get_block(2,0,old_blk);
  TEST("test age ordering", got_b1&&got_b3&&!got_b2 , true);

  //
  /////////--------------Test the cached resource--------------------///////
  //
  vcl_cout << "Start test of cached resource\n";
  sbj = 32;
  vil_blocked_image_resource_sptr cflbir = vil_new_cached_image_resource(bir);
  vil_blocked_image_resource_sptr cfabir = vil_new_cached_image_resource(fabir);
  if (cflbir&&cfabir)
  {
    vil_image_view<unsigned short> cflview = cflbir->get_copy_view(0,sbi,0,sbj);
    vil_image_view<unsigned short> cflblk = cflbir->get_block(0,0);
    vil_image_view<unsigned short> cfaview = cfabir->get_copy_view(0,sbi,0,sbj);
    vil_image_view<unsigned short> cfablk = cfabir->get_block(0,0);

    bool  valid = true;
    for (unsigned i = 0; i<sbi; ++i)
      for (unsigned j = 0; j<sbj; ++j)
        valid = valid && cflview(i,j)==cfaview(i,j) &&
          cflview(i,j)==cflblk(i,j) && cflview(i,j)==cfablk(i,j);
    TEST("Get block from cache", valid , true);
  }
  else
  {
    TEST("Get block from cache", false , true);
  }
  // set sptr's to 0 so the underlying objects are destructed and the
  // temporary image files are closed.  Otherwise the unlink below will
  // fail.
  ir = 0;
  bir = 0;
  lir = 0;
  bir2 = 0;
  bif = 0;
  dir = 0;
  dbif = 0;
  flbir = 0;
  fabir = 0;
  cflbir = 0;
  cfabir = 0;
  // delete temporary files
  vpl_unlink(path.c_str());
  vpl_unlink(path2.c_str());
  //
  ///////--------------------- Test NITF Blocked Resource ---------------////
  vcl_string nitf_path = image_file + "ff_nitf_16bit.nitf";
  vil_image_resource_sptr imgr = vil_load_image_resource(nitf_path.c_str());
  if (imgr)
  {
    TEST("NITF blocked resource",
         imgr->get_property(vil_property_size_block_i, &sbi) &&
         imgr->get_property(vil_property_size_block_j, &sbj),
         true);
  }
  else
  {
    TEST("NITF resource ", false, true);
  }
  vil_blocked_image_resource_sptr bimgr = blocked_image_resource(imgr);
  if (bimgr)
  {
    vil_image_view<unsigned short> view = bimgr->get_block(0, 0);
    for (unsigned bi = 0; bi<sbi; ++bi)
      for (unsigned bj = 0; bj<sbj; ++bj)
        vcl_cout << "NITF v(" << bi << ' ' << bj << ")=" << view(bi,bj) << '\n';
    TEST("Test NITF ", view(1,0)==8191&&sbi==2, true);
  }
  else
  {
    TEST("NITF blocked image resource", false, true);
  }
}

int
test_blocked_image_resource_main( int argc, char* argv[] )
{
  vcl_cout << "test_blocked_image_resource main\n";
  if ( argc >= 2 ) {
    image_file = argv[1];
    image_file += "/";
  }
  else
    image_file = "core/vil/tests/file_read_data/";
  vcl_cout << "Start test process\n";
  test_blocked_image_resource();
  return 0;
}

