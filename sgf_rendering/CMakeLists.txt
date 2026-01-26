cmake_minimum_required(VERSION 3.14)
project(sgf_rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SGF_RENDERING_TESTS "Build sgf_rendering tests" OFF)

include(FetchContent)

if (SGF_RENDERING_TESTS)
    # get googletest package
    if(CMAKE_VERSION VERSION_LESS 3.24)
        FetchContent_Declare(googletest
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
    set(BUILD_GMOCK OFF)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    # get GLFW package
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG dc46d3f8129712e42856c20e99a604a3b08ad581
    )
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)
endif()

# get GLAD package
FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG 73db193f853e2ee079bf3ca8a64aa2eaf6459043
    SOURCE_SUBDIR cmake
)
FetchContent_MakeAvailable(glad)
glad_add_library(
    glad_sgf_rendering
    STATIC
    REPRODUCIBLE
    LOADER
    API gl:compatibility=3.3
)

# get glm package
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 8d1fd52e5ab5590e2c81768ace50c72bae28f2ed
)
FetchContent_MakeAvailable(glm)

# get stb headers
FetchContent_Declare(stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG f1c79c02822848a9bed4315b12c8c8f3761e1296
    SOURCE_SUBDIR "MADE-UP-DIRECTORY"
)
FetchContent_MakeAvailable(stb)

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

# create sgf_rendering library
file(GLOB_RECURSE sgf_rendering_sources src/*.cpp)

add_library(sgf_rendering ${sgf_rendering_sources})
target_include_directories(sgf_rendering
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${FETCHCONTENT_BASE_DIR}/stb-src
)
target_link_libraries(sgf_rendering
    PUBLIC
        sgf_utils
        glm::glm
    PRIVATE
        glad_sgf_rendering
)

if (SGF_RENDERING_TESTS)
    # create unit test executable
    add_executable(sgf_rendering_test
        test/ut_all.cpp
    )
    set_target_properties(sgf_rendering_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        OUTPUT_NAME "ut_all"
    )
    target_compile_options(sgf_rendering_test
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/Wall>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wfatal-errors>
    )
    target_link_libraries(sgf_rendering_test
        GTest::gtest_main
        glfw
        glad_sgf_rendering
        sgf_utils
        sgf_rendering
    )

    target_compile_definitions(sgf_rendering_test
        PRIVATE
            SGF_RENDERING_UNSAFE
            PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
            TEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources"
    )

    # googletest
    include(GoogleTest)
    gtest_discover_tests(sgf_rendering_test)
endif()