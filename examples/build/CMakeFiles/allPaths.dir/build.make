# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/build

# Include any dependencies generated for this target.
include CMakeFiles/allPaths.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/allPaths.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/allPaths.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/allPaths.dir/flags.make

CMakeFiles/allPaths.dir/codegen:
.PHONY : CMakeFiles/allPaths.dir/codegen

CMakeFiles/allPaths.dir/allPaths.cpp.o: CMakeFiles/allPaths.dir/flags.make
CMakeFiles/allPaths.dir/allPaths.cpp.o: /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/allPaths.cpp
CMakeFiles/allPaths.dir/allPaths.cpp.o: CMakeFiles/allPaths.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/allPaths.dir/allPaths.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/allPaths.dir/allPaths.cpp.o -MF CMakeFiles/allPaths.dir/allPaths.cpp.o.d -o CMakeFiles/allPaths.dir/allPaths.cpp.o -c /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/allPaths.cpp

CMakeFiles/allPaths.dir/allPaths.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/allPaths.dir/allPaths.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/allPaths.cpp > CMakeFiles/allPaths.dir/allPaths.cpp.i

CMakeFiles/allPaths.dir/allPaths.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/allPaths.dir/allPaths.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/allPaths.cpp -o CMakeFiles/allPaths.dir/allPaths.cpp.s

# Object files for target allPaths
allPaths_OBJECTS = \
"CMakeFiles/allPaths.dir/allPaths.cpp.o"

# External object files for target allPaths
allPaths_EXTERNAL_OBJECTS =

allPaths: CMakeFiles/allPaths.dir/allPaths.cpp.o
allPaths: CMakeFiles/allPaths.dir/build.make
allPaths: CMakeFiles/allPaths.dir/compiler_depend.ts
allPaths: CMakeFiles/allPaths.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable allPaths"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/allPaths.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/allPaths.dir/build: allPaths
.PHONY : CMakeFiles/allPaths.dir/build

CMakeFiles/allPaths.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/allPaths.dir/cmake_clean.cmake
.PHONY : CMakeFiles/allPaths.dir/clean

CMakeFiles/allPaths.dir/depend:
	cd /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/build /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/build /home/anirudh2/AppledoreDevelopment/Appledore_Testing/Appledore/examples/build/CMakeFiles/allPaths.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/allPaths.dir/depend

