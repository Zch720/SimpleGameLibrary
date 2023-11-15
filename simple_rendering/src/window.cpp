#include <stdexcept>
#include "../include/window.h"

Window::Window(int width, int height, std::string title) {
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
}

GLFWwindow * Window::getGLFWWindow() {
    return window;
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(window);
}