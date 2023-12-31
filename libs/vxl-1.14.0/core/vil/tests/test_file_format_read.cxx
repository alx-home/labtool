// This is core/vil/tests/test_file_format_read.cxx
#include <vcl_iostream.h>
#include <vcl_fstream.h>
#include <vcl_vector.h>
#include <vcl_cmath.h>
#include <vxl_config.h> // for vxl_uint_16 etc.

#include <testlib/testlib_test.h>

#include <vil/vil_file_format.h>
#include <vil/vil_rgb.h>
#include <vil/vil_load.h>
#include <vil/vil_image_view.h>
#include <vil/vil_print.h>
#include <vil/vil_config.h>

// For testing specific file formats
#include <vil/vil_stream_fstream.h>

// \author Amitha Perera
// \date Apr 2002
//
// Compare the results of loading different files with the true data
// that's supposed to be in those files.

static vcl_string image_base;


// A comparator interface to check if the pixels match. It will be
// called with all the components at a single location (given by i, j and p).
//
template<class TruePixelType, class ImgPixelType>
struct Compare
{
  virtual ~Compare() {}
  virtual bool operator() ( vil_image_view<ImgPixelType> const&,
                            int p, int i, int j,
                            const vcl_vector<TruePixelType>& pixel ) const = 0;
};


// Below are various "real" comparators


template<class PixelType>
struct CompareRGB
  : public Compare<PixelType, vil_rgb<PixelType> >
{
  virtual bool operator() ( vil_image_view< vil_rgb<PixelType> > const& img,
                            int p, int i, int j,
                            const vcl_vector<PixelType>& pixel ) const
  {
    return p==0 && pixel.size() == 3 &&
           img(i,j).r == pixel[0] &&
           img(i,j).g == pixel[1] &&
           img(i,j).b == pixel[2];
  }
};


template<class PixelType>
struct CompareRGBA
  : public Compare<PixelType, vil_rgba<PixelType> >
{
  virtual bool operator() ( vil_image_view< vil_rgba<PixelType> > const& img,
                            int p, int i, int j,
                            const vcl_vector<PixelType>& pixel ) const
  {
    return p==0 && pixel.size() == 4 &&
           img(i,j).r == pixel[0] &&
           img(i,j).g == pixel[1] &&
           img(i,j).b == pixel[2] &&
           img(i,j).a == pixel[3];
  }
};


template<class PixelType>
struct CompareRGBNear
  : public Compare<PixelType, vil_rgb<PixelType> >
{
  virtual bool operator() ( vil_image_view< vil_rgb<PixelType> > const& img,
                            int p, int i, int j,
                            const vcl_vector<PixelType>& pixel ) const
    {
      if ( p == 0 && pixel.size() == 3 ) {
        // Find difference in two values whilst avoiding unsigned underflow
        PixelType diff_A = static_cast<PixelType>
                           ( pixel[0]*pixel[0] + img(i,j).r * img(i,j).r +
                             pixel[1]*pixel[1] + img(i,j).g * img(i,j).g +
                             pixel[2]*pixel[2] + img(i,j).b * img(i,j).b );

        PixelType diff_B = static_cast<PixelType>
                           ( 2 * pixel[0] * img(i,j).r + tol_sq_ +
                             2 * pixel[1] * img(i,j).g + tol_sq_ +
                             2 * pixel[2] * img(i,j).b + tol_sq_ );
        return diff_A < diff_B;
      }
      else {
        return false;
      }
    }

  CompareRGBNear( PixelType tol )
    : tol_sq_( static_cast<PixelType>(tol*tol) )
    { }

  PixelType tol_sq_;
};


template<class PixelType, int num_planes>
struct ComparePlanes
  : public Compare<PixelType, PixelType >
{
  virtual bool operator() ( vil_image_view<PixelType> const& img,
                            int p, int i, int j,
                            const vcl_vector<PixelType>& pixel ) const
  {
    return 0 <= p && p < num_planes && pixel.size() == 1 && img(i,j,p) == pixel[0];
  }
};


// Greyscale is simply planar with 1 plane.
template<class PixelType>
struct CompareGrey
  : public ComparePlanes<PixelType, 1>
{
};


template<class PixelType>
struct CompareGreyFloat
  : public Compare<PixelType,PixelType>
{
  virtual bool operator() ( vil_image_view<PixelType> const& img,
                            int p, int i, int j,
                            const vcl_vector<PixelType>& pixel ) const
  {
    return p==0 && pixel.size() == 1 &&
           vcl_fabs( pixel[0] - img(i,j) ) <= 1e-6 * vcl_fabs( pixel[0] );
  }
};


