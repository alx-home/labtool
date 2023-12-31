#ifndef vipl_accessors_vbl_array_2d_h_
#define vipl_accessors_vbl_array_2d_h_
#include <vbl/vbl_array_2d.h>

#define FILTER_IMPTR_DEC_REFCOUNT(v) {delete (v); (v)=0;}
#define FILTER_IMPTR_INC_REFCOUNT(v)
#define FILTER_KERNPTR_DEC_REFCOUNT(v)

template <class DataType> DataType fgetpixel(vbl_array_2d<DataType> const& i, int x, int y, DataType);
template <class DataType> void fsetpixel(vbl_array_2d<DataType>& i, int x, int y, DataType e);
template <class DataType> DataType getpixel(vbl_array_2d<DataType> const& i, int x, int y, DataType);
template <class DataType> void setpixel(vbl_array_2d<DataType>& i, int x, int y, DataType e);
#define VIPL_DECLARE_ACCESSORS(T) \
T fgetpixel(vbl_array_2d<T> const& i, int x, int y, T); \
void fsetpixel(vbl_array_2d<T>& i, int x, int y, T e); \
T getpixel(vbl_array_2d<T> const& i, int x, int y, T); \
void setpixel(vbl_array_2d<T>& i, int x, int y, T e)

#ifdef INSTANTIATE_TEMPLATES
#include "vipl_accessors_vbl_array_2d.txx"
#endif

#endif // vipl_accessors_vbl_array_2d_h_
