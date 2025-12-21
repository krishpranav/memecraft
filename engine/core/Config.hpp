#pragma once

#include <string>

struct EngineConfig {
    int windowWidth = 1280;
    int windowHeight = 720;
    std::string windowTitle = "Memecraft Engine";
    bool vsync = true;
};

class Config {
public:
    static EngineConfig& engine();
};