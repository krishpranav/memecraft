//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();

private:
    GLFWwindow* window = nullptr;
};