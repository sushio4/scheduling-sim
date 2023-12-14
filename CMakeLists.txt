cmake_minimum_required(VERSION 3.10)

project(scheduling-sim VERSION 1.0)

add_executable(schedule 
    main.cpp
    BaseScheduler.cpp
    Util.cpp
    RoundRobin.cpp
    TextSched.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)