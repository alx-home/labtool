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
include contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/depend.make

# Include the progress variables for this target.
include contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/flags.make

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/flags.make
contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/includes_CXX.rsp
contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj: ../contrib/rpl/rgrl/examples/registration_landmark.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\registration_landmark.dir\registration_landmark.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples\registration_landmark.cxx

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/registration_landmark.dir/registration_landmark.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples\registration_landmark.cxx > CMakeFiles\registration_landmark.dir\registration_landmark.i

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/registration_landmark.dir/registration_landmark.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples\registration_landmark.cxx -o CMakeFiles\registration_landmark.dir\registration_landmark.s

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.requires:

.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.requires

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.provides: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.requires
	$(MAKE) -f contrib\rpl\rgrl\examples\CMakeFiles\registration_landmark.dir\build.make contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.provides.build
.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.provides

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.provides.build: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj


# Object files for target registration_landmark
registration_landmark_OBJECTS = \
"CMakeFiles/registration_landmark.dir/registration_landmark.obj"

# External object files for target registration_landmark
registration_landmark_EXTERNAL_OBJECTS =

contrib/rpl/rgrl/examples/registration_landmark.exe: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj
contrib/rpl/rgrl/examples/registration_landmark.exe: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/build.make
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/librgrl.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libtestlib.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/librrel.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvgl.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/librsdl.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvil3d.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvsl.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvil.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libgeotiff.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libtiff.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libjpeg.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libpng.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libz.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvnl_algo.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libnetlib.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libv3p_netlib.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvnl.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvbl.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvul.a
contrib/rpl/rgrl/examples/registration_landmark.exe: lib/libvcl.a
contrib/rpl/rgrl/examples/registration_landmark.exe: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/linklibs.rsp
contrib/rpl/rgrl/examples/registration_landmark.exe: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/objects1.rsp
contrib/rpl/rgrl/examples/registration_landmark.exe: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable registration_landmark.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\registration_landmark.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/build: contrib/rpl/rgrl/examples/registration_landmark.exe

.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/build

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/requires: contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/registration_landmark.obj.requires

.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/requires

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples && $(CMAKE_COMMAND) -P CMakeFiles\registration_landmark.dir\cmake_clean.cmake
.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/clean

contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\rpl\rgrl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\rpl\rgrl\examples\CMakeFiles\registration_landmark.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/rpl/rgrl/examples/CMakeFiles/registration_landmark.dir/depend

