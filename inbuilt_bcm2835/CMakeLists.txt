# CMakeLists.txt for app

# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(app)

# TODO 2: Use add_subdirectory() to add MathFunctions to this project
#add_subdirectory(rpi_lib)

# Add the library source files
set(LIB_SOURCES
    lib/src/rpi_init.c 
    lib/src/rpi_mem_ops.c
)

# Add the library include directory
include_directories(lib/inc)

# Add source files 
set(SOURCES
    app/blink.cpp
)

# Add the executable
add_executable(blink ${SOURCES})

# Link the executable with rpi_lib
target_link_libraries(blink PRIVATE bcm2835)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
# target_include_directories(blink PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}/rpi_lib"
#                           )