//
// Created by Krisna Pranav on 21/12/25.
//

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspect)
    : aspectRatio(aspect)
{
    projMat = glm::perspective(
        glm::radians(70.0f),
        aspectRatio,
        0.1f,
        2000.0f
    );

    position = { 0.0f, 80.0f, 0.0f };
    forward  = { 0.0f, -1.0f, -1.0f };
    up       = { 0.0f,  1.0f,  0.0f };

    updateView();
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
    updateView();
}

void Camera::lookAt(const glm::vec3& target) {
    forward = glm::normalize(target - position);
    updateView();
}

void Camera::updateView() {
    viewMat = glm::lookAt(
        position,
        position + forward,
        up
    );
}

const glm::mat4& Camera::view() const {
    return viewMat;
}

const glm::mat4& Camera::projection() const {
    return projMat;
}

const glm::vec3& Camera::getPosition() const {
    return position;
}

const glm::vec3& Camera::getForward() const {
    return forward;
}