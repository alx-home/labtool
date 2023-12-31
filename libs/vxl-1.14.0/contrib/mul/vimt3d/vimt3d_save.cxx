// This is mul/vimt3d/vimt3d_save.cxx
#include "vimt3d_save.h"
//:
// \file
// \author Ian Scott

#include <mbl/mbl_log.h>
#include <vil3d/vil3d_image_resource.h>
#include <vil3d/vil3d_new.h>
#include <vil3d/vil3d_save.h>
#include <vimt3d/vimt3d_transform_3d.h>
#include <vimt3d/vimt3d_image_3d.h>
#include <vimt3d/vimt3d_vil3d_v3i.h>


static mbl_logger& logger()
{
  static mbl_logger l("contrib.mul.vimt3d.save");
  return l;
}

//: Create a transform from the properties of image resource.
// The transform will be from world co-ordinates in metres to image co-ordinates (or mm if requested).
void vimt3d_save_transform(vil3d_image_resource_sptr &ir,
                           const vimt3d_transform_3d& trans, 
                           bool use_millimetres /*=false*/)
{
  if (dynamic_cast<vimt3d_vil3d_v3i_image *>(ir.ptr()))
  {
    vgl_vector_3d<double> vox_per_mm = trans.delta(vgl_point_3d<double>(0,0,0), 
                                                   vgl_vector_3d<double>(1.0, 1.0, 1.0));

    // get the translation component
    double tx =  trans.matrix()(0,3);
    double ty =  trans.matrix()(1,3);
    double tz =  trans.matrix()(2,3);

    vimt3d_transform_3d tr;
    //const double units_scaling = use_millimetres ? 1000.0 : 1.0;
    tr.set_zoom_only (1000.0*vox_per_mm.x(),
                      1000.0*vox_per_mm.y(),
                      1000.0*vox_per_mm.z(), tx,ty,tz );

    static_cast<vimt3d_vil3d_v3i_image &>(*ir).set_world2im(tr);
  }
  else
  {
    vimt3d_transform_3d i2w=trans.inverse();
    vgl_vector_3d<double> dp = i2w.delta(vgl_point_3d<double> (0,0,0),
                                         vgl_vector_3d<double> (1.0, 1.0, 1.0));
    if (!ir->set_voxel_size(float(dp.x()),float(dp.y()),float(dp.z())))
      MBL_LOG(WARN, logger(), "vimt3d_save_transform(): Unable to include voxel sizes:"
              <<dp.x()<<','<<dp.y()<<','<<dp.z() );
  }
}


bool vimt3d_save(const vcl_string& path,
                 const vimt3d_image_3d& image,
                 bool use_millimetres /*=false*/)
{
  const vimt3d_image_3d & iv = image;
  const vil3d_image_view_base & ib = iv.image_base();

  vil3d_image_resource_sptr ir = vil3d_new_image_resource(
    path.c_str(), ib.ni(), ib.nj(), ib.nk(), ib.nplanes(), ib.pixel_format(),
    vil3d_save_guess_file_format(path.c_str()));

  if (!ir)
    return false;

  ir->put_view(ib);

  vimt3d_save_transform(ir, image.world2im(), use_millimetres);
  return true;
}
