add_library(Math src/math.cxx)

target_include_directories(Math PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(Math INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
