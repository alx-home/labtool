# Install script for directory: C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/btk-0.3" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/moka/build/bin/libBTKBasicFilters.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/btk-0.3/BasicFilters" TYPE FILE FILES
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkAcquisitionUnitConverter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkAnalogOffsetRemover.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkCollectionAssembly.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkDownsampleFilter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkForcePlatformsExtractor.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkForcePlatformWrenchFilter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkGroundReactionWrenchFilter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkIMUsExtractor.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkMeasureFrameExtractor.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkMergeAcquisitionFilter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkSeparateKnownVirtualMarkersFilter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkSpecializedPointsExtractor.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkSubAcquisitionFilter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkVerticalGroundReactionForceGaitEventDetector.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/BasicFilters/btkWrenchDirectionAngleFilter.h"
    )
endif()

