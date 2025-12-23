//
// Created by Krisna Pranav on 21/12/25.
//

#include "Player.hpp"
#include "game/world/ChunkManager.hpp"
#include "game/world/Collision.hpp"
#include <cmath>
#include <algorithm>

Player::Player() {}

void Player::update(float dt, ChunkManager& world) {
    dt = std::min(dt, 0.05f);

    applyGravity(dt);
    applyMovement(dt);

    grounded = false;

    position.y += velocity.y * dt;
    resolveCollisionAxis(world, 1);

    position.x += velocity.x * dt;
    resolveCollisionAxis(world, 0);

    position.z += velocity.z * dt;
    resolveCollisionAxis(world, 2);

    if (jumpRequested && grounded) {
        velocity.y = jumpVelocity;
        grounded = false;
    }
    jumpRequested = false;

    moveInput = glm::vec3(0.0f);
}

void Player::setMoveInput(const glm::vec3& input) {
    moveInput = input;
}

void Player::setYaw(float y) {
    yaw = y;
}

void Player::setPitch(float p) {
    pitch = glm::clamp(p, -89.0f, 89.0f);
}

void Player::jump() {
    // if (grounded) {
    //     jumpRequested = true;
    // }
    jumpRequested = true;
}

glm::vec3 Player::getForward() const {
    return glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));
}

glm::vec3 Player::getRight() const {
    glm::vec3 forward = getForward();
    return glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
}

AABB Player::getBoundingBox() const {
    float halfWidth = width * 0.5f;
    return AABB{
        glm::vec3(position.x - halfWidth, position.y, position.z - halfWidth),
        glm::vec3(position.x + halfWidth, position.y + height, position.z + halfWidth)
    };
}

void Player::applyGravity(float dt) {
    if (!grounded) {
        velocity.y -= gravity * dt;
        velocity.y = std::max(velocity.y, -terminalVelocity);
    }
}

void Player::applyMovement(float dt) {
    if (glm::length(moveInput) < 0.001f) {
        velocity.x *= groundFriction;
        velocity.z *= groundFriction;
        return;
    }

    glm::vec3 flatForward = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)),
        0.0f,
        sin(glm::radians(yaw))
    ));
    glm::vec3 flatRight = glm::normalize(glm::cross(flatForward, glm::vec3(0, 1, 0)));

    glm::vec3 moveDir = flatForward * moveInput.z + flatRight * moveInput.x;
    if (glm::length(moveDir) > 0.001f) {
        moveDir = glm::normalize(moveDir);
    }

    float speed = moveSpeed;
    float control = grounded ? 1.0f : airControl;

    velocity.x = moveDir.x * speed * control + velocity.x * (1.0f - control);
    velocity.z = moveDir.z * speed * control + velocity.z * (1.0f - control);
}

bool Player::checkCollision(ChunkManager& world, const AABB& box) const {
    int minX = static_cast<int>(std::floor(box.min.x));
    int minY = static_cast<int>(std::floor(box.min.y));
    int minZ = static_cast<int>(std::floor(box.min.z));
    int maxX = static_cast<int>(std::floor(box.max.x));
    int maxY = static_cast<int>(std::floor(box.max.y));
    int maxZ = static_cast<int>(std::floor(box.max.z));

    for (int y = minY; y <= maxY; ++y) {
        for (int z = minZ; z <= maxZ; ++z) {
            for (int x = minX; x <= maxX; ++x) {
                if (isSolidBlock(world, x, y, z)) {
                    AABB blockBox{
                        glm::vec3(x, y, z),
                        glm::vec3(x + 1, y + 1, z + 1)
                    };
                    if (box.intersects(blockBox)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Player::resolveCollisions(ChunkManager& world) {
    resolveCollisionAxis(world, 1);
    resolveCollisionAxis(world, 0);
    resolveCollisionAxis(world, 2);
}

void Player::resolveCollisionAxis(ChunkManager& world, int axis) {
    AABB box = getBoundingBox();

    int minX = static_cast<int>(std::floor(box.min.x));
    int minY = static_cast<int>(std::floor(box.min.y));
    int minZ = static_cast<int>(std::floor(box.min.z));
    int maxX = static_cast<int>(std::floor(box.max.x));
    int maxY = static_cast<int>(std::floor(box.max.y));
    int maxZ = static_cast<int>(std::floor(box.max.z));

    for (int y = minY; y <= maxY; ++y) {
        for (int z = minZ; z <= maxZ; ++z) {
            for (int x = minX; x <= maxX; ++x) {
                if (!isSolidBlock(world, x, y, z)) continue;

                AABB blockBox{
                    glm::vec3(x, y, z),
                    glm::vec3(x + 1, y + 1, z + 1)
                };

                if (!box.intersects(blockBox)) continue;

                if (axis == 0) {
                    if (velocity.x > 0) {
                        position.x = x - width * 0.5f - 0.001f;
                    } else if (velocity.x < 0) {
                        position.x = x + 1 + width * 0.5f + 0.001f;
                    }
                    velocity.x = 0;
                } else if (axis == 1) {
                    if (velocity.y > 0) {
                        position.y = y - height - 0.001f;
                    } else if (velocity.y < 0) {
                        position.y = y + 1 + 0.001f;
                        grounded = true;
                    }
                    velocity.y = 0;
                } else if (axis == 2) {
                    if (velocity.z > 0) {
                        position.z = z - width * 0.5f - 0.001f;
                    } else if (velocity.z < 0) {
                        position.z = z + 1 + width * 0.5f + 0.001f;
                    }
                    velocity.z = 0;
                }

                box = getBoundingBox();
            }
        }
    }

    if (axis == 1) {
        AABB feetBox = getBoundingBox();
        feetBox.min.y -= 0.05f;
        feetBox.max.y = feetBox.min.y + 0.1f;

        if (!checkCollision(world, feetBox)) {
            grounded = false;
        }
    }
}
