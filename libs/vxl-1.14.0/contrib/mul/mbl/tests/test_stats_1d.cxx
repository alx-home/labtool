// This is mul/mbl/tests/test_stats_1d.cxx
#include <vcl_iostream.h>
#include <mbl/mbl_stats_1d.h>
#include <testlib/testlib_test.h>

void test_stats_1d()
{
  vcl_cout << "**********************\n"
           << " Testing mbl_stats_1d\n"
           << "**********************\n";

  mbl_stats_1d stats;

  TEST("Empty N.obs",stats.nObs(), 0);
  TEST("Empty mean", stats.mean(), 0.0);

  for (int i=0;i<5;++i)
    stats.obs(i);

  TEST("nObs()",stats.nObs()==5,true);
  vcl_cout<<stats<<vcl_endl;
  TEST_NEAR("mean()", stats.mean(),  2, 1e-9);
  TEST_NEAR("sd()"  , stats.sd()  , 1.414213562, 1e-9);
  TEST_NEAR("sum()" , stats.sum() , 10, 1e-9);
  TEST_NEAR("sumSq()",stats.sumSq(),30, 1e-9);

  mbl_stats_1d stats2 = stats;
  TEST("Equality operator",stats, stats2);

  stats.clear();
  mbl_stats_1d stats_slow;
  for (int i=0;i<5;++i)
  {
    stats.obs(i, i);
    for (int j=0;j<i;++j)
      stats_slow.obs(i);
  }

  TEST_NEAR("weights", stats.wObs(), stats_slow.wObs(), 1e-9);
  TEST_NEAR("mean", stats.mean(), stats_slow.mean(), 1e-9);
  TEST_NEAR("std error", stats.stdError(), stats_slow.stdError(), 1e-9);




}

TESTMAIN(test_stats_1d);
