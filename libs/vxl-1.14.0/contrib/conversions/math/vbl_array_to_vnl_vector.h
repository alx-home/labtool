#ifndef vbl_array_to_vnl_vector_h_
#define vbl_array_to_vnl_vector_h_

#include <vcl_limits.h>
#include <vcl_cassert.h>
#include <vnl/vnl_vector.h>
#include <vbl/vbl_array_1d.h>

template <class T>
inline vnl_vector<T> vbl_array_to_vnl_vector(vbl_array_1d<T> a)
{
  assert(a.end() < a.begin() + vcl_numeric_limits<typename vnl_vector<T>::size_type>::max());
  return vnl_vector<T>(a.begin(), static_cast<typename vnl_vector<T>::size_type>(a.end()-a.begin()));
}

#endif // vbl_array_to_vnl_vector_h_
