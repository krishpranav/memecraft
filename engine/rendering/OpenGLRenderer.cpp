//
// Created by Krisna Pranav on 21/12/25.
//

#include "OpenGLRenderer.hpp"
#include "ShaderUtils.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

OpenGLRenderer::OpenGLRenderer(int width, int height)
    : cam(static_cast<float>(width) / height) {

    glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

    // glClearColor(0.53f, 0.75f, 0.98f, 1.0f);
    glClearColor(0.60f, 0.78f, 0.92f, 1.0f);

    auto vert = loadTextFile("shaders/voxel.vert");
    auto frag = loadTextFile("shaders/voxel.frag");

    voxelShader = new Shader(vert, frag);
}

void OpenGLRenderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::endFrame() {
    // swapBuffers handled by Window
}

void OpenGLRenderer::beginScene() {
    voxelShader->bind();

    glm::mat4 viewProj = cam.projection() * cam.view();
    voxelShader->setMat4("u_ViewProj", viewProj);

	voxelShader->setMat4("u_Model", glm::mat4(1.0f));
}

void OpenGLRenderer::endScene() {
    voxelShader->unbind();
}

void OpenGLRenderer::setModelMatrix(const glm::mat4& model) {
    voxelShader->setMat4("u_Model", model);
}

Camera& OpenGLRenderer::camera() {
    return cam;
}