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
include core/examples/CMakeFiles/example_create_image_vil.dir/depend.make

# Include the progress variables for this target.
include core/examples/CMakeFiles/example_create_image_vil.dir/progress.make

# Include the compile flags for this target's objects.
include core/examples/CMakeFiles/example_create_image_vil.dir/flags.make

core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj: core/examples/CMakeFiles/example_create_image_vil.dir/flags.make
core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj: core/examples/CMakeFiles/example_create_image_vil.dir/includes_CXX.rsp
core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj: ../core/examples/create_image_vil.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\example_create_image_vil.dir\create_image_vil.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples\create_image_vil.cxx

core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example_create_image_vil.dir/create_image_vil.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples\create_image_vil.cxx > CMakeFiles\example_create_image_vil.dir\create_image_vil.i

core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example_create_image_vil.dir/create_image_vil.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples\create_image_vil.cxx -o CMakeFiles\example_create_image_vil.dir\create_image_vil.s

core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.requires:

.PHONY : core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.requires

core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.provides: core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.requires
	$(MAKE) -f core\examples\CMakeFiles\example_create_image_vil.dir\build.make core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.provides.build
.PHONY : core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.provides

core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.provides.build: core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj


# Object files for target example_create_image_vil
example_create_image_vil_OBJECTS = \
"CMakeFiles/example_create_image_vil.dir/create_image_vil.obj"

# External object files for target example_create_image_vil
example_create_image_vil_EXTERNAL_OBJECTS =

core/examples/example_create_image_vil.exe: core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj
core/examples/example_create_image_vil.exe: core/examples/CMakeFiles/example_create_image_vil.dir/build.make
core/examples/example_create_image_vil.exe: lib/libvul.a
core/examples/example_create_image_vil.exe: lib/libvil.a
core/examples/example_create_image_vil.exe: lib/libvcl.a
core/examples/example_create_image_vil.exe: lib/libgeotiff.a
core/examples/example_create_image_vil.exe: lib/libtiff.a
core/examples/example_create_image_vil.exe: lib/libjpeg.a
core/examples/example_create_image_vil.exe: lib/libpng.a
core/examples/example_create_image_vil.exe: lib/libz.a
core/examples/example_create_image_vil.exe: core/examples/CMakeFiles/example_create_image_vil.dir/linklibs.rsp
core/examples/example_create_image_vil.exe: core/examples/CMakeFiles/example_create_image_vil.dir/objects1.rsp
core/examples/example_create_image_vil.exe: core/examples/CMakeFiles/example_create_image_vil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example_create_image_vil.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\example_create_image_vil.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/examples/CMakeFiles/example_create_image_vil.dir/build: core/examples/example_create_image_vil.exe

.PHONY : core/examples/CMakeFiles/example_create_image_vil.dir/build

core/examples/CMakeFiles/example_create_image_vil.dir/requires: core/examples/CMakeFiles/example_create_image_vil.dir/create_image_vil.obj.requires

.PHONY : core/examples/CMakeFiles/example_create_image_vil.dir/requires

core/examples/CMakeFiles/example_create_image_vil.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples && $(CMAKE_COMMAND) -P CMakeFiles\example_create_image_vil.dir\cmake_clean.cmake
.PHONY : core/examples/CMakeFiles/example_create_image_vil.dir/clean

core/examples/CMakeFiles/example_create_image_vil.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\CMakeFiles\example_create_image_vil.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : core/examples/CMakeFiles/example_create_image_vil.dir/depend

