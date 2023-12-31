// This is tbl/vepl2/examples/example_erode_disk.cxx

//:
// \file
//  This example program shows a typical use of a morphological function on
//  a ubyte image.  The input image (argv[1]) must be ubyte, and in that
//  case is eroded (circular kernel, default 3x3 square) to argv[2]
//  which is always a PGM file image.
//
// \author Peter Vanroose, K.U.Leuven, ESAT/PSI
// \date   7 October 2002, from vepl/examples
//
#include <vepl2/vepl2_erode_disk.h>

// for I/O:
#include <vil/vil_load.h>
#include <vil/vil_save.h>
#include <vcl_iostream.h>
#include <vcl_cstdlib.h> // for atof()

int
main(int argc, char** argv) {
  if (argc < 3)
  {
    vcl_cerr << "Syntax: example_erode_disk file_in file_out [radius]\n";
    return 1;
  }

  // The input image:
  vil_image_resource_sptr in = vil_load_image_resource(argv[1]);
  if (!in) { vcl_cerr << "Please use a ubyte image as input\n"; return 2; }

  // The radius: (default is 3x3 square)
  float radius = (argc < 4) ? 1.5f : (float)vcl_atof(argv[3]);

  // The filter:
  vil_image_resource_sptr out = vepl2_erode_disk(in,radius);

  // Write output:
  if (vil_save_image_resource(out, argv[2], "pnm"))
    vcl_cout << "Written eroded image to PNM image "<< argv[2]<< '\n';
  else
    vcl_cout << "Could not write eroded image as PNM to " << argv[2] << '\n';

  return 0;
}
