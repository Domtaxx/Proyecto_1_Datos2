cmake_minimum_required(VERSION 3.5)

project(VSC_ext LANGUAGES CXX)

#find_package(Doxygen REQUIRED)
#find_library(rapidjson REQUIRED_FILES)
#doxygen_add_docs(docs . ALL)

find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(VSC_ext
    main.cpp
    vsptr.hpp
    Linked_List.hpp
    garbage.hpp
    garbage.cpp
    socket_C.cpp
    vsptrNT.hpp
    socket_C.h
    socket_S.hpp)
set_target_properties(VSC_ext PROPERTIES COMPILE_FLAGS -pthread LINK_FLAGS -pthread)
