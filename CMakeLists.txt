cmake_minimum_required(VERSION 3.25)

project(cpp_game
    VERSION 0.1.0
    DESCRIPTION "A 2D game built with SDL3"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Emit compile_commands.json so editors/clangd understand the build.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------
include(FetchContent)

# Build SDL as a shared library only, and skip the parts we don't need.
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)

FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.16
    GIT_SHALLOW    TRUE
    SYSTEM         # treat SDL headers as system headers: no warnings from them
)
FetchContent_MakeAvailable(SDL3)

# ---------------------------------------------------------------------------
# Game executable
# ---------------------------------------------------------------------------
add_executable(game
    src/main.cpp
)

target_link_libraries(game PRIVATE SDL3::SDL3)

target_compile_options(game PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Wshadow -Wconversion>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
)

# Copy SDL3.dll (and any other runtime DLLs) next to game.exe after each build
# so the game runs without PATH tweaks.
if(WIN32)
    add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:game> $<TARGET_FILE_DIR:game>
        COMMAND_EXPAND_LISTS
    )
endif()
