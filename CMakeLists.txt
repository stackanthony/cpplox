cmake_minimum_required(VERSION 3.10)
project(Lox)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpplox
    main.cpp
    classes/lox.cpp
)

target_include_directories(cpplox PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/classes
)
