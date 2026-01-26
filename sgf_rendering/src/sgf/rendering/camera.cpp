#include "../../../include/sgf/rendering/camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sgf_core {
    Camera::Camera():
        positionValue(0.0f),
        rotationValue(0.0f),
        viewMatrix(1.0f)
    {
    }

    void Camera::update() {
        if (viewDirty) {
            calculateView();
        }
    }

    glm::mat4 Camera::getViewMatrix() const {
        return viewMatrix;
    }

    glm::mat4 Camera::getProjectionMatrix() const {
        return projectionData.getProjectionMatrix();
    }

    Projection & Camera::projection() {
        return projectionData;
    }

    const Projection & Camera::projection() const {
        return projectionData;
    }

    glm::vec3 Camera::position() const {
        return positionValue;
    }

    void Camera::position(const glm::vec3 & position) {
        positionValue = position;
        viewDirty = true;
    }

    void Camera::translate(const glm::vec3 & translation) {
        positionValue += translation;
        viewDirty = true;
    }

    void Camera::translateX(const float delta) {
        positionValue.x += delta;
        viewDirty = true;
    }

    void Camera::translateY(const float delta) {
        positionValue.y += delta;
        viewDirty = true;
    }

    void Camera::translateZ(const float delta) {
        positionValue.z += delta;
        viewDirty = true;
    }

    glm::vec3 Camera::rotation() const {
        return rotationValue;
    }

    void Camera::rotation(const glm::vec3 & rotation) {
        rotationValue = rotation;
        viewDirty = true;
    }

    void Camera::rotate(const glm::vec3 & rotate) {
        rotationValue += rotate;
        viewDirty = true;
    }

    void Camera::rotateX(const float delta) {
        rotationValue.x += delta;
        viewDirty = true;
    }

    void Camera::rotateY(const float delta) {
        rotationValue.y += delta;
        viewDirty = true;
    }

    void Camera::rotateZ(const float delta) {
        rotationValue.z += delta;
        viewDirty = true;
    }

    void Camera::calculateView() {
        glm::mat4 view(1.0f);
    
        view = glm::rotate(view, glm::radians(-rotationValue.x), glm::vec3(1, 0, 0));
        view = glm::rotate(view, glm::radians(-rotationValue.y), glm::vec3(0, 1, 0));
        view = glm::rotate(view, glm::radians(-rotationValue.z), glm::vec3(0, 0, 1));
    
        view = glm::translate(view, -positionValue);
    
        viewMatrix = view;

        viewDirty = false;
    }
}
