#pragma once

class Time {
public:
    static void init();
    static void update();

    static float deltaTime();
    static double timeSinceStart();

private:
    static double lastTime;
    static float delta;
};