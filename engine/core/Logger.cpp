#include "Logger.hpp"
#include <iostream>
#include <ctime>

static const char* levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARN";
        case LogLevel::Error: return "ERROR";
    }
    return "UNKNOWN";
}

void Logger::init() {
    log(LogLevel::Info, "Logger initialized");
}

void Logger::log(LogLevel level, const std::string& message) {
    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now));

    std::cout << "[" << buf << "] "
              << levelToString(level) << ": "
              << message << std::endl;
}