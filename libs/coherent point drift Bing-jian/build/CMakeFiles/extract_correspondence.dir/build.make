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
include CMakeFiles/extract_correspondence.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/extract_correspondence.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/extract_correspondence.dir/flags.make

CMakeFiles/extract_correspondence.dir/extract_correspondence.obj: CMakeFiles/extract_correspondence.dir/flags.make
CMakeFiles/extract_correspondence.dir/extract_correspondence.obj: CMakeFiles/extract_correspondence.dir/includes_CXX.rsp
CMakeFiles/extract_correspondence.dir/extract_correspondence.obj: C:/workspace/libs/coherent\ point\ drift\ Bing-jian/C++/extract_correspondence.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\workspace\libs\coherent point drift Bing-jian\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/extract_correspondence.dir/extract_correspondence.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\extract_correspondence.dir\extract_correspondence.obj -c "C:\workspace\libs\coherent point drift Bing-jian\C++\extract_correspondence.cpp"

CMakeFiles/extract_correspondence.dir/extract_correspondence.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/extract_correspondence.dir/extract_correspondence.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\libs\coherent point drift Bing-jian\C++\extract_correspondence.cpp" > CMakeFiles\extract_correspondence.dir\extract_correspondence.i

CMakeFiles/extract_correspondence.dir/extract_correspondence.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/extract_correspondence.dir/extract_correspondence.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\libs\coherent point drift Bing-jian\C++\extract_correspondence.cpp" -o CMakeFiles\extract_correspondence.dir\extract_correspondence.s

CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.requires:

.PHONY : CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.requires

CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.provides: CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.requires
	$(MAKE) -f CMakeFiles\extract_correspondence.dir\build.make CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.provides.build
.PHONY : CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.provides

CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.provides.build: CMakeFiles/extract_correspondence.dir/extract_correspondence.obj


# Object files for target extract_correspondence
extract_correspondence_OBJECTS = \
"CMakeFiles/extract_correspondence.dir/extract_correspondence.obj"

# External object files for target extract_correspondence
extract_correspondence_EXTERNAL_OBJECTS =

extract_correspondence.exe: CMakeFiles/extract_correspondence.dir/extract_correspondence.obj
extract_correspondence.exe: CMakeFiles/extract_correspondence.dir/build.make
extract_correspondence.exe: CMakeFiles/extract_correspondence.dir/linklibs.rsp
extract_correspondence.exe: CMakeFiles/extract_correspondence.dir/objects1.rsp
extract_correspondence.exe: CMakeFiles/extract_correspondence.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\workspace\libs\coherent point drift Bing-jian\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable extract_correspondence.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\extract_correspondence.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/extract_correspondence.dir/build: extract_correspondence.exe

.PHONY : CMakeFiles/extract_correspondence.dir/build

CMakeFiles/extract_correspondence.dir/requires: CMakeFiles/extract_correspondence.dir/extract_correspondence.obj.requires

.PHONY : CMakeFiles/extract_correspondence.dir/requires

CMakeFiles/extract_correspondence.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\extract_correspondence.dir\cmake_clean.cmake
.PHONY : CMakeFiles/extract_correspondence.dir/clean

CMakeFiles/extract_correspondence.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\workspace\libs\coherent point drift Bing-jian\C++" "C:\workspace\libs\coherent point drift Bing-jian\C++" "C:\workspace\libs\coherent point drift Bing-jian\build" "C:\workspace\libs\coherent point drift Bing-jian\build" "C:\workspace\libs\coherent point drift Bing-jian\build\CMakeFiles\extract_correspondence.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/extract_correspondence.dir/depend

