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
CMAKE_SOURCE_DIR = "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Projeto_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Projeto_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projeto_1.dir/flags.make

CMakeFiles/Projeto_1.dir/main.c.o: CMakeFiles/Projeto_1.dir/flags.make
CMakeFiles/Projeto_1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Projeto_1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Projeto_1.dir/main.c.o   -c "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/main.c"

CMakeFiles/Projeto_1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projeto_1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/main.c" > CMakeFiles/Projeto_1.dir/main.c.i

CMakeFiles/Projeto_1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projeto_1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/main.c" -o CMakeFiles/Projeto_1.dir/main.c.s

CMakeFiles/Projeto_1.dir/gerais.c.o: CMakeFiles/Projeto_1.dir/flags.make
CMakeFiles/Projeto_1.dir/gerais.c.o: ../gerais.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Projeto_1.dir/gerais.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Projeto_1.dir/gerais.c.o   -c "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/gerais.c"

CMakeFiles/Projeto_1.dir/gerais.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projeto_1.dir/gerais.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/gerais.c" > CMakeFiles/Projeto_1.dir/gerais.c.i

CMakeFiles/Projeto_1.dir/gerais.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projeto_1.dir/gerais.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/gerais.c" -o CMakeFiles/Projeto_1.dir/gerais.c.s

CMakeFiles/Projeto_1.dir/linhas.c.o: CMakeFiles/Projeto_1.dir/flags.make
CMakeFiles/Projeto_1.dir/linhas.c.o: ../linhas.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Projeto_1.dir/linhas.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Projeto_1.dir/linhas.c.o   -c "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/linhas.c"

CMakeFiles/Projeto_1.dir/linhas.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projeto_1.dir/linhas.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/linhas.c" > CMakeFiles/Projeto_1.dir/linhas.c.i

CMakeFiles/Projeto_1.dir/linhas.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projeto_1.dir/linhas.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/linhas.c" -o CMakeFiles/Projeto_1.dir/linhas.c.s

CMakeFiles/Projeto_1.dir/veiculos.c.o: CMakeFiles/Projeto_1.dir/flags.make
CMakeFiles/Projeto_1.dir/veiculos.c.o: ../veiculos.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Projeto_1.dir/veiculos.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Projeto_1.dir/veiculos.c.o   -c "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/veiculos.c"

CMakeFiles/Projeto_1.dir/veiculos.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projeto_1.dir/veiculos.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/veiculos.c" > CMakeFiles/Projeto_1.dir/veiculos.c.i

CMakeFiles/Projeto_1.dir/veiculos.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projeto_1.dir/veiculos.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/veiculos.c" -o CMakeFiles/Projeto_1.dir/veiculos.c.s

# Object files for target Projeto_1
Projeto_1_OBJECTS = \
"CMakeFiles/Projeto_1.dir/main.c.o" \
"CMakeFiles/Projeto_1.dir/gerais.c.o" \
"CMakeFiles/Projeto_1.dir/linhas.c.o" \
"CMakeFiles/Projeto_1.dir/veiculos.c.o"

# External object files for target Projeto_1
Projeto_1_EXTERNAL_OBJECTS =

Projeto_1: CMakeFiles/Projeto_1.dir/main.c.o
Projeto_1: CMakeFiles/Projeto_1.dir/gerais.c.o
Projeto_1: CMakeFiles/Projeto_1.dir/linhas.c.o
Projeto_1: CMakeFiles/Projeto_1.dir/veiculos.c.o
Projeto_1: CMakeFiles/Projeto_1.dir/build.make
Projeto_1: CMakeFiles/Projeto_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable Projeto_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Projeto_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Projeto_1.dir/build: Projeto_1

.PHONY : CMakeFiles/Projeto_1.dir/build

CMakeFiles/Projeto_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Projeto_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Projeto_1.dir/clean

CMakeFiles/Projeto_1.dir/depend:
	cd "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1" "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1" "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug" "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug" "/mnt/c/Workspace/CLion/Facul/Arquivos/Projeto 1/cmake-build-debug/CMakeFiles/Projeto_1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Projeto_1.dir/depend

