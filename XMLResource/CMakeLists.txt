cmake_minimum_required(VERSION 3.26)
project(XMLResource)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_HEADERS NodeXML.hpp TreeXML.hpp XMLResource.hpp)
add_executable(XMLResource ${PROJECT_SOURCE_DIR}/ Main.cpp NodeXML.cpp TreeXML.cpp XMLResource.cpp)