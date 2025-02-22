# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Appledore-v2.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Automatically collect all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Loop through all .cpp files and create executables
foreach(source_file ${SOURCES})
    get_filename_component(target_name ${source_file} NAME_WE)
    add_executable(${target_name} ${source_file})
endforeach()