# CMake generated Testfile for 
# Source directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/testlib/tests
# Build directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/core/testlib/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(testlib_assert "./testlib_test_all" "test_assert")
add_test(testlib_macros "./testlib_test_all" "test_macros")
add_test(testlib_args "./testlib_test_all" "test_args" "one" "two")
add_test(testlib_root_dir "./testlib_test_all" "test_root_dir")
add_test(testlib_test_link "./testlib_test_link")
add_test(testlib_all "./testlib_test_all" "all" "one" "two")
