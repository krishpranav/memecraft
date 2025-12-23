//
// Created by Krisna Pranav on 21/12/25.
//

#include "Raycast.hpp"
#include <cmath>

static int sign(float v) { return (v > 0) - (v < 0); }

bool raycastBlock(
    const glm::vec3& origin,
    const glm::vec3& dir,
    float maxDist,
    ChunkManager& world,
    RaycastHit& hit
) {
    if (glm::length(dir) < 0.0001f) return false;

    glm::vec3 rayDir = glm::normalize(dir);

    int x = static_cast<int>(std::floor(origin.x));
    int y = static_cast<int>(std::floor(origin.y));
    int z = static_cast<int>(std::floor(origin.z));

    glm::ivec3 step(sign(rayDir.x), sign(rayDir.y), sign(rayDir.z));

    glm::vec3 tDelta(
        step.x != 0 ? std::abs(1.0f / rayDir.x) : 1e30f,
        step.y != 0 ? std::abs(1.0f / rayDir.y) : 1e30f,
        step.z != 0 ? std::abs(1.0f / rayDir.z) : 1e30f
    );

    glm::vec3 tMax(
        step.x > 0 ? (x + 1 - origin.x) * tDelta.x : (origin.x - x) * tDelta.x,
        step.y > 0 ? (y + 1 - origin.y) * tDelta.y : (origin.y - y) * tDelta.y,
        step.z > 0 ? (z + 1 - origin.z) * tDelta.z : (origin.z - z) * tDelta.z
    );

    float dist = 0.0f;
    int face = -1;

    while (dist < maxDist) {
        BlockID block = world.getBlock(x, y, z);
        if (block != 0) {
            hit.wx = x;
            hit.wy = y;
            hit.wz = z;
            hit.face = face;
            hit.hit = true;
            return true;
        }

        if (tMax.x < tMax.y && tMax.x < tMax.z) {
            dist = tMax.x;
            tMax.x += tDelta.x;
            x += step.x;
            face = step.x > 0 ? 0 : 1;
        } else if (tMax.y < tMax.z) {
            dist = tMax.y;
            tMax.y += tDelta.y;
            y += step.y;
            face = step.y > 0 ? 2 : 3;
        } else {
            dist = tMax.z;
            tMax.z += tDelta.z;
            z += step.z;
            face = step.z > 0 ? 4 : 5;
        }
    }

    hit.hit = false;
    return false;
}
