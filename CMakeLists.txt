cmake_minimum_required(VERSION 3.17)
project(CPPRefresh LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(LibraryApp src/library.cpp)

# ----
add_library(dbapp src/dbapp.cpp src/dbapp.hpp)
add_executable(DBMain src/dbappmain.cpp src/dbapp.hpp)
target_link_libraries(DBMain dbapp)
# ----
