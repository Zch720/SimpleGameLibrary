#include "../../../include/renderable/shapes/polygon.h"
#include <algorithm>
#include <unordered_set>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../../../include/shader_manager.h"
#include "../../../include/window_manager.h"

Polygon::Polygon() :
        Renderable(),
        vao(0),
        vbo(0),
        ebo(0),
        vertices(),
        indices() {
}

Polygon::Polygon(WindowId windowId, ShaderId shaderId, const std::vector<glm::vec2> & points) :
        Renderable(windowId, shaderId),
        vertices(),
        indices() {
    for (size_t i = 0; i < points.size(); i++) {
        vertices.push_back(points[i].x);
        vertices.push_back(points[i].y);
        vertices.push_back(0.0f);
    }
    calculateIndices(points);
    bindGlDatas();
}

Polygon::Polygon(const Polygon & other) : Renderable(other), vertices(other.vertices), indices(other.indices) {
    bindGlDatas();
}

Polygon::~Polygon() {
    deleteGlDatas();
}

Polygon & Polygon::operator=(const Polygon & other) {
    if (this == &other) return * this;

    deleteGlDatas();

    Renderable::operator=(other);
    vertices = other.vertices;
    indices = other.indices;
    bindGlDatas();
    
    return * this;
}

std::vector<glm::vec2> Polygon::SortConvexPolygonVertices(const std::vector<glm::vec2> & points) {
    std::vector<glm::vec2> sortedPoints = points;
    glm::vec2 centerPoint = glm::vec2(0.0f, 0.0f);
    for (glm::vec2 point : points) centerPoint += point;
    centerPoint /= points.size();
    std::sort(sortedPoints.begin(), sortedPoints.end(), [](const glm::vec2 & a, const glm::vec2 & b) {
        return atan2(a.y, a.x) < atan2(b.y, b.x);
    });
    return sortedPoints;
}

void Polygon::renderImpl() const {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool towPointAtSameSideOfLine(const glm::vec2 & p1, const glm::vec2 & p2, const glm::vec2 & a, const glm::vec2 & b) {
    return ((p1.x - a.x) * (b.y - a.y) - (b.x - a.x) * (p1.y - a.y)) * ((p2.x - a.x) * (b.y - a.y) - (b.x - a.x) * (p2.y - a.y)) > 0;
}

bool checkPointInsideTriangle(const glm::vec2 & p, const glm::vec2 & a, const glm::vec2 & b, const glm::vec2 & c) {
    return towPointAtSameSideOfLine(p, a, b, c) && towPointAtSameSideOfLine(p, b, a, c) && towPointAtSameSideOfLine(p, c, a, b);
}

void Polygon::deleteGlDatas() {
    if (vao == 0) return;
    if (!WindowManager::Instance().isWindowExist(windowId)) return;
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    vao = 0;
    vbo = 0;
    ebo = 0;
}

void Polygon::calculateIndices(const std::vector<glm::vec2> & points) {
    std::vector<int> leftPoints;

    for (int i = 0; i < points.size(); i++) leftPoints.push_back(i);

    while (leftPoints.size() > 2) {
        for (int i = 0; i < leftPoints.size(); i++) {
            int apos = i;
            int bpos = (i + 1) % leftPoints.size();
            int cpos = (i + leftPoints.size() - 1) % leftPoints.size();

            int j;
            for (j = 0; j < leftPoints.size(); j++) {
                if (j == apos || j == bpos || j == cpos) continue;
                if (checkPointInsideTriangle(points[leftPoints[j]], points[leftPoints[apos]], points[leftPoints[bpos]], points[leftPoints[cpos]])) {
                    break;
                }
            }
            if (j != leftPoints.size()) continue;

            indices.push_back(leftPoints[apos]);
            indices.push_back(leftPoints[bpos]);
            indices.push_back(leftPoints[cpos]);
            leftPoints.erase(leftPoints.begin() + i);
            break;
        }
    }
}

void Polygon::bindGlDatas() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
