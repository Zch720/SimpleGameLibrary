#include <gtest/gtest.h>
#include "./test_env.h"
#include "./utils.h"
#include "../include/renderable.h"

using namespace glm;

class RenderableSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        sgf_test::createOpenGLContext();

        shaderId = context.ShaderManager.create({
            .vertexShaderSource = vertexShaderSource,
            .fragmentShaderSource = fragmentShaderSource
        });
        context.ShaderManager.getRef(shaderId).registerUniformVariable("transform", "model");
        material = new Material(shaderId);
        triangleVertexLayout = VertexLayout();
        triangleVertexLayout.addAttribute({ .index = 0, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 0 });
        triangleMesh = new Mesh(triangleVertices.data(), 3, triangleIndices.data(), 3, triangleVertexLayout);
    }

    virtual void TearDown() {
        delete material;
        delete triangleMesh;
        context.ShaderManager.destroyAll();

        sgf_test::OpenGLContextTerminate();
    }

    RenderContext context;
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

    Renderable triangle(&mesh, material);

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
    Mesh mesh((void *)vertices.data(), 4, indices.data(), 6, vertexLayout);

    Renderable rectangle(&mesh, material);

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
    Mesh mesh((void *)vertices.data(), 5, indices.data(), 9, vertexLayout);

    Renderable pentagon(&mesh, material);

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

    Renderable triangle(triangleMesh, material);
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

    Renderable triangle(triangleMesh, material);
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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle1(triangleMesh, material);
    Renderable triangle2(triangleMesh, material);
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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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

    Renderable triangle(triangleMesh, material);

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
