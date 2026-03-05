cmake_minimum_required(VERSION 3.10)

project(CGL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SOURCES src/*.c)

add_executable(game ${SOURCES})
target_include_directories(game 
    SYSTEM PRIVATE external
)
target_include_directories(game 
    PRIVATE src
)
if (MSVC)
    target_compile_options(game PRIVATE /W4 /WX)
else()
    target_compile_options(game PRIVATE -Wall -Wextra -Werror)
endif()

include(FetchContent)

find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    message(STATUS "GLFW not found, fetching from GitHub...")

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )

    FetchContent_MakeAvailable(glfw)
endif()

target_link_libraries(game
    m
    glfw
    GL
)
