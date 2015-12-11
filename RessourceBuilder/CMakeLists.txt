cmake_minimum_required(VERSION 3.3)


# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()


add_definitions("-std=c++11")

file(GLOB_RECURSE SRCS src/*.cpp)

add_executable(ressourceBuilder ${SRCS})

install (TARGETS ressourceBuilder RUNTIME DESTINATION bin)

SET(CMAKE_INSTALL_PREFIX_ "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64" CACHE PATH "Prefix prepended to install directories")
SET(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX_}" CACHE INTERNAL "Prefix prepended to install directories" FORCE)