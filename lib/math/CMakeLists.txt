add_library(Math src/math.cxx)

target_include_directories(Math
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<INSTALL_INTERFACE:include>
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}")

option(USE_CUSTOM_MATH "Use custom math library" ON)
if(USE_CUSTOM_MATH)
    target_compile_definitions(Math PRIVATE USE_CUSTOM_MATH)

    add_executable(MakeTable src/make-table.cxx)

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

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/table.hxx
            COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/table.hxx
            DEPENDS MakeTable)

    # library that just does sqrt
    add_library(SqrtLibrary STATIC src/custom-sqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/table.hxx)

    # add compile definitions
    if(HAVE_LOG AND HAVE_EXP)
        target_compile_definitions(SqrtLibrary PRIVATE "HAVE_LOG" "HAVE_EXP")
    endif()

    target_include_directories(SqrtLibrary PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}")

    # state that SqrtLibrary needs PIC when the default is shared library
    set_target_properties(SqrtLibrary PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBRARIES})

    target_link_libraries(Math PRIVATE SqrtLibrary)
endif()

# define the symbol stating we are using declspec(dllexport) when building on windows
target_compile_definitions(Math PRIVATE "EXPORTING_MATH")

# install rules
set(installable_libs Math tutorial_compiler_flags)
if(TARGET SqrtLibrary)
    list(APPEND installable_libs SqrtLibrary)
endif()
install(TARGETS ${installable_libs}
        DESTINATION lib
        EXPORT MathTargets)
install(FILES src/math.hxx ${CMAKE_CURRENT_BINARY_DIR}/table.hxx DESTINATION include)
