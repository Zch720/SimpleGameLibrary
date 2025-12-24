#pragma once

#include <string>
#include <vector>
#include <queue>
#include "./window_id.h"
#include "./renderable/renderable_id.h"

class Window;

class WindowManager {
public:
    static WindowManager & Instance();

    bool isWindowExist(WindowId id);
    bool isWindowClose(WindowId id);

    WindowId createWindow(int width, int height, std::string title);
    void useWindow(WindowId id);
    void clearAll();
    void terminate();

    void clearWindow(WindowId id);
    void closeWindow(WindowId id);
    void destroyWindow(WindowId id);
    void renameWindow(WindowId id, std::string newTitle);
    void resizeWindow(WindowId id, int width, int height);
    void setWindowColor(WindowId id, float r, float g, float b, float a);
    void renderWindow(WindowId id);

    RenderableId createRenderable(WindowId id, Mesh * mesh, Material * material);
    Renderable& getRenderable(WindowId id, RenderableId renderableId);

protected:
    WindowManager();
    ~WindowManager();

private:
    static WindowManager instance;

    bool isRunning;
    bool isFirstWindow;
    std::vector<Window *> windows;
    std::vector<uint64_t> generation;
    std::queue<uint64_t> freeId;

    void initGlfw();
    void initGlfwWindowHint();
    void initGlad();

    WindowId newWindowId();
    void checkWindowExist(WindowId id);
};
