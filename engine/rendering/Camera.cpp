//
// Created by Krisna Pranav on 21/12/25.
//

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspect) {
    projMat = glm::perspective(
        glm::radians(70.0f),
        aspect,
        0.1f,
        1000.0f
    );

    position = {0.0f, 0.0f, 0.0f};
    viewMat  = glm::mat4(1.0f);
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Camera::lookAt(const glm::vec3& target) {
    viewMat = glm::lookAt(position, target, {0,1,0});
}

const glm::mat4& Camera::view() const { return viewMat; }
const glm::mat4& Camera::projection() const { return projMat; }