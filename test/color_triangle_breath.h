#include <gtest/gtest.h>
#include <sgf/control/game_control_context.h>
#include <sgf/rendering/renderable.h>

class ColorTriangleBreathSuite: public testing::Test {
protected:
    void SetUp() override {
        layout.addAttribute({ .index = 0, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 0 });
        layout.addAttribute({ .index = 1, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 3 * sizeof(float) });
    }

    std::string vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;   // The vertex position data
        layout (location = 1) in vec3 aColor;  // The vertex color data
        
        uniform mat4 model = mat4(1.0);

        out vec3 ourColor; // Output a color to the fragment shader

        void main()
        {
            gl_Position = model * vec4(aPos, 1.0); // Set the position
            ourColor = aColor; // Pass the color to the fragment shader
        }
    )";

    std::string fragmentShader = R"(
        #version 330 core
        out vec4 FragColor; // The final output color for the pixel

        in vec3 ourColor; // Input color from the vertex shader (interpolated)

        void main()
        {
            FragColor = vec4(ourColor, 1.0f); // Set the final color, including alpha (opacity)
        }
    )";

    float vertices[18] {
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top (Red)
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom Left (Green)
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom Right (Blue)
    };
    uint32_t indices[3] {0, 1, 2};
    sgf_core::VertexLayout layout;
};

TEST_F(ColorTriangleBreathSuite, Breath) {
    sgf_core::PlatformContext platformContext;
    platformContext.createWindow({ .width = 800, .height = 800, .title = "Test Window" });

    sgf_core::RenderContext renderContext;
    renderContext.initialize();
    platformContext.setWindowClearBuffer(renderContext.getClearFrameBufferBits());
    
    sgf_core::GameControlContext gameContext(renderContext, platformContext);

    
    sgf_core::ShaderId shaderId = renderContext.ShaderManager.create({
        .vertexShaderSource = vertexShader,
        .fragmentShaderSource = fragmentShader,
    });
    sgf_core::MeshId meshId = renderContext.MeshManager.create({
        .vertices = vertices,
        .verticesCount = 3,
        .indices = indices,
        .indicesCount = 3,
        .vertexLayout = layout,
    });
    sgf_core::MaterialId materialId = renderContext.MaterialManager.create({
        .useTexture = false,
        .shaderId = shaderId,
    });
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "model", sgf_core::UniformSource::TRANSFORM_MATRIX);

    sgf_core::Manager<sgf_core::Renderable> renderableManager;
    sgf_core::RenderableId renderableId = renderableManager.create({
        .meshId = meshId,
        .materialId = materialId,
    });

    gameContext.GameLoop().addRenderFunction([&renderableManager, &renderableId](const sgf_core::RenderContext & context) {
        renderableManager.getRef(renderableId).render(context);
    });

    gameContext.GameLoop().addUpdateFunction([&renderableManager, &renderableId, &gameContext]() {
        renderableManager.getRef(renderableId).rotateX(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderableManager.getRef(renderableId).rotateY(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderableManager.getRef(renderableId).rotateZ(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderableManager.getRef(renderableId).update();
    });

    gameContext.GameLoop().addUpdateFunction([&platformContext, &gameContext]() {
        if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
            gameContext.GameLoop().stop();
        }
    });

    gameContext.GameLoop().run();

    renderContext.destroyAllResources();
    platformContext.terminate();
}

class ColorCubeBreathSuite: public testing::Test {
protected:
    void SetUp() override {
        layout.addAttribute({ .index = 0, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 0 });
        layout.addAttribute({ .index = 1, .size = 3, .type = sgf_core::VertexLayout::FLOAT, .normalized = false, .offset = 3 * sizeof(float) });
    }

    std::string vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;   // The vertex position data
        layout (location = 1) in vec3 aColor;  // The vertex color data
        
        uniform mat4 model = mat4(1.0);

        out vec3 ourColor; // Output a color to the fragment shader

        void main()
        {
            gl_Position = model * vec4(aPos, 1.0); // Set the position
            ourColor = aColor; // Pass the color to the fragment shader
        }
    )";

    std::string fragmentShader = R"(
        #version 330 core
        out vec4 FragColor; // The final output color for the pixel

        in vec3 ourColor; // Input color from the vertex shader (interpolated)

        void main()
        {
            FragColor = vec4(ourColor, 1.0f); // Set the final color, including alpha (opacity)
        }
    )";

    float vertices[144] {
         0.5,  0.5,  0.5,   1.0, 0.0, 0.0,
         0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
        -0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
        -0.5,  0.5,  0.5,   1.0, 0.0, 0.0,

         0.5,  0.5, -0.5,   0.0, 1.0, 0.0,
         0.5,  0.5,  0.5,   0.0, 1.0, 0.0,
        -0.5,  0.5,  0.5,   0.0, 1.0, 0.0,
        -0.5,  0.5, -0.5,   0.0, 1.0, 0.0,

         0.5, -0.5, -0.5,   1.0, 0.0, 0.0,
         0.5,  0.5, -0.5,   1.0, 0.0, 0.0,
        -0.5,  0.5, -0.5,   1.0, 0.0, 0.0,
        -0.5, -0.5, -0.5,   1.0, 0.0, 0.0,

         0.5, -0.5,  0.5,   0.0, 1.0, 0.0,
         0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
        -0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
        -0.5, -0.5,  0.5,   0.0, 1.0, 0.0,

         0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
         0.5, -0.5, -0.5,   0.0, 0.0, 1.0,
         0.5, -0.5,  0.5,   0.0, 0.0, 1.0,
         0.5,  0.5,  0.5,   0.0, 0.0, 1.0,

        -0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
        -0.5, -0.5, -0.5,   0.0, 0.0, 1.0,
        -0.5, -0.5,  0.5,   0.0, 0.0, 1.0,
        -0.5,  0.5,  0.5,   0.0, 0.0, 1.0,
    };
    uint32_t indices[36] {
         0,  1,  2,    0,  2,  3,
         4,  5,  6,    4,  6,  7,
         8,  9, 10,    8, 10, 11,
        12, 13, 14,   12, 14, 15,
        16, 17, 18,   16, 18, 19,
        20, 21, 22,   20, 22, 23,
    };
    sgf_core::VertexLayout layout;
};

