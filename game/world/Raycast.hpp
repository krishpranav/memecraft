//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include <glm/glm.hpp>
#include "ChunkManager.hpp"

struct RaycastHit {
    int wx = 0, wy = 0, wz = 0;
    int face = -1;
    bool hit = false;
};

bool raycastBlock(
    const glm::vec3& origin,
    const glm::vec3& direction,
    float maxDistance,
    ChunkManager& world,
    RaycastHit& outHit
);