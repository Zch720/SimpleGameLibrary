#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "./util.hpp"

namespace sgf_test {
    GLFWwindow * window = nullptr;

#define WINDOW_LOOP(failMessage, code)                              \
    while(!glfwWindowShouldClose(sgf_test::window)) {               \
        glfwSwapBuffers(sgf_test::window);                          \
        glClearColor(0, 0, 0, 0);                                   \
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         \
        { code; }                                                   \
        if (SuccessCheckFromInputForLoop("Image show wrong")) {     \
            glfwSetWindowShouldClose(sgf_test::window, true);       \
        }                                                           \
        glfwPollEvents();                                           \
    }

    void createOpenGLContext() {
        // Init GLFW
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        // Create GLFW Window
        window = glfwCreateWindow(800, 800, "Test Window", nullptr, nullptr);
        if (window == nullptr) {
            throw std::runtime_error("Failed to create GLFW window");
        }

        // Use context
        glfwMakeContextCurrent(window);
        
        // Init GLAD
        if (!gladLoadGL(glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLContextTerminate() {
        if (window != nullptr) {
            glfwDestroyWindow(window);
            window = nullptr;
        }
        glfwTerminate();
    }

    // bool isWindowClosed() {
    //     return glfwWindowShouldClose(window);
    // }

    // void clearWindow() {
    //     glfwSwapBuffers(window);
    //     glClearColor(0, 0, 0, 0);
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // }

    // void windowUpdate() {
    //     glfwPollEvents();
    // }

    // void closeWindow() {
    //     glfwSetWindowShouldClose(window, true);
    // }
}