// This is core/vil/vil_pyramid_image_resource.cxx
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma implementation
#endif
#include "vil_pyramid_image_resource.h"
//:
// \file
#include <vcl_cassert.h>
#include <vcl_cstring.h>
#include <vcl_vector.h>
#include <vil/vil_property.h>
#include <vil/vil_convert.h>
#include <vil/vil_blocked_image_resource.h>
#include <vil/vil_blocked_image_facade.h>
#include <vil/vil_image_view.h>
#include <vil/vil_new.h>
#include <vil/vil_load.h>


vil_pyramid_image_resource::vil_pyramid_image_resource()
{}

vil_pyramid_image_resource::~vil_pyramid_image_resource()
{}

bool vil_pyramid_image_resource::get_property(char const* tag, void* /*value*/) const
{
  return vcl_strcmp(vil_property_pyramid, tag)==0;
}


//: return a decimated block.  The input is a 2x2 2d array of blocks.
//  Assume all the data is valid
static vil_image_view<float>
decimate_block(vcl_vector<vcl_vector<vil_image_view<float> > > const& blocks)
{
  vil_image_view<float> blk = blocks[0][0];
  unsigned sbi = blk.ni(), sbj = blk.nj();
  vil_image_view<float> dec_block;
  dec_block.set_size(sbi, sbj);
  for (unsigned dj = 0; dj<sbj; ++dj)
  {
    unsigned r = 0, j0 = 2*dj;
    if (2*dj>=sbj)
    {
      r = 1;
      j0 = 2*dj-sbj;
    }
    for (unsigned di = 0; di<sbi; ++di)
    {
      unsigned c = 0, i0 = 2*di;
      if (2*di>=sbi)
      {
        c = 1;
        i0 = 2*di-sbi;
      }
      vil_image_view<float> blk = blocks[r][c];
      float v =
        0.25f*(blk(i0, j0)+blk(i0+1,j0)+blk(i0,j0+1)+blk(i0+1,j0+1));
      dec_block(di, dj) = v;
    }
  }
  return dec_block;
}

static
bool convert_multi_plane_to_float(vil_image_view_base_sptr& blk,
                                  vcl_vector<vil_image_view<float> >& fblk)
{
  if (!blk) return false;
  fblk.clear();
  vil_pixel_format fmt = blk->pixel_format();
  unsigned ni = blk->ni(), nj = blk->nj();
  unsigned np = blk->nplanes();
  if (fmt == VIL_PIXEL_FORMAT_BYTE)
  {
    vil_image_view<unsigned char> bv = blk;
    for (unsigned p = 0; p<np; ++p){
      vil_image_view<float> bvf(ni, nj);
      for (unsigned j = 0; j<nj; ++j)
        for (unsigned i= 0; i<ni; ++i)
          bvf(i,j) = bv(i,j,p);
      fblk.push_back(bvf);
    }
    return true;
  }
  else if (fmt == VIL_PIXEL_FORMAT_UINT_16)
  {
    vil_image_view<unsigned short> bv = blk;
    for (unsigned p = 0; p<np; ++p){
      vil_image_view<float> bvf(ni, nj);
      for (unsigned j = 0; j<nj; ++j)
        for (unsigned i= 0; i<ni; ++i)
          bvf(i,j) = bv(i,j,p);
      fblk.push_back(bvf);
    }
    return true;
  }
  return false;
}

static
void convert_multi_plane_from_float(vcl_vector<vil_image_view<float> >& fblk,
                                    vil_image_view<unsigned char>& blk)
{
  unsigned ni = fblk[0].ni(), nj = fblk[0].nj();
  unsigned np = fblk.size();
  for (unsigned p = 0; p<np; ++p)
    for (unsigned j = 0; j<nj; ++j)
      for (unsigned i= 0; i<ni; ++i)
        blk(i,j,p) = static_cast<unsigned char>(fblk[p](i,j));
}

static
void convert_multi_plane_from_float(vcl_vector<vil_image_view<float> >& fblk,
                                    vil_image_view<unsigned short>& blk)
{
  unsigned ni = fblk[0].ni(), nj = fblk[0].nj();
  unsigned np = fblk.size();
  for (unsigned p = 0; p<np; ++p)
    for (unsigned j = 0; j<nj; ++j)
      for (unsigned i= 0; i<ni; ++i)
        blk(i,j,p) = static_cast<unsigned short>(fblk[p](i,j));
}

