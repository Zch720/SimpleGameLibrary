#pragma once

#include <stdint.h>
#include <stddef.h>
#include <vector>

namespace sgf_core {
    class VertexLayout {
    public:
        enum VertexType {
            BYTE,
            UNSIGNED_BYTE,
            SHORT,
            UNSIGNED_SHORT,
            INT,
            UNSIGNED_INT,
            HALF_FLOAT,
            FLOAT,
            DOUBLE,
            INT_2_10_10_10_REV,
            UNSIGNED_INT_2_10_10_10_REV,
            UNSIGNED_INT_10F_11F_11F_REV,
        };

        struct VertexAttr {
            uint32_t index;
            uint32_t size;
            VertexType type;
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
}
