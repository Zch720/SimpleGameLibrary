#include <stdexcept>
#include "../include/window.h"

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
    makeContextCurrent();
    for (auto r : renderables) {
        r->update();
        r->render();
    }
}

RenderableId Window::createRenderable(Mesh * mesh, Material * material) {
    RenderableId renderableId = newRenderableId();
    Renderable * r = new Renderable(renderableId, mesh, material);
    renderables[renderableId.getId() - 1] = r;
    return renderableId;
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

Renderable& Window::getRenderable(RenderableId renderableId) {
    if (!isRenderableExist(renderableId)) {
        throw new std::runtime_error("Connet find renderable with id: " + std::to_string(renderableId.getId()));
    }

    return *renderables[renderableId.getId() - 1];
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
