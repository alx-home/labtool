INCLUDE(${MODULE_PATH}/FindPNG.cmake)

INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR})
LINK_LIBRARIES(${PNG_LIBRARIES})
IF (UNIX)
  LINK_LIBRARIES(m)
ENDIF (UNIX)
ADD_DEFINITIONS(${PNG_DEFINITIONS})

ADD_EXECUTABLE(pngtest pngtest.c)
ADD_TEST(png_test ${EXECUTABLE_OUTPUT_PATH}/pngtest ${CMAKE_CURRENT_SOURCE_DIR}/pngtest.png)