template<class PixelType>
struct CompareGreyNear
  : public Compare<PixelType,PixelType>
{
  virtual bool operator() ( vil_image_view<PixelType> const& img,
                            int p, int i, int j,
                            const vcl_vector<PixelType>& pixel ) const
    {
      if ( p==0 && pixel.size() == 1 ) {
        // Find difference in two values whilst avoiding unsigned underflow
        PixelType diff_A = static_cast<PixelType>(pixel[0] * pixel[0] + img(i,j) * img(i,j));
        PixelType diff_B = static_cast<PixelType>(2 * pixel[0] * img(i,j) + tol_sq_);
        return diff_A <= diff_B;
      }
      else {
        return false;
      }
    }

  CompareGreyNear( PixelType tol )
    : tol_sq_( static_cast<PixelType>(tol*tol) )
    { }

  PixelType tol_sq_;
};


// ===========================================================================
// read value

// To read the true pixel data, we can't just do a fin >> x when x is
// a char, because that would read in a character, not a small
// integer. The following function and its specializations are to
// solve this issue.

// Read in a number from the stream into pix.
// Return value is true if the read FAILED.
template<class TruePixelType>
bool
read_value( vcl_istream& fin, TruePixelType& pix )
{
  return ! (fin >> pix);
}

// Specialization to make char read as small integers and not characters
// See comments on template for return value.
VCL_DEFINE_SPECIALIZATION
bool
read_value( vcl_istream& fin, char& pix )
{
  int x;
  // use operator! to test the stream to avoid compiler warnings
  bool bad = ! ( fin >> x );
  if ( !bad ) pix = char(x);
  return bad;
}


// Specialization to make char read as small integers and not characters
// See comments on template for return value.
VCL_DEFINE_SPECIALIZATION
bool
read_value( vcl_istream& fin, unsigned char& pix )
{
  int x;
  // use operator! to test the stream to avoid compiler warnings
  bool bad = ! ( fin >> x );
  if ( !bad ) pix = static_cast<unsigned char>(x);
  return bad;
}


// Specialization to make char read as small integers and not characters
// See comments on template for return value.
VCL_DEFINE_SPECIALIZATION
bool
read_value( vcl_istream& fin, signed char& pix )
{
  int x;
  // use operator! to test the stream to avoid compiler warnings
  bool bad = ! ( fin >> x );
  if ( !bad ) pix = static_cast<signed char>(x);
  return bad;
}

// Specialization to make bool read as 0/1 integers
// See comments on template for return value.
VCL_DEFINE_SPECIALIZATION
bool
read_value( vcl_istream& fin, bool& pix )
{
  int x;
  // use operator! to test the stream to avoid compiler warnings
  bool bad = ! ( fin >> x );
  if ( !bad ) pix = ( x != 0 );
  return bad;
}


