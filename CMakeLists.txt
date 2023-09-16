cmake_minimum_required(VERSION 3.22)
project("PedalSteel")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(main src/main.cpp src/PedalSteelGuitar.cpp)
