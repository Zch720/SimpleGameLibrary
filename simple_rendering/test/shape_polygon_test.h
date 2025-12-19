#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/window_manager.h"
#include "../include/shader_manager.h"
#include "../include/renderable/shapes/polygon.h"
#include "./util.hpp"

class PolygonSuite : public ::testing::Test {
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
    
    std::vector<vec2> convexPolygonPoints = {
        {-0.4, -0.5},
        {0.4, -0.5},
        {0.62, 0.15},
        {0.0, 0.55},
        {-0.62, 0.15}
    };
    
    std::vector<vec2> concavePolygonPoints = {
        {-0.4, -0.5},
        {0.0, -0.22},
        {0.4, -0.5},
        {0.25, 0.0},
        {0.62, 0.15},
        {0.16, 0.2},
        {0.0, 0.55},
        {-0.17, 0.2},
        {-0.62, 0.15},
        {-0.25, 0.0}
    };

    static bool skipHandTest;
};

bool PolygonSuite::skipHandTest = false;

TEST_F(PolygonSuite, CreatePolygon) {
    ASSERT_NO_THROW(WindowManager::Instance().createRenderable<Polygon>(windowId, windowId, shaderId, convexPolygonPoints));
}

TEST_F(PolygonSuite, DrawConvexPolygon) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Polygon>(windowId, windowId, shaderId, convexPolygonPoints);

    PRINTF("There should be a white pentagon on the screen\n");
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

TEST_F(PolygonSuite, DrawUnorderedConvexPolygon) {
    if (skipHandTest) GTEST_SKIP();
    
    std::vector<vec2> unorderedPoints = {
        {-0.4, -0.5},
        {0.62, 0.15},
        {0.4, -0.5},
        {-0.62, 0.15},
        {0.0, 0.55}
    };

    WindowManager::Instance().createRenderable<Polygon>(windowId, windowId, shaderId, Polygon::SortConvexPolygonVertices(unorderedPoints));

    PRINTF("There should be a white pentagon on the screen\n");
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

TEST_F(PolygonSuite, DrawConcavePolygon) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Polygon>(windowId, windowId, shaderId, concavePolygonPoints);

    PRINTF("There should be a white star on the screen\n");
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
