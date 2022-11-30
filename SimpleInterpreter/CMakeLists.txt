# cmake_minimum_required(VERSION <specify CMake version here>)
project(lispy)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(lispy
        main.cpp
        logger.hpp
        token.hpp
        visitor.hpp
        ast.cpp
        ast.hpp
        interpreter.cpp
        interpreter.hpp
        parser.cpp
        parser.hpp
        scanner.cpp
        scanner.hpp
        )