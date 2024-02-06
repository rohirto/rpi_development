# CMakeLists.txt for project

# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project name
project(volansys_rpi)

# Add the library include directory
include_directories(lib/inc)


add_subdirectory(app)
add_subdirectory(lib)




# Add the executable target
add_executable(MyApp app/app.cpp)


target_link_libraries(MyApp PUBLIC rpi_lib)
target_link_libraries(MyApp PUBLIC SSD1306_lib)


