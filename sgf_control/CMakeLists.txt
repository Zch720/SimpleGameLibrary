cmake_minimum_required(VERSION 3.14)
project(sgf_control)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_CONTROL_TESTS "Build sgf_platform tests" OFF)

include(FetchContent)

if (SGF_CONTROL_TESTS)
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

# add sgf_rendering package
find_package(sgf_rendering CONFIG QUIET)
if (NOT TARGET sgf_rendering)
    message(STATUS "sgf_rendering target not found, adding as subdirectory")
    add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_rendering
        ${CMAKE_BINARY_DIR}/bin/sgf_rendering
        EXCLUDE_FROM_ALL
    )
endif()

# add sgf_platform package
find_package(sgf_platform CONFIG QUIET)
if (NOT TARGET sgf_platform)
    message(STATUS "sgf_platform target not found, adding as subdirectory")
    add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_platform
        ${CMAKE_BINARY_DIR}/bin/sgf_platform
        EXCLUDE_FROM_ALL
    )
endif()

# create sgf_control library
file(GLOB_RECURSE sgf_control_sources src/*.cpp)

add_library(sgf_control ${sgf_control_sources})
target_include_directories(sgf_control
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(sgf_control
    PUBLIC
        sgf_rendering
        sgf_platform
)

if (SGF_CONTROL_TESTS)
    # create unit test executable
    add_executable(
        sgf_control_unit_test
        test/ut_all.cpp
    )
    set_target_properties(sgf_control_unit_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_control_unit_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_control_unit_test
        GTest::gtest_main
        sgf_control
    )

    target_compile_definitions(sgf_control_unit_test
        PRIVATE
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_control_unit_test)
endif()
