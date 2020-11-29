cmake_minimum_required(VERSION 3.17)
project(yellow_belt_final)

set(CMAKE_CXX_STANDARD 17)

add_executable(yellow_belt_final
        main.cpp
        token.h token.cpp
        condition_parser.h condition_parser.cpp
        condition_parser_test.cpp
        node.cpp node.h
        date.cpp date.h
        database.cpp database.h
        test_runner.h)