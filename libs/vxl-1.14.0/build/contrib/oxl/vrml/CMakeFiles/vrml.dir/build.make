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
include contrib/oxl/vrml/CMakeFiles/vrml.dir/depend.make

# Include the progress variables for this target.
include contrib/oxl/vrml/CMakeFiles/vrml.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/oxl/vrml/CMakeFiles/vrml.dir/flags.make

contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj: contrib/oxl/vrml/CMakeFiles/vrml.dir/flags.make
contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj: contrib/oxl/vrml/CMakeFiles/vrml.dir/includes_CXX.rsp
contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj: ../contrib/oxl/vrml/vrml_out.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vrml.dir\vrml_out.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\vrml\vrml_out.cxx

contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vrml.dir/vrml_out.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\vrml\vrml_out.cxx > CMakeFiles\vrml.dir\vrml_out.i

contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vrml.dir/vrml_out.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\vrml\vrml_out.cxx -o CMakeFiles\vrml.dir\vrml_out.s

contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.requires:

.PHONY : contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.requires

contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.provides: contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.requires
	$(MAKE) -f contrib\oxl\vrml\CMakeFiles\vrml.dir\build.make contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.provides.build
.PHONY : contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.provides

contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.provides.build: contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj


# Object files for target vrml
vrml_OBJECTS = \
"CMakeFiles/vrml.dir/vrml_out.obj"

# External object files for target vrml
vrml_EXTERNAL_OBJECTS =

lib/libvrml.a: contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj
lib/libvrml.a: contrib/oxl/vrml/CMakeFiles/vrml.dir/build.make
lib/libvrml.a: contrib/oxl/vrml/CMakeFiles/vrml.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\..\lib\libvrml.a"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml && $(CMAKE_COMMAND) -P CMakeFiles\vrml.dir\cmake_clean_target.cmake
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vrml.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/oxl/vrml/CMakeFiles/vrml.dir/build: lib/libvrml.a

.PHONY : contrib/oxl/vrml/CMakeFiles/vrml.dir/build

contrib/oxl/vrml/CMakeFiles/vrml.dir/requires: contrib/oxl/vrml/CMakeFiles/vrml.dir/vrml_out.obj.requires

.PHONY : contrib/oxl/vrml/CMakeFiles/vrml.dir/requires

contrib/oxl/vrml/CMakeFiles/vrml.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml && $(CMAKE_COMMAND) -P CMakeFiles\vrml.dir\cmake_clean.cmake
.PHONY : contrib/oxl/vrml/CMakeFiles/vrml.dir/clean

contrib/oxl/vrml/CMakeFiles/vrml.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\oxl\vrml C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\oxl\vrml\CMakeFiles\vrml.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/oxl/vrml/CMakeFiles/vrml.dir/depend
