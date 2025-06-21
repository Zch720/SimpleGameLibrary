#pragma once

#include <string>
#include <glm/vec2.hpp>
#include "./polygon.h"

using namespace glm;

class Window;

class Rectangle : public Polygon {
public:
    friend Window;

    ~Rectangle();

private:
    Rectangle(const std::string & windowIdentifyName, const std::string & shaderIdentifyName, const glm::vec2 & point1, const glm::vec2 & point2, const glm::vec2 & point3, const glm::vec2 & point4);
};