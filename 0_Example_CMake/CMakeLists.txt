# cmake needs this line
cmake_minimum_required(VERSION 3.8)

# Declare the executable target built from your sources
add_executable(example example.cpp)

# Link your application with OpenCV libraries
target_link_libraries(example PRIVATE ${OpenCV_LIBS})
