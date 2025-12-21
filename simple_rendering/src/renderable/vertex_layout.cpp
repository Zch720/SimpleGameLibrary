#include "../../include/renderable/vertex_layout.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

size_t getTypeSize(GLenum glType) {
    switch (glType) {
        case GL_BYTE: return sizeof(int8_t);
        case GL_UNSIGNED_BYTE: return sizeof(uint8_t);
        case GL_SHORT: return sizeof(int16_t);
        case GL_UNSIGNED_SHORT: return sizeof(uint16_t);
        case GL_INT: return sizeof(int32_t);
        case GL_UNSIGNED_INT: return sizeof(uint32_t);
        case GL_HALF_FLOAT: return sizeof(int16_t);
        case GL_FLOAT: return sizeof(float);
        case GL_DOUBLE: return sizeof(double);
        case GL_INT_2_10_10_10_REV: return sizeof(int32_t);
        case GL_UNSIGNED_INT_2_10_10_10_REV: return sizeof(uint32_t);
        case GL_UNSIGNED_INT_10F_11F_11F_REV: return sizeof(uint32_t);
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
        glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized ? GL_TRUE : GL_FALSE, stride, (void *)(attr.offset));
        glEnableVertexAttribArray(attr.index);
    }
}