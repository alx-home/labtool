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
include core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/depend.make

# Include the progress variables for this target.
include core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/progress.make

# Include the compile flags for this target's objects.
include core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/flags.make

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/flags.make
core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/includes_CXX.rsp
core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj: ../core/vidl/examples/vidl_transcode_video.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vidl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vidl_transcode_video.dir\vidl_transcode_video.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vidl\examples\vidl_transcode_video.cxx

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vidl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vidl\examples\vidl_transcode_video.cxx > CMakeFiles\vidl_transcode_video.dir\vidl_transcode_video.i

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vidl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vidl\examples\vidl_transcode_video.cxx -o CMakeFiles\vidl_transcode_video.dir\vidl_transcode_video.s

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.requires:

.PHONY : core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.requires

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.provides: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.requires
	$(MAKE) -f core\vidl\examples\CMakeFiles\vidl_transcode_video.dir\build.make core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.provides.build
.PHONY : core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.provides

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.provides.build: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj


# Object files for target vidl_transcode_video
vidl_transcode_video_OBJECTS = \
"CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj"

# External object files for target vidl_transcode_video
vidl_transcode_video_EXTERNAL_OBJECTS =

core/vidl/examples/vidl_transcode_video.exe: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj
core/vidl/examples/vidl_transcode_video.exe: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/build.make
core/vidl/examples/vidl_transcode_video.exe: lib/libvidl.a
core/vidl/examples/vidl_transcode_video.exe: lib/libvul.a
core/vidl/examples/vidl_transcode_video.exe: lib/libvil.a
core/vidl/examples/vidl_transcode_video.exe: lib/libgeotiff.a
core/vidl/examples/vidl_transcode_video.exe: lib/libtiff.a
core/vidl/examples/vidl_transcode_video.exe: lib/libjpeg.a
core/vidl/examples/vidl_transcode_video.exe: lib/libpng.a
core/vidl/examples/vidl_transcode_video.exe: lib/libz.a
core/vidl/examples/vidl_transcode_video.exe: lib/libvbl.a
core/vidl/examples/vidl_transcode_video.exe: lib/libvcl.a
core/vidl/examples/vidl_transcode_video.exe: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/linklibs.rsp
core/vidl/examples/vidl_transcode_video.exe: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/objects1.rsp
core/vidl/examples/vidl_transcode_video.exe: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vidl_transcode_video.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vidl\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vidl_transcode_video.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/build: core/vidl/examples/vidl_transcode_video.exe

.PHONY : core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/build

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/requires: core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/vidl_transcode_video.obj.requires

.PHONY : core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/requires

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vidl\examples && $(CMAKE_COMMAND) -P CMakeFiles\vidl_transcode_video.dir\cmake_clean.cmake
.PHONY : core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/clean

core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vidl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vidl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vidl\examples\CMakeFiles\vidl_transcode_video.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : core/vidl/examples/CMakeFiles/vidl_transcode_video.dir/depend
