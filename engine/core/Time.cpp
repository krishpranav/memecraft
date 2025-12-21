#include "Time.hpp"
#include <GLFW/glfw3.h>

double Time::lastTime = 0.0;
float Time::delta = 0.0f;

void Time::init() {
    lastTime = glfwGetTime();
}

void Time::update() {
    double current = glfwGetTime();
    delta = static_cast<float>(current - lastTime);
    lastTime = current;
}

float Time::deltaTime() {
    return delta;
}

double Time::timeSinceStart() {
    return glfwGetTime();
}