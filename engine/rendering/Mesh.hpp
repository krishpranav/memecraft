//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include <vector>
#include "Vertex.hpp"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    void clear() {
        vertices.clear();
        indices.clear();
    }
};