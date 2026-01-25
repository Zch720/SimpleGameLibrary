#include "../../../include/sgf/rendering/vertex_layout.h"
#include <glad/gl.h>

namespace sgf_core {
    uint32_t getGlType(VertexLayout::VertexType type) {
        switch (type) {
            case VertexLayout::VertexType::BYTE: return GL_BYTE;
            case VertexLayout::VertexType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
            case VertexLayout::VertexType::SHORT: return GL_SHORT;
            case VertexLayout::VertexType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
            case VertexLayout::VertexType::INT: return GL_INT;
            case VertexLayout::VertexType::UNSIGNED_INT: return GL_UNSIGNED_INT;
            case VertexLayout::VertexType::HALF_FLOAT: return GL_HALF_FLOAT;
            case VertexLayout::VertexType::FLOAT: return GL_FLOAT;
            case VertexLayout::VertexType::DOUBLE: return GL_DOUBLE;
            case VertexLayout::VertexType::INT_2_10_10_10_REV: return GL_INT_2_10_10_10_REV;
            case VertexLayout::VertexType::UNSIGNED_INT_2_10_10_10_REV: return GL_UNSIGNED_INT_2_10_10_10_REV;
            case VertexLayout::VertexType::UNSIGNED_INT_10F_11F_11F_REV: return GL_UNSIGNED_INT_10F_11F_11F_REV;
        }
        return 0;
    }

    size_t getTypeSize(VertexLayout::VertexType type) {
        switch (type) {
            case VertexLayout::VertexType::BYTE: return sizeof(int8_t);
            case VertexLayout::VertexType::UNSIGNED_BYTE: return sizeof(uint8_t);
            case VertexLayout::VertexType::SHORT: return sizeof(int16_t);
            case VertexLayout::VertexType::UNSIGNED_SHORT: return sizeof(uint16_t);
            case VertexLayout::VertexType::INT: return sizeof(int32_t);
            case VertexLayout::VertexType::UNSIGNED_INT: return sizeof(uint32_t);
            case VertexLayout::VertexType::HALF_FLOAT: return sizeof(int16_t);
            case VertexLayout::VertexType::FLOAT: return sizeof(float);
            case VertexLayout::VertexType::DOUBLE: return sizeof(double);
            case VertexLayout::VertexType::INT_2_10_10_10_REV: return sizeof(int32_t);
            case VertexLayout::VertexType::UNSIGNED_INT_2_10_10_10_REV: return sizeof(uint32_t);
            case VertexLayout::VertexType::UNSIGNED_INT_10F_11F_11F_REV: return sizeof(uint32_t);
        }
        return 0;
    }

    size_t VertexLayout::getStride() const {
        return stride;
    }

    void VertexLayout::addAttribute(VertexAttr attr) {
        attrs.push_back(attr);
        stride += attr.size * getTypeSize(attr.type);
    }

    void VertexLayout::apply() const {
        for (const VertexAttr & attr : attrs) {
            glVertexAttribPointer(attr.index, attr.size, getGlType(attr.type), attr.normalized ? GL_TRUE : GL_FALSE, stride, (void *)(attr.offset));
            glEnableVertexAttribArray(attr.index);
        }
    }
}
