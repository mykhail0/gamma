# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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


# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/misza/studia/2sem/IPP/duzy projekt/gamma"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/misza/studia/2sem/IPP/duzy projekt/gamma"

# Utility rule file for doc.

CMakeFiles/doc:
	/usr/bin/doxygen /home/misza/studia/2sem/IPP/duzy\ projekt/gamma/Doxyfile

doc: CMakeFiles/doc
doc: CMakeFiles/doc.dir/build.make

.PHONY : doc

# Rule to build all files generated by this target.
CMakeFiles/doc.dir/build: doc

.PHONY : CMakeFiles/doc.dir/build

CMakeFiles/doc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/doc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/doc.dir/clean

CMakeFiles/doc.dir/depend:
	cd "/home/misza/studia/2sem/IPP/duzy projekt/gamma" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/misza/studia/2sem/IPP/duzy projekt/gamma" "/home/misza/studia/2sem/IPP/duzy projekt/gamma" "/home/misza/studia/2sem/IPP/duzy projekt/gamma" "/home/misza/studia/2sem/IPP/duzy projekt/gamma" "/home/misza/studia/2sem/IPP/duzy projekt/gamma/CMakeFiles/doc.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/doc.dir/depend
