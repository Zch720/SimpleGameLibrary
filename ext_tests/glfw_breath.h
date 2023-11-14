#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

TEST(GlfwSuite, Breath) {
    if (!glfwInit()) {
        FAIL() << "glfwInit() failed";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow * window = glfwCreateWindow(640, 480, "glfw_breath", nullptr, nullptr);
    if (window == nullptr) {
        FAIL() << "glfwCreateWindow() failed";
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        FAIL() << "gladLoadGL() failed";
    }

    glfwTerminate();
}
