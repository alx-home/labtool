// This is mul/vimt3d/vimt3d_vil3d_v3i.h
#ifndef vimt3d_vil3d_v3i_h_
#define vimt3d_vil3d_v3i_h_
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma interface
#endif
//:
// \file
// \brief Reader/Writer for v3i format images.
// \author Ian Scott - Manchester
// v3i is a VXL specific format designed to store all the information that
// can be stored in a vimt3d image. We don't recommed its use in general,
// having no wish to add to the plethora of badly designed image formats
// out there. However, a means of being able to save, and reload a full
// vil3d/vimt3d image using the standard vil3d_load_* API is very useful.
// The file format currently is that provided by the default vsl
// serialisation scheme. There is an extra v3i-specific magic number to
// avoid confusion with other vsl data files, and a version number to allow
// for a change in format.
//
// To use the v3i format with vil3d_load, vil3d_save, etc add
// the following code at the start of your program
// \verbatim
//  vil3d_file_format::add_format(new vimt3d_vil3d_v3i_format);  
// \endverbatim


#include <vil3d/vil3d_file_format.h>
#include <vimt3d/vimt3d_image_3d.h>
#include <vcl_iosfwd.h>
#include <vcl_memory.h>

//: Reader/Writer for v3i format images.
//
// To use the v3i format with vil3d_load, vil3d_save, etc add
// the following code at the start of your program
// \verbatim
//  vil3d_file_format::add_format(new vimt3d_vil3d_v3i_format);  
// \endverbatim
class vimt3d_vil3d_v3i_format: public vil3d_file_format
{
 public:
  vimt3d_vil3d_v3i_format() {}
  //: The destructor must be virtual so that the memory chunk is destroyed.
  virtual ~vimt3d_vil3d_v3i_format() {}

  virtual vil3d_image_resource_sptr make_input_image(const char *) const;

  //: Make a "generic_image" on which put_section may be applied.
  // The file may be opened immediately for writing so that a header can be written.
  virtual vil3d_image_resource_sptr make_output_image(const char* filename,
                                                      unsigned ni,
                                                      unsigned nj,
                                                      unsigned nk,
                                                      unsigned nplanes,
                                                      enum vil_pixel_format) const;

  //: default filename tag for this image.
  virtual const char * tag() const {return "v3i";}

  //: The magic number to identify a vsl stream as a v3i image.
  // You can create/read a v3i image using vsl by opening the stream,
  // reading/writing magic_number(), then reading/writing a pointer to a vimt_image.
  static unsigned magic_number();
};


// You can't create one of these yourself.
// Use vimt3d_vil3d_v3i_format instead.
//
// To use the v3i format with vil3d_load, vil3d_save, etc add
// the following code at the start of your program
// \verbatim
//  vil3d_file_format::add_format(new vimt3d_vil3d_v3i_format);  
// \endverbatim
class vimt3d_vil3d_v3i_image: public vil3d_image_resource
{
  friend class vimt3d_vil3d_v3i_format;
  //: Pointer to open image file.
  vcl_fstream *file_;
  //: Image cache.
  // Currently the whole image is cached im memory. This should be fixed.
  mutable vimt3d_image_3d *im_;
  //: If true, write image file on exit.
  bool dirty_;

  //: Private constructor, use vil3d_load instead.
  // This object takes ownership of the image.
  vimt3d_vil3d_v3i_image(vcl_auto_ptr<vcl_fstream> im);
  //: Private constructor, use vil3d_save instead.
  // This object takes ownership of the file, for writing.
  vimt3d_vil3d_v3i_image(vcl_auto_ptr<vcl_fstream> file, unsigned ni, unsigned nj,
                         unsigned nk, unsigned nplanes, vil_pixel_format format);

  //: Storage type for header information when the whole image has not yet been loaded.
  struct header_t
  {
    unsigned ni, nj, nk, nplanes;
    vimt3d_transform_3d w2i;
    header_t(): ni(0), nj(0), nk(0), nplanes(0) {}
    //: Expected pixel type.
    enum vil_pixel_format pixel_format;
    bool operator ==(const header_t& rhs) const;
  };

  //: Storage for header information when the whole image has not yet been loaded.
  mutable header_t header_;

  //: Skip the reading of a vil_memory_chunk
  // Return false if failed, and is error flag on stream if unrecoverable.
  bool skip_b_read_vil_memory_chunk(vsl_b_istream& is, unsigned sizeof_T) const;

  //: Load full image on demand.
  void load_full_image() const;

 public:
  virtual ~vimt3d_vil3d_v3i_image();

  //: Dimensions:  nplanes x ni x nj x nk.
  // This concept is treated as a synonym to components.
  virtual unsigned nplanes() const;
  //: Dimensions:  nplanes x ni x nj x nk.
  // The number of pixels in each row.
  virtual unsigned ni() const;
  //: Dimensions:  nplanes x ni x nj x nk.
  // The number of pixels in each column.
  virtual unsigned nj() const;
  //: Dimensions:  nplanes x ni x nj x nk.
  // The number of slices per image.
  virtual unsigned nk() const;

  //: Pixel Format.
  virtual enum vil_pixel_format pixel_format() const;

  //: Set the size of the each pixel in the i,j,k directions.
  // Return false if underlying image doesn't store pixel sizes.
  virtual bool set_voxel_size(float i, float j, float k);

  //: Get full world to image transform
  const vimt3d_transform_3d & world2im() const;

  //: Set full world to image transform
  // Call this before using put_view();
  void set_world2im(const vimt3d_transform_3d & tr);

  //: Create a read/write view of a copy of this data.
  // This function will always return a
  // multi-plane scalar-pixel view of the data.
  // \return 0 if unable to get view of correct size, or if resource is write-only.
  virtual vil3d_image_view_base_sptr get_copy_view(unsigned i0, unsigned ni,
                                                   unsigned j0, unsigned nj,
                                                   unsigned k0, unsigned nk) const;

  //: Create a read/write view of a copy of this data.
  // This function will always return a
  // multi-plane scalar-pixel view of the data.
  // \return 0 if unable to get view of correct size, or if resource is write-only.
  virtual vil3d_image_view_base_sptr get_view(unsigned i0, unsigned ni,
                                              unsigned j0, unsigned nj,
                                              unsigned k0, unsigned nk) const;

  //: Put the data in this view back into the image source.
  // The view must be of scalar components. Assign your
  // view to a scalar-component view if this is not the case.
  // \return false if failed, because e.g. resource is read-only,
  // format of view is not correct (if it is a compound pixel type, try
  // assigning it to a multi-plane scalar pixel view.)
  virtual bool put_view(const vil3d_image_view_base& im,
                        unsigned i0, unsigned j0, unsigned k0);

  //: Return a string describing the file format.
  // Only file images have a format, others return 0
  virtual char const* file_format() const { return "v3i"; }

  //: Extra property information
  // This will just return the property of the first slice in the list.
  virtual bool get_property(char const* label, void* property_value = 0) const;
};

#endif
