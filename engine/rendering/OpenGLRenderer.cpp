#include "OpenGLRenderer.hpp"
#include "ShaderUtils.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

OpenGLRenderer::OpenGLRenderer(int width, int height)
    : cam(static_cast<float>(width) / height) {

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.60f, 0.78f, 0.92f, 1.0f);

    auto vert = loadTextFile("shaders/voxel.vert");
    auto frag = loadTextFile("shaders/voxel.frag");

    voxelShader = new Shader(vert, frag);
}

OpenGLRenderer::~OpenGLRenderer() {
    delete voxelShader;
    voxelShader = nullptr;
}

void OpenGLRenderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::endFrame() {}

void OpenGLRenderer::beginScene() {

    // ✅ SAFE GUARD
    if (!voxelShader) return;

    voxelShader->bind();

    GLuint program = voxelShader->program();
    if (program == 0) return;

    glm::mat4 viewProj = cam.projection() * cam.view();
    voxelShader->setMat4("u_ViewProj", viewProj);
    voxelShader->setMat4("u_Model", glm::mat4(1.0f));

    // ---- uniforms ----
    const glm::vec3& camPos = cam.getPosition();

    GLint camLoc = glGetUniformLocation(program, "u_CameraPos");
    if (camLoc >= 0)
        glUniform3f(camLoc, camPos.x, camPos.y, camPos.z);

    GLint radiusLoc = glGetUniformLocation(program, "u_WorldRadius");
    if (radiusLoc >= 0)
        glUniform1f(radiusLoc, 500.0f);
}

void OpenGLRenderer::endScene() {
    if (voxelShader)
        voxelShader->unbind();
}

void OpenGLRenderer::setModelMatrix(const glm::mat4& model) {
    if (voxelShader)
        voxelShader->setMat4("u_Model", model);
}

Camera& OpenGLRenderer::camera() {
    return cam;
}