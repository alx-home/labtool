// stub file for IUE class IUE_UTM_geodetic_transform
// generated by the IUE LateX macros from file
// UTM_geodetic_transform.tex

// Copyright (c) 1993 - 1997 Amerinex Applied Imaging, Inc.
// 409 Main St Amherst, MA 01002 All Rights Reserved
// Reproduction rights limited as described in the COPYRIGHT file.

// A @class{IUE_UTM_geodetic_transform} is one that relates UTM coordinates to a geodetic lat_long coordinate_system (phi, lambda, h) using a reference spheroid to define the shape of the earth (or other celestial object). where in the geodetic lat_long coordinate system, coordinates phi and lambda are the values of latitude and longitude, respectively.
#include "bgeo_utm.h"
#include <vcl_iostream.h>
#include <vcl_limits.h>
#include <vnl/vnl_math.h>
#define DBLLONG 4.61168601e18
#define EPSLN   1.0e-10
#define D2R     1.745329251994328e-2
#define MAX_VAL  4

// *****************************************************************************
// NAME UNIVERSAL TRANSVERSE MERCATOR - GEODETIC
//
// PURPOSE: Transforms UTM (x, y, z) to geodetic (phi, lambda, h).
//                 x,y,z values must be in meters, and (phi, lambda, h) will
//         be returned in radians.
//
// NOTE: UTM coordinate system has both zone and central_meridian slots.
//                 If zone is defined (i.e. zone <> 0), then zone is used.
//         Otherwise, central_meridian is used.
//
//         When dealing with Northern Hemisphere, is_southern_hemisphere
//         slot must be 0, and phi must be positive or equal to 0.
//         When dealing with Southern Hemisphere, is_southern_hemisphere
//         slot must be 1, and phi must be negative or equal to 0.
//
// ALGORITHM REFERENCES
//
// 1. Snyder, John P., "Map Projections--A Working Manual", U.S. Geological
//     Survey Professional Paper 1395 (Supersedes USGS Bulletin 1532), United
//     State Government Printing Office, Washington D.C., 1987.
//
// 2. Snyder, John P. and Voxland, Philip M., "An Album of Map Projections",
//     U.S. Geological Survey Professional Paper 1453 , United State Government
//     Printing Office, Washington D.C., 1989.
//
// 3. Code adapted from "USGS General Cartographic Transformation Package -
//       C code (GCTPC).
// *****************************************************************************
static double scale_factor2;
static double es2, esp2;
static double ml02;
static double false_easting2;
static double false_northing2 ;
static int ind2;
static double e02,e12,e22,e32;

// Function to return the sign of an argument
// ------------------------------------------
static inline int sign(double x) { return (x < 0.0) ? -1 : 1;}

static inline double sqr(double x) { return x*x; }
// Function to adjust a longitude angle to range from -180 to 180 radians
// added if statements
// ----------------------------------------------------------------------
static double adjust_lon2(double x) // Angle in radians
{
  for (long count = 0; count <= MAX_VAL; ++count)
  {
    if (vnl_math_abs(x)<=vnl_math::pi)
      break;
    else if (long(vnl_math_abs(x / (vnl_math::pi))) < 2)
      x -= (sign(x) * 2*vnl_math::pi);
    else if (long(vnl_math_abs(x / (2*vnl_math::pi))) < vcl_numeric_limits<long>::max())
      x -= long((x /(2*vnl_math::pi))*2*vnl_math::pi);
    else if (((long) vnl_math_abs(x / (vcl_numeric_limits<long>::max() * 2*vnl_math::pi))) < vcl_numeric_limits<long>::max())
      x -= (((long)(x / (vcl_numeric_limits<long>::max() * 2*vnl_math::pi))) * (2*vnl_math::pi * vcl_numeric_limits<long>::max()));
    else if (((long) vnl_math_abs(x / (DBLLONG * 2*vnl_math::pi))) < vcl_numeric_limits<long>::max())
      x -= (((long)(x / (DBLLONG * 2*vnl_math::pi))) * (2*vnl_math::pi * DBLLONG));
    else
      x -= (sign(x) *2*vnl_math::pi);
  }

  return x;
}

