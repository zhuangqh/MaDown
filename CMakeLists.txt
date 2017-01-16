cmake_minimum_required(VERSION 3.6)
project(MaDown)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/AST.cpp
        src/AST.h
        src/Parser.cpp
        src/Parser.hpp
        src/Render.cpp
        src/Render.h
        src/Madown.h
        src/Lexer.cpp
        src/Lexer.h
        src/TextStream.cpp
        src/TextStream.h
        src/util.h
        src/Visitor.h
        )

add_library(MaDown ${SOURCE_FILES})

set(EXAMPLE example/main.cpp)

add_executable(example ${SOURCE_FILES} ${EXAMPLE})
