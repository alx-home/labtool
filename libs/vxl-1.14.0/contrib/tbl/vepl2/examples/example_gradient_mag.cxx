//:
// \file
//  This example program shows a typical use of an IP filter, namely
//  the gradient magnitude operator on a greyscale image.  The input image
//  (argv[1]) must be a ubyte image, and in that case its gradient is
//  written to argv[2] which is always a PGM file image.
//
// \author Peter Vanroose, K.U.Leuven, ESAT/PSI
// \date   7 October 2002, from vepl/examples
//
#include <vepl2/vepl2_gradient_mag.h>

// for I/O:
#include <vil/vil_load.h>
#include <vil/vil_save.h>
#include <vcl_iostream.h>

int
main(int argc, char** argv) {
  if (argc < 3)
  {
    vcl_cerr << "Syntax: example_gradient_mag file_in file_out\n";
    return 1;
  }

  // The input image:
  vil_image_resource_sptr in = vil_load_image_resource(argv[1]);
  if (!in) { vcl_cerr << "Please use a ubyte image as input\n"; return 2; }

  // The filter:
  vil_image_resource_sptr out = vepl2_gradient_mag(in);

  // Write output:
  if (vil_save_image_resource(out, argv[2], "pnm"))
    vcl_cout << "Written gradient image to PNM image "<< argv[2]<< '\n';
  else
    vcl_cout << "Could not write gradient image as PNM to " << argv[2] << '\n';

  return 0;
}
