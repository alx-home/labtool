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
include contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/depend.make

# Include the progress variables for this target.
include contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/flags.make

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/flags.make
contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/includes_CXX.rsp
contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj: ../contrib/oxl/osl/tests/test_include.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\osl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\osl_test_include.dir\test_include.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\osl\tests\test_include.cxx

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/osl_test_include.dir/test_include.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\osl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\osl\tests\test_include.cxx > CMakeFiles\osl_test_include.dir\test_include.i

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/osl_test_include.dir/test_include.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\osl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\osl\tests\test_include.cxx -o CMakeFiles\osl_test_include.dir\test_include.s

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.requires:

.PHONY : contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.requires

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.provides: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.requires
	$(MAKE) -f contrib\oxl\osl\tests\CMakeFiles\osl_test_include.dir\build.make contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.provides.build
.PHONY : contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.provides

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.provides.build: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj


# Object files for target osl_test_include
osl_test_include_OBJECTS = \
"CMakeFiles/osl_test_include.dir/test_include.obj"

# External object files for target osl_test_include
osl_test_include_EXTERNAL_OBJECTS =

contrib/oxl/osl/tests/osl_test_include.exe: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj
contrib/oxl/osl/tests/osl_test_include.exe: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/build.make
contrib/oxl/osl/tests/osl_test_include.exe: lib/libosl.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libvnl_algo.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libnetlib.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libv3p_netlib.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libvnl.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libvgl.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libvil1.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libtiff.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libjpeg.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libpng.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libz.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libvbl.a
contrib/oxl/osl/tests/osl_test_include.exe: lib/libvcl.a
contrib/oxl/osl/tests/osl_test_include.exe: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/linklibs.rsp
contrib/oxl/osl/tests/osl_test_include.exe: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/objects1.rsp
contrib/oxl/osl/tests/osl_test_include.exe: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable osl_test_include.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\osl\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\osl_test_include.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/build: contrib/oxl/osl/tests/osl_test_include.exe

.PHONY : contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/build

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/requires: contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/test_include.obj.requires

.PHONY : contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/requires

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\osl\tests && $(CMAKE_COMMAND) -P CMakeFiles\osl_test_include.dir\cmake_clean.cmake
.PHONY : contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/clean

contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\osl\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\osl\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\osl\tests\CMakeFiles\osl_test_include.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/oxl/osl/tests/CMakeFiles/osl_test_include.dir/depend

