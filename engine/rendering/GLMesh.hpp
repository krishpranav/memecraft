//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include <glad/glad.h>
#include "engine/rendering/Mesh.hpp"

class GLMesh {
public:
    GLMesh();
    ~GLMesh();

    void upload(const Mesh& mesh);
    void draw() const;

private:
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
    unsigned int indexCount = 0;
};