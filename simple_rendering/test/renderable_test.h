#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./test_env.h"
#include "./util.hpp"
#include "../include/window_manager.h"
#include "../include/shader_manager.h"
#include "../include/renderable/renderable.h"

class RenderableSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        windowId = WindowManager::Instance().createWindow(800, 800, "Shapes Test");
        shaderId = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSource);
        ShaderManager::Instance().registerShaderUniformVariable(shaderId, "transform", "model");
        material = new Material(shaderId);
        triangleVertexLayout = VertexLayout();
        triangleVertexLayout.addAttribute({ .index = 0, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 0 });
        triangleMesh = new Mesh(triangleVertices.data(), 3, triangleIndices.data(), 3, triangleVertexLayout);
    }

    virtual void TearDown() {
        delete material;
        delete triangleMesh;
        ShaderManager::Instance().destroyShaders();
        WindowManager::Instance().terminate();
    }

    WindowId windowId;
    ShaderId shaderId;
    Material * material;
    VertexLayout triangleVertexLayout;
    Mesh * triangleMesh = nullptr;
    std::vector<float> triangleVertices {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    std::vector<uint32_t> triangleIndices { 0, 1, 2 };
    
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
};

TEST_F(RenderableSuite, DrawTriangle) {
    if (skipHandTest) GTEST_SKIP();

    std::vector<float> vertices {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    std::vector<uint32_t> indices { 0, 1, 2 };
    VertexLayout vertexLayout;
    vertexLayout.addAttribute({ .index = 0, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 0 });
    Mesh mesh((void *)vertices.data(), 3, indices.data(), 3, vertexLayout);

    WindowManager::Instance().createRenderable(windowId, &mesh, material);

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

TEST_F(RenderableSuite, DrawRectangle) {
    if (skipHandTest) GTEST_SKIP();

    std::vector<float> vertices {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    std::vector<uint32_t> indices { 0, 1, 2, 0, 2, 3 };
    VertexLayout vertexLayout;
    vertexLayout.addAttribute({ .index = 0, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 0 });
    Mesh mesh((void *)vertices.data(), 4, indices.data(), 6, vertexLayout);

    WindowManager::Instance().createRenderable(windowId, &mesh, material);

    PRINTF("There should be a white Rectangle on the screen\n");
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

TEST_F(RenderableSuite, DrawPentagon) {
    if (skipHandTest) GTEST_SKIP();

    std::vector<float> vertices {
        -0.65f, 0.25f, 0.0f,
        0.0f, 0.7f, 0.0f,
        0.65f, 0.25f, 0.0f,
        0.4f, -0.4f, 0.0f,
        -0.4f, -0.4f, 0.0f
    };
    std::vector<uint32_t> indices { 0, 1, 2, 0, 2, 3, 0, 3, 4 };
    VertexLayout vertexLayout;
    vertexLayout.addAttribute({ .index = 0, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 0 });
    Mesh mesh((void *)vertices.data(), 5, indices.data(), 9, vertexLayout);

    WindowManager::Instance().createRenderable(windowId, &mesh, material);

    PRINTF("There should be a white Rectangle on the screen\n");
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

TEST_F(RenderableSuite, SetColor) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);
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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);
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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangle1Id = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle1 = WindowManager::Instance().getRenderable(windowId, triangle1Id);
    RenderableId triangle2Id = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle2 = WindowManager::Instance().getRenderable(windowId, triangle2Id);
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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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

    RenderableId triangleId = WindowManager::Instance().createRenderable(windowId, triangleMesh, material);
    Renderable& triangle = WindowManager::Instance().getRenderable(windowId, triangleId);

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