static double adjust_lat2(double x) // Angle in radians
{
  for (long count = 0; count <= MAX_VAL; ++count)
  {
    if (vnl_math_abs(x)<=vnl_math::pi_over_2)
      break;
    else if (((long) vnl_math_abs(x / vnl_math::pi_over_2)) < 2)
      x -= (sign(x) * vnl_math::pi);
    else if (((long) vnl_math_abs(x / vnl_math::pi)) < vcl_numeric_limits<long>::max())
      x -= (((long)(x / vnl_math::pi))*vnl_math::pi);
    else if (((long) vnl_math_abs(x / (vcl_numeric_limits<long>::max() * vnl_math::pi))) < vcl_numeric_limits<long>::max())
      x -= (((long)(x / (vcl_numeric_limits<long>::max() * vnl_math::pi))) * (vnl_math::pi * vcl_numeric_limits<long>::max()));
    else if (((long) vnl_math_abs(x / (DBLLONG * vnl_math::pi))) < vcl_numeric_limits<long>::max())
      x -= (((long)(x / (DBLLONG * vnl_math::pi))) * (vnl_math::pi * DBLLONG));
    else
      x -= (sign(x) *vnl_math::pi);
  }

  return x;
}

// Function computes the value of M which is the distance along a meridian
// from the Equator to latitude phi.
// ---------------------------------------------
static inline double mlfn2(double e0, double e1, double e2, double e3, double phi)
{
  return e0*phi-e1*vcl_sin(2.0*phi)+e2*vcl_sin(4.0*phi)-e3*vcl_sin(6.0*phi);
}

// Initialization function of UTM transform
// ----------------------------------------
static void UTM_init2(double lat_center2, double r_major, double e, int south_flag)
{
  scale_factor2 = 0.9996;

  es2 = (double) e * (double) e;
  e02 = 1.0-0.25*es2*(1.0+es2/16.0*(3.0+1.25*es2));
  e12 = 0.375*es2*(1.0+0.25*es2*(1.0+0.46875*es2));
  e22 = 0.05859375*es2*es2*(1.0+0.75*es2);
  e32 = es2*es2*es2*(35.0/3072.0);
  esp2 = es2/(1.0 - es2);
  ml02 = r_major * mlfn2(e02, e12, e22, e32, lat_center2);
  false_easting2 = 500000.0;

  false_northing2 = (south_flag) ? 10000000.0 : 0.0;

  if (es2 < .00001)
    ind2 = 1;
  else
    ind2 = 0;
}

// Constructors

// other constructors (from doc)

// Construct a transform with the given coordinate systems.

bgeo_utm::bgeo_utm()
  :   a_(6378137), b_(6356752.3142) //WGS-84 by default
{}

bgeo_utm::bgeo_utm(const bgeo_utm& t)
  :    a_(t.a_), b_(t.b_)
{}

bgeo_utm::~bgeo_utm()
{}

