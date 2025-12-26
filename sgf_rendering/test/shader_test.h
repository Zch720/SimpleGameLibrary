#include <gtest/gtest.h>
#include <sgf/utils/manager.h>
#include "./test_env.h"
#include "./utils.h"
#include "../include/sgf/rendering/shader.h"

using namespace glm;
using namespace sgf_core;

class ShaderSuite : public ::testing::Test {
protected:
    void SetUp() override {
        sgf_test::createOpenGLContext();
    }

    void TearDown() override {
        sgf_test::OpenGLContextTerminate();
    }

    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        uniform vec4 color;
        out vec4 FragColor;
        void main() {
            FragColor = color;
        }
    )";

    std::string fragmentShaderSourceForUniformTest = R"(
        #version 330 core

        uniform int test_shader_int;
        uniform float test_shader_float;
        uniform vec2 test_shader_vec2;
        uniform vec3 test_shader_vec3;
        uniform vec4 test_shader_vec4;
        uniform mat2 test_shader_mat2;
        uniform mat3 test_shader_mat3;
        uniform mat4 test_shader_mat4;
        uniform mat2x3 test_shader_mat2x3;
        uniform mat3x2 test_shader_mat3x2;
        uniform mat2x4 test_shader_mat2x4;
        uniform mat4x2 test_shader_mat4x2;
        uniform mat3x4 test_shader_mat3x4;
        uniform mat4x3 test_shader_mat4x3;

        uniform vec4 color;
        out vec4 FragColor;
        void main() {
            FragColor = test_shader_int *
                        test_shader_float *
                        test_shader_vec2[0] *
                        test_shader_vec3[0] *
                        test_shader_vec4[0] *
                        test_shader_mat2[0][0] *
                        test_shader_mat3[0][0] *
                        test_shader_mat4[0][0] *
                        test_shader_mat2x3[0][0] *
                        test_shader_mat3x2[0][0] *
                        test_shader_mat2x4[0][0] *
                        test_shader_mat4x2[0][0] *
                        test_shader_mat3x4[0][0] *
                        test_shader_mat4x3[0][0] *
                        color;
        }
    )";
};

TEST_F(ShaderSuite, CreateShader) {
    ASSERT_NO_THROW({
        Manager<Shader> manager;
        manager.create(Shader::Construct {
            .vertexShaderSource = vertexShaderSource,
            .fragmentShaderSource = fragmentShaderSource
        });
    });
}

TEST_F(ShaderSuite, VertexShaderCompileFail) {
#ifdef _WIN32
    std::string expectedMessage = "Compile shader failed, cause: ERROR: 0:2: '' :  syntax error, unexpected IDENTIFIER\n"
                                  "ERROR: 1 compilation errors.  No code generated.\n"
                                  "\n";
#else
    std::string expectedMessage = "Compile shader failed, cause: 0:1(1): error: syntax error, unexpected NEW_IDENTIFIER\n";
#endif

    ASSERT_THROW_MESSAGE(
        {
            Manager<Shader> manager;
            manager.create(Shader::Construct {
                .vertexShaderSource = "invalid vertex shader source",
                .fragmentShaderSource = fragmentShaderSource
            });
        },
        std::runtime_error,
        expectedMessage
    );
}

TEST_F(ShaderSuite, FragmentShaderCompileFail) {
#ifdef _WIN32
    std::string expectedMessage = "Compile shader failed, cause: ERROR: 0:2: '' :  syntax error, unexpected IDENTIFIER\n"
                                  "ERROR: 1 compilation errors.  No code generated.\n"
                                  "\n";
#else
    std::string expectedMessage = "Compile shader failed, cause: 0:1(1): error: syntax error, unexpected NEW_IDENTIFIER\n";
#endif

    ASSERT_THROW_MESSAGE(
        {
            Manager<Shader> manager;
            manager.create(Shader::Construct {
                .vertexShaderSource = "invalid fragment shader source",
                .fragmentShaderSource = fragmentShaderSource
            });
        },
        std::runtime_error,
        expectedMessage
    );
}

TEST_F(ShaderSuite, DefaultUniformVariableRegister) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSource
    });

    ASSERT_TRUE(manager.getRef(id).hasUniformVariable("color"));
}

TEST_F(ShaderSuite, RegisterUniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSource
    });

    ASSERT_NO_THROW(manager.getRef(id).registerUniformVariable("test shader color", "color"));
}

TEST_F(ShaderSuite, RegisterUniformVariableNotExistShouldFail) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });

    ASSERT_THROW_MESSAGE(
        manager.getRef(id).registerUniformVariable("test shader color", "clr"),
        std::runtime_error,
        "Uniform variable \"clr\" not found"
    );
}

TEST_F(ShaderSuite, RegisterUniformVariableTwiceShouldFail) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSource
    });

    manager.getRef(id).registerUniformVariable("test shader color", "color");
    ASSERT_THROW_MESSAGE(
        manager.getRef(id).registerUniformVariable("test shader color", "color"),
        std::runtime_error,
        "Uniform variable \"test shader color\" already registered"
    );
}

