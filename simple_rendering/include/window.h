#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, std::string title);

    GLFWwindow * getGLFWWindow();

    void setClearColor(float r, float g, float b, float a);

    bool isClose();

    void makeContextCurrent();
    void clear();
    void close();
    void destroy();

    void rename(std::string title);
    void resize(int width, int height);

private:
    struct ClearColor {
        float r = 0;
        float g = 0;
        float b = 0;
        float a = 1;
    };

    GLFWwindow * window;
    ClearColor clearColor;
};