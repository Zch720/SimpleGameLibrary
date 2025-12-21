#include <stdexcept>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/window.h"
#include "../include/window_manager.h"

WindowManager WindowManager::instance;

WindowManager & WindowManager::Instance() {
    return instance;
}

WindowManager::WindowManager() {
    isFirstWindow = true;
    isRunning = false;
    windows = {};
}

WindowManager::~WindowManager() {
    terminate();
}

bool WindowManager::isWindowExist(WindowId id) {
    if (id.getId() == 0 && id.getGen() == 0) {
        return false;
    }
    if (id.getId() - 1 < windows.size() && id.getGen() == generation[id.getId() - 1]) {
        return true;
    }
    return false;
}

bool WindowManager::isWindowClose(WindowId id) {
    checkWindowExist(id);
    return windows[id.getId() - 1]->isClose();
}

WindowId WindowManager::createWindow(int width, int height, std::string title) {
    if (isFirstWindow) initGlfw();

    WindowId windowId = newWindowId();
    Window * newWindow = new Window(windowId, width, height, title);
    windows[windowId.getId() - 1] = newWindow;

    if (isFirstWindow) {
        newWindow->makeContextCurrent();
        initGlad();
        glEnable(GL_DEPTH_TEST);
        isFirstWindow = false;
        isRunning = true;
    }

    return windowId;
}

void WindowManager::useWindow(WindowId id) {
    checkWindowExist(id);
    windows[id.getId() - 1]->makeContextCurrent();
}

void WindowManager::clearAll() {
    for (Window * window : windows) {
        window->clear();
    }
}

void WindowManager::terminate() {
    if (!isRunning) return;
    for (Window * window : windows) {
        if (window) {
            window->destroy();
            delete window;
        }
    }
    windows.clear();
    generation.clear();
    while (!freeId.empty()) {
        freeId.pop();
    }
    glfwTerminate();
    isFirstWindow = true;
    isRunning = false;
}

void WindowManager::clearWindow(WindowId id) {
    checkWindowExist(id);
    windows[id.getId() - 1]->clear();
}

void WindowManager::closeWindow(WindowId id) {
    checkWindowExist(id);
    windows[id.getId() - 1]->close();
}

void WindowManager::destroyWindow(WindowId id) {
    checkWindowExist(id);
    windows[id.getId() - 1]->destroy();
    delete windows[id.getId() - 1];
    windows[id.getId() - 1] = nullptr;
    generation[id.getId() - 1]++;
    freeId.push(id.getId());
}

void WindowManager::renameWindow(WindowId id, std::string newTitle) {
    checkWindowExist(id);
    windows[id.getId() - 1]->rename(newTitle);
}

void WindowManager::resizeWindow(WindowId id, int width, int height) {
    checkWindowExist(id);
    windows[id.getId() - 1]->resize(width, height);
}

void WindowManager::setWindowColor(WindowId id, float r, float g, float b, float a) {
    checkWindowExist(id);
    windows[id.getId() - 1]->setClearColor(r, g, b, a);
}

void WindowManager::renderWindow(WindowId id) {
    checkWindowExist(id);
    windows[id.getId() - 1]->render();
}

RenderableId WindowManager::createRenderable(WindowId id, Mesh * mesh, Material * material) {
    checkWindowExist(id);
    return windows[id.getId() - 1]->createRenderable(mesh, material);
}

Renderable& WindowManager::getRenderable(WindowId id, RenderableId renderableId) {
    checkWindowExist(id);
    return windows[id.getId() - 1]->getRenderable(renderableId);
}

void WindowManager::initGlfw() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    initGlfwWindowHint();
}

void WindowManager::initGlfwWindowHint() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void WindowManager::initGlad() {
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

WindowId WindowManager::newWindowId() {
    WindowId windowId;
    if (freeId.empty()) {
        windows.push_back(nullptr);
        generation.push_back(1);
        windowId = WindowId(windows.size(), 1);
    } else {
        uint64_t id = freeId.front();
        freeId.pop();
        windowId = WindowId(id, generation[id - 1]);
    }
    return windowId;
}

void WindowManager::checkWindowExist(WindowId id) {
    if (!isWindowExist(id)) {
        throw std::runtime_error("Cannot find window with id: " + std::to_string(id.getId()) + ", gen: " + std::to_string(id.getId()));
    }
}