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
include core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/depend.make

# Include the progress variables for this target.
include core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/progress.make

# Include the compile flags for this target's objects.
include core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/flags.make

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/flags.make
core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/includes_CXX.rsp
core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj: ../core/examples/vnl_calc/vnl_calc.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\vnl_calc && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vnl_calc.dir\vnl_calc.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples\vnl_calc\vnl_calc.cxx

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vnl_calc.dir/vnl_calc.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\vnl_calc && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples\vnl_calc\vnl_calc.cxx > CMakeFiles\vnl_calc.dir\vnl_calc.i

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vnl_calc.dir/vnl_calc.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\vnl_calc && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples\vnl_calc\vnl_calc.cxx -o CMakeFiles\vnl_calc.dir\vnl_calc.s

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.requires:

.PHONY : core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.requires

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.provides: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.requires
	$(MAKE) -f core\examples\vnl_calc\CMakeFiles\vnl_calc.dir\build.make core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.provides.build
.PHONY : core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.provides

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.provides.build: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj


# Object files for target vnl_calc
vnl_calc_OBJECTS = \
"CMakeFiles/vnl_calc.dir/vnl_calc.obj"

# External object files for target vnl_calc
vnl_calc_EXTERNAL_OBJECTS =

core/examples/vnl_calc/vnl_calc.exe: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj
core/examples/vnl_calc/vnl_calc.exe: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/build.make
core/examples/vnl_calc/vnl_calc.exe: lib/libvnl_algo.a
core/examples/vnl_calc/vnl_calc.exe: lib/libvnl.a
core/examples/vnl_calc/vnl_calc.exe: lib/libvcl.a
core/examples/vnl_calc/vnl_calc.exe: lib/libnetlib.a
core/examples/vnl_calc/vnl_calc.exe: lib/libv3p_netlib.a
core/examples/vnl_calc/vnl_calc.exe: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/linklibs.rsp
core/examples/vnl_calc/vnl_calc.exe: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/objects1.rsp
core/examples/vnl_calc/vnl_calc.exe: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vnl_calc.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\vnl_calc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vnl_calc.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/build: core/examples/vnl_calc/vnl_calc.exe

.PHONY : core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/build

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/requires: core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/vnl_calc.obj.requires

.PHONY : core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/requires

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\vnl_calc && $(CMAKE_COMMAND) -P CMakeFiles\vnl_calc.dir\cmake_clean.cmake
.PHONY : core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/clean

core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\examples\vnl_calc C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\vnl_calc C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\examples\vnl_calc\CMakeFiles\vnl_calc.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : core/examples/vnl_calc/CMakeFiles/vnl_calc.dir/depend

