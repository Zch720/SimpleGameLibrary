#include <stdexcept>
#include "../include/window.h"

RenderableId::RenderableId(): id(0), gen(0) {
}

RenderableId::RenderableId(WindowId windowId, uint64_t id, uint64_t gen): windowId(windowId), id(id), gen(gen) {
}

WindowId RenderableId::getWindowId() const {
    return windowId;
}

uint64_t RenderableId::getId() const {
    return id;
}

uint64_t RenderableId::getGen() const {
    return gen;
}

Window::Window(WindowId id, int width, int height, std::string title): id(id) {
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
}

Window::~Window() {
}

WindowId Window::getId() const {
    return id;
}

GLFWwindow * Window::getGLFWWindow() {
    return window;
}

void Window::setClearColor(float r, float g, float b, float a) {
    clearColor.r = r;
    clearColor.g = g;
    clearColor.b = b;
    clearColor.a = a;
    // TODO: maybe glClearColor should be removed from here
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close() {
    glfwSetWindowShouldClose(window, true);
}

void Window::destroy() {
    if (window != nullptr) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

void Window::rename(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void Window::resize(int width, int height) {
    glfwSetWindowSize(window, width, height);
}

void Window::render() {
    clear();
    for (auto r : renderables) {
        r->render();
    }
}

bool Window::isRenderableExist(RenderableId renderableId) {
    if (renderableId.getWindowId() != id) {
        return false;
    }
    if (renderableId.getId() == 0 && renderableId.getGen() == 0) {
        return false;
    } else if (renderableId.getId() - 1 < renderables.size() && renderableId.getGen() == renderablesGenertrion[renderableId.getId() - 1]) {
        return true;
    }
    return false;
}

RenderableId Window::newRenderableId() {
    RenderableId renderableId;
    if (renderablesFreeId.empty()) {
        renderables.push_back(nullptr);
        renderablesGenertrion.push_back(1);
        renderableId = RenderableId(id, renderables.size(), 1);
    } else {
        uint64_t freeId = renderablesFreeId.front();
        renderablesFreeId.pop();
        renderableId = RenderableId(id, freeId, renderablesGenertrion[freeId - 1]);
    }
    return renderableId;
}
