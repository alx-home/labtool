# Install script for directory: C:/workspace/libs/coherent point drift Bing-jian/C++

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/gmmreg_api" TYPE STATIC_LIBRARY FILES "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/lib/gmmreg_api/libgmmreg_api.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gmmreg_api" TYPE FILE FILES
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_api.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_base.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_cpd.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_grbf.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_grbf_func.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_rigid.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_rigid_func.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_tps.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_tps_func.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_utils.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/port_ini.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/utils/io_utils.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/utils/match_utils.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/utils/misc_utils.h"
    "C:/workspace/libs/coherent point drift Bing-jian/C++/utils/rotation_utils.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/gmmreg_api/cmake/gmmreg_apiTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/gmmreg_api/cmake/gmmreg_apiTargets.cmake"
         "C:/workspace/libs/coherent point drift Bing-jian/build/CMakeFiles/Export/share/gmmreg_api/cmake/gmmreg_apiTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/gmmreg_api/cmake/gmmreg_apiTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/gmmreg_api/cmake/gmmreg_apiTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gmmreg_api/cmake" TYPE FILE FILES "C:/workspace/libs/coherent point drift Bing-jian/build/CMakeFiles/Export/share/gmmreg_api/cmake/gmmreg_apiTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gmmreg_api/cmake" TYPE FILE FILES "C:/workspace/libs/coherent point drift Bing-jian/build/CMakeFiles/Export/share/gmmreg_api/cmake/gmmreg_apiTargets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gmmreg_api/cmake" TYPE FILE FILES "C:/workspace/libs/coherent point drift Bing-jian/C++/gmmreg_apiConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/workspace/libs/coherent point drift Bing-jian/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
