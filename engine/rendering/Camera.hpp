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

    const glm::vec3& getPosition() const;

private:
    glm::vec3 position{0};
    glm::vec3 forward{0,0,-1};
    glm::vec3 up{0,1,0};
    float aspectRatio = 1.0f;

    glm::mat4 viewMat{1.0f};
    glm::mat4 projMat{1.0f};

    void updateView();
};