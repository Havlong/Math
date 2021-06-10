cmake_minimum_required(VERSION 3.19)
project(Math)

set(CMAKE_CXX_STANDARD 17)

add_executable(Math main.cpp)
add_executable(MatModel model.cpp)
add_executable(Simplex simplex.cpp)
add_executable(DoubleSimplex doubleSimplex.cpp)
add_executable(IntegerSimplex integerSimplex.cpp)