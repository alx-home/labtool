set(MINGW_FOUND TRUE)

macro(set_includes)
    get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    
    foreach(dir ${dirs})
    	String(REGEX REPLACE " " "\\\\ " dir ${dir})
    endforeach()
    execute_process(COMMAND java -jar C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/share/MINGW/cmake/setInclude.jar ${dirs}
    		OUTPUT_VARIABLE return
    		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    		
    message("${return}")
    		
endmacro()

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

set_option(MINGW_PATH "C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64" PATH "mingw dir")
STRING(REGEX REPLACE "\\\\" "/" AppData "$ENV{appdata}")

set_option(GNUMEX_PATH "C:/gnumex/R2011a" PATH "mex libraries")
set_option(MATLAB_PATH "C:/Program Files/MATLAB/R2011a" PATH "Matlab root directory")