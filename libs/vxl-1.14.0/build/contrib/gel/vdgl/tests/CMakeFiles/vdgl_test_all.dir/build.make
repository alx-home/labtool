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
include contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/depend.make

# Include the progress variables for this target.
include contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/flags.make

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/flags.make
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/includes_CXX.rsp
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj: ../contrib/gel/vdgl/tests/test_driver.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vdgl_test_all.dir\test_driver.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_driver.cxx

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vdgl_test_all.dir/test_driver.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_driver.cxx > CMakeFiles\vdgl_test_all.dir\test_driver.i

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vdgl_test_all.dir/test_driver.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_driver.cxx -o CMakeFiles\vdgl_test_all.dir\test_driver.s

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.requires:

.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.requires

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.provides: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.requires
	$(MAKE) -f contrib\gel\vdgl\tests\CMakeFiles\vdgl_test_all.dir\build.make contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.provides.build
.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.provides

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.provides.build: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj


contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/flags.make
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/includes_CXX.rsp
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj: ../contrib/gel/vdgl/tests/test_vdgl.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vdgl_test_all.dir\test_vdgl.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_vdgl.cxx

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vdgl_test_all.dir/test_vdgl.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_vdgl.cxx > CMakeFiles\vdgl_test_all.dir\test_vdgl.i

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vdgl_test_all.dir/test_vdgl.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_vdgl.cxx -o CMakeFiles\vdgl_test_all.dir\test_vdgl.s

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.requires:

.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.requires

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.provides: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.requires
	$(MAKE) -f contrib\gel\vdgl\tests\CMakeFiles\vdgl_test_all.dir\build.make contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.provides.build
.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.provides

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.provides.build: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj


contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/flags.make
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/includes_CXX.rsp
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj: ../contrib/gel/vdgl/tests/test1_vdgl.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vdgl_test_all.dir\test1_vdgl.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test1_vdgl.cxx

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vdgl_test_all.dir/test1_vdgl.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test1_vdgl.cxx > CMakeFiles\vdgl_test_all.dir\test1_vdgl.i

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vdgl_test_all.dir/test1_vdgl.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test1_vdgl.cxx -o CMakeFiles\vdgl_test_all.dir\test1_vdgl.s

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.requires:

.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.requires

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.provides: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.requires
	$(MAKE) -f contrib\gel\vdgl\tests\CMakeFiles\vdgl_test_all.dir\build.make contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.provides.build
.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.provides

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.provides.build: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj


contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/flags.make
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/includes_CXX.rsp
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj: ../contrib/gel/vdgl/tests/test_vdgl_io.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vdgl_test_all.dir\test_vdgl_io.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_vdgl_io.cxx

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vdgl_test_all.dir/test_vdgl_io.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_vdgl_io.cxx > CMakeFiles\vdgl_test_all.dir\test_vdgl_io.i

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vdgl_test_all.dir/test_vdgl_io.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests\test_vdgl_io.cxx -o CMakeFiles\vdgl_test_all.dir\test_vdgl_io.s

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.requires:

.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.requires

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.provides: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.requires
	$(MAKE) -f contrib\gel\vdgl\tests\CMakeFiles\vdgl_test_all.dir\build.make contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.provides.build
.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.provides

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.provides.build: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj


# Object files for target vdgl_test_all
vdgl_test_all_OBJECTS = \
"CMakeFiles/vdgl_test_all.dir/test_driver.obj" \
"CMakeFiles/vdgl_test_all.dir/test_vdgl.obj" \
"CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj" \
"CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj"

# External object files for target vdgl_test_all
vdgl_test_all_EXTERNAL_OBJECTS =

contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj
contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj
contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj
contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj
contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/build.make
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvsol.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvdgl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvbl_io.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvsl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvpl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libtestlib.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvsol.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvgl_io.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvbl_io.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvsl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvgl_algo.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvgl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvbl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvul.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvnl_algo.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvnl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libnetlib.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libv3p_netlib.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: lib/libvcl.a
contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/linklibs.rsp
contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/objects1.rsp
contrib/gel/vdgl/tests/vdgl_test_all.exe: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable vdgl_test_all.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vdgl_test_all.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/build: contrib/gel/vdgl/tests/vdgl_test_all.exe

.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/build

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/requires: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_driver.obj.requires
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/requires: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl.obj.requires
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/requires: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test1_vdgl.obj.requires
contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/requires: contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/test_vdgl_io.obj.requires

.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/requires

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests && $(CMAKE_COMMAND) -P CMakeFiles\vdgl_test_all.dir\cmake_clean.cmake
.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/clean

contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\gel\vdgl\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\gel\vdgl\tests\CMakeFiles\vdgl_test_all.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/gel/vdgl/tests/CMakeFiles/vdgl_test_all.dir/depend

