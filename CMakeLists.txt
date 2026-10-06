cmake_minimum_required(VERSION 3.10)
project(EscapeRoomGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES src/*.cpp)

add_executable(escape ${SOURCES})
