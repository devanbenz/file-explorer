cmake_minimum_required(VERSION 3.26)
project(file_explorer)

set(CMAKE_CXX_STANDARD 20)

add_executable(file_explorer src/main.cpp
        src/file-operations.cpp
        src/user-interface.cpp
        include/file-operations.h
        include/user-interface.h)

link_directories(C:\\Users\\Devan\\Documents\\Programming\\C++\\file-explorer\\include)
