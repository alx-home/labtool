# Brown geospatial library
# gel/mrc/vpgl/bgeo/CMakeLists.txt

SET(bgeo_sources
  bgeo_lvcs.cxx              bgeo_lvcs.h           bgeo_lvcs_sptr.h
  bgeo_datum_conversion.cxx  bgeo_datum_conversion.h
                             bgeo_earth_constants.h
  bgeo_utm.cxx               bgeo_utm.h
  bgeo_dll.h
  bgeo_sun_pos.h             bgeo_sun_pos.cxx
)
AUX_SOURCE_DIRECTORY(Templates bgeo_sources)

ADD_LIBRARY(bgeo ${bgeo_sources})
INSTALL_TARGETS(/lib bgeo)
INSTALL_NOBASE_HEADER_FILES(/include/vxl/contrib/gel/mrc/vpgl/bgeo ${bgeo_sources})

TARGET_LINK_LIBRARIES(bgeo vsl vnl vbl)

IF(BUILD_TESTING)
  SUBDIRS(tests)
ENDIF(BUILD_TESTING)
