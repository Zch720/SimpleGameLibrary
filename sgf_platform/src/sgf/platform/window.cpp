#include <stdexcept>
#include "../../../include/sgf/platform/window.h"

namespace sgf_core {
    const std::string WindowTag::TypeName = "Window";
    const std::string Window::TypeName = "Window";

    Window::Window(const Id & id, const Construct & constructParameter) {
        this->id = id;

        window = glfwCreateWindow(
            constructParameter.width,
            constructParameter.height,
            constructParameter.title.c_str(),
            nullptr,
            nullptr
        );
        if (window == nullptr) {
            throw std::runtime_error("Failed to create GLFW window");
        }
    }

    Window::~Window() {
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
}
