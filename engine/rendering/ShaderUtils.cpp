//
// Created by Krisna Pranav on 21/12/25.
//

#include "ShaderUtils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string loadTextFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}