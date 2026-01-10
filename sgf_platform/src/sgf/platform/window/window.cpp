#include "../../../../include/sgf/platform/window/window.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace sgf_core {
    const std::string WindowTag::TypeName = "Window";
    const std::string Window::TypeName = "Window";

    struct Window::WindowImpl {
        GLFWwindow * window;
    };

    Window::Window(const Id & id, const Construct & constructParameter) {
        this->id = id;

        impl = std::make_unique<WindowImpl>();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        
        impl->window = glfwCreateWindow(
            constructParameter.width,
            constructParameter.height,
            constructParameter.title.c_str(),
            nullptr,
            nullptr
        );
        if (impl->window == nullptr) {
            throw std::runtime_error("Failed to create GLFW window");
        }
    }

    Window::~Window() {
        glfwSetWindowUserPointer(impl->window, nullptr);
        glfwDestroyWindow(impl->window);
    }

    void Window::setClearColor(float r, float g, float b, float a) {
        clearColor.r = r;
        clearColor.g = g;
        clearColor.b = b;
        clearColor.a = a;
        // TODO: maybe glClearColor should be removed from here
        glClearColor(r, g, b, a);
    }

    bool Window::isClose() const {
        return glfwWindowShouldClose(impl->window);
    }

    void Window::makeContextCurrent() {
        glfwMakeContextCurrent(impl->window);
    }

    void Window::swapBuffer() {
        glfwSwapBuffers(impl->window);
    }

    void Window::clearBuffer(uint32_t bits) {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | bits);
    }

    void Window::close() {
        glfwSetWindowShouldClose(impl->window, true);
    }

    void Window::rename(std::string title) {
        glfwSetWindowTitle(impl->window, title.c_str());
    }

    void Window::resize(int width, int height) {
        glfwSetWindowSize(impl->window, width, height);
    }
}
