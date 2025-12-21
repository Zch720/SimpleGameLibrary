#include <gtest/gtest.h>
#include "../include/window_manager.h"
#include "../include/renderable/texture_2d.h"
#include "./util.hpp"

class Texture2DSuite: public ::testing::Test {
protected:
    void SetUp() override {
        WindowManager::Instance().createWindow(800, 800, "Test Window");
    }

    void TearDown() override {
        WindowManager::Instance().terminate();
    }
};

TEST_F(Texture2DSuite, LoadPngImage) {
    Texture2D texture;
    ASSERT_NO_THROW(texture = Texture2D(TEST_RESOURCES_DIR"/image.png"));
    ASSERT_EQ(225, texture.getWidth());
    ASSERT_EQ(225, texture.getHeight());
    ASSERT_NE(0, texture.getTextureId());
}

TEST_F(Texture2DSuite, LoadJpgImage) {
    Texture2D texture;
    ASSERT_NO_THROW(texture = Texture2D(TEST_RESOURCES_DIR"/image.jpg"));
    ASSERT_EQ(225, texture.getWidth());
    ASSERT_EQ(225, texture.getHeight());
    ASSERT_NE(0, texture.getTextureId());
}

TEST_F(Texture2DSuite, LoadBmpImage) {
    Texture2D texture;
    ASSERT_NO_THROW(texture = Texture2D(TEST_RESOURCES_DIR"/image.bmp"));
    ASSERT_EQ(225, texture.getWidth());
    ASSERT_EQ(225, texture.getHeight());
    ASSERT_NE(0, texture.getTextureId());
}

TEST_F(Texture2DSuite, LoadTifImage) {
    ASSERT_THROW_MESSAGE(Texture2D texture(TEST_RESOURCES_DIR"/image.tif"),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/image.tif. Invalid texture type.");
}

TEST_F(Texture2DSuite, LoadImageNotExist) {
    ASSERT_THROW_MESSAGE(Texture2D texture(TEST_RESOURCES_DIR"/not_exist.png"),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/not_exist.png");
}