# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.3

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
CMAKE_SOURCE_DIR = "C:\workspace\libs\coherent point drift Bing-jian\C++"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\workspace\libs\coherent point drift Bing-jian\build"

# Include any dependencies generated for this target.
include CMakeFiles/test_gauss_transform.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_gauss_transform.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_gauss_transform.dir/flags.make

CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj: CMakeFiles/test_gauss_transform.dir/flags.make
CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj: CMakeFiles/test_gauss_transform.dir/includes_CXX.rsp
CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj: C:/workspace/libs/coherent\ point\ drift\ Bing-jian/C++/test_gauss_transform.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\workspace\libs\coherent point drift Bing-jian\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\test_gauss_transform.dir\test_gauss_transform.obj -c "C:\workspace\libs\coherent point drift Bing-jian\C++\test_gauss_transform.cpp"

CMakeFiles/test_gauss_transform.dir/test_gauss_transform.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_gauss_transform.dir/test_gauss_transform.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\libs\coherent point drift Bing-jian\C++\test_gauss_transform.cpp" > CMakeFiles\test_gauss_transform.dir\test_gauss_transform.i

CMakeFiles/test_gauss_transform.dir/test_gauss_transform.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_gauss_transform.dir/test_gauss_transform.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\libs\coherent point drift Bing-jian\C++\test_gauss_transform.cpp" -o CMakeFiles\test_gauss_transform.dir\test_gauss_transform.s

CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.requires:

.PHONY : CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.requires

CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.provides: CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.requires
	$(MAKE) -f CMakeFiles\test_gauss_transform.dir\build.make CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.provides.build
.PHONY : CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.provides

CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.provides.build: CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj


# Object files for target test_gauss_transform
test_gauss_transform_OBJECTS = \
"CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj"

# External object files for target test_gauss_transform
test_gauss_transform_EXTERNAL_OBJECTS =

test_gauss_transform.exe: CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj
test_gauss_transform.exe: CMakeFiles/test_gauss_transform.dir/build.make
test_gauss_transform.exe: CMakeFiles/test_gauss_transform.dir/linklibs.rsp
test_gauss_transform.exe: CMakeFiles/test_gauss_transform.dir/objects1.rsp
test_gauss_transform.exe: CMakeFiles/test_gauss_transform.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\workspace\libs\coherent point drift Bing-jian\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_gauss_transform.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test_gauss_transform.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_gauss_transform.dir/build: test_gauss_transform.exe

.PHONY : CMakeFiles/test_gauss_transform.dir/build

CMakeFiles/test_gauss_transform.dir/requires: CMakeFiles/test_gauss_transform.dir/test_gauss_transform.obj.requires

.PHONY : CMakeFiles/test_gauss_transform.dir/requires

CMakeFiles/test_gauss_transform.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\test_gauss_transform.dir\cmake_clean.cmake
.PHONY : CMakeFiles/test_gauss_transform.dir/clean

CMakeFiles/test_gauss_transform.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\workspace\libs\coherent point drift Bing-jian\C++" "C:\workspace\libs\coherent point drift Bing-jian\C++" "C:\workspace\libs\coherent point drift Bing-jian\build" "C:\workspace\libs\coherent point drift Bing-jian\build" "C:\workspace\libs\coherent point drift Bing-jian\build\CMakeFiles\test_gauss_transform.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/test_gauss_transform.dir/depend

