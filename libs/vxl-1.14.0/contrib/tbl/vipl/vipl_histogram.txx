// This is tbl/vipl/vipl_histogram.txx
#ifndef vipl_histogram_txx_
#define vipl_histogram_txx_

#include "vipl_histogram.h"

template <class ImgIn,class ImgOut,class DataIn,class DataOut,class PixelItr>
bool vipl_histogram <ImgIn,ImgOut,DataIn,DataOut,PixelItr> :: section_applyop()
{
  const ImgIn &in = this->in_data(0);
  ImgOut &out = *this->out_data_ptr();
  const int index = indexout();
#if 0
  if (index < 0) index = 0;
#endif
  if (checkrange() == 1)  { // check range is slow, we always keep the divide...
    for (int j = start(this->Y_Axis()), ej = stop(this->Y_Axis()) ; j < ej ; ++j)
      for (int i = start(this->X_Axis(),j), ei = stop(this->X_Axis(),j) ; i < ei ; ++i) {
        long bin = long(0.5 + (shiftin()+getpixel(in,i,j,DataIn(0)))/scalein());
#if 0
        if (bin < 0) bin = 0;
#endif
        // not fsetpixel !!! cannot assume `bin' will lie inside output image section
        DataOut bs = getpixel(out,bin,index,DataOut(0));
        setpixel(out, bin, index, scaleout()+bs);
      }
  }  // else we want speed, skip safety check, check special cases
  else  if (scalein() == 1 && scaleout() == 1 && shiftin() == 0) {
    for (int j = start(this->Y_Axis()), ej = stop(this->Y_Axis()) ; j < ej ; ++j)
      for (int i = start(this->X_Axis(),j), ei = stop(this->X_Axis(),j) ; i < ei ; ++i) {
        long bin = long(0.5 + (getpixel(in,i,j,DataIn(0))));
        DataOut bs = getpixel(out,bin,index,DataOut(0));
        setpixel(out, bin, index, bs+1);
      }
  } else  if (scalein() == 1)  {
    for (int j = start(this->Y_Axis()), ej = stop(this->Y_Axis()) ; j < ej ; ++j)
      for (int i = start(this->X_Axis(),j), ei = stop(this->X_Axis(),j) ; i < ei ; ++i) {
        long bin = long(0.5 + (shiftin()+getpixel(in,i,j,DataIn(0))));
        DataOut bs = getpixel(out,bin,index,DataOut(0));
        setpixel(out, bin, index, scaleout()+bs);
      }
  } else { // all modes
    for (int j = start(this->Y_Axis()), ej = stop(this->Y_Axis()) ; j < ej ; ++j)
      for (int i = start(this->X_Axis(),j), ei = stop(this->X_Axis(),j) ; i < ei ; ++i) {
        long bin = long(0.5 + (shiftin()+getpixel(in,i,j,DataIn(0)))/scalein());
        DataOut bs = getpixel(out,bin,index,DataOut(0));
        setpixel(out, bin, index, scaleout()+bs);
      }
  }
  return true;
}

template <class ImgIn,class ImgOut,class DataIn,class DataOut,class PixelItr>
bool vipl_histogram <ImgIn,ImgOut,DataIn,DataOut,PixelItr> :: section_preop()
{
  const int index = indexout();
  ImgOut &out = *this->out_data_ptr();
  for (int i = start_dst(this->X_Axis()),
    ei = stop_dst(this->X_Axis()); i < ei; ++i)
    setpixel(out, i, index, DataOut(0));
  return true;
}


#endif // vipl_histogram_txx_
