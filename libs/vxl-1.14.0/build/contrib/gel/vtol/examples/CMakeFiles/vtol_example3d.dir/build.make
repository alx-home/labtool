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
include contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/depend.make

# Include the progress variables for this target.
include contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/flags.make

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/flags.make
contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/includes_CXX.rsp
contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj: ../contrib/gel/vtol/examples/example3d.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vtol\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vtol_example3d.dir\example3d.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vtol\examples\example3d.cxx

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vtol_example3d.dir/example3d.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vtol\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vtol\examples\example3d.cxx > CMakeFiles\vtol_example3d.dir\example3d.i

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vtol_example3d.dir/example3d.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vtol\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vtol\examples\example3d.cxx -o CMakeFiles\vtol_example3d.dir\example3d.s

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.requires:

.PHONY : contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.requires

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.provides: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.requires
	$(MAKE) -f contrib\gel\vtol\examples\CMakeFiles\vtol_example3d.dir\build.make contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.provides.build
.PHONY : contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.provides

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.provides.build: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj


# Object files for target vtol_example3d
vtol_example3d_OBJECTS = \
"CMakeFiles/vtol_example3d.dir/example3d.obj"

# External object files for target vtol_example3d
vtol_example3d_EXTERNAL_OBJECTS =

contrib/gel/vtol/examples/vtol_example3d.exe: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj
contrib/gel/vtol/examples/vtol_example3d.exe: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/build.make
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvtol.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvbl.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvcl.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvdgl.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvsol.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvgl_algo.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvnl_algo.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libnetlib.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libv3p_netlib.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvbl_io.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvbl.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvgl_io.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvgl.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvsl.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvnl.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvul.a
contrib/gel/vtol/examples/vtol_example3d.exe: lib/libvcl.a
contrib/gel/vtol/examples/vtol_example3d.exe: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/linklibs.rsp
contrib/gel/vtol/examples/vtol_example3d.exe: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/objects1.rsp
contrib/gel/vtol/examples/vtol_example3d.exe: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vtol_example3d.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vtol\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vtol_example3d.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/build: contrib/gel/vtol/examples/vtol_example3d.exe

.PHONY : contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/build

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/requires: contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/example3d.obj.requires

.PHONY : contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/requires

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vtol\examples && $(CMAKE_COMMAND) -P CMakeFiles\vtol_example3d.dir\cmake_clean.cmake
.PHONY : contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/clean

contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vtol\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vtol\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vtol\examples\CMakeFiles\vtol_example3d.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/gel/vtol/examples/CMakeFiles/vtol_example3d.dir/depend

