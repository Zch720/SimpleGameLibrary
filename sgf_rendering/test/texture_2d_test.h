#include <gtest/gtest.h>
#include "./utils.h"
#include "../include/sgf/rendering/texture_2d.h"

using namespace sgf_core;

class Texture2DSuite: public ::testing::Test {
protected:
    void SetUp() override {
        sgf_test::createOpenGLContext();
    }

    void TearDown() override {
        sgf_test::OpenGLContextTerminate();
    }
};

TEST_F(Texture2DSuite, LoadPngImage) {
    ASSERT_NO_THROW(Texture2D(Texture2DId(), { .path = TEST_RESOURCES_DIR"/image.png" }));
}

TEST_F(Texture2DSuite, PngImageLoadedWithCorrectInfo) {
    Texture2D texture = Texture2D(Texture2DId(), { .path = TEST_RESOURCES_DIR"/image.png" });
    ASSERT_EQ(225, texture.getWidth());
    ASSERT_EQ(225, texture.getHeight());
}

TEST_F(Texture2DSuite, LoadJpgImage) {
    ASSERT_NO_THROW(Texture2D(Texture2DId(), { .path = TEST_RESOURCES_DIR"/image.jpg" }));
}

TEST_F(Texture2DSuite, JpgImageLoadedWithCorrectInfo) {
    Texture2D texture = Texture2D(Texture2DId(), { .path = TEST_RESOURCES_DIR"/image.jpg" });
    ASSERT_EQ(225, texture.getWidth());
    ASSERT_EQ(225, texture.getHeight());
}

TEST_F(Texture2DSuite, LoadBmpImage) {
    ASSERT_NO_THROW(Texture2D(Texture2DId(), { .path = TEST_RESOURCES_DIR"/image.bmp" }));
}

TEST_F(Texture2DSuite, BmpImageLoadedWithCorrectInfo) {
    Texture2D texture = Texture2D(Texture2DId(), { .path = TEST_RESOURCES_DIR"/image.bmp" });
    ASSERT_EQ(225, texture.getWidth());
    ASSERT_EQ(225, texture.getHeight());
}

TEST_F(Texture2DSuite, LoadTifImage) {
    ASSERT_THROW_MESSAGE(Texture2D texture(Texture2DId(), { .path = TEST_RESOURCES_DIR"/image.tif" }),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/image.tif. Invalid texture type.");
}

TEST_F(Texture2DSuite, LoadImageNotExist) {
    ASSERT_THROW_MESSAGE(Texture2D texture(Texture2DId(), { .path = TEST_RESOURCES_DIR"/not_exist.png" }),
        std::runtime_error,
        "Unable to load texture file: " TEST_RESOURCES_DIR "/not_exist.png");
}