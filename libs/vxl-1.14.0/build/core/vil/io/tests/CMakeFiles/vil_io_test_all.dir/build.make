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
include core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/depend.make

# Include the progress variables for this target.
include core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/progress.make

# Include the compile flags for this target's objects.
include core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/flags.make

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/flags.make
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/includes_CXX.rsp
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj: ../core/vil/io/tests/test_driver.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vil_io_test_all.dir\test_driver.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_driver.cxx

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vil_io_test_all.dir/test_driver.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_driver.cxx > CMakeFiles\vil_io_test_all.dir\test_driver.i

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vil_io_test_all.dir/test_driver.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_driver.cxx -o CMakeFiles\vil_io_test_all.dir\test_driver.s

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.requires:

.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.requires

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.provides: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.requires
	$(MAKE) -f core\vil\io\tests\CMakeFiles\vil_io_test_all.dir\build.make core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.provides.build
.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.provides

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.provides.build: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj


core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/flags.make
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/includes_CXX.rsp
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj: ../core/vil/io/tests/test_memory_chunk_io.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vil_io_test_all.dir\test_memory_chunk_io.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_memory_chunk_io.cxx

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_memory_chunk_io.cxx > CMakeFiles\vil_io_test_all.dir\test_memory_chunk_io.i

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_memory_chunk_io.cxx -o CMakeFiles\vil_io_test_all.dir\test_memory_chunk_io.s

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.requires:

.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.requires

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.provides: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.requires
	$(MAKE) -f core\vil\io\tests\CMakeFiles\vil_io_test_all.dir\build.make core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.provides.build
.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.provides

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.provides.build: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj


core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/flags.make
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/includes_CXX.rsp
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj: ../core/vil/io/tests/test_image_view_io.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vil_io_test_all.dir\test_image_view_io.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_image_view_io.cxx

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vil_io_test_all.dir/test_image_view_io.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_image_view_io.cxx > CMakeFiles\vil_io_test_all.dir\test_image_view_io.i

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vil_io_test_all.dir/test_image_view_io.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests\test_image_view_io.cxx -o CMakeFiles\vil_io_test_all.dir\test_image_view_io.s

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.requires:

.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.requires

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.provides: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.requires
	$(MAKE) -f core\vil\io\tests\CMakeFiles\vil_io_test_all.dir\build.make core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.provides.build
.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.provides

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.provides.build: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj


# Object files for target vil_io_test_all
vil_io_test_all_OBJECTS = \
"CMakeFiles/vil_io_test_all.dir/test_driver.obj" \
"CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj" \
"CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj"

# External object files for target vil_io_test_all
vil_io_test_all_EXTERNAL_OBJECTS =

core/vil/io/tests/vil_io_test_all.exe: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj
core/vil/io/tests/vil_io_test_all.exe: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj
core/vil/io/tests/vil_io_test_all.exe: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj
core/vil/io/tests/vil_io_test_all.exe: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/build.make
core/vil/io/tests/vil_io_test_all.exe: lib/libvil_io.a
core/vil/io/tests/vil_io_test_all.exe: lib/libvpl.a
core/vil/io/tests/vil_io_test_all.exe: lib/libtestlib.a
core/vil/io/tests/vil_io_test_all.exe: lib/libvil.a
core/vil/io/tests/vil_io_test_all.exe: lib/libgeotiff.a
core/vil/io/tests/vil_io_test_all.exe: lib/libtiff.a
core/vil/io/tests/vil_io_test_all.exe: lib/libjpeg.a
core/vil/io/tests/vil_io_test_all.exe: lib/libpng.a
core/vil/io/tests/vil_io_test_all.exe: lib/libz.a
core/vil/io/tests/vil_io_test_all.exe: lib/libvsl.a
core/vil/io/tests/vil_io_test_all.exe: lib/libvcl.a
core/vil/io/tests/vil_io_test_all.exe: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/linklibs.rsp
core/vil/io/tests/vil_io_test_all.exe: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/objects1.rsp
core/vil/io/tests/vil_io_test_all.exe: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable vil_io_test_all.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vil_io_test_all.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/build: core/vil/io/tests/vil_io_test_all.exe

.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/build

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/requires: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_driver.obj.requires
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/requires: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_memory_chunk_io.obj.requires
core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/requires: core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/test_image_view_io.obj.requires

.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/requires

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests && $(CMAKE_COMMAND) -P CMakeFiles\vil_io_test_all.dir\cmake_clean.cmake
.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/clean

core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\core\vil\io\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\core\vil\io\tests\CMakeFiles\vil_io_test_all.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : core/vil/io/tests/CMakeFiles/vil_io_test_all.dir/depend

