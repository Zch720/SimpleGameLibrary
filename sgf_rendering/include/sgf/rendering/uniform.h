#pragma once

#include <variant>
#include <glm/glm.hpp>

namespace sgf_core {
    enum UniformSource {
        TRANSFORM_MATRIX,
        RENDERABLE_COLOR,
        CUSTOM
    };

    using UniformType = std::variant<
        int,
        float,
        glm::vec2,
        glm::vec3,
        glm::vec4,
        glm::mat2,
        glm::mat3,
        glm::mat4,
        glm::mat2x3,
        glm::mat3x2,
        glm::mat2x4,
        glm::mat4x2,
        glm::mat3x4,
        glm::mat4x3
    >;
}
