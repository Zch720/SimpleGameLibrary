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

void Window::setClearColor(float r, float g, float b, float a) {
    clearColor.r = r;
    clearColor.g = g;
    clearColor.b = b;
    clearColor.a = a;
    glClearColor(r, g, b, a);
}

bool Window::isClose() {
    return glfwWindowShouldClose(window);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(window);
}

void Window::clear() {
    makeContextCurrent();
    glfwSwapBuffers(window);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::close() {
    glfwSetWindowShouldClose(window, true);
}

void Window::destroy() {
    glfwDestroyWindow(window);
    window = nullptr;
}

void Window::rename(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void Window::resize(int width, int height) {
    glfwSetWindowSize(window, width, height);
}