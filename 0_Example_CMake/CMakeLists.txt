# cmake needs this line
cmake_minimum_required(VERSION 3.8)

# Declare the executable target built from your sources
add_executable(0_Example_CMake example.cpp)

# Link your application with OpenCV libraries
target_link_libraries(0_Example_CMake PRIVATE ${OpenCV_LIBS})
