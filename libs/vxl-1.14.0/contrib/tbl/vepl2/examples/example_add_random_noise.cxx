//:
// \file
//  This example program shows a typical use of the vepl2_add_random_noise function
//  on a ubyte image.  The input image (argv[1]) must be ubyte, and in that
//  case random noise is added to it (Gaussian, with sigma argv[3], default
//  1) to argv[2] which is always a PGM file image.
//  The input and output vil_image_resources are directly passed to the filter.
//
// \author Peter Vanroose, K.U.Leuven, ESAT/PSI
// \date   7 October 2002, from vepl/examples
//
#include <vil/vil_load.h>
#include <vil/vil_save.h>

#include <vepl2/vepl2_add_random_noise.h>
#include <vcl_iostream.h>
#include <vcl_cstdlib.h> // for atof()

int
main(int argc, char** argv) {
  if (argc < 3) { vcl_cerr << "Syntax: example_add_random_noise file_in file_out [width]\n"; return 1; }

  // The input image:
  vil_image_resource_sptr in = vil_load_image_resource(argv[1]);
  if (!in) { vcl_cerr << "Cannot read image from "<<argv[1]<<'\n'; return 2; }

  // The noise `width':
  double sigma = (argc < 4) ? 5 : vcl_atof(argv[3]);

  // The filter:
  vil_image_resource_sptr out = vepl2_add_random_noise(in,sigma);

  // Output to file:
  if (vil_save_image_resource(out, argv[2], "pnm"))
    vcl_cout << "Written noisy image of type PNM to " << argv[2] << '\n';
  else
    vcl_cout << "Could not write noisy image as PNM to "<< argv[2]<<'\n';

  return 0;
}
