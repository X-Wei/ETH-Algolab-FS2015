# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples

# Include any dependencies generated for this target.
include CMakeFiles/miniball.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/miniball.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/miniball.dir/flags.make

CMakeFiles/miniball.dir/miniball.cpp.o: CMakeFiles/miniball.dir/flags.make
CMakeFiles/miniball.dir/miniball.cpp.o: miniball.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/miniball.dir/miniball.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/miniball.dir/miniball.cpp.o -c /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/miniball.cpp

CMakeFiles/miniball.dir/miniball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/miniball.dir/miniball.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/miniball.cpp > CMakeFiles/miniball.dir/miniball.cpp.i

CMakeFiles/miniball.dir/miniball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/miniball.dir/miniball.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/miniball.cpp -o CMakeFiles/miniball.dir/miniball.cpp.s

CMakeFiles/miniball.dir/miniball.cpp.o.requires:
.PHONY : CMakeFiles/miniball.dir/miniball.cpp.o.requires

CMakeFiles/miniball.dir/miniball.cpp.o.provides: CMakeFiles/miniball.dir/miniball.cpp.o.requires
	$(MAKE) -f CMakeFiles/miniball.dir/build.make CMakeFiles/miniball.dir/miniball.cpp.o.provides.build
.PHONY : CMakeFiles/miniball.dir/miniball.cpp.o.provides

CMakeFiles/miniball.dir/miniball.cpp.o.provides.build: CMakeFiles/miniball.dir/miniball.cpp.o

# Object files for target miniball
miniball_OBJECTS = \
"CMakeFiles/miniball.dir/miniball.cpp.o"

# External object files for target miniball
miniball_EXTERNAL_OBJECTS =

miniball: CMakeFiles/miniball.dir/miniball.cpp.o
miniball: CMakeFiles/miniball.dir/build.make
miniball: /usr/lib/i386-linux-gnu/libmpfr.so
miniball: /usr/lib/i386-linux-gnu/libgmp.so
miniball: /usr/lib/libCGAL_Core.so
miniball: /usr/lib/libCGAL.so
miniball: /usr/lib/i386-linux-gnu/libboost_thread.so
miniball: /usr/lib/i386-linux-gnu/libboost_system.so
miniball: /usr/lib/i386-linux-gnu/libpthread.so
miniball: /usr/lib/libCGAL_Core.so
miniball: /usr/lib/libCGAL.so
miniball: /usr/lib/i386-linux-gnu/libboost_thread.so
miniball: /usr/lib/i386-linux-gnu/libboost_system.so
miniball: /usr/lib/i386-linux-gnu/libpthread.so
miniball: CMakeFiles/miniball.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable miniball"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/miniball.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/miniball.dir/build: miniball
.PHONY : CMakeFiles/miniball.dir/build

CMakeFiles/miniball.dir/requires: CMakeFiles/miniball.dir/miniball.cpp.o.requires
.PHONY : CMakeFiles/miniball.dir/requires

CMakeFiles/miniball.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/miniball.dir/cmake_clean.cmake
.PHONY : CMakeFiles/miniball.dir/clean

CMakeFiles/miniball.dir/depend:
	cd /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/CMakeFiles/miniball.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/miniball.dir/depend

