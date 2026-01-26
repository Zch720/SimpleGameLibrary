#include "../../../include/sgf/rendering/projection.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sgf_core {
    Projection::Projection():
        data({
            .type = Type::ORTHOGRAPHIC,
            .width = 0,
            .height = 0,
            .near = 0,
            .far = 0,
            .fieldOfView = 0
        }),
        projectionMatrix(1.0f)
    {
    }

    Projection::Projection(const ProjectionData & data):
        data(data)
    {
        calculateProjection();
    }

    glm::mat4 Projection::getProjectionMatrix() const {
        return projectionMatrix;
    }

    void Projection::setProjectionData(const ProjectionData & data) {
        this->data = data;
        calculateProjection();
    }

    Projection::Type Projection::type() const {
        return data.type;
    }

    void Projection::type(const Type type) {
        data.type = type;
        calculateProjection();
    }

    float Projection::width() const {
        return data.width;
    }

    void Projection::width(const float width) {
        data.width = width;
        calculateProjection();
    }

    float Projection::height() const {
        return data.height;
    }

    void Projection::height(const float height) {
        data.height = height;
        calculateProjection();
    }

    float Projection::near() const {
        return data.near;
    }

    void Projection::near(const float near) {
        data.near = near;
        calculateProjection();
    }

    float Projection::far() const {
        return data.far;
    }

    void Projection::far(const float far) {
        data.far = far;
        calculateProjection();
    }

    float Projection::fieldOfView() const {
        return data.fieldOfView;
    }

    void Projection::fieldOfView(const float fieldOfView) {
        data.fieldOfView = fieldOfView;
        calculateProjection();
    }

    void Projection::calculateProjection() {
        if (data.type == Type::ORTHOGRAPHIC) {
            projectionMatrix = glm::ortho(
                -data.width / 2, data.width / 2,
                -data.height / 2, data.height / 2,
                data.near, data.far
            );
        } else if (data.type == Type::PERSPECTIVE) {
            projectionMatrix = glm::perspective(
                glm::radians(data.fieldOfView),
                data.width / data.height,
                data.near, data.far
            );
        }
    }
}
