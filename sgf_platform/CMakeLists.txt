cmake_minimum_required(VERSION 3.14)
project(sgf_platform)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_PLATFORM_TESTS "Build sgf_platform tests" OFF)

include(FetchContent)

if (SGF_PLATFORM_TESTS)
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

# get GLFW package
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG dc46d3f8129712e42856c20e99a604a3b08ad581
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# get GLAD package
FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG 73db193f853e2ee079bf3ca8a64aa2eaf6459043
    SOURCE_SUBDIR cmake
)
FetchContent_MakeAvailable(glad)
glad_add_library(
    glad_sgf_platform
    STATIC
    REPRODUCIBLE
    LOADER
    API gl:compatibility=3.3
)

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

# create sgf_platform library
file(GLOB_RECURSE sgf_platform_sources src/*.cpp)

add_library(sgf_platform ${sgf_platform_sources})
target_include_directories(sgf_platform
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(sgf_platform
    PUBLIC
        sgf_utils
    PRIVATE
        glfw
        glad_sgf_platform
)

if (SGF_PLATFORM_TESTS)
    # create unit test executable
    add_executable(
        sgf_platform_unit_test
        test/unit_test/ut_all.cpp
    )
    set_target_properties(sgf_platform_unit_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_platform_unit_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_platform_unit_test
        GTest::gtest_main
        sgf_platform
    )

    target_compile_definitions(sgf_platform_unit_test
        PRIVATE
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_platform_unit_test)
endif()