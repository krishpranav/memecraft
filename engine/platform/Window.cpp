#include "Window.hpp"
#include "engine/core/Logger.hpp"

#include <glad/glad.h>
#include <stdexcept>

Window::Window(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    // Capture mouse
    setCursorLocked(true);

    Logger::log(LogLevel::Info, "OpenGL context created");
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
    glfwSwapBuffers(window);
}

bool Window::isKeyPressed(int key) const {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Window::setCursorLocked(bool locked) {
    glfwSetInputMode(
        window,
        GLFW_CURSOR,
        locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
    );
    firstMouse = true;
}

void Window::getMouseDelta(double& dx, double& dy) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    dx = x - lastMouseX;
    dy = lastMouseY - y; // inverted Y

    lastMouseX = x;
    lastMouseY = y;
}