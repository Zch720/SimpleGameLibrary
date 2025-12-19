#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./test_env.h"
#include "./util.hpp"
#include "../include/window_manager.h"
#include "../include/shader_manager.h"
#include "../include/renderable/image.h"

class ImageSuite : public ::testing::Test {
protected:
    void SetUp() override {
        windowId = WindowManager::Instance().createWindow(800, 800, "Test Window");
        shaderId = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSource);
        ShaderManager::Instance().registerShaderUniformVariable(shaderId, "transform", "model");
    }

    void TearDown() override {
        ShaderManager::Instance().destroyShaders();
        WindowManager::Instance().terminate();
    }

    WindowId windowId;
    ShaderId shaderId;
    
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

TEST_F(ImageSuite, CreatePngImage) {
    RenderableId imageId = WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image.png");
    Image& image = WindowManager::Instance().getRenderable<Image>(windowId, imageId);
    
    ASSERT_EQ(225, image.width());
    ASSERT_EQ(225, image.height());
}

TEST_F(ImageSuite, DrawPngImage) {
    if (skipHandTest) GTEST_SKIP();

    RenderableId imageId = WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image.png");
    Image& image = WindowManager::Instance().getRenderable<Image>(windowId, imageId);
    image.scale({0.005, 0.005, 1});

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

    RenderableId imageId = WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image_transparent.png");
    Image& image = WindowManager::Instance().getRenderable<Image>(windowId, imageId);
    image.scale({0.005, 0.005, 1});

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

TEST_F(ImageSuite, CreateJpgImage) {
    RenderableId imageId = WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image.jpg");
    Image& image = WindowManager::Instance().getRenderable<Image>(windowId, imageId);
    
    ASSERT_EQ(225, image.width());
    ASSERT_EQ(225, image.height());
}

TEST_F(ImageSuite, DrawJpgImage) {
    if (skipHandTest) GTEST_SKIP();
    
    RenderableId imageId = WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image.jpg");
    Image& image = WindowManager::Instance().getRenderable<Image>(windowId, imageId);
    image.scale({0.005, 0.005, 1});

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

TEST_F(ImageSuite, CreateBmpImage) {
    RenderableId imageId = WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image.bmp");
    Image& image = WindowManager::Instance().getRenderable<Image>(windowId, imageId);
    
    ASSERT_EQ(225, image.width());
    ASSERT_EQ(225, image.height());
}

TEST_F(ImageSuite, DrawBmpImage) {
    if (skipHandTest) GTEST_SKIP();
    
    RenderableId imageId = WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image.bmp");
    Image& image = WindowManager::Instance().getRenderable<Image>(windowId, imageId);
    image.scale({0.005, 0.005, 1});

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

TEST_F(ImageSuite, CreateTifImage) {
    ASSERT_THROW_MESSAGE(WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/image.tif"),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/image.tif. Invalid texture type.");
}

TEST_F(ImageSuite, CreateImageFileNotExist) {
    ASSERT_THROW_MESSAGE(WindowManager::Instance().createRenderable<Image>(windowId, shaderId, TEST_RESOURCES_DIR"/not_exist.png"),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/not_exist.png");
}
