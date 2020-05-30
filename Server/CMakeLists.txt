cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Server
        garbage.cpp
        garbage.hpp
        Linked_List.hpp
        main.cpp
        md5.cpp
        md5.h
        socket_S.cpp
        socket_S.h
        vsptr.hpp
        vsptrNT.hpp)
