// This is core/vil1/vil1_pyramid.h
#ifndef vil1_pyramid_h_
#define vil1_pyramid_h_
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma interface
#endif
//:
// \file
// \author fsm

#include <vil1/vil1_image.h>
#include <vcl_vector.h>

//:
// vil1_pyramid is *not* an image. It is like an array of images, with
// the 0th element as the given image and the ith element a subsampled
// version of the (i-1)th element. The subsampled images are computed
// on demand and cached for later use.
struct vil1_pyramid
{
  enum cache_strategy {
    none = 0,
    memory = 1,
    blocked = 2 // not implemented. don't try to use it.
  };

  vil1_pyramid(vil1_image const &, cache_strategy = memory);
  ~vil1_pyramid();

  unsigned size() const { return levels.size(); }
  vil1_image operator[](unsigned i);

 private:
  cache_strategy cs;
  vcl_vector<vil1_image> levels;
};

#endif // vil1_pyramid_h_
