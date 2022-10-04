cmake_minimum_required(VERSION 3.22)
project(embedder)

include_directories(embedder
    /usr/include/python3.8
)

add_executable(embedder
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

target_link_libraries(embedder
    /usr/lib/python3.8/config-3.8-x86_64-linux-gnu/libpython3.8.so
)