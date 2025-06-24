#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/window_manager.h"
#include "../include/shader_manager.h"
#include "../include/renderable/shapes/triangle.h"
#include "./util.hpp"

class TriangleSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        windowId = WindowManager::Instance().createWindow(800, 800, "Shapes Test");
        shaderId = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSource);
        ShaderManager::Instance().registerShaderUniformVariable(shaderId, "transform", "model");
    }

    virtual void TearDown() {
        ShaderManager::Instance().destroyShaders();
        WindowManager::Instance().terminate();
    }

    WindowId windowId;
    ShaderId shaderId;
    
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 model = mat4(1.0);
        void main() {
            gl_Position = model * vec4(aPos, 1.0);
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        uniform vec4 color = vec4(1.0);
        out vec4 FragColor;
        void main() {
            FragColor = color;
        }
    )";

    vec2 point1 { 0.0f, 0.5f };
    vec2 point2 { -0.5f, -0.5f };
    vec2 point3 { 0.5f, -0.5f };

    static bool skipHandTest;
};

bool TriangleSuite::skipHandTest = false;

TEST_F(TriangleSuite, CreateTriangle) {
    ASSERT_NO_THROW(WindowManager::Instance().createRenderable<Triangle>(windowId, "polygon", windowId, shaderId, point1, point2, point3));
}

TEST_F(TriangleSuite, DrawTriangle) {
    if (skipHandTest) GTEST_SKIP();
    
    WindowManager::Instance().createRenderable<Triangle>(windowId, "polygon", windowId, shaderId, point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}
