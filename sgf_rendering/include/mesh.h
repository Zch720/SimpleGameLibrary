#pragma once

#include <stdint.h>
#include <resource.h>
#include "./mesh_id.h"
#include "./vertex_layout.h"

class UnsafeGLContext;

class Mesh: public Resource<Mesh, MeshId> {
public:
    static const std::string TypeName;
    struct Construct {
        void * vertices;
        size_t verticesCount;
        uint32_t * indices;
        size_t indicesCount;
        const VertexLayout & vertexLayout;
    };

    Mesh(const Id & id, const Construct & constructParameter);
    ~Mesh();

    size_t getVerticesCount() const;
    size_t getIndicesCount() const;

    void bind() const;
    void unbind() const;

private:
    friend UnsafeGLContext;

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    size_t verticesCount;
    size_t indicesCount;

    VertexLayout vertexLayout;
};
