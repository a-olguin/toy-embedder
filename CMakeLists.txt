cmake_minimum_required(VERSION 3.22)
project(embedder)

include_directories(embedder
    /usr/include/python3.8
)

add_executable(embedder
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)
