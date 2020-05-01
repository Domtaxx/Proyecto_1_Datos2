cmake_minimum_required(VERSION 3.5)

project(VSC_ext LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(VSC_ext
    main.cpp
    vsptr.hpp
    Linked_List.hpp
    garbage.hpp
    garbage.cpp)
