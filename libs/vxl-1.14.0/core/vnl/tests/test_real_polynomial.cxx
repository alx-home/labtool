#include <vcl_iostream.h>

#include <testlib/testlib_test.h>
#include <vnl/vnl_real_polynomial.h>
#include <vnl/vnl_double_3.h>
#include <vcl_sstream.h>

void test_real_polynomial()
{
  vnl_real_polynomial f1(3),f2(4);

  for (int i=0;i<=f1.degree();++i) f1[i]=i+1; // f1 = X^3 +2 X^2 +3 X + 4
  f1.print(vcl_cout); vcl_cout << vcl_endl;
  { vcl_stringstream testStream;
    f1.print(testStream);
    vcl_string expected = " X^3 +2 X^2 +3 X +4";
    TEST("f1 prints as X^3 +2 X^2 +3 X +4", testStream.str(), expected);
    vcl_cout << "Actual:\t\t\"" << testStream.str() << '"' << vcl_endl
             << "Expected:\t\"" << expected << '"' << vcl_endl;
  }

  for (int i=0;i<=f2.degree();++i) f2[i]=2*i+1; // f2 = X^4 +3 X^3 +5 X^2 +7 X +9
  f2.print(vcl_cout); vcl_cout << vcl_endl;

  vnl_real_polynomial f3 = f1+f2;
  f3.print(vcl_cout); vcl_cout << vcl_endl;
  TEST("f1+f2=f3",f1.evaluate(2.5)+f2.evaluate(2.5), f3.evaluate(2.5));
  // Evaluating in 2.5 is exact, since 2.5 is exactly representable (binary 10.1)

  vnl_real_polynomial f4 = f1-f2;
  f4.print(vcl_cout); vcl_cout << vcl_endl;
  TEST("f1-f2=f4",f1.evaluate(2.5)-f2.evaluate(2.5), f4.evaluate(2.5));

  vnl_real_polynomial f5 = f1*f2;
  f5.print(vcl_cout); vcl_cout << vcl_endl;

  TEST("f1*f2 has correct degree",f5.degree()==(f1.degree()+f2.degree()),true);

  TEST("f1*f2=f5",f1.evaluate(2.5)*f2.evaluate(2.5), f5.evaluate(2.5));

  vnl_real_polynomial f1d = f1.derivative();
  f1d.print(vcl_cout); vcl_cout << vcl_endl;
  vnl_real_polynomial f2d = f2.derivative();
  f2d.print(vcl_cout); vcl_cout << vcl_endl;

  TEST("Derivative", f5.derivative(), f1d*f2+f2d*f1);

  vnl_real_polynomial f5p = (f1d*f2+f2d*f1).primitive();
  f5p.print(vcl_cout); vcl_cout << vcl_endl;

  TEST("Primitive", f5p, f5-f5.evaluate(0.0));

  TEST_NEAR("Integral", f1.evaluate_integral(2.0), 70.0/3, 1e-9);

  TEST("Polynomial of degree 0", vnl_real_polynomial(1.0).evaluate(0.5),1.0);
  TEST("Vector initialisation",
       vnl_real_polynomial(vnl_double_3(3.0,2.0,1.0)).evaluate(2.0),17.0);

  TEST_NEAR("RMS difference(f1,f2)",vnl_rms_difference(f1,f1,0,1),0.0,1e-9);

  vnl_real_polynomial f6(1); //f6 = X + 1
  f6[0] = f6[1] = 1;
  { vcl_stringstream testStream;
    f6.print(testStream);
    vcl_string expected = " X +1";
    TEST("f6 prints as X +1", testStream.str(), expected);
    vcl_cout << "Actual:\t\t\"" << testStream.str() << '"' << vcl_endl
             << "Expected:\t\"" << expected << '"' << vcl_endl;
  }

  vnl_real_polynomial f7(1); //f7 = X - 1
  f7[0] = 1;
  f7[1] = -1;
  { vcl_stringstream testStream;
    f7.print(testStream);
    vcl_string expected = " X -1";
    TEST("f7 prints as X -1", testStream.str(), expected);
    vcl_cout << "Actual:\t\t\"" << testStream.str() << '"' << vcl_endl
             << "Expected:\t\"" << expected << '"' << vcl_endl;
  }

  vnl_real_polynomial f8(1); //f8 = 0
  f8[0] = 0;
  f8[1] = 0;
  { vcl_stringstream testStream;
    f8.print(testStream);
    vcl_string expected = "0 ";
    TEST("f8 prints as 0", testStream.str(), expected);
    vcl_cout << "Actual:\t\t\"" << testStream.str() << '"' << vcl_endl
             << "Expected:\t\"" << expected << '"' << vcl_endl;
  }
}

TESTMAIN(test_real_polynomial);
