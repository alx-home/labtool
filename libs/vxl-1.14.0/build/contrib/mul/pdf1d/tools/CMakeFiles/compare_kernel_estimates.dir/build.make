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
include contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/depend.make

# Include the progress variables for this target.
include contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/flags.make

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/flags.make
contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/includes_CXX.rsp
contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj: ../contrib/mul/pdf1d/tools/compare_kernel_estimates.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\pdf1d\tools && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\compare_kernel_estimates.dir\compare_kernel_estimates.obj -c C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\pdf1d\tools\compare_kernel_estimates.cxx

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.i"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\pdf1d\tools && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\pdf1d\tools\compare_kernel_estimates.cxx > CMakeFiles\compare_kernel_estimates.dir\compare_kernel_estimates.i

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.s"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\pdf1d\tools && C:\PROGRA~1\MINGW-~1\X86_64~1.2-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\pdf1d\tools\compare_kernel_estimates.cxx -o CMakeFiles\compare_kernel_estimates.dir\compare_kernel_estimates.s

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.requires:

.PHONY : contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.requires

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.provides: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.requires
	$(MAKE) -f contrib\mul\pdf1d\tools\CMakeFiles\compare_kernel_estimates.dir\build.make contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.provides.build
.PHONY : contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.provides

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.provides.build: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj


# Object files for target compare_kernel_estimates
compare_kernel_estimates_OBJECTS = \
"CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj"

# External object files for target compare_kernel_estimates
compare_kernel_estimates_EXTERNAL_OBJECTS =

contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/build.make
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libpdf1d.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libmbl.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvnl.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvnl_algo.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libnetlib.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libv3p_netlib.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvgl_io.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvgl.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvbl_io.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvil_io.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvil.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libgeotiff.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libtiff.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libjpeg.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libpng.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libz.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvul.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvbl.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvnl_io.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvnl.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvsl.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: lib/libvcl.a
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/linklibs.rsp
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/objects1.rsp
contrib/mul/pdf1d/tools/compare_kernel_estimates.exe: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compare_kernel_estimates.exe"
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\pdf1d\tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\compare_kernel_estimates.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/build: contrib/mul/pdf1d/tools/compare_kernel_estimates.exe

.PHONY : contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/build

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/requires: contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/compare_kernel_estimates.obj.requires

.PHONY : contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/requires

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/clean:
	cd /d C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\pdf1d\tools && $(CMAKE_COMMAND) -P CMakeFiles\compare_kernel_estimates.dir\cmake_clean.cmake
.PHONY : contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/clean

contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\alex\Documents\chu\libs\vxl-1.14.0 C:\Users\alex\Documents\chu\libs\vxl-1.14.0\contrib\mul\pdf1d\tools C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\pdf1d\tools C:\Users\alex\Documents\chu\libs\vxl-1.14.0\build\contrib\mul\pdf1d\tools\CMakeFiles\compare_kernel_estimates.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/mul/pdf1d/tools/CMakeFiles/compare_kernel_estimates.dir/depend

