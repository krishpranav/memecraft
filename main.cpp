#include "engine/core/Application.hpp"
#include "engine/threading/JobSystem.hpp"
#include "game/world/BlockRegistry.hpp"
#include <thread>

int main() {
    BlockRegistry::init();
    JobSystem::init(std::thread::hardware_concurrency());

    Application app;
    app.run();

    JobSystem::shutdown();
    return 0;
}