#pragma once

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "../renderable.h"

using namespace glm;

class Polygon : public Renderable {
public:
    Polygon();
    Polygon(const std::string & windowIdentifyName, const std::string & shaderIdentifyName, const std::vector<glm::vec2> & points);
    Polygon(const Polygon & other);
    ~Polygon();

    Polygon & operator=(const Polygon & other);

    static std::vector<glm::vec2> SortConvexPolygonVertices(const std::vector<glm::vec2> & points);

protected:
    void renderImpl() const override;

private:
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;

    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    void deleteGlDatas();
    
    void calculateIndices(const std::vector<glm::vec2> & points);
    void bindGlDatas();
};