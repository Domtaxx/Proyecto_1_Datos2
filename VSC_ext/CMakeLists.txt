cmake_minimum_required(VERSION 3.17)
project(VSC_ext)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(VSC_ext
        garbage.cpp
        garbage.hpp
        Linked_List.hpp
        socket.cpp
        socket.hpp
        socket_C.cpp
        socket_C.hpp
        vsptr.hpp
        vsptrNT.hpp)
target_link_libraries(VSC_ext Threads::Threads)
find_package(Doxygen REQUIRED)
doxygen_add_docs(docs . ALL)
