#include <gtest/gtest.h>
#include "./test_env.h"
#include "./utils.h"
#include "../include/sgf/rendering/render_context.h"
#include "../include/sgf/rendering/renderable.h"

using namespace glm;
using namespace sgf_core;

class RenderableSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        sgf_test::createOpenGLContext();

        context.initialize();
        shaderId = context.ShaderManager.create({
            .vertexShaderSource = vertexShaderSource,
            .fragmentShaderSource = fragmentShaderSource
        });
        context.ShaderManager.getRef(shaderId).registerUniformVariable("transform", "model");
        materialId = context.MaterialManager.create({ .useTexture = false, shaderId = shaderId });
        triangleVertexLayout = VertexLayout();
        triangleVertexLayout.addAttribute({ .index = 0, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 0 });
        triangleMeshId = context.MeshManager.create({ .vertices = triangleVertices.data(), .verticesCount = 3, .indices = triangleIndices.data(), .indicesCount = 3, .vertexLayout = triangleVertexLayout });
    }

    virtual void TearDown() {
        context.destroyAllResources();

        sgf_test::OpenGLContextTerminate();
    }

    RenderContext context;
    ShaderId shaderId;
    MaterialId materialId;
    VertexLayout triangleVertexLayout;
    MeshId triangleMeshId;
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
    MeshId meshId = context.MeshManager.create({ .vertices = (void *)vertices.data(), .verticesCount = 3, .indices = indices.data(), .indicesCount = 3, .vertexLayout = vertexLayout });

    Renderable triangle(RenderableId(), { .meshId = meshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    
    WINDOW_LOOP("Window display wrong", {
        triangle.update();
        triangle.render(context);
    });
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
    MeshId meshId = context.MeshManager.create({ .vertices = (void *)vertices.data(), .verticesCount = 4, .indices = indices.data(), .indicesCount = 6, .vertexLayout = vertexLayout });

    Renderable rectangle(RenderableId(), { .meshId = meshId, .materialId = materialId });

    PRINTF("There should be a white Rectangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    
    WINDOW_LOOP("Window display wrong", {
        rectangle.update();
        rectangle.render(context);
    });
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
    MeshId meshId = context.MeshManager.create({ .vertices = (void *)vertices.data(), .verticesCount = 5, .indices = indices.data(), .indicesCount = 9, .vertexLayout = vertexLayout });

    Renderable pentagon(RenderableId(), { .meshId = meshId, .materialId = materialId });

    PRINTF("There should be a white Rectangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Window display wrong", {
        pentagon.update();
        pentagon.render(context);
    });
}

TEST_F(RenderableSuite, SetColor) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a red triangle on the screen\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    WINDOW_LOOP("Window display wrong", {
        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, ChangeColorAtRuntime) {
    if (skipHandTest) GTEST_SKIP();

    glm::vec3 colors[] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a triangle on the screen\n");
    PRINTF("The triangle should change color between red, green and blue\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 200;
    int colorIndex = 0;
    WINDOW_LOOP("Window display wrong", {
        if (--count == 0) {
            count = 200;
            triangle.setColor(colors[colorIndex].r, colors[colorIndex].g, colors[colorIndex].b, 1.0f);
            colorIndex = (colorIndex + 1) % 3;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, Translate) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        triangle.translate({delta, delta, 0});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, TranslateX) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between left and right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        triangle.translateX(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, TranslateY) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between up and down\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        triangle.translateY(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, TranslateZ) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle1(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });
    Renderable triangle2(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });
    triangle2.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("There should be a white triangle and red triangle on the screen by terns\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        triangle1.translateZ(delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle1.update();
        triangle1.render(context);
        triangle2.update();
        triangle2.render(context);
    });
}

TEST_F(RenderableSuite, SetPosition) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle move between lower left and upper right\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 pos = triangle.position();
        triangle.position({pos.x + delta, pos.y + delta, pos.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, Scale) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically and horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 scale = triangle.scale();
        triangle.scale({scale.x + delta, scale.y + delta, scale.z});
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, ScaleX) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled horizontally\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 scale = triangle.scale();
        triangle.scaleX(scale.x + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, ScaleY) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be scaled vertically\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    int count = 75;
    double delta = 0.004;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 scale = triangle.scale();
        triangle.scaleY(scale.y + delta);
        count--;
        if (count == 0) {
            delta *= -1;
            count = 125;
        }

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, Rotate) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        triangle.rotate({0, 0, delta});

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, RotateX) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around x-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        triangle.rotateX(delta);

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, RotateY) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around y-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        triangle.rotateY(delta);

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, RotateZ) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate around z-axis\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        triangle.rotateZ(delta);

        triangle.update();
        triangle.render(context);
    });
}

TEST_F(RenderableSuite, SetRotation) {
    if (skipHandTest) GTEST_SKIP();

    Renderable triangle(RenderableId(), { .meshId = triangleMeshId, .materialId = materialId });

    PRINTF("There should be a white triangle on the screen\n");
    PRINTF("The triangle should be rotate clockwise\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    double delta = -0.5;
    WINDOW_LOOP("Window display wrong", {
        glm::vec3 rotation = triangle.rotation();
        triangle.rotation({rotation.x, rotation.y, rotation.z + delta});

        triangle.update();
        triangle.render(context);
    });
}
