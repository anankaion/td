cmake_minimum_required(VERSION 3.12)
project(td C)

set(CMAKE_C_STANDARD 99)

add_executable(td main.c todo.c todo.h)