bool vil_pyramid_image_resource::
blocked_decimate(vil_blocked_image_resource_sptr const& brsc,
                 vil_blocked_image_resource_sptr &  dec_resc)
{
  if (!brsc)
    return false;
  unsigned nbi = brsc->n_block_i(), nbj = brsc->n_block_j();
  if (nbi==0||nbj==0)
    return false;
  unsigned np = brsc->nplanes();

  //check for consistent block structure
  unsigned sbi_src = brsc->size_block_i(), sbj_src = brsc->size_block_j();
  unsigned sbi_dec = dec_resc->size_block_i(),
    sbj_dec = dec_resc->size_block_j();
  if (sbi_src!=sbi_dec||sbj_src!=sbj_dec)
    return false;
  vil_pixel_format fmt = brsc->pixel_format();

  //Set up the block buffer, a 2xnbi set of blocks needed to support 2x2
  //pixel decimation.  The buffer is updated as the next two rows of blocks is
  //scanned in from the resource.
  //
  //|b00 |b01|b02|b03|...|b0,nbi-1|
  //|b10 |b11|b12|b13|...|b1,nbi-1|
  //
  //=======================================================
  //
  //Decimate the image using a 2x2 block neigborhood
  //
  //   | buf[0][0]  buf[0][1] |==> [dec_blk]
  //   | buf[1][0]  buf[1][1] |
  //
  // This neigborhood "slides" along the 2xnbi block buffer,
  //  stepping two blocks each time.
  //=======================================================
  switch (np)
  {
    case 1: //grey scale images
    {
      vcl_vector<vcl_vector<vil_image_view<float> > > buf(2), nbrhd(2);
      for (unsigned k =0; k<2; ++k)
      {
        buf[k] = vcl_vector<vil_image_view<float> >(nbi);
        nbrhd[k] = vcl_vector<vil_image_view<float> >(2);
      }
      vil_image_view<float> dec_blk;
      for (unsigned bj=0; bj<nbj; bj+=2)
      {
        //update the block buffer by stepping down two block rows
        for (unsigned bi = 0; bi<nbi; ++bi)
        {
          buf[0][bi] = vil_convert_cast(float(),brsc->get_block(bi,bj));
          //if (bj+2<=nbj)//make sure there are enough block rows
          if (bj+1<nbj)//make sure there are enough block rows
            buf[1][bi] = vil_convert_cast(float(),brsc->get_block(bi,bj+1));
          else
            buf[1][bi]=buf[0][bi];//otherwise just copy the upper block
        }
        for (unsigned bi=0; bi<nbi; bi+=2)
        {
          //construct the 2x2 block neighborhood
          for (unsigned r = 0; r<2; ++r)
            for (unsigned c = 0; c<2; ++c)
            {
              unsigned ki = bi+c;
              if (ki>=nbi)//make sure there are enough blocks in the row
                ki = nbi-1;
              nbrhd[r][c] = buf[r][ki];//otherwise just copy
            }
          //construct the block
          dec_blk = decimate_block(nbrhd);
          //convert back to the orignal pixel format
          switch (fmt)
          {
#define CONVERT_BLOCK_CASE(FORMAT, T) \
           case FORMAT: { \
            vil_image_view<T> out_blk; \
            vil_convert_cast(dec_blk, out_blk); \
            if (!dec_resc->put_block(bi/2, bj/2, out_blk )) \
              return false;\
            break;\
           }
            CONVERT_BLOCK_CASE(VIL_PIXEL_FORMAT_BYTE, vxl_byte);
#if VXL_HAS_INT_64
            CONVERT_BLOCK_CASE(VIL_PIXEL_FORMAT_UINT_64, vxl_uint_64);
#endif
            CONVERT_BLOCK_CASE(VIL_PIXEL_FORMAT_UINT_32, vxl_uint_32);
            CONVERT_BLOCK_CASE(VIL_PIXEL_FORMAT_UINT_16, vxl_uint_16);
            CONVERT_BLOCK_CASE(VIL_PIXEL_FORMAT_FLOAT, float);
            CONVERT_BLOCK_CASE(VIL_PIXEL_FORMAT_DOUBLE, double);
#undef CONVERT_BLOCK_CASE

           default:
            assert(!"Unknown vil data type in pyramid image construction");
            return false;
          };
        }
      }
      return true;
    }// end of nplanes = 1 (grey scale)
    case 3:
    case 4:
    {
      vcl_vector<vcl_vector<vcl_vector<vil_image_view<float> > > > buf(2);
      vcl_vector<vcl_vector<vil_image_view<float> > > nbrhd(2);
      for (unsigned k =0; k<2; ++k)
      {
        buf[k] = vcl_vector<vcl_vector<vil_image_view<float> > >(nbi);
        nbrhd[k] = vcl_vector<vil_image_view<float> >(2);
      }

      // The color planes of a block are separated into
      // individual float views
      for (unsigned bj=0; bj<nbj; bj+=2)
      {
        //update the block buffer by stepping down two block rows
        for (unsigned bi = 0; bi<nbi; ++bi)
        {
          vil_image_view_base_sptr bij = brsc->get_block(bi,bj);
          vcl_vector<vil_image_view<float> > fbij;
          //convert to float
          if (!convert_multi_plane_to_float(bij, fbij)) return false;
          buf[0][bi]=fbij;
          if (bj+2<=nbj)//make sure there are enough block rows
          {
            bij = brsc->get_block(bi,bj+1);
            //convert to float
            if (!convert_multi_plane_to_float(bij, fbij)) return false;
            buf[1][bi] = fbij;
          }
          else
            buf[1][bi]=buf[0][bi];//otherwise just copy the upper block
        }
        for (unsigned bi=0; bi<nbi; bi+=2)
        {
          vcl_vector<vil_image_view<float> >dec_fblk(np);
          //create decimated blocks for each plane
          for (unsigned p = 0; p<np; ++p){
            for (unsigned r = 0; r<2; ++r)
              for (unsigned c = 0; c<2; ++c)
              {
                unsigned ki = bi+c;
                if (ki>=nbi)
                  ki = nbi-1;
                nbrhd[r][c] = buf[r][ki][p];
              }
            //construct the block
            vil_image_view<float> fplane = decimate_block(nbrhd);
            dec_fblk[p]=fplane;
          }
          //convert back to original format only allow 8 bit and 16 bit
          //color image formats
          if (fmt == VIL_PIXEL_FORMAT_BYTE){
            vil_image_view<unsigned char> dblk(sbi_src, sbj_src, np);
            convert_multi_plane_from_float(dec_fblk, dblk);
            dec_resc->put_block(bi/2, bj/2, dblk);
          }
          else if (fmt == VIL_PIXEL_FORMAT_UINT_16){
            vil_image_view<unsigned short> dblk(sbi_src, sbj_src, np);
            convert_multi_plane_from_float(dec_fblk, dblk);
            dec_resc->put_block(bi/2, bj/2, dblk);
          }
          else return false;
        }
      }
      return true;
    }// end of nplanes = 3, 4
   default:
    return false;
  }
}

