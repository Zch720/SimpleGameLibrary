#include <glm/gtc/matrix_transform.hpp>
#include "../../include/renderable/renderable.h"
#include "../../include/window_manager.h"
#include "../../include/shader_manager.h"

Renderable::Renderable() :
        shaderIdentifyName(""),
        color(1.0f),
        positionValue(0.0f),
        scaleValue(1.0f),
        rotationValue(0.0f) {
}

Renderable::Renderable(const std::string & windowIdentifyName, const std::string & shaderIdentifyName) :
        windowIdentifyName(windowIdentifyName),
        shaderIdentifyName(shaderIdentifyName),
        color(1.0f),
        positionValue(0.0f),
        scaleValue(1.0f),
        rotationValue(0.0f) {
}

void Renderable::render() const {
    WindowManager::Instance().useWindow(windowIdentifyName);
    ShaderManager::Instance().useShader(shaderIdentifyName);
    ShaderManager::Instance().setShaderVec4UniformVariable(shaderIdentifyName, "color", color);
    glm::mat4 transformationMatrix = calculateTransformationMatrix();
    ShaderManager::Instance().setShaderMat4UniformVariable(shaderIdentifyName, "transform", transformationMatrix);
    renderImpl();
}

void Renderable::setColor(float r, float g, float b, float a) {
    color = glm::vec4(r, g, b, a);
}

glm::vec3 Renderable::position() const {
    return positionValue;
}

void Renderable::position(const glm::vec3 & position) {
    positionValue = position;
}

void Renderable::translate(const glm::vec3 & translate) {
    positionValue += translate;
}

void Renderable::translateX(const float delta) {
    positionValue.x += delta;
}

void Renderable::translateY(const float delta) {
    positionValue.y += delta;
}

void Renderable::translateZ(const float delta) {
    positionValue.z += delta;
}

glm::vec3 Renderable::scale() const {
    return scaleValue;
}

void Renderable::scale(const glm::vec3 & scale) {
    scaleValue = scale;
}

void Renderable::scaleX(const float scale) {
    scaleValue.x = scale;
}

void Renderable::scaleY(const float scale) {
    scaleValue.y = scale;
}

void Renderable::scaleZ(const float scale) {
    scaleValue.z = scale;
}

glm::vec3 Renderable::rotation() const {
    return rotationValue;
}

void Renderable::rotation(const glm::vec3 & rotation) {
    rotationValue = rotation;
}

void Renderable::rotate(const glm::vec3 & rotate) {
    rotationValue += rotate;
}

void Renderable::rotateX(const float rotate) {
    rotationValue.x += rotate;
}

void Renderable::rotateY(const float rotate) {
    rotationValue.y += rotate;
}

void Renderable::rotateZ(const float rotate) {
    rotationValue.z += rotate;
}

glm::mat4 Renderable::calculateTransformationMatrix() const {
    glm::mat4 transformationMatrix(1.0f);
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotationValue.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotationValue.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotationValue.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transformationMatrix = glm::translate(transformationMatrix, positionValue);
    transformationMatrix = glm::scale(transformationMatrix, scaleValue);
    return transformationMatrix;
}