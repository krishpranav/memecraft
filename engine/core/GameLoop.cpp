#include "GameLoop.hpp"

#include "Time.hpp"
#include "Logger.hpp"
#include "Config.hpp"

#include "engine/platform/Window.hpp"
#include "engine/rendering/OpenGLRenderer.hpp"
#include "engine/rendering/GLMesh.hpp"

#include "game/world/ChunkManager.hpp"
#include "game/world/Mesher.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>

void GameLoop::run() {
    Window window(
        Config::engine().windowWidth,
        Config::engine().windowHeight,
        Config::engine().windowTitle
    );

    OpenGLRenderer renderer(
        Config::engine().windowWidth,
        Config::engine().windowHeight
    );

    ChunkManager world(1337);
    Mesher mesher;

    std::unordered_map<Chunk*, std::unique_ptr<GLMesh>> gpuMeshes;

    renderer.camera().setPosition({ 32.0f, 80.0f, 32.0f });
    renderer.camera().lookAt({ 32.0f, 0.0f, 32.0f });

    Time::init();

    while (!window.shouldClose()) {
        Time::update();

        world.update(playerChunkX, playerChunkZ);
        playerChunkX++;

        world.forEachChunk([&](Chunk& chunk) {
            if (chunk.dirty) {
                mesher.buildMesh(chunk);
                chunk.dirty = false;

                Logger::log(
                    LogLevel::Info,
                    "Chunk vertices: " + std::to_string(chunk.mesh.vertices.size())
                );

                auto& meshPtr = gpuMeshes[&chunk];
                if (!meshPtr) {
                    meshPtr = std::make_unique<GLMesh>();
                }
                meshPtr->upload(chunk.mesh);
            }
        });

        renderer.beginFrame();
        renderer.beginScene();

        world.forEachChunk([&](Chunk& chunk) {
            auto it = gpuMeshes.find(&chunk);
            if (it == gpuMeshes.end() || !it->second) return;

            glm::mat4 model(1.0f);
            model = glm::translate(
                model,
                glm::vec3(
                    chunk.x * CHUNK_SIZE_X,
                    0.0f,
                    chunk.z * CHUNK_SIZE_Z
                )
            );

            renderer.setModelMatrix(model);
            it->second->draw();
        });

        renderer.endScene();
        renderer.endFrame();

        window.swapBuffers();
        window.pollEvents();
    }

    Logger::log(LogLevel::Info, "Game loop exited cleanly");
}