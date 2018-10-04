cmake_minimum_required(VERSION 3.10.1)

set(CMAKE_CXX_STANDARD 17)

project(ArrayUtil)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

# build tests
add_executable(C_one_dimension test/C_one_dimension.cpp)
add_executable(C_multi_dimension test/C_multi_dimension.cpp)
add_executable(RView_one_dimension test/RView_one_dimension.cpp)