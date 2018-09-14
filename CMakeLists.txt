cmake_minimum_required(VERSION 3.12)
project(kvstore)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/home/vincent/Downloads/boost_1_67_0")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/home/vincent/Downloads/boost_1_67_0/stage/lib")

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost)
if(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
endif()

add_executable(kvstore src/server.cpp src/node.cpp)