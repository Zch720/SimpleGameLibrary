cmake_minimum_required(VERSION 3.14)
project(simple_game_framework)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_TESTS "Build SGF tests" OFF)

include(FetchContent)

if (SGF_TESTS)
    # get googletest package
    if(CMAKE_VERSION VERSION_LESS 3.24)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        )
    else()
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
            DOWNLOAD_EXTRACT_TIMESTAMP 1
        )
    endif()

    if(NOT UNIX)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    set(BUILD_GMOCK OFF)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
endif()

# get sgf_rendering, sgf_platform
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/sgf_rendering
    ${CMAKE_BINARY_DIR}/bin/sgf_rendering
    EXCLUDE_FROM_ALL
)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/sgf_platform
    ${CMAKE_BINARY_DIR}/bin/sgf_platform
    EXCLUDE_FROM_ALL
)

if (SGF_TESTS)
    # create unit test executable
    add_executable(
        simple_game_framework_test
        test/ut_all.cpp
    )
    set_target_properties(simple_game_framework_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(simple_game_framework_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(simple_game_framework_test
        GTest::gtest_main
        sgf_rendering
        sgf_platform
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(simple_game_framework_test)
endif()