TEST_F(ColorCubeBreathSuite, Breath) {
    sgf_core::PlatformContext platformContext;
    platformContext.createWindow({ .width = 800, .height = 800, .title = "Test Window" });

    sgf_core::RenderContext renderContext;
    renderContext.initialize();
    platformContext.setWindowClearBuffer(renderContext.getClearFrameBufferBits());
    
    sgf_core::GameControlContext gameContext(renderContext, platformContext);

    
    sgf_core::ShaderId shaderId = renderContext.ShaderManager.create({
        .vertexShaderSource = vertexShader,
        .fragmentShaderSource = fragmentShader,
    });
    sgf_core::MeshId meshId = renderContext.MeshManager.create({
        .vertices = vertices,
        .verticesCount = 24,
        .indices = indices,
        .indicesCount = 36,
        .vertexLayout = layout,
    });
    sgf_core::MaterialId materialId = renderContext.MaterialManager.create({
        .useTexture = false,
        .shaderId = shaderId,
    });
    renderContext.MaterialManager.getRef(materialId).registerUniform(renderContext, "model", sgf_core::UniformSource::TRANSFORM_MATRIX);

    sgf_core::Manager<sgf_core::Renderable> renderableManager;
    sgf_core::RenderableId renderableId = renderableManager.create({
        .meshId = meshId,
        .materialId = materialId,
    });

    gameContext.GameLoop().addRenderFunction([&renderableManager, &renderableId](const sgf_core::RenderContext & context) {
        renderableManager.getRef(renderableId).render(context);
    });

    gameContext.GameLoop().addUpdateFunction([&renderableManager, &renderableId, &gameContext]() {
        renderableManager.getRef(renderableId).rotateX(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderableManager.getRef(renderableId).rotateY(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderableManager.getRef(renderableId).rotateZ(30 * gameContext.GameLoop().Time().getDeltaTime());
        renderableManager.getRef(renderableId).update();
    });

    gameContext.GameLoop().addUpdateFunction([&platformContext, &gameContext]() {
        if (platformContext.Runtime().Input().Keyboard().isKeyDown(sgf_core::Key::ESCAPE)) {
            gameContext.GameLoop().stop();
        }
    });

    gameContext.GameLoop().run();

    renderContext.destroyAllResources();
    platformContext.terminate();
}
