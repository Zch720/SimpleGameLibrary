#pragma once

#include <glm/matrix.hpp>

namespace sgf_core {
    class Projection {
    public:
        enum Type {
            ORTHOGRAPHIC,
            PERSPECTIVE,
        };

        struct ProjectionData {
            Type type;
            float width;
            float height;
            float near;
            float far;
            float fieldOfView;
        };

        Projection();
        Projection(const ProjectionData & data);

        glm::mat4 getProjectionMatrix() const;

        void setProjectionData(const ProjectionData & data);

        Type type() const;
        void type(const Type type);

        float width() const;
        void width(const float width);
        
        float height() const;
        void height(const float height);

        float near() const;
        void near(const float near);

        float far() const;
        void far(const float far);

        float fieldOfView() const;
        void fieldOfView(const float fieldOfView);

    private:
        ProjectionData data;

        glm::mat4 projectionMatrix;

        void calculateProjection();
    };
}