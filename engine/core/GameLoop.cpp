// GameLoop.cpp
#include "GameLoop.hpp"
#include "Time.hpp"
#include "Logger.hpp"
#include "Config.hpp"

#include "engine/platform/Window.hpp"
#include "engine/rendering/OpenGLRenderer.hpp"
#include "engine/rendering/GLMesh.hpp"

#include "game/world/ChunkManager.hpp"
#include "game/world/Mesher.hpp"
#include "game/world/Raycast.hpp"
#include "game/player/Player.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <memory>
#include <cmath>

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
    Player player;

    std::unordered_map<Chunk*, std::unique_ptr<GLMesh>> gpuMeshes;

    // --- Spawn ---
    const int spawnX = 0;
    const int spawnZ = 0;

    world.update(0, 0);
    int groundY = world.getTerrainHeight(spawnX, spawnZ);

    player.setPosition(glm::vec3(
        spawnX + 0.5f,
        groundY + 10.0f,
        spawnZ + 0.5f
    ));

    Time::init();

    while (!window.shouldClose()) {
        Time::update();
        float dt = std::min(Time::deltaTime(), 0.05f);

        // ---- Input ----
        double dx, dy;
        window.getMouseDelta(dx, dy);
        player.setYaw(player.getYaw() + dx * 0.1f);
        player.setPitch(player.getPitch() + dy * 0.1f);

        glm::vec3 move{};
        if (window.isKeyPressed(GLFW_KEY_W)) move.z += 1;
        if (window.isKeyPressed(GLFW_KEY_S)) move.z -= 1;
        if (window.isKeyPressed(GLFW_KEY_A)) move.x -= 1;
        if (window.isKeyPressed(GLFW_KEY_D)) move.x += 1;
        if (window.isKeyPressed(GLFW_KEY_SPACE)) player.jump();
        player.setMoveInput(move);

        player.update(dt, world);

        renderer.camera().setPosition(player.getEyePosition());
        renderer.camera().lookAt(player.getEyePosition() + player.getForward());

        // ---- Chunk streaming ----
        glm::vec3 p = player.getPosition();
        world.update(
            (int)std::floor(p.x) / CHUNK_SIZE_X,
            (int)std::floor(p.z) / CHUNK_SIZE_Z
        );

        world.forEachChunk([&](Chunk& c) {
            if (!c.generated || !c.dirty) return;
            mesher.buildMesh(c);
            c.dirty = false;
            auto& mesh = gpuMeshes[&c];
            if (!mesh) mesh = std::make_unique<GLMesh>();
            mesh->upload(c.mesh);
        });

        // ---- Render ----
        renderer.beginFrame();
        renderer.beginScene();

        world.forEachChunk([&](Chunk& c) {
            auto it = gpuMeshes.find(&c);
            if (it == gpuMeshes.end()) return;

            glm::mat4 model = glm::translate(
                glm::mat4(1.0f),
                glm::vec3(
                    c.x * CHUNK_SIZE_X,
                    c.y * CHUNK_SIZE_Y,   // ✅ CRITICAL FIX
                    c.z * CHUNK_SIZE_Z
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

    Logger::log(LogLevel::Info, "Exited cleanly");
}