TEST_F(ShaderSuite, SetIntUniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader int", "test_shader_int");

    ASSERT_NO_THROW(manager.getRef(id).setIntUniformVariable("test shader int", 1));
    ASSERT_EQ(1, manager.getRef(id).getIntUniformVariable("test shader int"));
}

TEST_F(ShaderSuite, SetFloatUniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader float", "test_shader_float");

    ASSERT_NO_THROW(manager.getRef(id).setFloatUniformVariable("test shader float", 1.2f));
    ASSERT_EQ(1.2f, manager.getRef(id).getFloatUniformVariable("test shader float"));
}

TEST_F(ShaderSuite, SetVec2UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader vec2", "test_shader_vec2");

    vec2 value(1.0f, 4.0f);
    ASSERT_NO_THROW(manager.getRef(id).setVec2UniformVariable("test shader vec2", value));
    ASSERT_EQ(value, manager.getRef(id).getVec2UniformVariable("test shader vec2"));
}

TEST_F(ShaderSuite, SetVec3UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader vec3", "test_shader_vec3");

    vec3 value(1.0f, 4.0f, 5.0f);
    ASSERT_NO_THROW(manager.getRef(id).setVec3UniformVariable("test shader vec3", value));
    ASSERT_EQ(value, manager.getRef(id).getVec3UniformVariable("test shader vec3"));
}

TEST_F(ShaderSuite, SetVec4UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader vec4", "test_shader_vec4");

    vec4 value(1.0f, 4.0f, 5.0f, 2.0f);
    ASSERT_NO_THROW(manager.getRef(id).setVec4UniformVariable("test shader vec4", value));
    ASSERT_EQ(value, manager.getRef(id).getVec4UniformVariable("test shader vec4"));
}

TEST_F(ShaderSuite, SetMat2UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat2", "test_shader_mat2");

    mat2 value(1.0f, 2.0f, 3.0f, 4.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat2UniformVariable("test shader mat2", value));
    ASSERT_EQ(value, manager.getRef(id).getMat2UniformVariable("test shader mat2"));
}

TEST_F(ShaderSuite, SetMat3UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat3", "test_shader_mat3");

    mat3 value(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat3UniformVariable("test shader mat3", value));
    ASSERT_EQ(value, manager.getRef(id).getMat3UniformVariable("test shader mat3"));
}

TEST_F(ShaderSuite, SetMat4UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat4", "test_shader_mat4");

    mat4 value(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat4UniformVariable("test shader mat4", value));
    ASSERT_EQ(value, manager.getRef(id).getMat4UniformVariable("test shader mat4"));
}

TEST_F(ShaderSuite, SetMat2x3UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat2x3", "test_shader_mat2x3");

    mat2x3 value(
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat2x3UniformVariable("test shader mat2x3", value));
    ASSERT_EQ(value, manager.getRef(id).getMat2x3UniformVariable("test shader mat2x3"));
}

TEST_F(ShaderSuite, SetMat3x2UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat3x2", "test_shader_mat3x2");

    mat3x2 value(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat3x2UniformVariable("test shader mat3x2", value));
    ASSERT_EQ(value, manager.getRef(id).getMat3x2UniformVariable("test shader mat3x2"));
}

TEST_F(ShaderSuite, SetMat2x4UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat2x4", "test_shader_mat2x4");

    mat2x4 value(
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f,
        7.0f, 8.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat2x4UniformVariable("test shader mat2x4", value));
    ASSERT_EQ(value, manager.getRef(id).getMat2x4UniformVariable("test shader mat2x4"));
}

TEST_F(ShaderSuite, SetMat4x2UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat4x2", "test_shader_mat4x2");

    mat4x2 value(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat4x2UniformVariable("test shader mat4x2", value));
    ASSERT_EQ(value, manager.getRef(id).getMat4x2UniformVariable("test shader mat4x2"));
}

TEST_F(ShaderSuite, SetMat3x4UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat3x4", "test_shader_mat3x4");

    mat3x4 value(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f,
        10.0f, 11.0f, 12.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat3x4UniformVariable("test shader mat3x4", value));
    ASSERT_EQ(value, manager.getRef(id).getMat3x4UniformVariable("test shader mat3x4"));
}

TEST_F(ShaderSuite, SetMat4x3UniformVariable) {
    Manager<Shader> manager;
    Shader::Id id = manager.create(Shader::Construct {
        .vertexShaderSource = vertexShaderSource,
        .fragmentShaderSource = fragmentShaderSourceForUniformTest
    });
    manager.getRef(id).registerUniformVariable("test shader mat4x3", "test_shader_mat4x3");

    mat4x3 value(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f);
    ASSERT_NO_THROW(manager.getRef(id).setMat4x3UniformVariable("test shader mat4x3", value));
    ASSERT_EQ(value, manager.getRef(id).getMat4x3UniformVariable("test shader mat4x3"));
}