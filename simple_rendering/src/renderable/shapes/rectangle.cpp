#include "../../../include/renderable/shapes/rectangle.h"
#include "../../../include/shader_manager.h"

Rectangle::Rectangle(RenderableId renderableId, ShaderId shaderId, const glm::vec2 & point1, const glm::vec2 & point2, const glm::vec2 & point3, const glm::vec2 & point4) :
        Polygon(renderableId, shaderId, {point1, point2, point3, point4}) {
}

Rectangle::~Rectangle() {
}