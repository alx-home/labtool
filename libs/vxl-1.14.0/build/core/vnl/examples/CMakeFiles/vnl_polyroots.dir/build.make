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
include core/vnl/examples/CMakeFiles/vnl_polyroots.dir/depend.make

# Include the progress variables for this target.
include core/vnl/examples/CMakeFiles/vnl_polyroots.dir/progress.make

# Include the compile flags for this target's objects.
include core/vnl/examples/CMakeFiles/vnl_polyroots.dir/flags.make

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/flags.make
core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/includes_CXX.rsp
core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj: ../core/vnl/examples/vnl_polyroots.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vnl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vnl_polyroots.dir\vnl_polyroots.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vnl\examples\vnl_polyroots.cxx

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vnl_polyroots.dir/vnl_polyroots.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vnl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vnl\examples\vnl_polyroots.cxx > CMakeFiles\vnl_polyroots.dir\vnl_polyroots.i

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vnl_polyroots.dir/vnl_polyroots.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vnl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vnl\examples\vnl_polyroots.cxx -o CMakeFiles\vnl_polyroots.dir\vnl_polyroots.s

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.requires:

.PHONY : core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.requires

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.provides: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.requires
	$(MAKE) -f core\vnl\examples\CMakeFiles\vnl_polyroots.dir\build.make core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.provides.build
.PHONY : core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.provides

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.provides.build: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj


# Object files for target vnl_polyroots
vnl_polyroots_OBJECTS = \
"CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj"

# External object files for target vnl_polyroots
vnl_polyroots_EXTERNAL_OBJECTS =

core/vnl/examples/vnl_polyroots.exe: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj
core/vnl/examples/vnl_polyroots.exe: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/build.make
core/vnl/examples/vnl_polyroots.exe: lib/libvnl_algo.a
core/vnl/examples/vnl_polyroots.exe: lib/libvnl.a
core/vnl/examples/vnl_polyroots.exe: lib/libvul.a
core/vnl/examples/vnl_polyroots.exe: lib/libnetlib.a
core/vnl/examples/vnl_polyroots.exe: lib/libv3p_netlib.a
core/vnl/examples/vnl_polyroots.exe: lib/libvcl.a
core/vnl/examples/vnl_polyroots.exe: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/linklibs.rsp
core/vnl/examples/vnl_polyroots.exe: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/objects1.rsp
core/vnl/examples/vnl_polyroots.exe: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vnl_polyroots.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vnl\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vnl_polyroots.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/vnl/examples/CMakeFiles/vnl_polyroots.dir/build: core/vnl/examples/vnl_polyroots.exe

.PHONY : core/vnl/examples/CMakeFiles/vnl_polyroots.dir/build

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/requires: core/vnl/examples/CMakeFiles/vnl_polyroots.dir/vnl_polyroots.obj.requires

.PHONY : core/vnl/examples/CMakeFiles/vnl_polyroots.dir/requires

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vnl\examples && $(CMAKE_COMMAND) -P CMakeFiles\vnl_polyroots.dir\cmake_clean.cmake
.PHONY : core/vnl/examples/CMakeFiles/vnl_polyroots.dir/clean

core/vnl/examples/CMakeFiles/vnl_polyroots.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vnl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vnl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vnl\examples\CMakeFiles\vnl_polyroots.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : core/vnl/examples/CMakeFiles/vnl_polyroots.dir/depend

