#include <gtest/gtest.h>
#include "./utils.h"
#include "../include/sgf/rendering/render_context.h"

using namespace sgf_core;

TEST(UnsafeGLContextSuite, Breath) {
    std::vector<float> vertices {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    std::vector<uint32_t> indices { 0, 1, 2 };
    VertexLayout vertexLayout;
    vertexLayout.addAttribute({ .index = 0, .size = 3, .type = VertexLayout::VertexType::FLOAT, .normalized = false, .offset = 0 });

    sgf_test::createOpenGLContext();

    RenderContext context;
    ShaderId shaderId = context.ShaderManager.create({
        .vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )",
        .fragmentShaderSource = R"(
            #version 330 core
            uniform vec4 color;
            out vec4 FragColor;
            void main() {
                FragColor = color;
            }
        )"
    });
    MeshId meshId = context.MeshManager.create({
        .vertices = vertices.data(),
        .verticesCount = 3,
        .indices = indices.data(),
        .indicesCount = 3,
        .vertexLayout = vertexLayout
    });
    Texture2DId textureId = context.Texture2DManager.create({
        .path = TEST_RESOURCES_DIR"/image.png"
    });

    ASSERT_NO_THROW(context.unsafeExecute([&](const UnsafeGLContext & glContext) {
        glContext.getShaderProgramHandle(shaderId);
        glContext.getMeshVAO(meshId);
        glContext.getMeshVBO(meshId);
        glContext.getMeshEBO(meshId);
        glContext.getTexture2DTextureHandle(textureId);
    }));

    context.destroyAllResources();
    sgf_test::OpenGLContextTerminate();
}