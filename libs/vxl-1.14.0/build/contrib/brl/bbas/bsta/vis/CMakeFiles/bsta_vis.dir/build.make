# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\alex\Documents\chu\libs\vxl-1.14.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build

# Include any dependencies generated for this target.
include contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/depend.make

# Include the progress variables for this target.
include contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/flags.make

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/flags.make
contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/includes_CXX.rsp
contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj: ../contrib/brl/bbas/bsta/vis/bsta_svg_tools.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bsta_vis.dir\bsta_svg_tools.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bsta\vis\bsta_svg_tools.cxx

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bsta_vis.dir/bsta_svg_tools.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bsta\vis\bsta_svg_tools.cxx > CMakeFiles\bsta_vis.dir\bsta_svg_tools.i

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bsta_vis.dir/bsta_svg_tools.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bsta\vis\bsta_svg_tools.cxx -o CMakeFiles\bsta_vis.dir\bsta_svg_tools.s

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.requires:

.PHONY : contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.requires

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.provides: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.requires
	$(MAKE) -f contrib\brl\bbas\bsta\vis\CMakeFiles\bsta_vis.dir\build.make contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.provides.build
.PHONY : contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.provides

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.provides.build: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj


# Object files for target bsta_vis
bsta_vis_OBJECTS = \
"CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj"

# External object files for target bsta_vis
bsta_vis_EXTERNAL_OBJECTS =

lib/libbsta_vis.a: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj
lib/libbsta_vis.a: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/build.make
lib/libbsta_vis.a: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\..\..\..\lib\libbsta_vis.a"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis && $(CMAKE_COMMAND) -P CMakeFiles\bsta_vis.dir\cmake_clean_target.cmake
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bsta_vis.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/build: lib/libbsta_vis.a

.PHONY : contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/build

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/requires: contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/bsta_svg_tools.obj.requires

.PHONY : contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/requires

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis && $(CMAKE_COMMAND) -P CMakeFiles\bsta_vis.dir\cmake_clean.cmake
.PHONY : contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/clean

contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bsta\vis C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bsta\vis\CMakeFiles\bsta_vis.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/brl/bbas/bsta/vis/CMakeFiles/bsta_vis.dir/depend

