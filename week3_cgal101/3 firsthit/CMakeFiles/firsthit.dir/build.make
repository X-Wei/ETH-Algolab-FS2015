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
CMAKE_SOURCE_DIR = "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit"

# Include any dependencies generated for this target.
include CMakeFiles/firsthit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/firsthit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/firsthit.dir/flags.make

CMakeFiles/firsthit.dir/firsthit.cpp.o: CMakeFiles/firsthit.dir/flags.make
CMakeFiles/firsthit.dir/firsthit.cpp.o: firsthit.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/firsthit.dir/firsthit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/firsthit.dir/firsthit.cpp.o -c "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit/firsthit.cpp"

CMakeFiles/firsthit.dir/firsthit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/firsthit.dir/firsthit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit/firsthit.cpp" > CMakeFiles/firsthit.dir/firsthit.cpp.i

CMakeFiles/firsthit.dir/firsthit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/firsthit.dir/firsthit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit/firsthit.cpp" -o CMakeFiles/firsthit.dir/firsthit.cpp.s

CMakeFiles/firsthit.dir/firsthit.cpp.o.requires:
.PHONY : CMakeFiles/firsthit.dir/firsthit.cpp.o.requires

CMakeFiles/firsthit.dir/firsthit.cpp.o.provides: CMakeFiles/firsthit.dir/firsthit.cpp.o.requires
	$(MAKE) -f CMakeFiles/firsthit.dir/build.make CMakeFiles/firsthit.dir/firsthit.cpp.o.provides.build
.PHONY : CMakeFiles/firsthit.dir/firsthit.cpp.o.provides

CMakeFiles/firsthit.dir/firsthit.cpp.o.provides.build: CMakeFiles/firsthit.dir/firsthit.cpp.o

# Object files for target firsthit
firsthit_OBJECTS = \
"CMakeFiles/firsthit.dir/firsthit.cpp.o"

# External object files for target firsthit
firsthit_EXTERNAL_OBJECTS =

firsthit: CMakeFiles/firsthit.dir/firsthit.cpp.o
firsthit: CMakeFiles/firsthit.dir/build.make
firsthit: /usr/lib/i386-linux-gnu/libmpfr.so
firsthit: /usr/lib/i386-linux-gnu/libgmp.so
firsthit: /usr/lib/libCGAL_Core.so
firsthit: /usr/lib/libCGAL.so
firsthit: /usr/lib/i386-linux-gnu/libboost_thread.so
firsthit: /usr/lib/i386-linux-gnu/libboost_system.so
firsthit: /usr/lib/i386-linux-gnu/libpthread.so
firsthit: /usr/lib/libCGAL_Core.so
firsthit: /usr/lib/libCGAL.so
firsthit: /usr/lib/i386-linux-gnu/libboost_thread.so
firsthit: /usr/lib/i386-linux-gnu/libboost_system.so
firsthit: /usr/lib/i386-linux-gnu/libpthread.so
firsthit: CMakeFiles/firsthit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable firsthit"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/firsthit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/firsthit.dir/build: firsthit
.PHONY : CMakeFiles/firsthit.dir/build

CMakeFiles/firsthit.dir/requires: CMakeFiles/firsthit.dir/firsthit.cpp.o.requires
.PHONY : CMakeFiles/firsthit.dir/requires

CMakeFiles/firsthit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/firsthit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/firsthit.dir/clean

CMakeFiles/firsthit.dir/depend:
	cd "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit" "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit" "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit" "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit" "/home/algolab/Desktop/vb_shared/ETH/Algolab/week3/3 firsthit/CMakeFiles/firsthit.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/firsthit.dir/depend

