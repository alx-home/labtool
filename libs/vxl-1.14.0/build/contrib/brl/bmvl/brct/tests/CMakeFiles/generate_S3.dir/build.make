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
include contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/depend.make

# Include the progress variables for this target.
include contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/flags.make

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/flags.make
contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/includes_CXX.rsp
contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj: ../contrib/brl/bmvl/brct/tests/generate_S3.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bmvl\brct\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\generate_S3.dir\generate_S3.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bmvl\brct\tests\generate_S3.cxx

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/generate_S3.dir/generate_S3.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bmvl\brct\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bmvl\brct\tests\generate_S3.cxx > CMakeFiles\generate_S3.dir\generate_S3.i

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/generate_S3.dir/generate_S3.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bmvl\brct\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bmvl\brct\tests\generate_S3.cxx -o CMakeFiles\generate_S3.dir\generate_S3.s

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.requires:

.PHONY : contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.requires

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.provides: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.requires
	$(MAKE) -f contrib\brl\bmvl\brct\tests\CMakeFiles\generate_S3.dir\build.make contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.provides.build
.PHONY : contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.provides

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.provides.build: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj


# Object files for target generate_S3
generate_S3_OBJECTS = \
"CMakeFiles/generate_S3.dir/generate_S3.obj"

# External object files for target generate_S3
generate_S3_EXTERNAL_OBJECTS =

contrib/brl/bmvl/brct/tests/generate_S3.exe: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj
contrib/brl/bmvl/brct/tests/generate_S3.exe: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/build.make
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbrct.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libsdet.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbtol.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbil_algo.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbrip.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvil_algo.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbsta.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/librrel.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbsol.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvpgl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvnl_io.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbgeo.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libgevd.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvtol.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libmvl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbdgl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvdgl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvsol.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvul.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvgl_io.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvbl_io.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvsl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libbugl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvil.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libgeotiff.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvil1.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libtiff.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libjpeg.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libpng.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libz.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvgl_algo.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvgl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvnl_algo.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libnetlib.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libv3p_netlib.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvnl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvbl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: lib/libvcl.a
contrib/brl/bmvl/brct/tests/generate_S3.exe: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/linklibs.rsp
contrib/brl/bmvl/brct/tests/generate_S3.exe: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/objects1.rsp
contrib/brl/bmvl/brct/tests/generate_S3.exe: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable generate_S3.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bmvl\brct\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\generate_S3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/build: contrib/brl/bmvl/brct/tests/generate_S3.exe

.PHONY : contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/build

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/requires: contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/generate_S3.obj.requires

.PHONY : contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/requires

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bmvl\brct\tests && $(CMAKE_COMMAND) -P CMakeFiles\generate_S3.dir\cmake_clean.cmake
.PHONY : contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/clean

contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bmvl\brct\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bmvl\brct\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bmvl\brct\tests\CMakeFiles\generate_S3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/brl/bmvl/brct/tests/CMakeFiles/generate_S3.dir/depend

