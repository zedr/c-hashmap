cmake_minimum_required(VERSION 3.22)
project(hashmap C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)

add_executable(hashmap main.c hashmap.h hashmap.c)
add_executable(tests lib/minunit.h hashmap.h hashmap.c tests.c)