vil_image_resource_sptr vil_pyramid_image_resource::
decimate(vil_image_resource_sptr const& resc, char const* filename,
         char const* format)
{
  if (!resc)
    return 0;
  vil_pixel_format fmt = resc->pixel_format();
  switch (fmt)
  {
    case VIL_PIXEL_FORMAT_BYTE:
      break;
    case VIL_PIXEL_FORMAT_UINT_16:
      break;
    case VIL_PIXEL_FORMAT_UINT_32:
      break;
#if VXL_HAS_INT_64
    case VIL_PIXEL_FORMAT_UINT_64:
      break;
#endif
    case VIL_PIXEL_FORMAT_FLOAT:
      break;
    case VIL_PIXEL_FORMAT_DOUBLE:
      break;
    default:
      vcl_cout << "unrecognized pixel format in"
               << " vil_pyramid_image_resource::decimate()\n";
      return 0;
  }
  //first determine if the resource is blocked, if not create a facade
  vil_blocked_image_resource_sptr brsc = blocked_image_resource(resc);
  if (brsc&&(brsc->size_block_i()%2!=0||brsc->size_block_j()%2!=0))
  {
    vcl_cout << "Blocked pyramid images must have even block sizes\n";
    return 0;
  }
  if (!brsc)
    brsc = new vil_blocked_image_facade(resc);

  // create the output decimated resource
  { //file scope to close resource
    unsigned rni = resc->ni(), rnj = resc->nj();
    unsigned np = resc->nplanes();
    //if source image has even dimensions then just divide by 2
    unsigned dni = rni/2, dnj = rnj/2;
    //else if the dimension is odd, increase the output size by 1.
    dni += rni%2; dnj += rnj%2;
    vil_blocked_image_resource_sptr dec_resc =
      vil_new_blocked_image_resource(filename, dni, dnj, np,
                                     fmt, brsc->size_block_i(),
                                     brsc->size_block_j(),
                                     format);
    //fill the resource with decimated blocks.
    if (!blocked_decimate(brsc, dec_resc))
      return 0;
  } //file scope to close resource
  //reopen resource for reading
  vil_image_resource_sptr temp = vil_load_image_resource(filename);
  return temp;
}
