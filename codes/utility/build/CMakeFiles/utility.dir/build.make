# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/diwen/workspace/LinuxStudy/notes/codes/utility

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diwen/workspace/LinuxStudy/notes/codes/utility/build

# Include any dependencies generated for this target.
include CMakeFiles/utility.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/utility.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/utility.dir/flags.make

CMakeFiles/utility.dir/src/Alarm.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/Alarm.cpp.o: ../src/Alarm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/utility.dir/src/Alarm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/Alarm.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Alarm.cpp

CMakeFiles/utility.dir/src/Alarm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/Alarm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Alarm.cpp > CMakeFiles/utility.dir/src/Alarm.cpp.i

CMakeFiles/utility.dir/src/Alarm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/Alarm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Alarm.cpp -o CMakeFiles/utility.dir/src/Alarm.cpp.s

CMakeFiles/utility.dir/src/Alarm.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/Alarm.cpp.o.requires

CMakeFiles/utility.dir/src/Alarm.cpp.o.provides: CMakeFiles/utility.dir/src/Alarm.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/Alarm.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/Alarm.cpp.o.provides

CMakeFiles/utility.dir/src/Alarm.cpp.o.provides.build: CMakeFiles/utility.dir/src/Alarm.cpp.o


CMakeFiles/utility.dir/src/Clock.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/Clock.cpp.o: ../src/Clock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/utility.dir/src/Clock.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/Clock.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Clock.cpp

CMakeFiles/utility.dir/src/Clock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/Clock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Clock.cpp > CMakeFiles/utility.dir/src/Clock.cpp.i

CMakeFiles/utility.dir/src/Clock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/Clock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Clock.cpp -o CMakeFiles/utility.dir/src/Clock.cpp.s

CMakeFiles/utility.dir/src/Clock.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/Clock.cpp.o.requires

CMakeFiles/utility.dir/src/Clock.cpp.o.provides: CMakeFiles/utility.dir/src/Clock.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/Clock.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/Clock.cpp.o.provides

CMakeFiles/utility.dir/src/Clock.cpp.o.provides.build: CMakeFiles/utility.dir/src/Clock.cpp.o


CMakeFiles/utility.dir/src/HeartBeat.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/HeartBeat.cpp.o: ../src/HeartBeat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/utility.dir/src/HeartBeat.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/HeartBeat.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/HeartBeat.cpp

CMakeFiles/utility.dir/src/HeartBeat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/HeartBeat.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/HeartBeat.cpp > CMakeFiles/utility.dir/src/HeartBeat.cpp.i

CMakeFiles/utility.dir/src/HeartBeat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/HeartBeat.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/HeartBeat.cpp -o CMakeFiles/utility.dir/src/HeartBeat.cpp.s

CMakeFiles/utility.dir/src/HeartBeat.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/HeartBeat.cpp.o.requires

CMakeFiles/utility.dir/src/HeartBeat.cpp.o.provides: CMakeFiles/utility.dir/src/HeartBeat.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/HeartBeat.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/HeartBeat.cpp.o.provides

CMakeFiles/utility.dir/src/HeartBeat.cpp.o.provides.build: CMakeFiles/utility.dir/src/HeartBeat.cpp.o


CMakeFiles/utility.dir/src/INetSocket.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/INetSocket.cpp.o: ../src/INetSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/utility.dir/src/INetSocket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/INetSocket.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/INetSocket.cpp

CMakeFiles/utility.dir/src/INetSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/INetSocket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/INetSocket.cpp > CMakeFiles/utility.dir/src/INetSocket.cpp.i

CMakeFiles/utility.dir/src/INetSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/INetSocket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/INetSocket.cpp -o CMakeFiles/utility.dir/src/INetSocket.cpp.s

CMakeFiles/utility.dir/src/INetSocket.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/INetSocket.cpp.o.requires