// ===========================================================================
// Check pixels
//
// Compare the pixels in an already loaded image resource against the true
// pixel values with the given pixel comparator.
//
template<class TruePixelType, class ImgPixelType>
bool
CheckPixels( Compare<TruePixelType,ImgPixelType> const& check,
             char const* true_data_file,
             vil_image_resource_sptr ir )
{
  // The true data is a ASCII file consisting of a sequence of
  // numbers. The first set of numbers are:
  //    number of planes (P)
  //    number of components (C)
  //    width (in pixels, not components)
  //    height (in pixels, not components)
  //    planes*width*height*components of data, in the following order:
  //        plane1pix1comp1 plane1pix1comp2 ... plane1pixNcompC ... planePpix1comp1 ... planePpixNcompC
  //      where N = width*height

  int num_planes;
  int num_comp;
  int width;
  int height;

  vcl_ifstream fin( (image_base+true_data_file).c_str() );
  if ( !( fin >> num_planes >> num_comp >> width >> height ) ) {
    vcl_cout << "[couldn't read header from " << true_data_file << ']' << vcl_flush;
    return false;
  }

  // Generate different views from the resource, including the full image.
  //
  vcl_vector< vil_image_view<ImgPixelType> > views;
  vcl_vector< unsigned > offi;
  vcl_vector< unsigned > offj;
  for ( unsigned dl = 0; dl < 3; ++dl ) {
    for ( unsigned dt = 0; dt < 2; ++dt ) {
      for ( unsigned dr = 0; dr < 3; ++dr ) {
        for ( unsigned db = 0; db < 2; ++db ) {
          if ( dl+dr < ir->ni() && dt+db < ir->nj() ) {
            vil_image_view_base_sptr im =
              ir->get_copy_view( dl, ir->ni()-dl-dr, dt, ir->nj()-dt-db );
            if ( !im ) {
              vcl_cout << "[ couldn't read (sub)image data from " << ir << "]\n"
                       << "[ off=(" << dl << ',' << dt
                       << ")x(" << ir->ni()-dl-dr << ','
                       << ir->nj()-dt-db << " ]" << vcl_endl;
              return false;
            }
            vil_image_view<ImgPixelType> img = im;
            if ( !img ) {
              vcl_cout << "[ couldn't read (sub)image data of the expected format from "
                       << im << " at offset " << dl << ',' << dt << ']' << vcl_endl;
              return false;
            }

            if ( img.ni() != ir->ni()-dl-dr || img.nj() != ir->nj()-dt-db ) {
              vcl_cout << "[ (sub)image has wrong size (!= "
                       << ir->ni()-dl-dr << 'x' << ir->nj()-dt-db
                       << ") in " << img << vcl_endl;
              return false;
            }

#ifdef DEBUG
            if (img.size() < 100) {
              vcl_cout << "\nSubimage " << views.size() << " at ("<<dl<<','<<dt<<"):\n";
              vil_print_all(vcl_cout, img); vcl_cout.flush();
            }
            else {
              vcl_cout << "Subimage size = " << img.size() << ".  Too large to display all pixels." << vcl_endl;
            }
#endif

            views.push_back( img );
            offi.push_back( dl );
            offj.push_back( dt );
          }
        }
      }
    }
  }

  // Compare pixels
  //

  vcl_vector<TruePixelType> pixel( num_comp );

  for ( int p=0; p < num_planes; ++p ) {
    for ( int j=0; j < height; ++j ) {
      for ( int i=0; i < width; ++i ) {
        for ( int c=0; c < num_comp; ++c )
        {
          // Need to do things this way because pixel[c] may have a
          // type different from TruePixelType. For example,
          // vector<bool> has weird types to compensate for the packed
          // bit representation.
          //
          TruePixelType pv;
          if ( read_value( fin, pv ) )
          {
            return false;
          }
          pixel[c] = pv;
        }

        // Check the pixels of each view containing this coordinate.
        //
        for ( unsigned v = 0; v < views.size(); ++v ) {
          if ( i >= int(offi[v]) && i < int(offi[v]+views[v].ni()) &&
               j >= int(offj[v]) && j < int(offj[v]+views[v].nj()) &&
               !check( views[v], p, i-offi[v], j-offj[v], pixel ) ) {
            vcl_cout << "View " << v << " at offset (" << offi[v] << ',' << offj[v]
                     << ") [ " << views[v] << " ] has a mismatch at pixel (p="
                     << p << ",i=" << i << ",j=" << j << ')' << vcl_endl;
            if ( views[v].size() < 100 ) {
              vil_print_all( vcl_cout, views[v] );
              vcl_cout.flush();
            }
            return false;
          }
        }
      }
    }
  }

  return true;
}


// ===========================================================================
// Check file
//
// Load the given image file in the standard way and compare the
// pixels against the true pixel values with the given pixel
// comparator.
//
template<class TruePixelType, class ImgPixelType>
bool
CheckFile( Compare<TruePixelType,ImgPixelType> const& check,
           char const* true_data_file,
           char const* img_data_file )
{
  vil_image_resource_sptr ir = vil_load_image_resource((image_base + img_data_file).c_str());
  if ( !ir ) {
    vcl_cout << "[ couldn't load image file " << img_data_file << " ]" << vcl_endl;
    return false;
  }
  else {
    return CheckPixels( check, true_data_file, ir );
  }
}

// ===========================================================================
// Check format
//
// Load the given image file using the given file format and compare
// the pixels against the true pixel values with the given pixel
// comparator.
//
template<class TruePixelType, class ImgPixelType>
bool
CheckFormat( Compare<TruePixelType,ImgPixelType> const& check,
             char const* true_data_file,
             char const* img_data_file,
             vil_file_format* ffmt )
{
  bool result;
  vil_stream* is = new vil_stream_fstream( (image_base + img_data_file).c_str(), "r" );
  is->ref();
  if ( is->ok() ) {
    vil_image_resource_sptr ir = ffmt->make_input_image( is );
    if ( !ir ) {
      vcl_cout << "[ couldn't load image file " << img_data_file << " ]" << vcl_endl;
      result = false;
    }
    else {
      result = CheckPixels( check, true_data_file, ir );
    }
  }
  else {
    vcl_cout << "[ couldn't open file " << img_data_file << " for reading ]" << vcl_endl;
    result = false;
  }
  is->unref();
  return result;
}


