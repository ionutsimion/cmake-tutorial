add_library(Math src/math.cxx)

include(CheckSymbolExists)
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)
if(NOT (HAVE_LOG AND HAVE_EXP))
    unset(HAVE_LOG CACHE)
    unset(HAVE_EXP CACHE)
    set(CMAKE_REQUIRED_LIBRARIES "m")
    check_symbol_exists(log "math.h" HAVE_LOG)
    check_symbol_exists(exp "math.h" HAVE_EXP)
endif()

if(HAVE_LOG AND HAVE_EXP)
    target_link_libraries(Math PRIVATE m)
endif()

target_include_directories(Math INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" PRIVATE "${CMAKE_BINARY_DIR}")

install(TARGETS Math DESTINATION lib)
install(FILES src/math.hxx DESTINATION include)

