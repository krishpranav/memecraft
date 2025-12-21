#include "GameLoop.hpp"
#include "Time.hpp"
#include "Logger.hpp"
#include "Config.hpp"

#include "engine/platform/Window.hpp"
#include "game/world/ChunkManager.hpp"
#include "game/world/Mesher.hpp"

void GameLoop::run() {
    Window window(
        Config::engine().windowWidth,
        Config::engine().windowHeight,
        Config::engine().windowTitle
    );

    ChunkManager world(1337);
    Mesher mesher;

    Time::init();

    while (!window.shouldClose()) {
        Time::update();

        world.update(playerChunkX, playerChunkZ);
        playerChunkX++;

        world.forEachChunk([&](Chunk& chunk) {
            if (chunk.dirty) {
                mesher.buildMesh(chunk);
                chunk.dirty = false;
            }
        });

        window.pollEvents();
    }

    Logger::log(LogLevel::Info, "Game loop exited cleanly");
}