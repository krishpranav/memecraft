//
// Created by Krisna Pranav on 21/12/25.
//

#include "Window.hpp"
#include "engine/core/Logger.hpp"
#include <stdexcept>

Window::Window(int width, int height, const std::string &title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    Logger::log(LogLevel::Info, "Window created");
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
    Logger::log(LogLevel::Info, "Window destroyed");
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    // TODO
}
