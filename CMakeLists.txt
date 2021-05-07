cmake_minimum_required(VERSION 3.17)
set(VCPKG_FEATURE_FLAGS "versions")
set(CMAKE_TOOLCHAIN_FILE /usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(Compile)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)

add_executable(Compile main.cpp Scanner.cpp Scanner.h PrattParser.cpp PrattParser.h Expression.cpp Expression.h test/TestParttParser.cpp)
target_link_libraries(Compile GTest::gtest GTest::gtest_main glog::glog)