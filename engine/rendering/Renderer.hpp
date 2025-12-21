//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
};