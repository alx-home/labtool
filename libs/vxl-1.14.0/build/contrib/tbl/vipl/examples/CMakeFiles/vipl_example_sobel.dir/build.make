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
include contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/depend.make

# Include the progress variables for this target.
include contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/flags.make

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/flags.make
contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/includes_CXX.rsp
contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj: ../contrib/tbl/vipl/examples/example_sobel.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vipl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vipl_example_sobel.dir\example_sobel.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vipl\examples\example_sobel.cxx

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vipl_example_sobel.dir/example_sobel.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vipl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vipl\examples\example_sobel.cxx > CMakeFiles\vipl_example_sobel.dir\example_sobel.i

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vipl_example_sobel.dir/example_sobel.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vipl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vipl\examples\example_sobel.cxx -o CMakeFiles\vipl_example_sobel.dir\example_sobel.s

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.requires:

.PHONY : contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.requires

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.provides: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.requires
	$(MAKE) -f contrib\tbl\vipl\examples\CMakeFiles\vipl_example_sobel.dir\build.make contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.provides.build
.PHONY : contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.provides

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.provides.build: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj


# Object files for target vipl_example_sobel
vipl_example_sobel_OBJECTS = \
"CMakeFiles/vipl_example_sobel.dir/example_sobel.obj"

# External object files for target vipl_example_sobel
vipl_example_sobel_EXTERNAL_OBJECTS =

contrib/tbl/vipl/examples/vipl_example_sobel.exe: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj
contrib/tbl/vipl/examples/vipl_example_sobel.exe: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/build.make
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libvipl.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libvbl.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libvil.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libgeotiff.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libvil1.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libtiff.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libjpeg.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libpng.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libz.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libvnl.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: lib/libvcl.a
contrib/tbl/vipl/examples/vipl_example_sobel.exe: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/linklibs.rsp
contrib/tbl/vipl/examples/vipl_example_sobel.exe: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/objects1.rsp
contrib/tbl/vipl/examples/vipl_example_sobel.exe: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vipl_example_sobel.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vipl\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vipl_example_sobel.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/build: contrib/tbl/vipl/examples/vipl_example_sobel.exe

.PHONY : contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/build

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/requires: contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/example_sobel.obj.requires

.PHONY : contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/requires

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vipl\examples && $(CMAKE_COMMAND) -P CMakeFiles\vipl_example_sobel.dir\cmake_clean.cmake
.PHONY : contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/clean

contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\tbl\vipl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vipl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\tbl\vipl\examples\CMakeFiles\vipl_example_sobel.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/tbl/vipl/examples/CMakeFiles/vipl_example_sobel.dir/depend
