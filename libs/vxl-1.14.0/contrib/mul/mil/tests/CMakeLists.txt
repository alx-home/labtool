# mul/mil/tests/CMakeLists.txt

LINK_LIBRARIES( mil_algo mil vil1 vgl vnl vsl vpl testlib )

ADD_EXECUTABLE(mil_test_all test_mil.cxx)
ADD_TEST(mil_test_all ${EXECUTABLE_OUTPUT_PATH}/mil_test_all)

IF(CMAKE_COMPILER_IS_GNUCXX)
  SET_SOURCE_FILES_PROPERTIES(test_mil.cxx PROPERTIES COMPILE_FLAGS -O0)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

ADD_EXECUTABLE(mil_test_include test_include.cxx)
TARGET_LINK_LIBRARIES(mil_test_include mil_algo)
