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
include contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/depend.make

# Include the progress variables for this target.
include contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/flags.make

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/flags.make
contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/includes_CXX.rsp
contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj: ../contrib/mul/vimt/examples/example1.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\vimt\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vimt_example1.dir\example1.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\vimt\examples\example1.cxx

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vimt_example1.dir/example1.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\vimt\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\vimt\examples\example1.cxx > CMakeFiles\vimt_example1.dir\example1.i

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vimt_example1.dir/example1.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\vimt\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\vimt\examples\example1.cxx -o CMakeFiles\vimt_example1.dir\example1.s

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.requires:

.PHONY : contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.requires

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.provides: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.requires
	$(MAKE) -f contrib\mul\vimt\examples\CMakeFiles\vimt_example1.dir\build.make contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.provides.build
.PHONY : contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.provides

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.provides.build: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj


# Object files for target vimt_example1
vimt_example1_OBJECTS = \
"CMakeFiles/vimt_example1.dir/example1.obj"

# External object files for target vimt_example1
vimt_example1_EXTERNAL_OBJECTS =

contrib/mul/vimt/examples/vimt_example1.exe: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj
contrib/mul/vimt/examples/vimt_example1.exe: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/build.make
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvimt_algo.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvimt.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvnl.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvil.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvgl.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvul.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libmbl.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvul.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvnl_io.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvgl_io.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvbl_io.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvil_io.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvsl.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvbl.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvgl.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvil_algo.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvil.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libgeotiff.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libtiff.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libjpeg.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libpng.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libz.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvnl_algo.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvnl.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libnetlib.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libv3p_netlib.a
contrib/mul/vimt/examples/vimt_example1.exe: lib/libvcl.a
contrib/mul/vimt/examples/vimt_example1.exe: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/linklibs.rsp
contrib/mul/vimt/examples/vimt_example1.exe: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/objects1.rsp
contrib/mul/vimt/examples/vimt_example1.exe: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vimt_example1.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\vimt\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vimt_example1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/build: contrib/mul/vimt/examples/vimt_example1.exe

.PHONY : contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/build

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/requires: contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/example1.obj.requires

.PHONY : contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/requires

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\vimt\examples && $(CMAKE_COMMAND) -P CMakeFiles\vimt_example1.dir\cmake_clean.cmake
.PHONY : contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/clean

contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\vimt\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\vimt\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\vimt\examples\CMakeFiles\vimt_example1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/mul/vimt/examples/CMakeFiles/vimt_example1.dir/depend
