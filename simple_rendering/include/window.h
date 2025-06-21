#pragma once

#include <string>
#include <unordered_map>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./renderable/renderable.h"

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();

    GLFWwindow * getGLFWWindow();

    void setClearColor(float r, float g, float b, float a);

    bool isClose();

    void makeContextCurrent();
    void clear();
    void close();
    void destroy();

    void rename(std::string title);
    void resize(int width, int height);
    
    void render();

    template<typename R, typename... Args>
    void createRenderable(std::string renderableIdentifyName, Args&&... args);
    bool isRenderableExist(std::string renderableIdentifyName);
    template<typename R>
    R& getRenderable(std::string renderableIdentifyName);

private:
    struct ClearColor {
        float r = 0;
        float g = 0;
        float b = 0;
        float a = 1;
    };

    GLFWwindow * window;
    ClearColor clearColor;
    std::unordered_map<std::string, Renderable *> renderables;
};

#include "./window.tpp"
