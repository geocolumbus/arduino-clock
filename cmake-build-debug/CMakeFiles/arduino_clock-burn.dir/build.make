# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/georgecampbell/arduino/arduino-clock

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/georgecampbell/arduino/arduino-clock/cmake-build-debug

# Utility rule file for arduino_clock-burn.

# Include the progress variables for this target.
include CMakeFiles/arduino_clock-burn.dir/progress.make

CMakeFiles/arduino_clock-burn: arduino_clock.elf
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -cstk500v2 -Pusb -patmega328p -V -Uflash:w:/Users/georgecampbell/arduino/arduino-clock/cmake-build-debug/arduino_clock.hex

arduino_clock-burn: CMakeFiles/arduino_clock-burn
arduino_clock-burn: CMakeFiles/arduino_clock-burn.dir/build.make

.PHONY : arduino_clock-burn

# Rule to build all files generated by this target.
CMakeFiles/arduino_clock-burn.dir/build: arduino_clock-burn

.PHONY : CMakeFiles/arduino_clock-burn.dir/build

CMakeFiles/arduino_clock-burn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/arduino_clock-burn.dir/cmake_clean.cmake
.PHONY : CMakeFiles/arduino_clock-burn.dir/clean

CMakeFiles/arduino_clock-burn.dir/depend:
	cd /Users/georgecampbell/arduino/arduino-clock/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/georgecampbell/arduino/arduino-clock /Users/georgecampbell/arduino/arduino-clock /Users/georgecampbell/arduino/arduino-clock/cmake-build-debug /Users/georgecampbell/arduino/arduino-clock/cmake-build-debug /Users/georgecampbell/arduino/arduino-clock/cmake-build-debug/CMakeFiles/arduino_clock-burn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/arduino_clock-burn.dir/depend

