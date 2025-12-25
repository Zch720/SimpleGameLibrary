#pragma once

#include <stdint.h>
#include <stddef.h>
#include <vector>

class VertexLayout {
public:
    struct VertexAttr {
        uint32_t index;
        uint32_t size;
        /**
         * Allow types:
         * - GL_BYTE
         * - GL_UNSIGNED_BYTE
         * - GL_SHORT
         * - GL_UNSIGNED_SHORT
         * - GL_INT
         * - GL_UNSIGNED_INT
         * - GL_HALF_FLOAT
         * - GL_FLOAT
         * - GL_DOUBLE
         * - GL_INT_2_10_10_10_REV
         * - GL_UNSIGNED_INT_2_10_10_10_REV
         * - GL_UNSIGNED_INT_10F_11F_11F_REV
        */
        uint32_t type;
        bool normalized;
        size_t offset;
    };

    size_t getStride() const;

    void addAttribute(VertexAttr attr);
    void apply() const;

private:
    std::vector<VertexAttr> attrs;
    size_t stride = 0;
};
