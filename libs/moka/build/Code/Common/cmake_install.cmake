# Install script for directory: C:/Users/alex/Documents/chu/libs/moka/Code/Common

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/btk-0.3" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/moka/build/bin/libBTKCommon.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/btk-0.3/Common" TYPE FILE FILES
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkAcquisition.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkAnalog.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkAnalogCollection.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkCollection.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkConvert.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkDataObject.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkEvent.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkEventCollection.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkException.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkForcePlatform.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkForcePlatformCollection.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkForcePlatformTypes.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkIMU.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkIMUCollection.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkIMUTypes.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkLogger.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkMacro.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkMeasure.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkMetaData.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkMetaDataInfo.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkMetaDataUtils.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkNullPtr.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkObject.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkPoint.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkPointCollection.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkProcessObject.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkSharedPtr.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkTriangleMesh.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkWrench.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/Common/btkWrenchCollection.h"
    )
endif()

