#pragma once

#include <string>
#include <glm/vec2.hpp>
#include "./polygon.h"

using namespace glm;

class WindowId;
class ShaderId;
class Window;

class Triangle : public Polygon {
public:
    friend Window;

    ~Triangle();

private:
    Triangle(RenderableId renderableId, ShaderId shaderId, const glm::vec2 & point1, const glm::vec2 & point2, const glm::vec2 & point3);
};