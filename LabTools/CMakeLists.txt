cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Weffc++ -Werror")
find_package(gmmreg_api REQUIRED)
find_package(SFML REQUIRED)
find_package(GLEW REQUIRED)
find_package(cmake_eclipse_config)
find_package(VXL)

include(${VXL_CMAKE_DIR}/UseVXL.cmake)


include_directories(${SFML_INCLUDE_DIR})

SET(CMAKE_INSTALL_PREFIX_ ${MINGW_PATH} CACHE PATH "Prefix prepended to install directories")
SET(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX_}" CACHE INTERNAL "Prefix prepended to install directories" FORCE)

function(addResource fileName className)
    message("Ressource ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/files/${fileName} -> ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/classes/${className}.cpp")
    
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/classes/${className}.cpp")
        execute_process(
                    COMMAND ressourceBuilder.exe ${fileName} ${className} ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
    endif()
    
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/classes/${className}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/classes/${className}.h
        COMMAND ressourceBuilder.exe 
        ARGS ${fileName} ${className} ${CMAKE_CURRENT_SOURCE_DIR}/src
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/files/${fileName}
    )
    
   set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/classes/${className}.cpp APPEND PROPERTY OBJECT_DEPENDS 
    		${CMAKE_CURRENT_SOURCE_DIR}/src/resources/classes/${className}.h)
endfunction(addResource)

set_option(MATLAB FALSE BOOL "TRUE to build mexFile")
set_option(FINAL TRUE BOOL "TRUE to link statically libraries")
set_option(CMAKE_EXECUTABLE_INSTALL_DIR "C:/Users/AnalyseVidéoMarche/Dropbox/LabTools" STRING "Chemin vers le répertoir d'installation de l'executable")

include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

if (FINAL)
    link_directories(${CMAKE_INSTALL_PREFIX}/lib/SFML)
endif()

set(CMAKE_CXX_FLAGS)

if (MATLAB)
	message("Matlab configuration")
	
	add_definitions(-DMATLAB)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMATLAB_MEX_FILE -DFIX_CHAR16_T -O3 -DMX_COMPAT_32")
	set(CMAKE_EXE_LINKER_FLAGS
	      "${CMAKE_EXE_LINKER_FLAGS} /DEF:${GNUMEX_PATH}/mex.def")

	include_directories("${MATLAB_PATH}/extern/include"
	"${MATLAB_PATH}/simulink/include"
	"../MatlabMex/src" 
	../ressources)
	
	link_directories(${GNUMEX_PATH})
	
	set(SRCS)
	file(GLOB_RECURSE SRCS_TMP src/*.cpp)
	set(SRCS ${SRCS} ${SRCS_TMP})
	
	add_library(LabTools SHARED ${SRCS} src/resources/resource.rc)
	
   	target_link_libraries(LabTools libmx libmex libmat)
    	
	set_target_properties(LabTools PROPERTIES SUFFIX ".mexw64" PREFIX "")
	
    install (TARGETS LabTools DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/files)
                       
else ()
    set_option(WITH_INSTALLER FALSE BOOL "TRUE to build installer")
    
    if (WITH_INSTALLER)
        add_definitions(-DWITH_INSTALLER)
    endif()

	set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-Wl,-subsystem,windows")
	
	include_directories("../MatlabMex/src")
	     
	file(GLOB_RECURSE SRCS src/*.cpp)
	
	add_executable(LabTools ${SRCS} src/resources/resource.rc)
	
	install (TARGETS LabTools DESTINATION ${CMAKE_EXECUTABLE_INSTALL_DIR})
endif ()

if (FINAL)
    add_definitions(-DSFML_STATIC)

	target_link_libraries(LabTools
    	gmmreg_api vnl_algo vnl v3p_netlib vcl
    	sfml-graphics-s sfml-window-s sfml-system-s
    	glu32
    	${GLEW_LIBRARIES}
    	opengl32
    	winmm
    	gdi32
    	freetype
    	jpeg
    	Shlwapi
    	-static-libgcc
    	-static-libstdc++
    	-static
    	pthread
    )
else ()
    target_link_libraries(LabTools gmmreg_api vnl_algo vnl v3p_netlib vcl
    	sfml-graphics sfml-window sfml-system
    	glu32
    	${GLEW_LIBRARIES}
    	opengl32
    )
endif()

target_compile_features(LabTools PRIVATE cxx_range_for)

addResource(arial.ttf ArialFont)
addResource(fond.png SplashScreenBackground)
addResource(check.png CheckTexture)
addResource(model.settings XMLModelSettings)

if(WITH_INSTALLER)
    addResource(LabTools.mexw64 MexFile)
endif()

set_includes()