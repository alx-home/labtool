// This is core/vul/tests/test_string.cxx
#include <vcl_iostream.h>
#include <testlib/testlib_test.h>
#include <vul/vul_string.h>
#include <vpl/vpl.h>

void test_string()
{
  vcl_cout << "********************\n"
           << " Testing vul_string\n"
           << "********************\n";

  {char s[] = " 1 trUe False";
   TEST("vul_string_c_upcase(\" 1 trUe False\")", vul_string_c_upcase(s), vcl_string(" 1 TRUE FALSE"));
  }
  {char s[] = " 1 trUe False";
   TEST("vul_string_c_downcase(\" 1 trUe False\")", vul_string_c_downcase(s), vcl_string(" 1 true false"));
  }
  {char s[] = " 1 trUe False";
   TEST("vul_string_c_capitalize(\" 1 trUe False\")", vul_string_c_capitalize(s), vcl_string(" 1 TrUe False"));
  }
  {char s[] = " 1 trUe False";
   TEST("vul_string_c_trim(\" 1 trUe False\",\" \")", vul_string_c_trim(s," "), vcl_string("1trUeFalse"));
  }
  {char s[] = " 1 trUe False";
   TEST("vul_string_c_left_trim(\" 1 trUe False\",\" \")", vul_string_c_left_trim(s," "), vcl_string("1 trUe False"));
  }
  {char s[] = " 1 trUe False";
   TEST("vul_string_c_right_trim(\" 1 trUe False\",\" \")", vul_string_c_right_trim(s," "), vcl_string(s));
  }
  {char s[] = " 1 trUe False";
   TEST("vul_string_c_reverse(\" 1 trUe False\")", vul_string_c_reverse(s), vcl_string("eslaF eUrt 1 "));
  }
  {vcl_string s = " 1 trUe False";
   TEST("vul_string_upcase(\" 1 trUe False\")", vul_string_upcase(s), vcl_string(" 1 TRUE FALSE"));
  }
  {vcl_string s = " 1 trUe False";
   TEST("vul_string_downcase(\" 1 trUe False\")", vul_string_downcase(s), vcl_string(" 1 true false"));
  }
  {vcl_string s = " 1 trUe False";
   TEST("vul_string_capitalize(\" 1 trUe False\")", vul_string_capitalize(s), vcl_string(" 1 TrUe False"));
  }
  {vcl_string s = " 1 trUe False";
   TEST("vul_string_trim(\" 1 trUe False\",\" \")", vul_string_trim(s," "), vcl_string("1trUeFalse"));
  }
  {vcl_string s = " 1 trUe False";
   TEST("vul_string_left_trim(\" 1 trUe False\")", vul_string_left_trim(s," "), vcl_string("1 trUe False"));
  }
  {vcl_string s = " 1 trUe False";
   TEST("vul_string_right_trim(\" 1 trUe False\")", vul_string_right_trim(s," "), vcl_string(s));
  }
  {vcl_string s = " 1 trUe False";
   TEST("vul_string_reverse(\" 1 trUe False\")", vul_string_reverse(s), vcl_string("eslaF eUrt 1 "));
  }

  TEST("vul_string_atoi(\"123\")", vul_string_atoi("123"), 123);
  TEST("vul_string_atoi(\"-123\")", vul_string_atoi("-123"), -123);
  TEST("vul_string_atoi(\"0\")", vul_string_atoi("0"), 0);
  TEST("vul_string_atoi(\"nonsense\")", vul_string_atoi("nonsense"), 0);

  TEST("vul_string_atof_withsuffix(\"123\")", vul_string_atof_withsuffix("123"), 123.0);
  TEST("vul_string_atof_withsuffix(\"-123\")", vul_string_atof_withsuffix("-123"), -123.0);
  TEST("vul_string_atof_withsuffix(\"0\")", vul_string_atof_withsuffix("0"), 0.0);
  TEST("vul_string_atof_withsuffix(\"nonsense\")", vul_string_atof_withsuffix("nonsense"), 0.0);
  TEST("vul_string_atof_withsuffix(\"123k\")", vul_string_atof_withsuffix("123k"), 123.0e3);
  TEST("vul_string_atof_withsuffix(\"123kb\")", vul_string_atof_withsuffix("123ki"), 125952.0);
  TEST("vul_string_atof_withsuffix(\"123kb\")", vul_string_atof_withsuffix("123.0e-3ki"), 125.9520);
  TEST("vul_string_atof_withsuffix(\"3M\")", vul_string_atof_withsuffix("3M"), 3e6);
  TEST("vul_string_atof_withsuffix(\"-123Mb\")", vul_string_atof_withsuffix("-123Mi"), -128974848.0);
  TEST("vul_string_atof_withsuffix(\"-1G\")", vul_string_atof_withsuffix("-1G"), -1.0e9);
  TEST("vul_string_atof_withsuffix(\"1T\")", vul_string_atof_withsuffix("1T"), 1.0e12);


  TEST("vul_string_to_bool(\"YES\")", vul_string_to_bool("YES"), true);
  TEST("vul_string_to_bool(\"trUe\")", vul_string_to_bool("trUe"), true);
  TEST("vul_string_to_bool(\" 1 \")", vul_string_to_bool(" 1 "), true);
  TEST("vul_string_to_bool(\" on\")", vul_string_to_bool(" on"), true);
  TEST("vul_string_to_bool(Not \"FALSE\")", vul_string_to_bool("FALSE"), false);
  TEST("vul_string_to_bool(Not \"0\")", vul_string_to_bool("0"), false);
  TEST("vul_string_to_bool(Not \"onwibble\")", vul_string_to_bool("onwibble"), false);


  vpl_putenv("VUL_1=foo");
  vpl_putenv("VUL_2=bar");
  {
    vcl_string s("wibble$VUL_1wobble");
    TEST("vul_string_expand_var", vul_string_expand_var(s), true);
    TEST("vul_string_expand_var", s, "wibblefoowobble");
  }
  {
    vcl_string s("wibble$VUL_3wobble$VUL_2splat${VUL_1}");
    TEST("vul_string_expand_var", vul_string_expand_var(s), false);
    TEST("vul_string_expand_var", s, "wibble$VUL_3wobblebarsplatfoo");
  }
  {
    vcl_string s("wibble$VUL_3wobble$VUL_2splat$(VUL_1)");
    TEST("vul_string_expand_var", vul_string_expand_var(s), false);
    TEST("vul_string_expand_var", s, "wibble$VUL_3wobblebarsplatfoo");
  }
  {
    vcl_string s("wibble$$$VUL_1 wobble$[]");
    TEST("vul_string_expand_var", vul_string_expand_var(s), false);
    TEST("vul_string_expand_var", s, "wibble$foo wobble$[]");
  }

#if 0
  // replaces instances "find_str" in "full_str" with "replace_str"
  // a given "num_times"
  vul_string_replace( vcl_string& full_str,
                      const vcl_string& find_str,
                      const vcl_string& replace_str,
                      int num_times=1000);
#endif // 0
  {
    vcl_string s("I hate mices to pieces");
    vul_string_replace( s, "hate", "love" );
    TEST( "vul_string_replace", s== "I love mices to pieces", true);
  }
}

TEST_MAIN(test_string);
