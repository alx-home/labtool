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
include core/vil1/examples/CMakeFiles/vil1_convolve.dir/depend.make

# Include the progress variables for this target.
include core/vil1/examples/CMakeFiles/vil1_convolve.dir/progress.make

# Include the compile flags for this target's objects.
include core/vil1/examples/CMakeFiles/vil1_convolve.dir/flags.make

core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj: core/vil1/examples/CMakeFiles/vil1_convolve.dir/flags.make
core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj: core/vil1/examples/CMakeFiles/vil1_convolve.dir/includes_CXX.rsp
core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj: ../core/vil1/examples/vil1_convolve.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil1\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vil1_convolve.dir\vil1_convolve.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil1\examples\vil1_convolve.cxx

core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vil1_convolve.dir/vil1_convolve.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil1\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil1\examples\vil1_convolve.cxx > CMakeFiles\vil1_convolve.dir\vil1_convolve.i

core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vil1_convolve.dir/vil1_convolve.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil1\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil1\examples\vil1_convolve.cxx -o CMakeFiles\vil1_convolve.dir\vil1_convolve.s

core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.requires:

.PHONY : core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.requires

core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.provides: core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.requires
	$(MAKE) -f core\vil1\examples\CMakeFiles\vil1_convolve.dir\build.make core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.provides.build
.PHONY : core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.provides

core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.provides.build: core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj


# Object files for target vil1_convolve
vil1_convolve_OBJECTS = \
"CMakeFiles/vil1_convolve.dir/vil1_convolve.obj"

# External object files for target vil1_convolve
vil1_convolve_EXTERNAL_OBJECTS =

core/vil1/examples/vil1_convolve.exe: core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj
core/vil1/examples/vil1_convolve.exe: core/vil1/examples/CMakeFiles/vil1_convolve.dir/build.make
core/vil1/examples/vil1_convolve.exe: lib/libvil1.a
core/vil1/examples/vil1_convolve.exe: lib/libvul.a
core/vil1/examples/vil1_convolve.exe: lib/libtiff.a
core/vil1/examples/vil1_convolve.exe: lib/libjpeg.a
core/vil1/examples/vil1_convolve.exe: lib/libpng.a
core/vil1/examples/vil1_convolve.exe: lib/libz.a
core/vil1/examples/vil1_convolve.exe: lib/libvcl.a
core/vil1/examples/vil1_convolve.exe: core/vil1/examples/CMakeFiles/vil1_convolve.dir/linklibs.rsp
core/vil1/examples/vil1_convolve.exe: core/vil1/examples/CMakeFiles/vil1_convolve.dir/objects1.rsp
core/vil1/examples/vil1_convolve.exe: core/vil1/examples/CMakeFiles/vil1_convolve.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vil1_convolve.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil1\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vil1_convolve.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/vil1/examples/CMakeFiles/vil1_convolve.dir/build: core/vil1/examples/vil1_convolve.exe

.PHONY : core/vil1/examples/CMakeFiles/vil1_convolve.dir/build

core/vil1/examples/CMakeFiles/vil1_convolve.dir/requires: core/vil1/examples/CMakeFiles/vil1_convolve.dir/vil1_convolve.obj.requires

.PHONY : core/vil1/examples/CMakeFiles/vil1_convolve.dir/requires

core/vil1/examples/CMakeFiles/vil1_convolve.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil1\examples && $(CMAKE_COMMAND) -P CMakeFiles\vil1_convolve.dir\cmake_clean.cmake
.PHONY : core/vil1/examples/CMakeFiles/vil1_convolve.dir/clean

core/vil1/examples/CMakeFiles/vil1_convolve.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil1\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil1\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil1\examples\CMakeFiles\vil1_convolve.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : core/vil1/examples/CMakeFiles/vil1_convolve.dir/depend
