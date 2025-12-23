//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include "Shader.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

class OpenGLRenderer : public Renderer {
public:
    OpenGLRenderer(int width, int height);
    ~OpenGLRenderer();

    void beginFrame() override;
    void endFrame() override;

    void beginScene();
    void endScene();

    void setModelMatrix(const glm::mat4& model);

    Camera& camera();

private:
    Camera cam;
    Shader* voxelShader = nullptr;
};