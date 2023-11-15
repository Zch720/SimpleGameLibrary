#include <gtest/gtest.h>
#include <window.h>

TEST(SRenderingSuite, Breath) {
    if (!glfwInit()) {
        FAIL() << "Failed to initialize GLFW";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    Window window(800, 600, "Test Window");
    window.makeContextCurrent();

    if (!gladLoadGL(glfwGetProcAddress)) {
        FAIL() << "Failed to initialize GLAD";
    }

    ASSERT_EQ(glfwGetCurrentContext(), window.getGLFWWindow());

    glfwSetWindowShouldClose(window.getGLFWWindow(), true);
    glfwTerminate();
}