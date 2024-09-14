# Set the project name
cmake_minimum_required(VERSION 3.10)  
project(dynamic_multilevel_cache)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/CacheLevel.cpp
    src/MultilevelCache.cpp
    src/main.cpp
)

# Create the executable
add_executable(DynamicMultilevelCaching ${SOURCES})

# Include directories for header files
include_directories(src)
