cmake_minimum_required(VERSION 3.10)

project(CGL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

if (MSVC)
set(ALL_LIBS glfw opengl32)
else()
set(ALL_LIBS glfw GL m)
endif()

file(GLOB SOURCES 
    src/engine/*.c
    src/util/*.c
    src/renderer/*.c
    src/glad.c
    src/stb_image.c
)

function(add_executable_common name)
    # Forward all arguments (including source files and other keywords) to add_executable
    add_executable(${ARGV})
    # Point to include directories
    target_include_directories(${name}
        SYSTEM PRIVATE external
    )
    target_include_directories(${name}
        PRIVATE src
    )
    if (MSVC)
        target_compile_options(light PRIVATE /W4)
    else()
        target_compile_options(light PRIVATE -Wall -Werror -Wextra)
    endif()
    # Link the created target to the common libraries
    target_link_libraries(${name} PRIVATE ${ALL_LIBS}) #
endfunction()

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

add_executable_common(light ${SOURCES} src/lighting.c)
add_executable_common(basics ${SOURCES} src/basics.c)