CMakeFiles/utility.dir/src/INetSocket.cpp.o.provides: CMakeFiles/utility.dir/src/INetSocket.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/INetSocket.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/INetSocket.cpp.o.provides

CMakeFiles/utility.dir/src/INetSocket.cpp.o.provides.build: CMakeFiles/utility.dir/src/INetSocket.cpp.o


CMakeFiles/utility.dir/src/Network.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/Network.cpp.o: ../src/Network.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/utility.dir/src/Network.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/Network.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Network.cpp

CMakeFiles/utility.dir/src/Network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/Network.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Network.cpp > CMakeFiles/utility.dir/src/Network.cpp.i

CMakeFiles/utility.dir/src/Network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/Network.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Network.cpp -o CMakeFiles/utility.dir/src/Network.cpp.s

CMakeFiles/utility.dir/src/Network.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/Network.cpp.o.requires

CMakeFiles/utility.dir/src/Network.cpp.o.provides: CMakeFiles/utility.dir/src/Network.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/Network.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/Network.cpp.o.provides

CMakeFiles/utility.dir/src/Network.cpp.o.provides.build: CMakeFiles/utility.dir/src/Network.cpp.o


CMakeFiles/utility.dir/src/Partner.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/Partner.cpp.o: ../src/Partner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/utility.dir/src/Partner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/Partner.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Partner.cpp

CMakeFiles/utility.dir/src/Partner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/Partner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Partner.cpp > CMakeFiles/utility.dir/src/Partner.cpp.i

CMakeFiles/utility.dir/src/Partner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/Partner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Partner.cpp -o CMakeFiles/utility.dir/src/Partner.cpp.s

CMakeFiles/utility.dir/src/Partner.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/Partner.cpp.o.requires

CMakeFiles/utility.dir/src/Partner.cpp.o.provides: CMakeFiles/utility.dir/src/Partner.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/Partner.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/Partner.cpp.o.provides

CMakeFiles/utility.dir/src/Partner.cpp.o.provides.build: CMakeFiles/utility.dir/src/Partner.cpp.o


CMakeFiles/utility.dir/src/PartnerCallback.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/PartnerCallback.cpp.o: ../src/PartnerCallback.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/utility.dir/src/PartnerCallback.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/PartnerCallback.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/PartnerCallback.cpp

CMakeFiles/utility.dir/src/PartnerCallback.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/PartnerCallback.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/PartnerCallback.cpp > CMakeFiles/utility.dir/src/PartnerCallback.cpp.i

CMakeFiles/utility.dir/src/PartnerCallback.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/PartnerCallback.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/PartnerCallback.cpp -o CMakeFiles/utility.dir/src/PartnerCallback.cpp.s

CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.requires

CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.provides: CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.provides

CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.provides.build: CMakeFiles/utility.dir/src/PartnerCallback.cpp.o


CMakeFiles/utility.dir/src/ProcessFork.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/ProcessFork.cpp.o: ../src/ProcessFork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/utility.dir/src/ProcessFork.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/ProcessFork.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/ProcessFork.cpp

CMakeFiles/utility.dir/src/ProcessFork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/ProcessFork.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/ProcessFork.cpp > CMakeFiles/utility.dir/src/ProcessFork.cpp.i

CMakeFiles/utility.dir/src/ProcessFork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/ProcessFork.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/ProcessFork.cpp -o CMakeFiles/utility.dir/src/ProcessFork.cpp.s

CMakeFiles/utility.dir/src/ProcessFork.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/ProcessFork.cpp.o.requires

CMakeFiles/utility.dir/src/ProcessFork.cpp.o.provides: CMakeFiles/utility.dir/src/ProcessFork.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/ProcessFork.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/ProcessFork.cpp.o.provides

CMakeFiles/utility.dir/src/ProcessFork.cpp.o.provides.build: CMakeFiles/utility.dir/src/ProcessFork.cpp.o


CMakeFiles/utility.dir/src/String.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/String.cpp.o: ../src/String.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/utility.dir/src/String.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/String.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/String.cpp