// Applies the transform to the instance of 3d point representing a location in the from_coordinate_system (UTM_coordinate_system) and creates a point represented the transformed location in the to_coordinate_system(geodetic_coordinate_system).
void bgeo_utm::transform(int utm_zone, double x, double y, double z,
               double& lat, double& lon , double& elev,
               bool south_flag,
               double utm_central_meridian)
{
  //double D2R = vnl_math::pi/180.0;
  double e = vcl_sqrt((sqr(a_) - sqr(b_))/sqr(a_));

  if (utm_zone != 0)
    utm_central_meridian = (6 * utm_zone) - 183;

  double lon_center2 = adjust_lon2(utm_central_meridian * D2R);
  double lat_center2 = 0.0;

  double lambda, phi;

  UTM_init2(lat_center2, a_, e, south_flag);

  double con,temp_phi;    // temporary angles
  double delta_phi;    // difference between longitudes
  long i;    // counter variable
  double sin_phi, cos_phi, tan_phi;    // sin cos and tangent values
  double c, cs, t, ts, n, r, d, ds;    // temporary variables
  double f, h, g, temp;    // temporary variables
  long max_iter = 6;    // maximum number of iterations, I changed from 6 to 20

  if (ind2 != 0)
  {
    f = vcl_exp(x/(a_ * scale_factor2));
    g = .5 * (f - 1/f);
    temp = lat_center2 + y/(a_ * scale_factor2);
    h = vcl_cos(temp);
    con = vcl_sqrt((1.0 - h * h)/(1.0 + g * g));
    if (vnl_math_abs(con) > 1.0)
    {
      if (con > 1.0)
        phi = vcl_asin(1.0);
      else
        phi = vcl_asin(-1.0);
    }
    else
      phi = vcl_asin(con);

    if (temp < 0)
      phi = -phi;
    if ((g == 0) && (h == 0))
    {
      lambda = lon_center2;
    }
    else
    {
      lambda = adjust_lon2(vcl_atan2(g,h) + lon_center2);
    }
  }
  else
  {
    x -= false_easting2;
    y -= false_northing2;

    con = (ml02 + y / scale_factor2) / a_;
    temp_phi = con;
    for (i=0;;i++)
    {
      delta_phi =
        ((con + e12 * vcl_sin(2.0*temp_phi) - e22 * vcl_sin(4.0*temp_phi) + e32 *
          vcl_sin(6.0*temp_phi)) / e02) - temp_phi;
#if 0
      delta_phi = ((con + e12 * vcl_sin(2.0*phi) - e22 * vcl_sin(4.0*phi)) / e02) - phi;
#endif
      temp_phi += delta_phi;

      if (vnl_math_abs(delta_phi)<1E-6) break;

      if (i >= max_iter)
        vcl_cout << "Transform failed to converge" << vcl_endl;
    }

    if (vnl_math_abs(temp_phi) < vnl_math::pi_over_2)
    {
      sin_phi = vcl_sin(temp_phi);
      cos_phi = vcl_cos(temp_phi);
      tan_phi = vcl_tan(temp_phi);
      c = esp2 * sqr(cos_phi);
      cs = sqr(c);
      t = sqr(tan_phi);
      ts = sqr(t);
      con = 1.0 - es2 * sqr(sin_phi);
      n = a_ / vcl_sqrt(con);
      r = n * (1.0 - es2) / con;
      d = x / (n * scale_factor2);
      ds = sqr(d);
      phi =
        temp_phi - (n * tan_phi * ds / r) *
        (0.5 - ds / 24.0 * (5.0 + 3.0 * t + 10.0 * c - 4.0 * cs - 9.0 *
                esp2 - ds / 30.0 * (61.0 + 90.0 * t + 298.0 *
                            c + 45.0 * ts - 252.0 *
                            esp2 - 3.0 * cs)));
      lambda =
        adjust_lon2(lon_center2 +
            (d * (1.0 - ds / 6.0 * (1.0 + 2.0 * t + c - ds / 20.0
                        * (5.0 - 2.0 * c + 28.0 * t -
                           3.0 * cs + 8.0 * esp2 +
                           24.0 * ts))) / cos_phi));
    }
    else
    {
      phi = vnl_math::pi_over_2 * sign(y);
      lambda = lon_center2;
    }
  }

  lat = phi/D2R; lon = lambda/D2R, elev = z;
}

void bgeo_utm::transform(int utm_zone, double x, double y,
                                double& lat, double& lon,
                                bool south_flag,
                                double utm_central_meridian)
{
  double elev;
  this->transform(utm_zone, x, y, 0.0,
                  lat, lon, elev,
                  south_flag, utm_central_meridian);
  if (elev) { /* TODO */ }
}

void bgeo_utm::transform(double lat, double lon,
                                double& x, double& y, int& utm_zone)
{
  // double D2R = vnl_math::pi/180.0;
  utm_zone = int((lon+180)/6.0) + 1;
  double e = vcl_sqrt(1.0 - b_*b_/(a_*a_));
  // This value must eventually set by user. lon_zone stands for
  // longitudinal zone, and it must be between 1 and 60.
  int south_flag;
  double utm_central_meridian = 0;

  utm_central_meridian = (6 * utm_zone) - 183;

  south_flag = lat<0;

  double lon_center = adjust_lon2(utm_central_meridian * D2R);
  double lat_center = 0.0;

  double phi = adjust_lat2(lat*D2R);
  double lambda = adjust_lon2(lon*D2R);

  UTM_init2(lat_center, a_, e, south_flag);

  //  double bl = -1000000.0;

  double delta_lon = adjust_lon2(lambda - lon_center);

  double sin_phi = vcl_sin(phi);
  double cos_phi = vcl_cos(phi);

  double al = cos_phi * delta_lon;
  double als = sqr(al);
  double c = esp2 * sqr(cos_phi);
  double tq = vcl_tan(phi);
  double t = sqr(tq);
  double con = 1.0 - es2 * sqr(sin_phi);
  double n = a_ / vcl_sqrt(con);
  double ml = a_ * mlfn2(e02, e12, e22, e32, phi);

  x = scale_factor2 * n * al * (1.0 + (als / 6.0) *
                (1.0 - t + c + (als / 20.0) *
                 (5.0 - (18.0 * t) + sqr(t) + (72.0 * c) - (58.0 * esp2)))) + false_easting2;

  y = scale_factor2 * (ml - ml02 + n * tq * (als * (0.5 + (als / 24.0) *
                            (5.0 - t + (9.0 * c)
                             + (4.0 * sqr(c))
                             + (als / 30.0) *
                             (61.0 - (58.0 * t) +
                              sqr(t) +
                              (600.0 * c) -
                              330.0 * esp2))))) +
    false_northing2;
}