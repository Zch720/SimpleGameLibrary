cmake_minimum_required(VERSION 3.14)
project(sgf_audio)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_AUDIO_TESTS "Build sgf_audio tests" OFF)

include(FetchContent)

if (SGF_AUDIO_TESTS)
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

# get openal-soft package
FetchContent_Declare(openal_soft
    GIT_REPOSITORY git@github.com:kcat/openal-soft.git
    GIT_TAG 75c00596307bf05ba7bbc8c7022836bf52f17477
)
SET(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
SET(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
SET(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(openal_soft)

# add sgf_utils package
find_package(sgf_utils CONFIG QUIET)
if (NOT TARGET sgf_utils)
    message(STATUS "sgf_utils target not found, adding as subdirectory")
    add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../sgf_utils
        ${CMAKE_BINARY_DIR}/bin/sgf_utils
        EXCLUDE_FROM_ALL
    )
endif()

#create sgf_audio library
file (GLOB_RECURSE sgf_audio_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(sgf_audio ${sgf_audio_sources})
target_include_directories(sgf_audio
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(sgf_audio
    PUBLIC
        sgf_utils
    PRIVATE
        OpenAL::OpenAL
)

if (SGF_AUDIO_TESTS)
    add_executable(sgf_audio_unit_test
        test/ut_all.cpp
    )
    set_target_properties(sgf_audio_unit_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_audio_unit_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_audio_unit_test
        GTest::gtest_main
        sgf_audio
    )

    target_compile_definitions(sgf_audio_unit_test
        PRIVATE
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_audio_unit_test)
endif()
