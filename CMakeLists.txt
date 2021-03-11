cmake_minimum_required(VERSION 3.15)
project(grawing_way)

set(CMAKE_CXX_STANDARD 17)

add_executable(grawing_way
        Inc/Character.hpp
        src/Character.cpp
        Inc/Controller.hpp
        src/Controller.cpp
        main.cpp
        )

