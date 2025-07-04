cmake_minimum_required(VERSION 3.14)
project(simple_rendering)

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

add_subdirectory(../ext bin/ext EXCLUDE_FROM_ALL)

file(GLOB third_party_includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../ext/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../ext/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../ext/glm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../ext/stb/include
)
file(GLOB_RECURSE simple_rendering_sources src/*.cpp)

add_library(simple_rendering ${simple_rendering_sources})
target_include_directories(
    simple_rendering
    PRIVATE
    ${third_party_includes}
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(
    simple_rendering_test
    test/ut_all.cpp
)
set_target_properties(simple_rendering_test PROPERTIES OUTPUT_NAME "ut_all")
target_compile_options(simple_rendering_test PUBLIC -Wall -Wfatal-errors)
target_include_directories(
    simple_rendering_test
    PRIVATE
    ${third_party_includes}
)
target_link_libraries(
    simple_rendering_test
    GTest::gtest_main
    glfw
    glad
    simple_rendering
)

target_compile_definitions(
    simple_rendering_test
    PRIVATE
    PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
    TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
)

include(GoogleTest)
gtest_discover_tests(simple_rendering_test)