#ifndef vipl_accessors_vnl_matrix_h_
#define vipl_accessors_vnl_matrix_h_
#include <vnl/vnl_matrix.h>

#define FILTER_IMPTR_DEC_REFCOUNT(v) {delete (v); (v)=0;}
#define FILTER_IMPTR_INC_REFCOUNT(v)
#define FILTER_KERNPTR_DEC_REFCOUNT(v)

template <class DataType> DataType fgetpixel(vnl_matrix<DataType> const& i, int x, int y, DataType);
template <class DataType> void fsetpixel(vnl_matrix<DataType>& i, int x, int y, DataType e);
template <class DataType> DataType getpixel(vnl_matrix<DataType> const& i, int x, int y, DataType);
template <class DataType> void setpixel(vnl_matrix<DataType>& i, int x, int y, DataType e);
#define VIPL_DECLARE_ACCESSORS(T) \
T fgetpixel(vnl_matrix<T> const& i, int x, int y, T); \
void fsetpixel(vnl_matrix<T>& i, int x, int y, T e); \
T getpixel(vnl_matrix<T> const& i, int x, int y, T); \
void setpixel(vnl_matrix<T>& i, int x, int y, T e)

#ifdef INSTANTIATE_TEMPLATES
#include "vipl_accessors_vnl_matrix.txx"
#endif

#endif // vipl_accessors_vnl_matrix_h_
