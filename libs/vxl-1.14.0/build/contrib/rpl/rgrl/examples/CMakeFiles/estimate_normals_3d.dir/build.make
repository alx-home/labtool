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
include contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/depend.make

# Include the progress variables for this target.
include contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/flags.make

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/flags.make
contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/includes_CXX.rsp
contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj: ../contrib/rpl/rgrl/examples/estimate_normals_3d.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\estimate_normals_3d.dir\estimate_normals_3d.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples\estimate_normals_3d.cxx

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples\estimate_normals_3d.cxx > CMakeFiles\estimate_normals_3d.dir\estimate_normals_3d.i

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples\estimate_normals_3d.cxx -o CMakeFiles\estimate_normals_3d.dir\estimate_normals_3d.s

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.requires:

.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.requires

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.provides: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.requires
	$(MAKE) -f contrib\rpl\rgrl\examples\CMakeFiles\estimate_normals_3d.dir\build.make contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.provides.build
.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.provides

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.provides.build: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj


# Object files for target estimate_normals_3d
estimate_normals_3d_OBJECTS = \
"CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj"

# External object files for target estimate_normals_3d
estimate_normals_3d_EXTERNAL_OBJECTS =

contrib/rpl/rgrl/examples/estimate_normals_3d.exe: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/build.make
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/librrel.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/librsdl.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/libvnl_algo.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/libnetlib.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/libv3p_netlib.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/libvgl.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/libvnl.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/libvbl.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: lib/libvcl.a
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/linklibs.rsp
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/objects1.rsp
contrib/rpl/rgrl/examples/estimate_normals_3d.exe: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable estimate_normals_3d.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\estimate_normals_3d.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/build: contrib/rpl/rgrl/examples/estimate_normals_3d.exe

.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/build

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/requires: contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/estimate_normals_3d.obj.requires

.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/requires

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && $(CMAKE_COMMAND) -P CMakeFiles\estimate_normals_3d.dir\cmake_clean.cmake
.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/clean

contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples\CMakeFiles\estimate_normals_3d.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/estimate_normals_3d.dir/depend

