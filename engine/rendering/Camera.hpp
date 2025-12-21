//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    Camera(float aspect);

    void setPosition(const glm::vec3& pos);
    void lookAt(const glm::vec3& target);

    const glm::mat4& view() const;
    const glm::mat4& projection() const;

private:
    glm::mat4 viewMat{};
    glm::mat4 projMat{};
    glm::vec3 position{};
};