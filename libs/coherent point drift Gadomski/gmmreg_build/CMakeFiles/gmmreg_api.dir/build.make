# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = "C:\workspace\coherent point drift\gmmreg_src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\workspace\coherent point drift\gmmreg_build"

# Include any dependencies generated for this target.
include CMakeFiles/gmmreg_api.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gmmreg_api.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gmmreg_api.dir/flags.make

CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_utils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_utils.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_utils.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_utils.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_utils.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_utils.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_utils.i

CMakeFiles/gmmreg_api.dir/gmmreg_utils.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_utils.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_utils.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_utils.s

CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj

CMakeFiles/gmmreg_api.dir/gmmreg_base.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_base.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_base.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_base.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_base.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_base.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_base.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_base.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_base.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_base.i

CMakeFiles/gmmreg_api.dir/gmmreg_base.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_base.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_base.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_base.s

CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_base.obj

CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_cpd.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_cpd.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_cpd.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_cpd.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_cpd.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_cpd.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_cpd.i

CMakeFiles/gmmreg_api.dir/gmmreg_cpd.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_cpd.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_cpd.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_cpd.s

CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj

CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_tps.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_tps.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_tps.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_tps.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_tps.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_tps.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_tps.i

CMakeFiles/gmmreg_api.dir/gmmreg_tps.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_tps.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_tps.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_tps.s

CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj

CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_tps_func.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_tps_func.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_tps_func.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_tps_func.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_tps_func.i

CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_tps_func.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_tps_func.s

CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj

CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_grbf.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_grbf.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_grbf.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_grbf.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_grbf.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_grbf.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_grbf.i

CMakeFiles/gmmreg_api.dir/gmmreg_grbf.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_grbf.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_grbf.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_grbf.s

CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj

CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_grbf_func.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_grbf_func.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_grbf_func.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_grbf_func.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_grbf_func.i

CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_grbf_func.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_grbf_func.s

CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj

CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_rigid.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_rigid.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_rigid.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_rigid.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_rigid.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_rigid.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_rigid.i

CMakeFiles/gmmreg_api.dir/gmmreg_rigid.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_rigid.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_rigid.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_rigid.s

CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj

CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_rigid_func.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_rigid_func.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_rigid_func.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_rigid_func.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_rigid_func.i

CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_rigid_func.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_rigid_func.s

CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj

CMakeFiles/gmmreg_api.dir/gmmreg_api.obj: CMakeFiles/gmmreg_api.dir/flags.make
CMakeFiles/gmmreg_api.dir/gmmreg_api.obj: C:/workspace/coherent\ point\ drift/gmmreg_src/gmmreg_api.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles" $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gmmreg_api.dir/gmmreg_api.obj"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\gmmreg_api.dir\gmmreg_api.obj -c "C:\workspace\coherent point drift\gmmreg_src\gmmreg_api.cpp"

CMakeFiles/gmmreg_api.dir/gmmreg_api.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmmreg_api.dir/gmmreg_api.i"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E "C:\workspace\coherent point drift\gmmreg_src\gmmreg_api.cpp" > CMakeFiles\gmmreg_api.dir\gmmreg_api.i

CMakeFiles/gmmreg_api.dir/gmmreg_api.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmmreg_api.dir/gmmreg_api.s"
	C:\mingw-w64\x86_64-4.9.2-posix-seh-rt_v3-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S "C:\workspace\coherent point drift\gmmreg_src\gmmreg_api.cpp" -o CMakeFiles\gmmreg_api.dir\gmmreg_api.s

CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.requires:
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.requires

CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.provides: CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.requires
	$(MAKE) -f CMakeFiles\gmmreg_api.dir\build.make CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.provides.build
.PHONY : CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.provides

CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.provides.build: CMakeFiles/gmmreg_api.dir/gmmreg_api.obj

# Object files for target gmmreg_api
gmmreg_api_OBJECTS = \
"CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_base.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj" \
"CMakeFiles/gmmreg_api.dir/gmmreg_api.obj"

# External object files for target gmmreg_api
gmmreg_api_EXTERNAL_OBJECTS =

libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_base.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/gmmreg_api.obj
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/build.make
libgmmreg_api.a: CMakeFiles/gmmreg_api.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libgmmreg_api.a"
	$(CMAKE_COMMAND) -P CMakeFiles\gmmreg_api.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gmmreg_api.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gmmreg_api.dir/build: libgmmreg_api.a
.PHONY : CMakeFiles/gmmreg_api.dir/build

CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_utils.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_base.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_cpd.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_tps.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_tps_func.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_grbf.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_grbf_func.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_rigid.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_rigid_func.obj.requires
CMakeFiles/gmmreg_api.dir/requires: CMakeFiles/gmmreg_api.dir/gmmreg_api.obj.requires
.PHONY : CMakeFiles/gmmreg_api.dir/requires

CMakeFiles/gmmreg_api.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\gmmreg_api.dir\cmake_clean.cmake
.PHONY : CMakeFiles/gmmreg_api.dir/clean

CMakeFiles/gmmreg_api.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\workspace\coherent point drift\gmmreg_src" "C:\workspace\coherent point drift\gmmreg_src" "C:\workspace\coherent point drift\gmmreg_build" "C:\workspace\coherent point drift\gmmreg_build" "C:\workspace\coherent point drift\gmmreg_build\CMakeFiles\gmmreg_api.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/gmmreg_api.dir/depend
