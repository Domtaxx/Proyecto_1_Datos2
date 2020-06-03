cmake_minimum_required(VERSION 3.17)
project(VSC_ext)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)

add_executable(VSC_ext
        garbage.cpp
        garbage.hpp
        Linked_List.hpp
        main.cpp
        socket.cpp
        socket.hpp
        socket_C.cpp
        socket_C.hpp
        vsptr.hpp
        vsptrNT.hpp)
