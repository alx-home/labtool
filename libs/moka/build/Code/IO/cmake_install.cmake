# Install script for directory: C:/Users/alex/Documents/chu/libs/moka/Code/IO

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/btk-0.3" TYPE STATIC_LIBRARY FILES "C:/Users/alex/Documents/chu/libs/moka/build/bin/libBTKIO.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/btk-0.3/IO" TYPE FILE FILES
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkAcquisitionFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkAcquisitionFileIOFactory.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkAcquisitionFileIOHandle.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkAcquisitionFileIORegister.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkAcquisitionFileReader.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkAcquisitionFileWriter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkANBFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkANCFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkANGFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkASCIIFileWriter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkBinaryFileStream.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkBinaryFileStream_mmfstream.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkBSFFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkC3DFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkCALForcePlateFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkCLBFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkDelsysEMGFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkEMFFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkEMxFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkGRxFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkKistlerDATFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkMDFFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkMOMFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkMotionAnalysisFileIOUtils.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkMultiSTLFileWriter.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkPWRFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkRAxFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkRICFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkTDFFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkTRBFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkTRCFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkXLSOrthoTrakFileIO.h"
    "C:/Users/alex/Documents/chu/libs/moka/Code/IO/btkXMOVEFileIO.h"
    )
endif()

