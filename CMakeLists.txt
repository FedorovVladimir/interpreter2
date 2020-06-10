cmake_minimum_required(VERSION 3.16)
project(interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(interpreter main.cpp Scanner.cpp Scanner.h Node.cpp Node.h TypeLexeme.h Lexer.cpp Lexer.h)