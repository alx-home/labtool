// This is core/vil/vil_memory_chunk.cxx
#include "vil_memory_chunk.h"
//:
// \file
// \brief Ref. counted block of data on the heap
// \author Tim Cootes
#include <vcl_cstring.h>
#include <vcl_cassert.h>

//: Dflt ctor
vil_memory_chunk::vil_memory_chunk()
: data_(0), size_(0), pixel_format_(VIL_PIXEL_FORMAT_UNKNOWN), ref_count_(0)
{
}

//: Allocate n bytes of memory
vil_memory_chunk::vil_memory_chunk(vcl_size_t n, vil_pixel_format pixel_form)
: data_(new char[n]), size_(n), pixel_format_(pixel_form), ref_count_(0)
{
  assert(vil_pixel_format_num_components(pixel_form)==1
    || pixel_form==VIL_PIXEL_FORMAT_UNKNOWN );
}

//: Destructor
vil_memory_chunk::~vil_memory_chunk()
{
  delete [] reinterpret_cast<char*>(data_);
}

//: Copy ctor
vil_memory_chunk::vil_memory_chunk(const vil_memory_chunk& d)
: data_(new char[d.size()]), size_(d.size()), pixel_format_(d.pixel_format_), ref_count_(0)
{
  vcl_memcpy(data_,d.data_,size_);
}

//: Assignment operator
vil_memory_chunk& vil_memory_chunk::operator=(const vil_memory_chunk& d)
{
  if (this==&d) return *this;

  set_size(d.size(),d.pixel_format());
  vcl_memcpy(data_,d.data_,size_);
  return *this;
}

//: Decrement reference count and call destructor when it becomes zero
void vil_memory_chunk::unref()
{
  assert (ref_count_ >0);
  --ref_count_;
  if (ref_count_==0)
  {
    delete [] reinterpret_cast<char*>(data_); data_=0;
    delete this;
  }
}

//: Create empty space for n elements.
//  Leave existing data untouched if the size is already n.
void vil_memory_chunk::set_size(unsigned long n, vil_pixel_format pixel_form)
{
  if (size_==n) return;
  delete [] reinterpret_cast<char*>(data_);
  data_ = 0;
  if (n>0)
    data_ = new char[n];
  size_ = n;
  pixel_format_ = pixel_form;
}


