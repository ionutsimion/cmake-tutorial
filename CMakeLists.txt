cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0.0)
configure_file(config.in config.hxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Tutorial src/tutorial.cxx)

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")

