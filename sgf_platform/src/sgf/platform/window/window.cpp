#include "../../../../include/sgf/platform/window/window.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <stdexcept>
#include "../../../../include/sgf/platform/input/key_mapper.h"
#include "../../../../internal_include/sgf/platform/input/keyboard_input_injector.h"
#include "../../../../internal_include/sgf/platform/input/mouse_input_injector.h"

namespace sgf_core {
    const std::string WindowTag::TypeName = "Window";
    const std::string Window::TypeName = "Window";

    struct Window::WindowImpl {
        GLFWwindow * window;
        KeyboardInputInjector * keyboardInjector = nullptr;
        MouseInputInjector * mouseInjector = nullptr;
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

        glfwSetWindowUserPointer(impl->window, this);
        glfwSetKeyCallback(impl->window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
            Window * window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            if (action == GLFW_PRESS) {
                window->keyPressedHandler(KeyMapper::toSGFKey(key));
            } else if (action == GLFW_RELEASE) {
                window->keyReleasedHandler(KeyMapper::toSGFKey(key));
            }
        });
        glfwSetMouseButtonCallback(impl->window, [](GLFWwindow * glfwWindow, int button, int action, int mod) {
            Window * window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            if (action == GLFW_PRESS) {
                window->mousePressedHandler(KeyMapper::toSGFMouseKey(button));
            } else if (action == GLFW_RELEASE) {
                window->mouseReleasedHandler(KeyMapper::toSGFMouseKey(button));
            }
        });
        glfwSetCursorPosCallback(impl->window, [](GLFWwindow * glfwWindow, double xpos, double ypos) {
            Window * window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->cursorMovedHandler(xpos, ypos);
        });
        glfwSetScrollCallback(impl->window, [](GLFWwindow * glfwWindow, double xoffset, double yoffset) {
            Window * window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
            window->scrollScrolledHandler(xoffset, yoffset);
        });
    }

    Window::~Window() {
        impl->keyboardInjector = nullptr;
        impl->mouseInjector = nullptr;
        glfwSetKeyCallback(impl->window, nullptr);
        glfwSetMouseButtonCallback(impl->window, nullptr);
        glfwSetCursorPosCallback(impl->window, nullptr);
        glfwSetScrollCallback(impl->window, nullptr);
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

    void Window::setKeyboardInputInjector(KeyboardInputInjector & injector) {
        impl->keyboardInjector = &injector;
    }

    void Window::setMouseInputInjector(MouseInputInjector & injector) {
        impl->mouseInjector = &injector;
    }

    void Window::keyPressedHandler(Key key) {
        if (impl->keyboardInjector) {
            impl->keyboardInjector->onKeyPressed(key);
        }
    }

    void Window::keyReleasedHandler(Key key) {
        if (impl->keyboardInjector) {
            impl->keyboardInjector->onKeyReleased(key);
        }
    }

    void Window::mousePressedHandler(MouseKey key) {
        if (impl->mouseInjector) {
            impl->mouseInjector->onMouseButtonPressed(key);
        }
    }

    void Window::mouseReleasedHandler(MouseKey key) {
        if (impl->mouseInjector) {
            impl->mouseInjector->onMouseButtonReleased(key);
        }
    }

    void Window::cursorMovedHandler(double x, double y) {
        if (impl->mouseInjector) {
            impl->mouseInjector->onCursorMoved({ .x = x, .y = y });
        }
    }

    void Window::scrollScrolledHandler(double x, double y) {
        if (impl->mouseInjector) {
            impl->mouseInjector->onScrollScrolled({ .x = x, .y = y });
        }
    }
}
