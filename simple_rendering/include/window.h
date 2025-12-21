#pragma once

#include <string>
#include <queue>
#include <vector>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./window_id.h"
#include "./renderable/renderable_id.h"
#include "./renderable/renderable.h"

class Window {
public:
    Window(WindowId id, int width, int height, std::string title);
    ~Window();

    WindowId getId() const;
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

    RenderableId createRenderable(Mesh * mesh, Material * material);
    bool isRenderableExist(RenderableId renderableId);
    Renderable & getRenderable(RenderableId renderableId);

private:
    struct ClearColor {
        float r = 0;
        float g = 0;
        float b = 0;
        float a = 1;
    };

    WindowId id;
    GLFWwindow * window;
    ClearColor clearColor;
    std::vector<Renderable *> renderables;
    std::vector<uint64_t> renderablesGenertrion;
    std::queue<uint64_t> renderablesFreeId;

    RenderableId newRenderableId();
};
