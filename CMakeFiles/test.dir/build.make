# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/timmy/Documents/cpp/cardgame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/timmy/Documents/cpp/cardgame

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/cardgame/game/card.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/cardgame/game/card.cpp.o: cardgame/game/card.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/timmy/Documents/cpp/cardgame/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/cardgame/game/card.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/cardgame/game/card.cpp.o -c /home/timmy/Documents/cpp/cardgame/cardgame/game/card.cpp

CMakeFiles/test.dir/cardgame/game/card.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/cardgame/game/card.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/timmy/Documents/cpp/cardgame/cardgame/game/card.cpp > CMakeFiles/test.dir/cardgame/game/card.cpp.i

CMakeFiles/test.dir/cardgame/game/card.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/cardgame/game/card.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/timmy/Documents/cpp/cardgame/cardgame/game/card.cpp -o CMakeFiles/test.dir/cardgame/game/card.cpp.s

CMakeFiles/test.dir/cardgame/game/deck.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/cardgame/game/deck.cpp.o: cardgame/game/deck.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/timmy/Documents/cpp/cardgame/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/cardgame/game/deck.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/cardgame/game/deck.cpp.o -c /home/timmy/Documents/cpp/cardgame/cardgame/game/deck.cpp

CMakeFiles/test.dir/cardgame/game/deck.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/cardgame/game/deck.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/timmy/Documents/cpp/cardgame/cardgame/game/deck.cpp > CMakeFiles/test.dir/cardgame/game/deck.cpp.i

CMakeFiles/test.dir/cardgame/game/deck.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/cardgame/game/deck.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/timmy/Documents/cpp/cardgame/cardgame/game/deck.cpp -o CMakeFiles/test.dir/cardgame/game/deck.cpp.s

CMakeFiles/test.dir/cardgame/game/main.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/cardgame/game/main.cpp.o: cardgame/game/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/timmy/Documents/cpp/cardgame/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test.dir/cardgame/game/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/cardgame/game/main.cpp.o -c /home/timmy/Documents/cpp/cardgame/cardgame/game/main.cpp

CMakeFiles/test.dir/cardgame/game/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/cardgame/game/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/timmy/Documents/cpp/cardgame/cardgame/game/main.cpp > CMakeFiles/test.dir/cardgame/game/main.cpp.i

CMakeFiles/test.dir/cardgame/game/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/cardgame/game/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/timmy/Documents/cpp/cardgame/cardgame/game/main.cpp -o CMakeFiles/test.dir/cardgame/game/main.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/cardgame/game/card.cpp.o" \
"CMakeFiles/test.dir/cardgame/game/deck.cpp.o" \
"CMakeFiles/test.dir/cardgame/game/main.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/cardgame/game/card.cpp.o
test: CMakeFiles/test.dir/cardgame/game/deck.cpp.o
test: CMakeFiles/test.dir/cardgame/game/main.cpp.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/timmy/Documents/cpp/cardgame/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test

.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/timmy/Documents/cpp/cardgame && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/timmy/Documents/cpp/cardgame /home/timmy/Documents/cpp/cardgame /home/timmy/Documents/cpp/cardgame /home/timmy/Documents/cpp/cardgame /home/timmy/Documents/cpp/cardgame/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

