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
include contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/depend.make

# Include the progress variables for this target.
include contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/flags.make

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/flags.make
contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/includes_CXX.rsp
contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj: ../contrib/brl/b3p/expatpp/expatpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\expatpp.dir\expatpp.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\expatpp\expatpp.cpp

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expatpp.dir/expatpp.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\expatpp\expatpp.cpp > CMakeFiles\expatpp.dir\expatpp.i

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expatpp.dir/expatpp.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\expatpp\expatpp.cpp -o CMakeFiles\expatpp.dir\expatpp.s

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.requires:

.PHONY : contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.requires

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.provides: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.requires
	$(MAKE) -f contrib\brl\b3p\expatpp\CMakeFiles\expatpp.dir\build.make contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.provides.build
.PHONY : contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.provides

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.provides.build: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj


# Object files for target expatpp
expatpp_OBJECTS = \
"CMakeFiles/expatpp.dir/expatpp.obj"

# External object files for target expatpp
expatpp_EXTERNAL_OBJECTS =

lib/libexpatpp.a: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj
lib/libexpatpp.a: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/build.make
lib/libexpatpp.a: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\..\..\lib\libexpatpp.a"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp && $(CMAKE_COMMAND) -P CMakeFiles\expatpp.dir\cmake_clean_target.cmake
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\expatpp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/build: lib/libexpatpp.a

.PHONY : contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/build

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/requires: contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/expatpp.obj.requires

.PHONY : contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/requires

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp && $(CMAKE_COMMAND) -P CMakeFiles\expatpp.dir\cmake_clean.cmake
.PHONY : contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/clean

contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\expatpp C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\expatpp\CMakeFiles\expatpp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/brl/b3p/expatpp/CMakeFiles/expatpp.dir/depend
