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

set(BOOST_STATIC_LIBS libboost_system.a libboost_filesystem.a)
link_directories(lib/boost/lib)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${BOOST_STATIC_LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)