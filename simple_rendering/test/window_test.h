#include <gtest/gtest.h>
#include "../include/window.h"

class WindowSuite : public ::testing::Test {
protected:
    void SetUp() override {
        if (skipAll) {
            GTEST_SKIP();
        }

        SetUpGlfw();
    }

    void TearDown() override {
        if (skipAll) {
            return;
        }

        glfwTerminate();
    }

    void SetUpGlfw() {
        if (!glfwInit()) {
            skipAll = true;
            FAIL() << "Failed to initialize GLFW";
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    }

    void SetUpGlad() {
        if (!gladLoadGL(glfwGetProcAddress)) {
            skipAll = true;
            FAIL() << "Failed to initialize GLAD";
        }
    }

    static bool skipAll;
};

bool WindowSuite::skipAll = false;

TEST_F(WindowSuite, CreateWindow) {
    Window window(800, 600, "Test Window");
    window.makeContextCurrent();

    SetUpGlad();

    ASSERT_EQ(glfwGetCurrentContext(), window.getGLFWWindow());

    glfwSetWindowShouldClose(window.getGLFWWindow(), true);
}