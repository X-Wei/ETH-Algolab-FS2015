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
include CMakeFiles/hello.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hello.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hello.dir/flags.make

CMakeFiles/hello.dir/hello.cpp.o: CMakeFiles/hello.dir/flags.make
CMakeFiles/hello.dir/hello.cpp.o: hello.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/hello.dir/hello.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hello.dir/hello.cpp.o -c /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/hello.cpp

CMakeFiles/hello.dir/hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hello.dir/hello.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/hello.cpp > CMakeFiles/hello.dir/hello.cpp.i

CMakeFiles/hello.dir/hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hello.dir/hello.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/hello.cpp -o CMakeFiles/hello.dir/hello.cpp.s

CMakeFiles/hello.dir/hello.cpp.o.requires:
.PHONY : CMakeFiles/hello.dir/hello.cpp.o.requires

CMakeFiles/hello.dir/hello.cpp.o.provides: CMakeFiles/hello.dir/hello.cpp.o.requires
	$(MAKE) -f CMakeFiles/hello.dir/build.make CMakeFiles/hello.dir/hello.cpp.o.provides.build
.PHONY : CMakeFiles/hello.dir/hello.cpp.o.provides

CMakeFiles/hello.dir/hello.cpp.o.provides.build: CMakeFiles/hello.dir/hello.cpp.o

# Object files for target hello
hello_OBJECTS = \
"CMakeFiles/hello.dir/hello.cpp.o"

# External object files for target hello
hello_EXTERNAL_OBJECTS =

hello: CMakeFiles/hello.dir/hello.cpp.o
hello: CMakeFiles/hello.dir/build.make
hello: /usr/lib/i386-linux-gnu/libmpfr.so
hello: /usr/lib/i386-linux-gnu/libgmp.so
hello: /usr/lib/libCGAL_Core.so
hello: /usr/lib/libCGAL.so
hello: /usr/lib/i386-linux-gnu/libboost_thread.so
hello: /usr/lib/i386-linux-gnu/libboost_system.so
hello: /usr/lib/i386-linux-gnu/libpthread.so
hello: /usr/lib/libCGAL_Core.so
hello: /usr/lib/libCGAL.so
hello: /usr/lib/i386-linux-gnu/libboost_thread.so
hello: /usr/lib/i386-linux-gnu/libboost_system.so
hello: /usr/lib/i386-linux-gnu/libpthread.so
hello: CMakeFiles/hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable hello"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hello.dir/build: hello
.PHONY : CMakeFiles/hello.dir/build

CMakeFiles/hello.dir/requires: CMakeFiles/hello.dir/hello.cpp.o.requires
.PHONY : CMakeFiles/hello.dir/requires

CMakeFiles/hello.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hello.dir/clean

CMakeFiles/hello.dir/depend:
	cd /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples /home/algolab/Desktop/vb_shared/ETH/Algolab/week3/mess/cgal_examples/CMakeFiles/hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hello.dir/depend

