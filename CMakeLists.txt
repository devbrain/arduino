cmake_minimum_required (VERSION 3.10)

project(duino)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories (${CMAKE_SOURCE_DIR}/common)

add_subdirectory(desktop)
