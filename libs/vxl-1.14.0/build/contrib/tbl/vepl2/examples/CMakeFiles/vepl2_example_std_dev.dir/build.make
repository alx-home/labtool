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
include contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/depend.make

# Include the progress variables for this target.
include contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/flags.make

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/flags.make
contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/includes_CXX.rsp
contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj: ../contrib/tbl/vepl2/examples/example_std_dev.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vepl2\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -O0 -o CMakeFiles\vepl2_example_std_dev.dir\example_std_dev.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vepl2\examples\example_std_dev.cxx

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vepl2\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -O0 -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vepl2\examples\example_std_dev.cxx > CMakeFiles\vepl2_example_std_dev.dir\example_std_dev.i

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vepl2\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -O0 -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vepl2\examples\example_std_dev.cxx -o CMakeFiles\vepl2_example_std_dev.dir\example_std_dev.s

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.requires:

.PHONY : contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.requires

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.provides: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.requires
	$(MAKE) -f contrib\tbl\vepl2\examples\CMakeFiles\vepl2_example_std_dev.dir\build.make contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.provides.build
.PHONY : contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.provides

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.provides.build: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj


# Object files for target vepl2_example_std_dev
vepl2_example_std_dev_OBJECTS = \
"CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj"

# External object files for target vepl2_example_std_dev
vepl2_example_std_dev_EXTERNAL_OBJECTS =

contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/build.make
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvepl2.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvil.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvipl.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvil.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libgeotiff.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvil1.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libtiff.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libjpeg.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libpng.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libz.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvnl.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvbl.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: lib/libvcl.a
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/linklibs.rsp
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/objects1.rsp
contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vepl2_example_std_dev.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vepl2\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vepl2_example_std_dev.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/build: contrib/tbl/vepl2/examples/vepl2_example_std_dev.exe

.PHONY : contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/build

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/requires: contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/example_std_dev.obj.requires

.PHONY : contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/requires

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vepl2\examples && $(CMAKE_COMMAND) -P CMakeFiles\vepl2_example_std_dev.dir\cmake_clean.cmake
.PHONY : contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/clean

contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vepl2\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vepl2\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vepl2\examples\CMakeFiles\vepl2_example_std_dev.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/tbl/vepl2/examples/CMakeFiles/vepl2_example_std_dev.dir/depend

