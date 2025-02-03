cmake_minimum_required(VERSION 3.29)
project(QMS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include_directories(include)

add_executable(QMS
    include/admin.h
    include/manageQuiz.h
    src/admin.cpp
    src/player.cpp
    include/player.h
    src/manageQuiz.cpp
    src/utility.cpp
    include/utility.h
        main.cpp)
