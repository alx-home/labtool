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
include contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/depend.make

# Include the progress variables for this target.
include contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/flags.make

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/flags.make
contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/includes_CXX.rsp
contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj: ../contrib/brl/bbas/bdpg/tests/test_driver.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bdpg_test_all.dir\test_driver.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bdpg\tests\test_driver.cxx

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bdpg_test_all.dir/test_driver.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bdpg\tests\test_driver.cxx > CMakeFiles\bdpg_test_all.dir\test_driver.i

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bdpg_test_all.dir/test_driver.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bdpg\tests\test_driver.cxx -o CMakeFiles\bdpg_test_all.dir\test_driver.s

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.requires:

.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.requires

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.provides: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.requires
	$(MAKE) -f contrib\brl\bbas\bdpg\tests\CMakeFiles\bdpg_test_all.dir\build.make contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.provides.build
.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.provides

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.provides.build: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj


contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/flags.make
contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/includes_CXX.rsp
contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj: ../contrib/brl/bbas/bdpg/tests/test_array_dynamic_prg.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bdpg_test_all.dir\test_array_dynamic_prg.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bdpg\tests\test_array_dynamic_prg.cxx

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bdpg\tests\test_array_dynamic_prg.cxx > CMakeFiles\bdpg_test_all.dir\test_array_dynamic_prg.i

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bdpg\tests\test_array_dynamic_prg.cxx -o CMakeFiles\bdpg_test_all.dir\test_array_dynamic_prg.s

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.requires:

.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.requires

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.provides: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.requires
	$(MAKE) -f contrib\brl\bbas\bdpg\tests\CMakeFiles\bdpg_test_all.dir\build.make contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.provides.build
.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.provides

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.provides.build: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj


# Object files for target bdpg_test_all
bdpg_test_all_OBJECTS = \
"CMakeFiles/bdpg_test_all.dir/test_driver.obj" \
"CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj"

# External object files for target bdpg_test_all
bdpg_test_all_EXTERNAL_OBJECTS =

contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/build.make
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: lib/libbdpg.a
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: lib/libvnl.a
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: lib/libtestlib.a
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: lib/libvbl.a
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: lib/libvcl.a
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/linklibs.rsp
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/objects1.rsp
contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bdpg_test_all.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bdpg_test_all.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/build: contrib/brl/bbas/bdpg/tests/bdpg_test_all.exe

.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/build

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/requires: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_driver.obj.requires
contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/requires: contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/test_array_dynamic_prg.obj.requires

.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/requires

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests && $(CMAKE_COMMAND) -P CMakeFiles\bdpg_test_all.dir\cmake_clean.cmake
.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/clean

contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bbas\bdpg\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bbas\bdpg\tests\CMakeFiles\bdpg_test_all.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/brl/bbas/bdpg/tests/CMakeFiles/bdpg_test_all.dir/depend

