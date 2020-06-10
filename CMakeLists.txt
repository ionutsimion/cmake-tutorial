cmake_minimum_required(VERSION 3.10)

option(USE_CUSTOM_MATH "Use custom math library" ON)

project(Tutorial VERSION 1.0.0)
configure_file(config.in config.hxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(Tutorial src/tutorial.cxx)

# Add math library
if (USE_CUSTOM_MATH)
    add_subdirectory(lib/math)
    list(APPEND EXTRA_LIBS Math)
endif()

target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")
