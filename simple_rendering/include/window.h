#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, std::string title);

    GLFWwindow * getGLFWWindow();

    void makeContextCurrent();

private:
    GLFWwindow * window;
};