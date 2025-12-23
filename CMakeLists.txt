cmake_minimum_required(VERSION 3.21)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(memecraft
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include(FetchContent)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        v0.1.36
)

FetchContent_MakeAvailable(glad)

if(APPLE)
    target_link_libraries(glad PUBLIC "-framework OpenGL")
endif()

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

set(THREADING_SOURCES
        engine/threading/JobSystem.cpp
)

set(WORLD_SOURCES
        game/world/Chunk.cpp
        game/world/WorldGenerator.cpp
        game/world/ChunkManager.cpp
        game/world/BlockRegistry.cpp
        game/world/Mesher.cpp
        game/world/Raycast.cpp
        game/world/Collision.cpp
        game/world/Biome.cpp
        game/world/TreeGenerator.cpp
)

set(PLAYER_SOURCES
        game/player/Player.cpp
)

set(RENDERING_SOURCES
        engine/rendering/GLMesh.cpp
        engine/rendering/OpenGLRenderer.cpp
        engine/rendering/Camera.cpp
        engine/rendering/Shader.cpp
        engine/rendering/ShaderUtils.cpp
)

add_executable(memecraft
        main.cpp
        ${ENGINE_CORE_SOURCES}
        ${PLATFORM_SOURCES}
        ${THREADING_SOURCES}
        ${WORLD_SOURCES}
        ${PLAYER_SOURCES}
        ${RENDERING_SOURCES}
)


target_include_directories(memecraft
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(memecraft
        PRIVATE
        glfw
        glm::glm
        glad
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    target_compile_options(memecraft PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wconversion
            -Wno-unused-parameter
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
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

file(GLOB SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/engine/rendering/shaders/*")
file(COPY ${SHADER_FILES} DESTINATION "${CMAKE_BINARY_DIR}/shaders")