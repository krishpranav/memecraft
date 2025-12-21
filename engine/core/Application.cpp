//
// Created by Krisna Pranav on 21/12/25.
//

#include "Application.hpp"
#include "Logger.hpp"
#include "GameLoop.hpp"

void Application::run() {
    Logger::init();

    GameLoop loop;
    loop.run();
}
