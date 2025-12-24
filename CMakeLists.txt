cmake_minimum_required(VERSION 3.14)
project(simple_game_framework)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sgf_rendering EXCLUDE_FROM_ALL)

file(GLOB third_party_includes
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/glm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/stb/include
    ${CMAKE_CURRENT_SOURCE_DIR}/sgf_rendering/include
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(
    simple_game_framework_test
    test/ut_all.cpp
)
set_target_properties(simple_game_framework_test PROPERTIES OUTPUT_NAME "ut_all")
target_compile_options(simple_game_framework_test PUBLIC -Wall -Wfatal-errors)
target_include_directories(
    simple_game_framework_test
    PRIVATE
    ${third_party_includes}
)
target_link_libraries(
    simple_game_framework_test
    GTest::gtest_main
    glfw
    glad
    sgf_rendering
)

include(GoogleTest)
gtest_discover_tests(simple_game_framework_test)