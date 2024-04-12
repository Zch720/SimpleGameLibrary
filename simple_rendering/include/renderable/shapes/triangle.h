#pragma once

#include <string>
#include <glm/vec2.hpp>
#include "./polygon.h"

using namespace glm;

class Triangle : public Polygon {
public:
    Triangle(const std::string & shaderIdentifyName, const glm::vec2 & point1, const glm::vec2 & point2, const glm::vec2 & point3);
    ~Triangle();
};