static void
test_file_format_read( int argc, char* argv[] )
{
  if ( argc >= 2 ) {
    image_base = argv[1];
    image_base += "/";
  }

  // Test generic file loads

  vcl_cout << "GENERIC FILE LOAD\n\n"
           << "Portable aNy Map [pnm]: (pbm, pgm, ppm)\n";

  TEST("1-bit pbm ascii", CheckFile(CompareGrey<bool>(), "ff_grey1bit_true.txt", "ff_grey1bit_ascii.pbm" ), true);
  TEST("1-bit pbm raw", CheckFile(CompareGrey<bool>(), "ff_grey1bit_true.txt", "ff_grey1bit_raw.pbm" ), true);
  TEST("8-bit pgm ascii", CheckFile(CompareGrey<vxl_byte>(), "ff_grey8bit_true.txt", "ff_grey8bit_ascii.pgm" ), true);
  TEST("8-bit pgm raw", CheckFile(CompareGrey<vxl_byte>(), "ff_grey8bit_true.txt", "ff_grey8bit_raw.pgm" ), true);
  TEST("8-bit pgm raw 2", CheckFile(CompareGrey<vxl_byte>(), "ff_grey8bit_true.txt", "ff_grey8bit_raw2.pgm" ), true);
  TEST("16-bit pgm ascii", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_ascii.pgm" ), true);
  TEST("16-bit pgm raw", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_raw.pgm" ), true);
  TEST("8-bit ppm ascii", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_ascii.ppm" ), true);
  TEST("8-bit ppm ascii as planar", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_planar8bit_true.txt", "ff_rgb8bit_ascii.ppm" ), true);
  TEST("8-bit ppm raw", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_raw.ppm" ), true);
  TEST("8-bit ppm raw as planar", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_planar8bit_true.txt", "ff_rgb8bit_raw.ppm" ), true);
  TEST("16-bit ppm ascii", CheckFile(CompareRGB<vxl_uint_16>(), "ff_rgb16bit_true.txt", "ff_rgb16bit_ascii.ppm" ), true);
  TEST("16-bit ppm raw", CheckFile(CompareRGB<vxl_uint_16>(), "ff_rgb16bit_true.txt", "ff_rgb16bit_raw.ppm" ), true);

  vcl_cout << "JPEG [jpg]\n";
  TEST("8-bit grey, normal image to 4 quanta", CheckFile(CompareGreyNear<vxl_byte>(4), "ff_grey8bit_true.txt", "ff_grey8bit_compressed.jpg" ), true);
  TEST("8-bit RGB, easy image accurate to 3 quanta", CheckFile(CompareRGBNear<vxl_byte>(3), "ff_rgb8biteasy_true.txt", "ff_rgb8biteasy_compressed.jpg" ), true);

  vcl_cout << "Windows bitmap [bmp]\n";
  TEST("8-bit greyscale (xv created)", CheckFile(CompareGrey<vxl_byte>(), "ff_grey8bit_true.txt", "ff_grey8bit.bmp" ), true);
  TEST("8-bit RGB (xv created)", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_planar8bit_true.txt", "ff_rgb8bit_xv.bmp" ), true);

  vcl_cout << "Portable Network Graphics [png]\n";
  TEST("8-bit RGB uncompressed", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_uncompressed.png" ), true);
  TEST("8-bit RGB compressed", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_compressed.png" ), true);
  TEST("10-bit grey with bitdepth=true (from labview)", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey10bit_true.txt", "ff_grey10bit_labview_bitdepth_true.png" ), true);
  TEST("10-bit grey with bitdepth=false (from labview)", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey10bit_true.txt", "ff_grey10bit_labview_bitdepth_false.png" ), true);
  TEST("16-bit grey with bitdepth=true (from labview)", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_labview_bitdepth_true.png" ), true);
  TEST("16-bit grey with bitdepth=false (from labview)", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_labview_bitdepth_false.png" ), true);

  vcl_cout << "TIFF [tiff]\n";
  TEST("8-bit RGB uncompressed", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_uncompressed.tif" ), true);

  TEST("8-bit RGB packbits", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_packbits.tif" ), true);
  TEST("32-bit float grey", CheckFile(CompareGreyFloat<float>(), "ff_grey_float_true.txt", "ff_grey_float.tif" ), true);
  TEST("8-bit RGBA uncompressed", CheckFile(CompareRGBA<vxl_byte>(), "ff_rgba8bit_true.txt", "ff_rgba8bit_uncompressed.tif" ), true);
  TEST("8-bit RGBA without RowsPerStrip", CheckFile(CompareRGBA<vxl_byte>(), "no_rowsperstrip_true.txt", "no_rowsperstrip.tif" ), true);

  // The following tests are targeted to the vil_nitf2_image class which can read NITF 2.1, NITF 2.0 and
  // NSIF 1.0 files.  All three of these formats are covered here as well as all four different
  // types of data layouts for uncompressed data (IMODE).  Also we test a fair number of different
  // data types (eg. 8-bit unsigned, 16-bit unsigned, 32-bit signed, double, float, bool)
  // TODO: Create NITF tests for the following cases:
  // 1) read second image test (ie. multiple images in one file)
  vcl_cout << "NITF 2.1 [nitf] (uncompressed)\n";
  TEST("8-bit unsigned int (IMODE=P)", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_nitf_8bit_true.txt", "ff_nitf_8bit_p.nitf" ), true);
  TEST("8-bit unsigned int (IMODE=B)", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_nitf_8bit_true.txt", "ff_nitf_8bit_b.nitf" ), true);
  TEST("8-bit unsigned int (IMODE=R)", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_nitf_8bit_true.txt", "ff_nitf_8bit_r.nitf" ), true);
  TEST("8-bit unsigned int (IMODE=S)", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_nitf_8bit_true.txt", "ff_nitf_8bit_s.nitf" ), true);
  TEST("16-bit unsigned int (ABPP=13)", CheckFile(CompareGrey<vxl_uint_16>(), "ff_nitf_16bit_true.txt", "ff_nitf_16bit.nitf" ), true);
  vcl_cout << "NITF 2.0 [nitf] (uncompressed)\n";
  TEST("32-bit signed int", CheckFile(CompareGrey<vxl_int_32>(), "ff_nitf_32bit_true.txt", "ff_nitf_32bit.nitf" ), true);
  TEST("32-bit float", CheckFile(CompareGreyFloat<float>(), "ff_nitf_float_true.txt", "ff_nitf_float.nitf" ), true);
  TEST("64-bit float (double)", CheckFile(CompareGreyFloat<double>(), "ff_nitf_float_true.txt", "ff_nitf_double.nitf" ), true);
  vcl_cout << "NSIF 1.0 [nitf] (uncompressed)\n";
  TEST("1-bit bool (NSIF w/ LUT to parse)", CheckFile(CompareGrey<bool>(), "ff_nitf_1bit_lut_true.txt", "ff_nitf_1bit_lut.nsif" ), true);

#if HAS_J2K
  vcl_cout << "JPEG 2000 [j2k,jpc]\n";
  TEST("p0_12 (3x5x1 x 8Bit)", CheckFile(CompareGrey<vxl_byte>(), "p0_12_true.txt", "p0_12.j2k" ), true);

  vcl_cout << "NITF 2.1 [nitf] (JPEG 2000 compressed)\n";
  TEST("p0_12 (3x5x1 x 8Bit)", CheckFile(CompareGrey<vxl_byte>(), "p0_12_true.txt", "p0_12a.ntf" ), true);
#endif // HAS_J2K

  vcl_cout << "Sun raster [ras]\n";
  TEST("8-bit grey, no colourmap", CheckFile(CompareGrey<vxl_byte>(), "ff_grey8bit_true.txt", "ff_grey8bit_nocol.ras" ), true);
  TEST("8-bit RGB, no colourmap", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_raw.ras" ), true);
  TEST("8-bit indexed RGB", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit_indexed.ras" ), true);

  vcl_cout << "Khoros VIFF [viff]\n";
  TEST("8-bit grey big endian", CheckFile(CompareGrey<vxl_uint_8>(), "ff_grey8bit_true.txt", "ff_grey8bit_bigendian.viff" ), true);
  TEST("8-bit RGB big endian", CheckFile(ComparePlanes<vxl_uint_8,3>(), "ff_planar8bit_true.txt", "ff_rgb8bit_bigendian.viff" ), true);
  TEST("16-bit grey big endian", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_bigendian.viff" ), true);
  TEST("16-bit RGB big endian", CheckFile(ComparePlanes<vxl_uint_16,3>(), "ff_planar16bit_true.txt", "ff_rgb16bit_bigendian.viff" ), true);
  TEST("32-bit grey big endian", CheckFile(CompareGrey<vxl_uint_32>(), "ff_grey32bit_true.txt", "ff_grey32bit_bigendian.viff" ), true);
  TEST("32-bit float grey big endian", CheckFile(CompareGreyFloat<float>(), "ff_grey_float_true.txt", "ff_grey_float_bigendian.viff" ), true);
  TEST("64-bit float grey big endian", CheckFile(CompareGreyFloat<double>(), "ff_grey_float_true.txt", "ff_grey_double_bigendian.viff" ), true);

  TEST("8-bit grey little endian", CheckFile(CompareGrey<vxl_uint_8>(), "ff_grey8bit_true.txt", "ff_grey8bit_littleendian.viff" ), true);
  TEST("8-bit RGB little endian", CheckFile(ComparePlanes<vxl_uint_8,3>(), "ff_planar8bit_true.txt", "ff_rgb8bit_littleendian.viff" ), true);
  TEST("16-bit grey little endian", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_littleendian.viff" ), true);
  TEST("16-bit RGB little endian", CheckFile(ComparePlanes<vxl_uint_16,3>(), "ff_planar16bit_true.txt", "ff_rgb16bit_littleendian.viff" ), true);
  TEST("32-bit grey little endian", CheckFile(CompareGrey<vxl_uint_32>(), "ff_grey32bit_true.txt", "ff_grey32bit_littleendian.viff" ), true);
  TEST("32-bit float grey little endian", CheckFile(CompareGreyFloat<float>(), "ff_grey_float_true.txt", "ff_grey_float_littleendian.viff" ), true);
  TEST("64-bit float grey little endian", CheckFile(CompareGreyFloat<double>(), "ff_grey_float_true.txt", "ff_grey_double_littleendian.viff" ), true);

  vcl_cout << "SGI IRIS [iris]\n";
  TEST("8-bit grey rle", CheckFile(CompareGrey<vxl_byte>(), "ff_grey8bit_true.txt", "ff_grey8bit.iris" ), true);
  TEST("16-bit grey verbatim", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit.iris" ), true);
  TEST("8-bit RGB rle", CheckFile(ComparePlanes<vxl_byte,3>(), "ff_planar8bit_true.txt", "ff_rgb8bit.iris" ), true);

  vcl_cout << "MIT [mit]\n";
  TEST("8-bit grey", CheckFile(CompareGrey<vxl_byte>(), "ff_grey8bit_true.txt", "ff_grey8bit.mit" ), true);
  TEST("16-bit grey", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit.mit" ), true);
  TEST("8-bit RGB", CheckFile(CompareRGB<vxl_byte>(), "ff_rgb8bit_true.txt", "ff_rgb8bit.mit" ), true);

#if HAS_DCMTK
  vcl_cout << "DICOM [dcm]\n";
  TEST("16-bit greyscale uncompressed", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true_for_dicom.txt", "ff_grey16bit_uncompressed.dcm"), true);
  // These only pass if the DCMTK-based DICOM loader is available
  TEST("16-bit greyscale uncompressed 2", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_uncompressed2.dcm" ), true);
  TEST("8-bit greyscale uncompressed", CheckFile(CompareGrey<vxl_uint_8>(), "ff_grey8bit_true.txt", "ff_grey8bit_uncompressed.dcm" ), true);
  TEST("8-bit greyscale uncompressed 2", CheckFile(CompareGrey<vxl_uint_8>(), "ff_grey8bit_true.txt", "ff_grey8bit_uncompressed2.dcm" ), true);
  TEST("16-bit greyscale uncompressed 3", CheckFile(CompareGrey<vxl_uint_16>(), "ff_grey16bit_true.txt", "ff_grey16bit_uncompressed3.dcm" ), true);
  TEST("12-bit greyscale float uncompressed", CheckFile(CompareGreyFloat<float>(), "ff_grey_float_true_for_dicom.txt", "ff_grey_float_12bit_uncompressed.dcm" ), true);
#endif // HAS_DCMTK
}

TESTMAIN_ARGS(test_file_format_read);
