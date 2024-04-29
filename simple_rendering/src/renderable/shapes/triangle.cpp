#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include "../../../include/renderable/shapes/triangle.h"
#include "../../../include/shader_manager.h"

Triangle::Triangle(const std::string & windowIdentifyName, const std::string & shaderIdentifyName, const glm::vec2 & point1, const glm::vec2 & point2, const glm::vec2 & point3) :
        Polygon(windowIdentifyName, shaderIdentifyName, {point1, point2, point3}) {
}

Triangle::~Triangle() {
}