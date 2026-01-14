cmake_minimum_required(VERSION 3.14)
project(sgf_utils)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_UTILS_TESTS "Build sgf_utils tests" OFF)

include(FetchContent)

if (SGF_UTILS_TESTS)
    # get googletest package
    if(CMAKE_VERSION VERSION_LESS 3.24)
        FetchContent_Declare(oogletest
            URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        )
    else()
        FetchContent_Declare(googletest
            URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
            DOWNLOAD_EXTRACT_TIMESTAMP 1
        )
    endif()

    if(NOT UNIX)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
endif()

# get fmt package
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 407c905e45ad75fc29bf0f9bb7c5c2fd3475976f
)
FetchContent_MakeAvailable(fmt)

# get spdlog package
FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG 486b55554f11c9cccc913e11a87085b2a91f706f
)
FetchContent_MakeAvailable(spdlog)

# create sgf_utils library
file(GLOB_RECURSE sgf_utils_sources src/*.cpp)

add_library(sgf_utils ${sgf_utils_sources})
target_include_directories(sgf_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(sgf_utils
    PUBLIC
        fmt::fmt
    PRIVATE
        spdlog::spdlog
)

if (SGF_UTILS_TESTS)
    # create unit test executable
    add_executable(sgf_utils_test
        test/ut_all.cpp
    )
    set_target_properties(sgf_utils_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_utils_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_utils_test
        GTest::gtest_main
        sgf_utils
    )
    target_compile_definitions(sgf_utils_test
        PRIVATE
            SGF_LOG
            SGF_DEBUG_LOG
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_utils_test)
endif()