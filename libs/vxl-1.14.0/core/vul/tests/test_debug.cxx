// This is core/vul/tests/test_debug.cxx
#include <testlib/testlib_test.h>
//:
// \file
// \brief Tests core dumping etc.
// \author Ian Scott
//

#include <vcl_iostream.h>
#include <vcl_new.h>
#include <vul/vul_debug.h>
#include <vul/vul_file.h>
#include <vul/vul_sprintf.h>
#include <vpl/vpl.h>
#include <vcl_string.h>

//=======================================================================
static void test_debug()
{
  vcl_cout <<"\n*******************\n"
           <<  " Testing vul_debug\n"
           <<  "*******************\n\n";

  unsigned int pid = vpl_getpid();

  const char * filetemplate = "test_core%.3d.dmp";
  {
    vcl_cout << "Test simple forced coredump\n";

    const char * base_filename = "test_core000.dmp";
    vpl_unlink(base_filename);
    vcl_string long_filename = vul_sprintf("%s.%d", base_filename, pid);
    vpl_unlink(long_filename.c_str());

    vul_debug_core_dump(filetemplate);

    TEST("Core dump file exists", vul_file_exists(base_filename) || vul_file_exists(long_filename), true);
    TEST("Core dump file is sensible size", vul_file_size(base_filename)+vul_file_size(long_filename) > 100, true);
  }

#ifdef VCL_HAS_EXCEPTIONS

#if defined(_WIN32) && THOROUGH_TESTING
  {
    vcl_cout << "Test Structured exception coredump\n";

    const char * base_filename = "test_core001.dmp";
    vpl_unlink(base_filename);
    vcl_string long_filename = vul_sprintf("%s.%d", base_filename, pid);
    vpl_unlink(long_filename.c_str());

    vul_debug_set_coredump_and_throw_on_windows_se(filetemplate);
    bool caught_exception=false;
    try
    {
      // force a segmentation violation exception
      if (*static_cast<int *>(0)==0)
        vcl_cout << "*Null is false" << vcl_endl;
      else
        vcl_cout << "*Null is true" << vcl_endl;
    }
    catch (const vul_debug_windows_structured_exception &)
    {
      caught_exception=true;
    }
    TEST("Windows SEGV exception caught", caught_exception, true);
    TEST("Core dump file exists", vul_file_exists(base_filename) || vul_file_exists(long_filename), true);
    TEST("Core dump file is sensible size", vul_file_size(base_filename)+vul_file_size(long_filename) > 100, true);
  }
#endif // defined(_WIN32) && THOROUGH_TESTING
  {
    vcl_cout << "Test out-of-memory coredump\n";

    const char * base_filename = "test_core001.dmp";
    vpl_unlink(base_filename);
    vcl_string long_filename = vul_sprintf("%s.%d", base_filename, pid);
    vpl_unlink(long_filename.c_str());

    vul_debug_set_coredump_and_throw_on_out_of_memory(filetemplate);
    bool caught_exception=false;
    try
    {
      vcl_size_t too_much=0;
      too_much -= 1000;
      char * p = new char[too_much];
      p[0] = '\0';
    }
    catch (const vcl_bad_alloc &)
    {
      caught_exception=true;
    }
    TEST("Out-of-memory exception caught", caught_exception, true);
    TEST("Core dump file exists", vul_file_exists(base_filename) || vul_file_exists(long_filename), true);
    TEST("Core dump file is sensible size", vul_file_size(base_filename)+vul_file_size(long_filename) > 100, true);
  }
#endif // VCL_HAS_EXCEPTIONS
}

TEST_MAIN(test_debug);
