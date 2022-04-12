cmake_minimum_required(VERSION 3.17)
project(CPPRefresh LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(LibraryApp src/library.cpp)
