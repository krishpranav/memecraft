//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once
#include <glm/glm.hpp>

class ChunkManager;

struct AABB {
    glm::vec3 min;
    glm::vec3 max;

    bool intersects(const AABB& other) const {
        return (min.x <= other.max.x && max.x >= other.min.x) &&
               (min.y <= other.max.y && max.y >= other.min.y) &&
               (min.z <= other.max.z && max.z >= other.min.z);
    }
};

class Player {
public:
    Player();

    void update(float dt, ChunkManager& world);

    void setMoveInput(const glm::vec3& input);
    void setYaw(float yaw);
    void setPitch(float pitch);
    void jump();

    const glm::vec3& getPosition() const { return position; }
    const glm::vec3& getVelocity() const { return velocity; }
    glm::vec3 getEyePosition() const { return position + glm::vec3(0, eyeHeight, 0); }
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    float getYaw() const { return yaw; }
    float getPitch() const { return pitch; }
    bool isGrounded() const { return grounded; }
    void setPosition(const glm::vec3& pos) { position = pos; }

    AABB getBoundingBox() const;

    static constexpr float width = 0.6f;
    static constexpr float height = 1.8f;
    static constexpr float eyeHeight = 1.62f;

private:
    glm::vec3 position{32.0f, 160.0f, 32.0f};
    glm::vec3 velocity{0.0f};
    glm::vec3 moveInput{0.0f};

    float yaw = 45.0f;
    float pitch = -45.0f;

    bool grounded = false;
    bool jumpRequested = false;

    static constexpr float gravity = 32.0f;
    static constexpr float jumpVelocity = 9.0f;
    static constexpr float moveSpeed = 4.317f;
    static constexpr float sprintMultiplier = 1.3f;
    static constexpr float airControl = 0.2f;
    static constexpr float groundFriction = 0.9f;
    static constexpr float terminalVelocity = 78.4f;

    void applyGravity(float dt);
    void applyMovement(float dt);
    void resolveCollisions(ChunkManager& world);
    void resolveCollisionAxis(ChunkManager& world, int axis);
    bool checkCollision(ChunkManager& world, const AABB& box) const;
};
