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
include contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/depend.make

# Include the progress variables for this target.
include contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/flags.make

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/flags.make
contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/includes_CXX.rsp
contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj: ../contrib/brl/bseg/boxm/algo/boxm_merge_mog.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\boxm_algo.dir\boxm_merge_mog.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bseg\boxm\algo\boxm_merge_mog.cxx

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boxm_algo.dir/boxm_merge_mog.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bseg\boxm\algo\boxm_merge_mog.cxx > CMakeFiles\boxm_algo.dir\boxm_merge_mog.i

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boxm_algo.dir/boxm_merge_mog.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bseg\boxm\algo\boxm_merge_mog.cxx -o CMakeFiles\boxm_algo.dir\boxm_merge_mog.s

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.requires:

.PHONY : contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.requires

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.provides: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.requires
	$(MAKE) -f contrib\brl\bseg\boxm\algo\CMakeFiles\boxm_algo.dir\build.make contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.provides.build
.PHONY : contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.provides

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.provides.build: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj


# Object files for target boxm_algo
boxm_algo_OBJECTS = \
"CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj"

# External object files for target boxm_algo
boxm_algo_EXTERNAL_OBJECTS =

lib/libboxm_algo.a: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj
lib/libboxm_algo.a: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/build.make
lib/libboxm_algo.a: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\..\..\..\lib\libboxm_algo.a"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo && $(CMAKE_COMMAND) -P CMakeFiles\boxm_algo.dir\cmake_clean_target.cmake
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\boxm_algo.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/build: lib/libboxm_algo.a

.PHONY : contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/build

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/requires: contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/boxm_merge_mog.obj.requires

.PHONY : contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/requires

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo && $(CMAKE_COMMAND) -P CMakeFiles\boxm_algo.dir\cmake_clean.cmake
.PHONY : contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/clean

contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\bseg\boxm\algo C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\bseg\boxm\algo\CMakeFiles\boxm_algo.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/brl/bseg/boxm/algo/CMakeFiles/boxm_algo.dir/depend

