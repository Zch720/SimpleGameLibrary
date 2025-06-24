#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/window_manager.h"
#include "../include/shader_manager.h"
#include "../include/renderable/shapes/triangle.h"
#include "./util.hpp"

class RenderableSuite : public ::testing::Test {
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

bool RenderableSuite::skipHandTest = false;

TEST_F(RenderableSuite, SetColor) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a red triangle on the screen\n");
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

TEST_F(RenderableSuite, ChangeColorAtRuntime) {
    if (skipHandTest) GTEST_SKIP();

    glm::vec3 colors[] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a triangle on the screen\n");
    PRINTF("The triangle should change color between red, green and blue\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 200;
    int colorIndex = 0;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        if (--count == 0) {
            count = 200;
            triangle.setColor(colors[colorIndex].r, colors[colorIndex].g, colors[colorIndex].b, 1.0f);
            colorIndex = (colorIndex + 1) % 3;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, Translate) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle.translate({delta, delta, 0});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, TranslateX) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between left and right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle.translateX(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, TranslateY) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between up and down\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle.translateY(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, TranslateZ) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle1", windowId, shaderId, point1, point2, point3);
    Triangle& triangle1 = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle1");
    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle2", windowId, shaderId, point1, point2, point3);
    Triangle& triangle2 = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle2");
    triangle2.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a white triangle and red triangle on the screen by terns\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle1.translateZ(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, SetPosition) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        glm::vec3 pos = triangle.position();
        triangle.position({pos.x + delta, pos.y + delta, pos.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, Scale) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically and horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        glm::vec3 scale = triangle.scale();
        triangle.scale({scale.x + delta, scale.y + delta, scale.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, ScaleX) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        glm::vec3 scale = triangle.scale();
        triangle.scaleX(scale.x + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, ScaleY) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        glm::vec3 scale = triangle.scale();
        triangle.scaleY(scale.y + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, Rotate) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle.rotate({0, 0, delta});
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, RotateX) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around x-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle.rotateX(delta);
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, RotateY) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around y-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle.rotateY(delta);
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, RotateZ) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around z-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        triangle.rotateZ(delta);
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(RenderableSuite, SetRotation) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Triangle>(windowId, "triangle", windowId, shaderId, point1, point2, point3);
    Triangle& triangle = WindowManager::Instance().getRenderable<Triangle>(windowId, "triangle");

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        glm::vec3 rotation = triangle.rotation();
        triangle.rotation({rotation.x, rotation.y, rotation.z + delta});
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}
