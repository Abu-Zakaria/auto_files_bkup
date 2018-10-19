cmake_minimum_required(VERSION 3.5)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        TestConfigReader.cpp
        ../src/ConfigReader.hpp
        ../src/ConfigReader.cpp)

include_directories(../lib/catch2)

find_package(Boost 1.68.0 COMPONENTS system filesystem REQUIRED)

add_executable(test ${SOURCE_FILES})

target_link_libraries(test Boost::system Boost::filesystem)