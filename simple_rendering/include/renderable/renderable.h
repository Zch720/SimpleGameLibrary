#pragma once

#include <string>
#include <glm/matrix.hpp>
#include "../shader_manager.h"

class Renderable {
public:
    void render() const;
    void setColor(float r, float g, float b, float a);

    glm::vec3 position() const;
    void position(const glm::vec3 & position);
    void translate(const glm::vec3 & translate);
    void translateX(const float delta);
    void translateY(const float delta);
    void translateZ(const float delta);

    glm::vec3 scale() const;
    void scale(const glm::vec3 & scale);
    void scaleX(const float scale);
    void scaleY(const float scale);
    void scaleZ(const float scale);

    /**
     * Get the rotation of the object in degrees.
    */
    glm::vec3 rotation() const;
    /**
     * Set the rotation of the object in degrees.
    */
    void rotation(const glm::vec3 & rotation);
    /**
     * Rotate the object by the given vector. The vector is in degrees.
    */
    void rotate(const glm::vec3 & rotate);
    /**
     * Rotate the object with x-axis as its central axis by the given angle in degrees.
    */
    void rotateX(const float rotate);
    /**
     * Rotate the object with y-axis as its central axis by the given angle in degrees.
    */
    void rotateY(const float rotate);
    /**
     * Rotate the object with z-axis as its central axis by the given angle in degrees.
    */
    void rotateZ(const float rotate);

protected:
    Renderable();
    Renderable(const std::string & windowIdentifyName, ShaderId shaderId);

    virtual void renderImpl() const = 0;
    virtual glm::mat4 calculateTransformationMatrix() const;

    std::string windowIdentifyName;
    ShaderId shaderId;
    glm::vec4 color;

    glm::vec3 positionValue;
    glm::vec3 scaleValue;
    glm::vec3 rotationValue;
};