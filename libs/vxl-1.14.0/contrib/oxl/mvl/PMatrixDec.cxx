// This is oxl/mvl/PMatrixDec.cxx
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma implementation
#endif
//:
//  \file

#include "PMatrixDec.h"

#include <vcl_cmath.h>
#include <vcl_iostream.h>

//--------------------------------------------------------------
//: Constructor

PMatrixDec::PMatrixDec(const vnl_matrix<double>& p_matrix)
  : PMatrix(p_matrix), j_matrix_(3,3), d_matrix_(4,4)
{
  if (!((p_matrix.rows() == 3) && (p_matrix.columns() == 4)))
    vcl_cerr << "PMatrixDec WARNING: Incorrect size of matrix\n";
  Init();
}


//--------------------------------------------------------------
//: Destructor

PMatrixDec::~PMatrixDec() {}


//--------------------------------------------------------------
//: Auxiliary Constructor

void PMatrixDec::Init()
{
    double u0 = p_matrix_(0,0)*p_matrix_(2,0)
              + p_matrix_(0,1)*p_matrix_(2,1)
              + p_matrix_(0,2)*p_matrix_(2,2);
    double v0 = p_matrix_(1,0)*p_matrix_(2,0)
              + p_matrix_(1,1)*p_matrix_(2,1)
              + p_matrix_(1,2)*p_matrix_(2,2);

    double a_u = p_matrix_(0,0)*p_matrix_(0,0)
               + p_matrix_(0,1)*p_matrix_(0,1)
               + p_matrix_(0,2)*p_matrix_(0,2);
    double a_v = p_matrix_(1,0)*p_matrix_(1,0)
               + p_matrix_(1,1)*p_matrix_(1,1)
               + p_matrix_(1,2)*p_matrix_(1,2);
    a_u = a_u-u0*u0;
    a_v = a_v-v0*v0;
    if ((a_u <= 0.0) || (a_v <= 0.0))
      vcl_cerr << "PMatrixDec WARNING: Incorrect projection matrix\n";
    else
    {
      a_u = vcl_sqrt(a_u);
      a_v = vcl_sqrt(a_v);

      // INTRINSIC parameters => J
      j_matrix_(0,0) = a_u;
      j_matrix_(0,1) = 0.0;
      j_matrix_(0,2) = u0;

      j_matrix_(1,0) = 0.0;
      j_matrix_(1,1) = a_v;
      j_matrix_(1,2) = v0;

      j_matrix_(2,0) = 0.0;
      j_matrix_(2,1) = 0.0;
      j_matrix_(2,2) = 1.0; // last diagonal element = 1

      // EXTRINSIC parameters => D
      d_matrix_(0,0) = (p_matrix_(0,0) - u0*p_matrix_(2,0))/a_u;
      d_matrix_(0,1) = (p_matrix_(0,1) - u0*p_matrix_(2,1))/a_u;
      d_matrix_(0,2) = (p_matrix_(0,2) - u0*p_matrix_(2,2))/a_u;
      d_matrix_(0,3) = (p_matrix_(0,3) - u0*p_matrix_(2,3))/a_u;

      d_matrix_(1,0) = (p_matrix_(1,0) - v0*p_matrix_(2,0))/a_v;
      d_matrix_(1,1) = (p_matrix_(1,1) - v0*p_matrix_(2,1))/a_v;
      d_matrix_(1,2) = (p_matrix_(1,2) - v0*p_matrix_(2,2))/a_v;
      d_matrix_(1,3) = (p_matrix_(1,3) - v0*p_matrix_(2,3))/a_v;

      d_matrix_(2,0) = p_matrix_(2,0);
      d_matrix_(2,1) = p_matrix_(2,1);
      d_matrix_(2,2) = p_matrix_(2,2);
      d_matrix_(2,3) = p_matrix_(2,3);

      d_matrix_(3,0) = 0.0;
      d_matrix_(3,1) = 0.0;
      d_matrix_(3,2) = 0.0;
      d_matrix_(3,3) = 1.0; // last diagonal element = 1
    }
}


//---------------------------------------------------------------
//: Print to vcl_ostream
vcl_ostream& operator<<(vcl_ostream& s, const PMatrixDec& P)
{
  s << "PROJECTION MATRIX = [\n" << P.get_matrix() << "]\n"
    << "DECOMPOSITION: \n"
    << "Intrinsic Parameters = [\n" << P.j_matrix_ << "]\n"
    << "Extrinsic Parameters = [\n" << P.d_matrix_ << "]\n";
  return s;
}


//---------------------------------------------------------------
//: Test --

void PMatrixDec::Test()
{
  vnl_matrix<double> matrix1(3,4);
  matrix1(0,0)= 568.051; matrix1(1,0)= -83.1082;matrix1(2,0)= -0.274578;
  matrix1(0,1)= 9.18145; matrix1(1,1)= 689.13;  matrix1(2,1)= -0.0458282;
  matrix1(0,2)= 552.506; matrix1(1,2)= 194.806; matrix1(2,2)= 0.960472;
  matrix1(0,3)= -596.353;matrix1(1,3)= 92.4159; matrix1(2,3)= 0.228363;

  vcl_cerr << "Correct Matrix: \n" << matrix1 << vcl_endl;
  PMatrixDec pmat1(matrix1);
  vcl_cerr << pmat1;
  vnl_matrix<double> J(3,4);
  J.update(pmat1.IntrinsicParameters(), 0, 0); // Copy columns 0,1 and 2
  J(0,3) = 0.0; // Last column = 0
  J(1,3) = 0.0;
  J(2,3) = 0.0;
  vcl_cerr << "P = [J O_3]*D = [\n"
           << J * pmat1.ExtrinsicParameters() << "]\n"
           << "AlphaU=" << pmat1.GetAlphaU() << vcl_endl
           << "AlphaV=" << pmat1.GetAlphaV() << vcl_endl
           << "U0=" << pmat1.GetU0() << vcl_endl
           << "V0=" << pmat1.GetV0() << vcl_endl;

  vnl_matrix<double> matrix2(4, 4);
  int i,j;
  for (j=0; j<4; j++)
    for (i=0; i<4; i++)
      matrix2(i,j)= 1.0;

  vcl_cerr << "Another Incorrect Matrix: \n"
           << matrix2 << vcl_endl;
  PMatrixDec pmat2(matrix2);
  vcl_cerr << pmat2;

  vnl_matrix<double> matrix3(2, 2);
  for (j=0; j<2; j++)
    for (i=0; i<2; i++)
      matrix3(i,j)= 2.0;

  vcl_cerr << "Incorrect Matrix: \n"
           << matrix3 << vcl_endl;
  PMatrixDec pmat3(matrix3);
  vcl_cerr << pmat3;
}
