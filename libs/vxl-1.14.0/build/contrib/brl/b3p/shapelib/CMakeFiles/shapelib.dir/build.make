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
include contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/depend.make

# Include the progress variables for this target.
include contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/flags.make

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/flags.make
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/includes_C.rsp
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj: ../contrib/brl/b3p/shapelib/shptree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shapelib.dir\shptree.obj   -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\shptree.c

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shapelib.dir/shptree.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\shptree.c > CMakeFiles\shapelib.dir\shptree.i

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shapelib.dir/shptree.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\shptree.c -o CMakeFiles\shapelib.dir\shptree.s

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.requires:

.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.requires

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.provides: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.requires
	$(MAKE) -f contrib\brl\b3p\shapelib\CMakeFiles\shapelib.dir\build.make contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.provides.build
.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.provides

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.provides.build: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj


contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/flags.make
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/includes_C.rsp
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj: ../contrib/brl/b3p/shapelib/shpopen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shapelib.dir\shpopen.obj   -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\shpopen.c

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shapelib.dir/shpopen.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\shpopen.c > CMakeFiles\shapelib.dir\shpopen.i

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shapelib.dir/shpopen.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\shpopen.c -o CMakeFiles\shapelib.dir\shpopen.s

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.requires:

.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.requires

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.provides: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.requires
	$(MAKE) -f contrib\brl\b3p\shapelib\CMakeFiles\shapelib.dir\build.make contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.provides.build
.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.provides

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.provides.build: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj


contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/flags.make
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/includes_C.rsp
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj: ../contrib/brl/b3p/shapelib/dbfopen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shapelib.dir\dbfopen.obj   -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\dbfopen.c

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shapelib.dir/dbfopen.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\dbfopen.c > CMakeFiles\shapelib.dir\dbfopen.i

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shapelib.dir/dbfopen.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib\dbfopen.c -o CMakeFiles\shapelib.dir\dbfopen.s

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.requires:

.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.requires

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.provides: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.requires
	$(MAKE) -f contrib\brl\b3p\shapelib\CMakeFiles\shapelib.dir\build.make contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.provides.build
.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.provides

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.provides.build: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj


# Object files for target shapelib
shapelib_OBJECTS = \
"CMakeFiles/shapelib.dir/shptree.obj" \
"CMakeFiles/shapelib.dir/shpopen.obj" \
"CMakeFiles/shapelib.dir/dbfopen.obj"

# External object files for target shapelib
shapelib_EXTERNAL_OBJECTS =

lib/libshapelib.a: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj
lib/libshapelib.a: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj
lib/libshapelib.a: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj
lib/libshapelib.a: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/build.make
lib/libshapelib.a: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library ..\..\..\..\lib\libshapelib.a"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && $(CMAKE_COMMAND) -P CMakeFiles\shapelib.dir\cmake_clean_target.cmake
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\shapelib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/build: lib/libshapelib.a

.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/build

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/requires: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shptree.obj.requires
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/requires: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/shpopen.obj.requires
contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/requires: contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/dbfopen.obj.requires

.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/requires

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib && $(CMAKE_COMMAND) -P CMakeFiles\shapelib.dir\cmake_clean.cmake
.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/clean

contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\brl\b3p\shapelib C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\brl\b3p\shapelib\CMakeFiles\shapelib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/brl/b3p/shapelib/CMakeFiles/shapelib.dir/depend

