#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./test_env.h"
#include "./util.hpp"
#include "../include/window_manager.h"
#include "../include/shader_manager.h"

class ImageSuite : public ::testing::Test {
protected:
    void SetUp() override {
        windowId = WindowManager::Instance().createWindow(800, 800, "Test Window");
        shaderId = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSource);
        ShaderManager::Instance().registerShaderUniformVariable(shaderId, "transform", "model");
        imageVertexLayout = VertexLayout();
        imageVertexLayout.addAttribute({ .index = 0, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 0 });
        imageVertexLayout.addAttribute({ .index = 1, .size = 2, .type = GL_FLOAT, .normalized = false, .offset = sizeof(float) * 3 });
        imageMesh = new Mesh(imageVertices.data(), 4, triangleIndices.data(), 6, imageVertexLayout);
    }

    void TearDown() override {
        ShaderManager::Instance().destroyShaders();
        WindowManager::Instance().terminate();
    }

    WindowId windowId;
    ShaderId shaderId;
    VertexLayout imageVertexLayout;
    Mesh * imageMesh = nullptr;
    std::vector<float> imageVertices {
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };
    std::vector<uint32_t> triangleIndices { 0, 1, 2, 0, 2, 3 };
    
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;
        uniform mat4 model = mat4(1.0);
        out vec2 texCoord;
        void main() {
            gl_Position = model * vec4(aPos, 1.0);
            texCoord = aTexCoord;
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        in vec2 texCoord;
        out vec4 FragColor;
        uniform vec4 color = vec4(1.0);
        uniform sampler2D tex;
        void main() {
            vec4 textureColor = texture(tex, texCoord) * color;
            if (textureColor.a < 0.1) {
                discard;
            }
            FragColor = textureColor;
        }
    )";
};

TEST_F(ImageSuite, DrawPngImage) {
    if (skipHandTest) GTEST_SKIP();

    Texture2D texture(TEST_RESOURCES_DIR"/image.png");
    Material material(shaderId, &texture);

    WindowManager::Instance().createRenderable(windowId, imageMesh, &material);

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(ImageSuite, DrawTransparentPngImage) {
    if (skipHandTest) GTEST_SKIP();

    Texture2D texture(TEST_RESOURCES_DIR"/image_transparent.png");
    Material material(shaderId, &texture);

    WindowManager::Instance().createRenderable(windowId, imageMesh, &material);

    PRINTF("There should be a smile image with no background in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(ImageSuite, DrawJpgImage) {
    if (skipHandTest) GTEST_SKIP();

    Texture2D texture(TEST_RESOURCES_DIR"/image.jpg");
    Material material(shaderId, &texture);

    WindowManager::Instance().createRenderable(windowId, imageMesh, &material);

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}

TEST_F(ImageSuite, DrawBmpImage) {
    if (skipHandTest) GTEST_SKIP();

    Texture2D texture(TEST_RESOURCES_DIR"/image.bmp");
    Material material(shaderId, &texture);

    WindowManager::Instance().createRenderable(windowId, imageMesh, &material);

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(windowId);
    while (!WindowManager::Instance().isWindowClose(windowId)) {
        WindowManager::Instance().renderWindow(windowId);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(windowId);
        }
        glfwPollEvents();
    }
}
