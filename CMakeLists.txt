cmake_minimum_required(VERSION 3.5)
project(auto_files_bkup)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
        src/main.cpp
        src/Transfer.hpp
        src/ConfigReader.hpp
        src/Reader.hpp
        src/Transfer.cpp
        src/helpers.hpp
        src/ConfigReader.cpp
        )

include_directories(include)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.68.0 COMPONENTS system filesystem REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)