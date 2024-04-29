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
        WindowManager::Instance().createWindow("main_window", 800, 800, "Shapes Test");
        ShaderManager::Instance().createShader("main_shader", vertexShaderSource, fragmentShaderSource);
        ShaderManager::Instance().registerShaderUniformVariable("main_shader", "color", "color");
        ShaderManager::Instance().registerShaderUniformVariable("main_shader", "transform", "model");
    }

    virtual void TearDown() {
        ShaderManager::Instance().destroyShaders();
        WindowManager::Instance().terminate();
    }
    
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
    ASSERT_NO_THROW(Polygon("main_window", "main_shader", convexPolygonPoints));
}

TEST_F(PolygonSuite, DrawConvexPolygon) {
    if (skipHandTest) GTEST_SKIP();

    Polygon polygon = Polygon("main_window", "main_shader", convexPolygonPoints);

    PRINTF("There should be a white pentagon on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        polygon.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
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

    Polygon polygon = Polygon("main_window", "main_shader", Polygon::SortConvexPolygonVertices(unorderedPoints));

    PRINTF("There should be a white pentagon on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        polygon.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(PolygonSuite, DrawConcavePolygon) {
    if (skipHandTest) GTEST_SKIP();

    Polygon polygon = Polygon("main_window", "main_shader", concavePolygonPoints);

    PRINTF("There should be a white star on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        polygon.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}
