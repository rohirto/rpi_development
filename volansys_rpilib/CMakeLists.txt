# CMakeLists.txt for project

# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(volansys_rpi)

# Add the library source files
set(LIB_SOURCES
    lib/src/rpi_init.c 
    lib/src/rpi_mem_ops.c
    lib/src/rpi_gpio.c
)

# Add the library include directory
include_directories(lib/inc)

# Create the library
add_library(rpi_lib ${LIB_SOURCES})

# Add the executable target
add_executable(MyApp app/app.cpp)

# Link the executable with the library
target_link_libraries(MyApp rpi_lib)

