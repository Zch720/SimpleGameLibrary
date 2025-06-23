#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/window_manager.h"
#include "../include/shader_manager.h"
#include "../include/renderable/image.h"
#include "./util.hpp"

class ImageSuite : public ::testing::Test {
protected:
    void SetUp() override {
        WindowManager::Instance().createWindow(DEFAULT_WINDOW, 800, 800, "Test Window");
        shaderId = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSource);
        ShaderManager::Instance().registerShaderUniformVariable(shaderId, "transform", "model");
    }

    void TearDown() override {
        ShaderManager::Instance().destroyShaders();
        WindowManager::Instance().terminate();
    }

    const std::string DEFAULT_WINDOW = "main window";
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

    static bool skipHandTest;
};

bool ImageSuite::skipHandTest = false;

TEST_F(ImageSuite, CreatePngImage) {
    WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image.png");
    Image& image = WindowManager::Instance().getRenderable<Image>(DEFAULT_WINDOW, "image");
    
    ASSERT_EQ(225, image.width());
    ASSERT_EQ(225, image.height());
}

TEST_F(ImageSuite, DrawPngImage) {
    if (ImageSuite::skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image.png");
    Image& image = WindowManager::Instance().getRenderable<Image>(DEFAULT_WINDOW, "image");
    image.scale({0.005, 0.005, 1});

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(DEFAULT_WINDOW);
    while (!WindowManager::Instance().isWindowClose(DEFAULT_WINDOW)) {
        WindowManager::Instance().renderWindow(DEFAULT_WINDOW);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(DEFAULT_WINDOW);
        }
        glfwPollEvents();
    }
}

TEST_F(ImageSuite, DrawTransparentPngImage) {
    if (ImageSuite::skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image_transparent.png");
    Image& image = WindowManager::Instance().getRenderable<Image>(DEFAULT_WINDOW, "image");
    image.scale({0.005, 0.005, 1});

    PRINTF("There should be a smile image with no background in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(DEFAULT_WINDOW);
    while (!WindowManager::Instance().isWindowClose(DEFAULT_WINDOW)) {
        WindowManager::Instance().renderWindow(DEFAULT_WINDOW);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(DEFAULT_WINDOW);
        }
        glfwPollEvents();
    }
}

TEST_F(ImageSuite, CreateJpgImage) {
    WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image.jpg");
    Image& image = WindowManager::Instance().getRenderable<Image>(DEFAULT_WINDOW, "image");
    
    ASSERT_EQ(225, image.width());
    ASSERT_EQ(225, image.height());
}

TEST_F(ImageSuite, DrawJpgImage) {
    if (ImageSuite::skipHandTest) GTEST_SKIP();
    
    WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image.jpg");
    Image& image = WindowManager::Instance().getRenderable<Image>(DEFAULT_WINDOW, "image");
    image.scale({0.005, 0.005, 1});

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(DEFAULT_WINDOW);
    while (!WindowManager::Instance().isWindowClose(DEFAULT_WINDOW)) {
        WindowManager::Instance().renderWindow(DEFAULT_WINDOW);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(DEFAULT_WINDOW);
        }
        glfwPollEvents();
    }
}

TEST_F(ImageSuite, CreateBmpImage) {
    WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image.bmp");
    Image& image = WindowManager::Instance().getRenderable<Image>(DEFAULT_WINDOW, "image");
    
    ASSERT_EQ(225, image.width());
    ASSERT_EQ(225, image.height());
}

TEST_F(ImageSuite, DrawBmpImage) {
    if (ImageSuite::skipHandTest) GTEST_SKIP();
    
    WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image.bmp");
    Image& image = WindowManager::Instance().getRenderable<Image>(DEFAULT_WINDOW, "image");
    image.scale({0.005, 0.005, 1});

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WindowManager::Instance().useWindow(DEFAULT_WINDOW);
    while (!WindowManager::Instance().isWindowClose(DEFAULT_WINDOW)) {
        WindowManager::Instance().renderWindow(DEFAULT_WINDOW);
        if (SuccessCheckFromInputForLoop("Image show wrong")) {
            WindowManager::Instance().closeWindow(DEFAULT_WINDOW);
        }
        glfwPollEvents();
    }
}

TEST_F(ImageSuite, CreateTifImage) {
    ASSERT_THROW_MESSAGE(WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/image.tif"),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/image.tif. Invalid texture type.");
}

TEST_F(ImageSuite, CreateImageFileNotExist) {
    ASSERT_THROW_MESSAGE(WindowManager::Instance().createRenderable<Image>(DEFAULT_WINDOW, "image", DEFAULT_WINDOW, shaderId, TEST_RESOURCES_DIR"/not_exist.png"),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/not_exist.png");
}
