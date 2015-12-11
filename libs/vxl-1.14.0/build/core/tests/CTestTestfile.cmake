# CMake generated Testfile for 
# Source directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/core/tests
# Build directory: C:/Users/alex/Documents/chu/libs/vxl-1.14.0/build/core/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(core_test_config "./core_test_all" "test_config")
add_test(core_test_build_info "./core_test_all" "test_build_info")
add_test(cmake_config "./vxl_echo" "nl" "MAKECOMMAND:" "C:/Program\ Files\ (x86)/CMake/bin/cmake.exe --build . --config \"${CTEST_CONFIGURATION_TYPE}\" -- -i" "nl" "CMAKE_CXX_FLAGS:" " " "nl" "CMAKE_C_FLAGS:" " " "nl" "BUILD_SHARED_LIBS:" "OFF" "nl" "CMAKE_EXE_LINKER_FLAGS:" " " "nl" "CMAKE_MODULE_LINKER_FLAGS:" " " "nl" "CMAKE_SHARED_LINKER_FLAGS:" " " "nl" "VXL_USE_CMAKE_CONFIGURE:" "nl")