CMakeFiles/utility.dir/src/String.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/String.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/String.cpp > CMakeFiles/utility.dir/src/String.cpp.i

CMakeFiles/utility.dir/src/String.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/String.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/String.cpp -o CMakeFiles/utility.dir/src/String.cpp.s

CMakeFiles/utility.dir/src/String.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/String.cpp.o.requires

CMakeFiles/utility.dir/src/String.cpp.o.provides: CMakeFiles/utility.dir/src/String.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/String.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/String.cpp.o.provides

CMakeFiles/utility.dir/src/String.cpp.o.provides.build: CMakeFiles/utility.dir/src/String.cpp.o


CMakeFiles/utility.dir/src/StringTrans.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/StringTrans.cpp.o: ../src/StringTrans.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/utility.dir/src/StringTrans.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/StringTrans.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/StringTrans.cpp

CMakeFiles/utility.dir/src/StringTrans.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/StringTrans.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/StringTrans.cpp > CMakeFiles/utility.dir/src/StringTrans.cpp.i

CMakeFiles/utility.dir/src/StringTrans.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/StringTrans.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/StringTrans.cpp -o CMakeFiles/utility.dir/src/StringTrans.cpp.s

CMakeFiles/utility.dir/src/StringTrans.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/StringTrans.cpp.o.requires

CMakeFiles/utility.dir/src/StringTrans.cpp.o.provides: CMakeFiles/utility.dir/src/StringTrans.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/StringTrans.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/StringTrans.cpp.o.provides

CMakeFiles/utility.dir/src/StringTrans.cpp.o.provides.build: CMakeFiles/utility.dir/src/StringTrans.cpp.o


CMakeFiles/utility.dir/src/Timer.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/Timer.cpp.o: ../src/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/utility.dir/src/Timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/Timer.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Timer.cpp

CMakeFiles/utility.dir/src/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Timer.cpp > CMakeFiles/utility.dir/src/Timer.cpp.i

CMakeFiles/utility.dir/src/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/Timer.cpp -o CMakeFiles/utility.dir/src/Timer.cpp.s

CMakeFiles/utility.dir/src/Timer.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/Timer.cpp.o.requires

CMakeFiles/utility.dir/src/Timer.cpp.o.provides: CMakeFiles/utility.dir/src/Timer.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/Timer.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/Timer.cpp.o.provides

CMakeFiles/utility.dir/src/Timer.cpp.o.provides.build: CMakeFiles/utility.dir/src/Timer.cpp.o


CMakeFiles/utility.dir/src/main.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/utility.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/main.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/main.cpp

CMakeFiles/utility.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/main.cpp > CMakeFiles/utility.dir/src/main.cpp.i

CMakeFiles/utility.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/main.cpp -o CMakeFiles/utility.dir/src/main.cpp.s

CMakeFiles/utility.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/main.cpp.o.requires

CMakeFiles/utility.dir/src/main.cpp.o.provides: CMakeFiles/utility.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/main.cpp.o.provides

CMakeFiles/utility.dir/src/main.cpp.o.provides.build: CMakeFiles/utility.dir/src/main.cpp.o


CMakeFiles/utility.dir/src/utility.cpp.o: CMakeFiles/utility.dir/flags.make
CMakeFiles/utility.dir/src/utility.cpp.o: ../src/utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/utility.dir/src/utility.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utility.dir/src/utility.cpp.o -c /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/utility.cpp

CMakeFiles/utility.dir/src/utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility.dir/src/utility.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/utility.cpp > CMakeFiles/utility.dir/src/utility.cpp.i

CMakeFiles/utility.dir/src/utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility.dir/src/utility.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diwen/workspace/LinuxStudy/notes/codes/utility/src/utility.cpp -o CMakeFiles/utility.dir/src/utility.cpp.s

CMakeFiles/utility.dir/src/utility.cpp.o.requires:

.PHONY : CMakeFiles/utility.dir/src/utility.cpp.o.requires

CMakeFiles/utility.dir/src/utility.cpp.o.provides: CMakeFiles/utility.dir/src/utility.cpp.o.requires
	$(MAKE) -f CMakeFiles/utility.dir/build.make CMakeFiles/utility.dir/src/utility.cpp.o.provides.build
.PHONY : CMakeFiles/utility.dir/src/utility.cpp.o.provides

CMakeFiles/utility.dir/src/utility.cpp.o.provides.build: CMakeFiles/utility.dir/src/utility.cpp.o


# Object files for target utility
utility_OBJECTS = \
"CMakeFiles/utility.dir/src/Alarm.cpp.o" \
"CMakeFiles/utility.dir/src/Clock.cpp.o" \
"CMakeFiles/utility.dir/src/HeartBeat.cpp.o" \
"CMakeFiles/utility.dir/src/INetSocket.cpp.o" \
"CMakeFiles/utility.dir/src/Network.cpp.o" \
"CMakeFiles/utility.dir/src/Partner.cpp.o" \
"CMakeFiles/utility.dir/src/PartnerCallback.cpp.o" \
"CMakeFiles/utility.dir/src/ProcessFork.cpp.o" \
"CMakeFiles/utility.dir/src/String.cpp.o" \
"CMakeFiles/utility.dir/src/StringTrans.cpp.o" \
"CMakeFiles/utility.dir/src/Timer.cpp.o" \
"CMakeFiles/utility.dir/src/main.cpp.o" \
"CMakeFiles/utility.dir/src/utility.cpp.o"

# External object files for target utility
utility_EXTERNAL_OBJECTS =

utility: CMakeFiles/utility.dir/src/Alarm.cpp.o
utility: CMakeFiles/utility.dir/src/Clock.cpp.o
utility: CMakeFiles/utility.dir/src/HeartBeat.cpp.o
utility: CMakeFiles/utility.dir/src/INetSocket.cpp.o
utility: CMakeFiles/utility.dir/src/Network.cpp.o
utility: CMakeFiles/utility.dir/src/Partner.cpp.o
utility: CMakeFiles/utility.dir/src/PartnerCallback.cpp.o
utility: CMakeFiles/utility.dir/src/ProcessFork.cpp.o
utility: CMakeFiles/utility.dir/src/String.cpp.o
utility: CMakeFiles/utility.dir/src/StringTrans.cpp.o
utility: CMakeFiles/utility.dir/src/Timer.cpp.o
utility: CMakeFiles/utility.dir/src/main.cpp.o
utility: CMakeFiles/utility.dir/src/utility.cpp.o
utility: CMakeFiles/utility.dir/build.make
utility: CMakeFiles/utility.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable utility"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utility.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/utility.dir/build: utility

.PHONY : CMakeFiles/utility.dir/build

CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/Alarm.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/Clock.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/HeartBeat.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/INetSocket.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/Network.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/Partner.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/PartnerCallback.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/ProcessFork.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/String.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/StringTrans.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/Timer.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/main.cpp.o.requires
CMakeFiles/utility.dir/requires: CMakeFiles/utility.dir/src/utility.cpp.o.requires

.PHONY : CMakeFiles/utility.dir/requires

CMakeFiles/utility.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/utility.dir/cmake_clean.cmake
.PHONY : CMakeFiles/utility.dir/clean

CMakeFiles/utility.dir/depend:
	cd /home/diwen/workspace/LinuxStudy/notes/codes/utility/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diwen/workspace/LinuxStudy/notes/codes/utility /home/diwen/workspace/LinuxStudy/notes/codes/utility /home/diwen/workspace/LinuxStudy/notes/codes/utility/build /home/diwen/workspace/LinuxStudy/notes/codes/utility/build /home/diwen/workspace/LinuxStudy/notes/codes/utility/build/CMakeFiles/utility.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/utility.dir/depend

