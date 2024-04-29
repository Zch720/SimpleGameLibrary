#include "../../../include/renderable/shapes/rectangle.h"

Rectangle::Rectangle(const std::string & windowIdentifyName, const std::string & shaderIdentifyName, const glm::vec2 & point1, const glm::vec2 & point2, const glm::vec2 & point3, const glm::vec2 & point4) :
        Polygon(windowIdentifyName, shaderIdentifyName, {point1, point2, point3, point4}) {
}

Rectangle::~Rectangle() {
}