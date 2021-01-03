add_executable(MakeTable src/make-table.cxx)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/table.hxx
                   COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/table.hxx
                   DEPENDS MakeTable)

add_library(Math src/math.cxx ${CMAKE_CURRENT_BINARY_DIR}/table.hxx) 

include(CheckSymbolExists)
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)
if(NOT (HAVE_LOG AND HAVE_EXP))
    unset(HAVE_LOG CACHE)
    unset(HAVE_EXP CACHE)
    set(CMAKE_REQUIRED_LIBRARIES "m")
    check_symbol_exists(log "math.h" HAVE_LOG)
    check_symbol_exists(exp "math.h" HAVE_EXP)

    if(HAVE_LOG AND HAVE_EXP)
        target_link_libraries(Math PRIVATE m)
    endif()
endif()

# add compile definitions
if(HAVE_LOG AND HAVE_EXP)
    target_compile_definitions(Math PRIVATE "HAVE_LOG" "HAVE_EXP")
endif()

target_include_directories(Math
        INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}")

install(TARGETS Math DESTINATION lib)
install(FILES src/math.hxx src/table.hxx DESTINATION include)
