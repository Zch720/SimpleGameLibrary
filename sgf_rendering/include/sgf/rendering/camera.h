#pragma once

#include <glm/matrix.hpp>
#include "./projection.h"

namespace sgf_core {
    class Camera {
    public:
        Camera();

        void update();
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;

        Projection & projection();
        const Projection & projection() const;

        glm::vec3 position() const;
        void position(const glm::vec3 & position);
        void translate(const glm::vec3 & translation);
        void translateX(const float delta);
        void translateY(const float delta);
        void translateZ(const float delta);

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
        void rotateX(const float delta);
        /**
         * Rotate the object with y-axis as its central axis by the given angle in degrees.
        */
        void rotateY(const float delta);
        /**
         * Rotate the object with z-axis as its central axis by the given angle in degrees.
        */
        void rotateZ(const float delta);

    private:
        bool viewDirty;

        glm::vec3 positionValue;
        glm::vec3 rotationValue;

        glm::mat4 viewMatrix;

        Projection projectionData;

        void calculateView();
    };
}
