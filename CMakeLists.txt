cmake_minimum_required(VERSION 4.1)
project(memecraft
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(glfw3 REQUIRED)

set(ENGINE_CORE_SOURCES
        engine/core/Application.cpp
        engine/core/GameLoop.cpp
        engine/core/Time.cpp
        engine/core/Logger.cpp
        engine/core/Config.cpp
)

set(PLATFORM_SOURCES
        engine/platform/Window.cpp
)

set(RENDERING_SOURCES
        engine/rendering/Mesh.hpp
        engine/rendering/Vertex.hpp
)

set(THREADING_SOURCES
        engine/threading/JobSystem.cpp
)

set(WORLD_ENGINE_SOURCES
        engine/world/WorldSystem.cpp
)

set(WORLD_SOURCES
        game/world/Chunk.cpp
        game/world/WorldGenerator.cpp
        game/world/ChunkManager.cpp
        game/world/BlockRegistry.cpp
        game/world/Mesher.cpp
)

add_executable(memecraft
        main.cpp
        ${ENGINE_CORE_SOURCES}
        ${PLATFORM_SOURCES}
        ${THREADING_SOURCES}
        ${WORLD_SOURCES}
)

target_include_directories(memecraft
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(memecraft
        PRIVATE
        glfw
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    target_compile_options(memecraft PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wconversion
            -Wno-unused-parameter
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(memecraft PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

if(APPLE)
    target_compile_definitions(memecraft PRIVATE MEMECRAFT_PLATFORM_MACOS)
elseif(WIN32)
    target_compile_definitions(memecraft PRIVATE MEMECRAFT_PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(memecraft PRIVATE MEMECRAFT_PLATFORM_LINUX)
endif()