#include "GameLoop.hpp"
#include "Time.hpp"
#include "Logger.hpp"
#include "engine/platform/Window.hpp"
#include "Config.hpp"
#include "game/world/ChunkManager.hpp"

void GameLoop::run() {
    Window window(
        Config::engine().windowWidth,
        Config::engine().windowHeight,
        Config::engine().windowTitle
    );

    ChunkManager world(1337);

    Time::init();

    while (!window.shouldClose()) {
        Time::update();

        world.update(playerChunkX, playerChunkZ);
        playerChunkX++;

        window.pollEvents();
    }

    Logger::log(LogLevel::Info, "Game loop exited cleanly");
}
