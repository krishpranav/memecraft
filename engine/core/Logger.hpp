#pragma once

#include <string>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    static void init();
    static void log(LogLevel leve, const std::string& message);
};