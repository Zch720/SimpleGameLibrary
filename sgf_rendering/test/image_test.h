#include <gtest/gtest.h>
#include "./test_env.h"
#include "./utils.h"
#include "../include/sgf/rendering/render_context.h"
#include "../include/sgf/rendering/renderable.h"

using namespace sgf_core;

class ImageSuite : public ::testing::Test {
protected:
    void SetUp() override {
        sgf_test::createOpenGLContext();

        context.initialize();
        shaderId = context.ShaderManager.create({
            .vertexShaderSource = vertexShaderSource,
            .fragmentShaderSource = fragmentShaderSource
        });
        context.ShaderManager.getRef(shaderId).registerUniformVariable("transform", "model");
        imageVertexLayout = VertexLayout();
        imageVertexLayout.addAttribute({ .index = 0, .size = 3, .type = VertexLayout::VertexType::FLOAT, .normalized = false, .offset = 0 });
        imageVertexLayout.addAttribute({ .index = 1, .size = 2, .type = VertexLayout::VertexType::FLOAT, .normalized = false, .offset = sizeof(float) * 3 });
        imageMeshId = context.MeshManager.create({ .vertices = imageVertices.data(), .verticesCount = 4, .indices = triangleIndices.data(), .indicesCount = 6, .vertexLayout = imageVertexLayout });
    }

    void TearDown() override {
        context.destroyAllResources();

        sgf_test::OpenGLContextTerminate();
    }

    RenderContext context;
    ShaderId shaderId;
    VertexLayout imageVertexLayout;
    MeshId imageMeshId;
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

    Texture2DId textureId = context.Texture2DManager.create({ .path = TEST_RESOURCES_DIR"/image.png" });
    MaterialId materialId = context.MaterialManager.create({ .useTexture = true, .shaderId = shaderId, .textureId = textureId });

    Renderable image(RenderableId(), { .meshId = imageMeshId, .materialId = materialId });

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Image show wrong", {
        image.update();
        image.render(context);
    });
}

TEST_F(ImageSuite, DrawTransparentPngImage) {
    if (skipHandTest) GTEST_SKIP();

    Texture2DId textureId = context.Texture2DManager.create({ .path = TEST_RESOURCES_DIR"/image_transparent.png" });
    MaterialId materialId = context.MaterialManager.create({ .useTexture = true, .shaderId = shaderId, .textureId = textureId });

    Renderable image(RenderableId(), { .meshId = imageMeshId, .materialId = materialId });

    PRINTF("There should be a smile image with no background in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Image show wrong", {
        image.update();
        image.render(context);
    });
}

TEST_F(ImageSuite, DrawJpgImage) {
    if (skipHandTest) GTEST_SKIP();

    Texture2DId textureId = context.Texture2DManager.create({ .path = TEST_RESOURCES_DIR"/image.jpg" });
    MaterialId materialId = context.MaterialManager.create({ .useTexture = true, .shaderId = shaderId, .textureId = textureId });

    Renderable image(RenderableId(), { .meshId = imageMeshId, .materialId = materialId });

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Image show wrong", {
        image.update();
        image.render(context);
    });
}

TEST_F(ImageSuite, DrawBmpImage) {
    if (skipHandTest) GTEST_SKIP();

    Texture2DId textureId = context.Texture2DManager.create({ .path = TEST_RESOURCES_DIR"/image.bmp" });
    MaterialId materialId = context.MaterialManager.create({ .useTexture = true, .shaderId = shaderId, .textureId = textureId });

    Renderable image(RenderableId(), { .meshId = imageMeshId, .materialId = materialId });

    PRINTF("There should be a smile image in the window.\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Image show wrong", {
        image.update();
        image.render(context);
    });
}
