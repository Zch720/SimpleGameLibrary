#include "../../../include/sgf/rendering/mesh.h"
#include <glad/gl.h>

const std::string MeshTag::TypeName = "Mesh";
const std::string Mesh::TypeName = "Mesh";

Mesh::Mesh(const Id & id, const Construct & constructParameter):
    verticesCount(constructParameter.verticesCount),
    indicesCount(constructParameter.indicesCount),
    vertexLayout(constructParameter.vertexLayout) {
    this->id = id;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexLayout.getStride() * verticesCount, constructParameter.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indicesCount, constructParameter.indices, GL_STATIC_DRAW);

    vertexLayout.apply();

    unbind();
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

size_t Mesh::getVerticesCount() const {
    return verticesCount;
}

size_t Mesh::getIndicesCount() const {
    return indicesCount;
}

void Mesh::bind() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Mesh::unbind() const {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}