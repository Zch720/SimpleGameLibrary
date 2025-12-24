#pragma once

#include <stdint.h>
#include "./vertex_layout.h"

class Mesh {
public:
    Mesh(const void * vertices, const size_t verticesCount, const uint32_t * indices, const size_t indicesCount, const VertexLayout & vertexLayout);
    ~Mesh();

    size_t getIndicesCount() const;

    void bind() const;
    void unbind() const;

private:
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    size_t verticesCount;
    size_t indicesCount;

    VertexLayout vertexLayout;
};
