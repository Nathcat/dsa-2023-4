# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++

# Include any dependencies generated for this target.
include CMakeFiles/DSALab4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DSALab4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DSALab4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DSALab4.dir/flags.make

CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o: CMakeFiles/DSALab4.dir/flags.make
CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o: Lab4/src/test.cpp
CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o: CMakeFiles/DSALab4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o -MF CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o.d -o CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o -c /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++/Lab4/src/test.cpp

CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++/Lab4/src/test.cpp > CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.i

CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++/Lab4/src/test.cpp -o CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.s

# Object files for target DSALab4
DSALab4_OBJECTS = \
"CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o"

# External object files for target DSALab4
DSALab4_EXTERNAL_OBJECTS =

Lab4/build/DSALab4: CMakeFiles/DSALab4.dir/Lab4/src/test.cpp.o
Lab4/build/DSALab4: CMakeFiles/DSALab4.dir/build.make
Lab4/build/DSALab4: build/libDSALabs-2024.so
Lab4/build/DSALab4: CMakeFiles/DSALab4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab4/build/DSALab4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DSALab4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DSALab4.dir/build: Lab4/build/DSALab4
.PHONY : CMakeFiles/DSALab4.dir/build

CMakeFiles/DSALab4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DSALab4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DSALab4.dir/clean

CMakeFiles/DSALab4.dir/depend:
	cd /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++ && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++ /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++ /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++ /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++ /media/nathcat/Data/Projects/GitHub/dsa-2023-4/C++/CMakeFiles/DSALab4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DSALab4.dir/depend

