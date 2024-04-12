#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/window_manager.h"
#include "../include/shader_manager.h"
#include "../include/renderable/shapes/triangle.h"
#include "./util.hpp"

class ShapeSuite : public ::testing::Test {
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

    vec2 point1 { 0.0f, 0.5f };
    vec2 point2 { -0.5f, -0.5f };
    vec2 point3 { 0.5f, -0.5f };

    static bool skipHandTest;
};

bool ShapeSuite::skipHandTest = false;

TEST_F(ShapeSuite, SetColor) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a red triangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, ChangeColorAtRuntimme) {
    if (skipHandTest) GTEST_SKIP();

    glm::vec3 colors[] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    Triangle triangle = Triangle("main_shader", point1, point2, point3);
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a triangle on the screen\n");
    PRINTF("The triangle should change color between red, green and blue\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 200;
    int colorIndex = 0;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        if (--count == 0) {
            count = 200;
            triangle.setColor(colors[colorIndex].r, colors[colorIndex].g, colors[colorIndex].b, 1.0f);
            colorIndex = (colorIndex + 1) % 3;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, SetColorButShaderDidNotRigesterColorIdentify) {
    ShaderManager::Instance().createShader("no_color_shader", vertexShaderSource, fragmentShaderSource);

    Triangle triangle = Triangle("no_color_shader", point1, point2, point3);
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    WindowManager::Instance().useWindow("main_window");
    WindowManager::Instance().clearWindow("main_window");
    ASSERT_ANY_THROW(triangle.render());
    WindowManager::Instance().closeWindow("main_window");
}

TEST_F(ShapeSuite, Translate) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.translate({delta, delta, 0});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, TranslateX) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between left and right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.translateX(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, TranslateY) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between up and down\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.translateY(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, TranslateZ) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);
    Triangle triangle2 = Triangle("main_shader", point1, point2, point3);
    triangle2.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a white triangle and red triangle on the screen by terns\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.translateZ(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        triangle2.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, SetPosition) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        glm::vec3 pos = triangle.position();
        triangle.position({pos.x + delta, pos.y + delta, pos.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, Scale) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically and horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        glm::vec3 scale = triangle.scale();
        triangle.scale({scale.x + delta, scale.y + delta, scale.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, ScaleX) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        glm::vec3 scale = triangle.scale();
        triangle.scaleX(scale.x + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, ScaleY) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        glm::vec3 scale = triangle.scale();
        triangle.scaleY(scale.y + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, Rotate) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.rotate({0, 0, delta});
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, RotateX) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around x-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.rotateX(delta);
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, RotateY) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around y-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.rotateY(delta);
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, RotateZ) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around z-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        triangle.rotateZ(delta);
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}

TEST_F(ShapeSuite, SetRotation) {
    if (skipHandTest) GTEST_SKIP();

    Triangle triangle = Triangle("main_shader", point1, point2, point3);

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WindowManager::Instance().useWindow("main_window");
    while (!WindowManager::Instance().isWindowClose("main_window")) {
        WindowManager::Instance().clearWindow("main_window");
        glm::vec3 rotation = triangle.rotation();
        triangle.rotation({rotation.x, rotation.y, rotation.z + delta});
        triangle.render();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow("main_window");
        }
        glfwPollEvents();
    }
}
