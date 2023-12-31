// This is core/vnl/tests/test_sparse_matrix.cxx
#include <vcl_iostream.h>
#include <vnl/vnl_sparse_matrix.h>
#include <testlib/testlib_test.h>

static
void test_sparse_int()
{
  vcl_cout << "********************************\n"
           << " Testing vnl_sparse_matrix<int>\n"
           << "********************************\n";
  vnl_sparse_matrix<int> m0(2000,3000);
  TEST("vnl_sparse_matrix<int> m0(2000,3000)", (m0.rows()==2000 && m0.columns()==3000), true);
  vnl_sparse_matrix<int> m1(3000,4000);
  TEST("vnl_sparse_matrix<int> m1(3000,4000)", (m1.rows()==3000 && m1.columns()==4000), true);
  m0(1111,2222) = m1(1111,2222) = 3333;
  TEST("(vnl_sparse_matrix)(i,j)", m0(1111,2222), 3333);
  const vnl_sparse_matrix<int> ma = m0;
  TEST("copy constructor", ma, m0);
  vnl_sparse_matrix<int> m2(m1);
  TEST("vnl_sparse_matrix<int> m2(m1)", m1, m2);
  TEST("(const vnl_sparse_matrix)(i,j)", ma(1111,2222), 3333);
  vnl_sparse_matrix<int> mb; mb = m0;
  TEST("assignment operator", mb(1111,2222), 3333);
  TEST("m0 == ma", (m0 == ma), true);
  TEST("m1.put(1,1,3)", (m1.put(1,1,3),m1(1,1)==3), true);
  TEST("m1.get(1,1)", m1.get(1,1), 3);
  TEST("!(m0 == m1)", (m0 == m1), false);
  TEST("m0 != m1", (m0 != m1), true);
  TEST("!(m1 == m2)", (m1 == m2), false);

  // test additions and subtractions
  TEST("mb = -m0", (mb = -m0, (mb.get(0,0)==0 && mb.get(1111,2222)==-3333)), true);
  TEST("mb=m1+m2", (mb=m1+m2, (mb.get(0,0)==0 && mb.get(1111,2222)==6666 && mb.get(1,1)==3)), true);
  TEST("mb=m1-m2", (mb=m1-m2, (mb.get(0,0)==0 && mb.get(1111,2222)==0 && mb.get(1,1)==3)), true);
  TEST("m1 -= m2", (m1 -= m2, m1), mb);
  TEST("m1 += m2", (m1 += m2, m1), mb+m2);

  /// test multiplications and divisions
  TEST("mb=m1*5", (mb=m1*5, (mb.get(0,0)==0 && mb.get(1,1)==15)), true);
  TEST("mb=5*m1", (mb=5*m1, (mb.get(0,0)==0 && mb.get(1,1)==15)), true);
  TEST("m1*=5",   (m1*=5,   m1), mb);
  TEST("mb=m1/5", (mb=m1/5, (mb.get(0,0)==0 && mb.get(1,1)==3)), true);
  TEST("m1/=5",   (m1/=5,   m1), mb);

  TEST("mb=m0*m1", (mb=m0*m1, mb), vnl_sparse_matrix<int>(2000,4000)); // all-zero matrix
  TEST("m0*=m1", (m0*=m1, m0), mb);
  vnl_sparse_matrix<int> c0(4000,1); c0(2222,0) = 1;
  vnl_sparse_matrix<int> c1;
  TEST("c1=m0*c0", (c1=m0*c0, c1.rows()==m0.rows() && c1.columns()==c0.columns() && c1.get(1111,0)==m0(1111,2222)), true);
  vnl_sparse_matrix<int> r0(1,2000); r0(0,1111) = 1;
  vnl_sparse_matrix<int> r1;
  TEST("r1=r0*m0", (r1=r0*m0, r1.rows()==r0.rows() && r1.columns()==m0.columns() && r1.get(0,2222)==m0(1111,2222)), true);
  TEST("r0*=m0", (r0*=m0, r0==r1), true);

  // Zero-size
  {
    vnl_sparse_matrix<int> m1(0,3);
    vnl_sparse_matrix<int> m2(3,4);
    vnl_sparse_matrix<int> m3(4,0);
    m2(0,0) = m2(0,1) = m2(0,2) = m2(0,3) = 777;
    m2(1,0) = m2(1,1) = m2(1,2) = m2(1,3) = 888;
    m2(2,0) = m2(2,1) = m2(2,2) = m2(2,3) = 999;
    vnl_sparse_matrix<int> m = m1 * (m2 * m3);
    TEST("zero-size mult rows", m.rows(), 0);
    TEST("zero-size mult cols", m.columns(), 0);

    m = (m1 * m2) * m3;
    TEST("zero-size mult rows", m.rows(), 0);
    TEST("zero-size mult cols", m.columns(), 0);

    m2.clear();
    TEST("empty after clear()", m2, vnl_sparse_matrix<int>(3,4)); // all-zero matrix
  }
}

