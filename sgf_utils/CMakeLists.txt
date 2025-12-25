cmake_minimum_required(VERSION 3.14)
project(sgf_utils)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include(FetchContent)
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

file(GLOB_RECURSE sgf_utils_sourecs src/*.cpp)

add_library(sgf_utils ${sgf_utils_sourecs})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(
    sgf_utils_test
    test/ut_all.cpp
)
set_target_properties(sgf_utils_test PROPERTIES OUTPUT_NAME "ut_all")
target_compile_options(sgf_utils_test PUBLIC -Wall -Wfatal-errors)
target_link_libraries(
    sgf_utils_test
    GTest::gtest_main
    sgf_utils
)

include(GoogleTest)
gtest_discover_tests(sgf_utils_test)