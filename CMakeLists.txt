cmake_minimum_required(VERSION 3.17)
project(Compile)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compile main.cpp Scanner.cpp Scanner.h PrattParser.cpp PrattParser.h Expression.cpp Expression.h)