void test_sparse_float()
{
  vcl_cout << "**********************************\n"
           << " Testing vnl_sparse_matrix<float>\n"
           << "**********************************\n";
  vnl_sparse_matrix<float> d0(2,2);
  TEST("vnl_sparse_matrix<float> d0(2,2)", (d0.rows()==2 && d0.columns()==2), true);
  vnl_sparse_matrix<float> d1(3,4);
  TEST("vnl_sparse_matrix<float> d1(3,4)", (d1.rows()==3 && d1.columns()==4), true);
  vnl_sparse_matrix<float> d2(d1);
  TEST("copy constructor", d2, d1);
  TEST("d2.put(1,1,3.f)", (d2.put(1,1,3.f),d2.get(1,1)), 3.f);
  TEST("d2.get(1,1)", d2.get(1,1), 3.f);
  TEST("!(d0 == d2)", (d0 == d2), false);
  TEST("d0 != d2", (d0 != d2), true);
  TEST("d0=d2", (d0=d2,  (d0==d2)), true);
  vnl_sparse_matrix<float> d5(2,2);
  TEST("d5=d0+d2", (d5=d0+d2, (d5.get(0,0)==0.f && d5.get(0,1)==0.f && d5.get(1,0)==0.f && d5.get(1,1)==6.f)), true);
  TEST("d0+=d2",   (d0+=d2,   d0), d5);
  TEST("d0=d2*5.f",(d0=d2*5.f,(d0.get(0,0)==0.f && d0.get(0,1)==0.f && d0.get(1,0)==0.f && d0.get(1,1)==15.f)), true);
  TEST("d2*=5.f",  (d2*=5.f,  d2), d0);
}

void test_sparse_double()
{
  vcl_cout << "***********************************\n"
           << " Testing vnl_sparse_matrix<double>\n"
           << "***********************************\n";
  vnl_sparse_matrix<double> d0(2,2);
  TEST("vnl_sparse_matrix<double> d0(2,2)", (d0.rows()==2 && d0.columns()==2), true);
  vnl_sparse_matrix<double> d1(3,4);
  TEST("vnl_sparse_matrix<double> d1(3,4)", (d1.rows()==3 && d1.columns()==4), true);
  vnl_sparse_matrix<double> d2=d0;
  TEST("copy constructor", d0, d2);
  TEST("d2.put(1,1,3.0)", (d2.put(1,1,3.0),d2.get(1,1)), 3.0);
  TEST("d2.get(1,1)", d2.get(1,1), 3.0);
  d2(1,0) = 4.0;
  TEST("d2(1,0) = 4.0", d2(1,0), 4.0);
  TEST("!(d0 == d2)", (d0 == d2), false);
  TEST("d0 != d2", (d0 != d2), true);
  vnl_sparse_matrix<double> d3(d2);
  TEST("vnl_sparse_matrix<double> d3(d2)", d2, d3);
  TEST("d0=d2", (d0=d2,  (d0==d2)), true);
  vnl_sparse_matrix<double> d5(2,2);

  // normalizations
  d2(0,1) = 7.0;
  d2.normalize_rows();
  TEST("normalize_rows()", d2(0,0)==0 && d2(0,1)==1, true);
  TEST_NEAR("normalize_rows()", d2(1,0), 0.8, 1e-12);
  TEST_NEAR("normalize_rows()", d2(1,1), 0.6, 1e-12);
}

static
void test_sparse_matrix()
{
  test_sparse_int();
  test_sparse_float();
  test_sparse_double();
}

TESTMAIN(test_sparse_matrix);
