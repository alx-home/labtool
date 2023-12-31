// This is brl/bseg/bvxm/grid/io/bvxm_io_voxel_grid.h
#ifndef bvxm_io_voxel_grid_h
#define bvxm_io_voxel_grid_h
//:
// \file
// \brief set of io functionalities for bvxm_grid
//
// \author Isabel Restrepo mir@lems.brown.edu
//
// \date  June 18, 2009
//
// \verbatim
//  Modifications
//   Jun 29, 2009  Gamze Tunali
//                 Added a datatype member to bvxm_drishti_header class. It is the datatype
//                 to fill the drishti grid. It is needen specifically for bvxm_opinion
//                 because that type as T cannot be used to fill the resulting grid.
// \endverbatim

#include "../bvxm_voxel_grid.h"
#include "../bvxm_voxel_grid_base.h"
#include "../bvxm_opinion.h"
#include <bsta/bsta_attributes.h>
#include <bsta/bsta_gauss_f1.h>
#include <vcl_limits.h>
#include <vcl_iostream.h>

//: Traits for saving grids of different datatypes to Dristhi .raw file
template <class T>
class bvxm_dristhi_traits;

//: Dristhi datypes for header:
// 0 : unsigned byte - 1 byte per voxel
// 1 : signed byte - 1 byte per voxel
// 2 : unsigned short - 2 bytes per voxel
// 3 : signed short - 2 bytes per voxel
// 4 : integer - 4 bytes per voxel
// 8 : float - 4 bytes per voxel

//: Dristhi traits specializations. Please extent as needed

template <>
class bvxm_dristhi_traits<float>
{
 public:
  static unsigned char dristhi_header() {return 8;}
  typedef float datatype;
};

template<>
class bvxm_dristhi_traits<unsigned char>
{
 public:
  static unsigned char dristhi_header() {return 0;}
  typedef unsigned char datatype;
};

template<>
class bvxm_dristhi_traits<char>
{
 public:
  static unsigned char dristhi_header() {return 1;}
  typedef char datatype;
};
template<>
class bvxm_dristhi_traits<unsigned int>
{
 public:
  static unsigned char dristhi_header() {return 4;}
  typedef unsigned int datatype;
};
//opinion values will be written as float
template<>
class bvxm_dristhi_traits<bvxm_opinion>
{
 public:
  static unsigned char dristhi_header() {return 8;}
  typedef float datatype;
};

template<>
class bvxm_dristhi_traits<bsta_num_obs<bsta_gauss_f1> >
{
 public:
  static unsigned char dristhi_header() {return 8;}
  typedef float datatype;
};


//: Save to dristi raw file
template<class T>
bool bvxm_grid_save_raw(bvxm_voxel_grid<T> *grid,  vcl_string filename)
{
    vcl_fstream ofs(filename.c_str(),vcl_ios::binary | vcl_ios::out);
    if (!ofs.is_open()) {
      vcl_cerr << "error opening file " << filename << " for write!\n";
      return false;
    }

    // write header
    unsigned char data_type = bvxm_dristhi_traits<T>::dristhi_header();

    vxl_uint_32 nx = grid->grid_size().x();
    vxl_uint_32 ny = grid->grid_size().y();
    vxl_uint_32 nz = grid->grid_size().z();

    ofs.write(reinterpret_cast<char*>(&data_type),sizeof(data_type));
    ofs.write(reinterpret_cast<char*>(&nx),sizeof(nx));
    ofs.write(reinterpret_cast<char*>(&ny),sizeof(ny));
    ofs.write(reinterpret_cast<char*>(&nz),sizeof(nz));

    //get the range
    typename bvxm_voxel_grid<T>::iterator grid_it = grid->begin();
    T max = vcl_numeric_limits<T>::min();
    T min = vcl_numeric_limits<T>::max();
    for (unsigned k=0; grid_it != grid->end(); ++grid_it, ++k) {
      for (unsigned i=0; i<(*grid_it).nx(); ++i) {
        for (unsigned j=0; j < (*grid_it).ny(); ++j) {
          if ((*grid_it)(i,j)> max)
            max = (*grid_it)(i,j)-0; // -0 is for bvxm_opinion voxel type
          if ((*grid_it)(i,j)< min)
            min = (*grid_it)(i,j)-0;
        }
      }
    }
    vcl_cout << "max =  " << max << " min= " <<min << vcl_endl;
  
   // write data
   // iterate through slabs and fill in memory array
   typedef typename bvxm_dristhi_traits<T>::datatype DataType;
   grid_it = grid->begin();
   DataType *data_array = new DataType[nx*ny];
    for (unsigned k=0; grid_it != grid->end(); ++grid_it, ++k) {
      vcl_cout << '.' <<vcl_flush;
      for (unsigned i=0; i<(*grid_it).nx(); ++i) {
        for (unsigned j=0; j < (*grid_it).ny(); ++j) {
          data_array[i*ny + j] =(*grid_it)(i,j)-DataType(0);  // +0 is needed for bvxm_opinion, do not delete
        }
      }
      ofs.write(reinterpret_cast<char*>(data_array),sizeof(DataType)*nx*ny);
    }
    vcl_cout << vcl_endl;
    delete [] data_array;
    ofs.close();

    

    return true;
}

template <>
bool bvxm_grid_save_raw<bsta_num_obs<bsta_gauss_f1> >(bvxm_voxel_grid<bsta_num_obs<bsta_gauss_f1> > *grid,  vcl_string filename);

#endif // bvxm_io_voxel_grid_h
