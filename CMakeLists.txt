cmake_minimum_required(VERSION 3.16.3)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(untitled main.cpp
        Scanner.h
        Token.h
        Parser.h
        Parameter.h
        Rule.h
        Predicate.h
        Datalog.h Datalog.cpp
        Scheme.h
        Scheme.cpp
        Tuple.cpp
        Tuple.h
        Relation.cpp
        Relation.h)
