#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./util.hpp"
#include "../include/window_manager.h"
#include "../include/shader.h"

class ShaderSuite : public ::testing::Test {
protected:
    void SetUp() override {
        WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    }

    void TearDown() override {
        WindowManager::Instance().terminate();
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
    ASSERT_NO_THROW(Shader shader(vertexShaderSource, fragmentShaderSource));
}

TEST_F(ShaderSuite, VertexShaderCompileFail) {
    ASSERT_THROW_MESSAGE(
        Shader shader("invalid vertex shader source", fragmentShaderSource),
        std::runtime_error,
        "Compile shader failed, cause: 0:1(1): error: syntax error, unexpected NEW_IDENTIFIER\n"
    );
}

TEST_F(ShaderSuite, FragmentShaderCompileFail) {
    ASSERT_THROW_MESSAGE(
        Shader shader(vertexShaderSource, "invalid fragment shader source"),
        std::runtime_error,
        "Compile shader failed, cause: 0:1(1): error: syntax error, unexpected NEW_IDENTIFIER\n"
    );
}

TEST_F(ShaderSuite, RegisterUniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSource);

    ASSERT_NO_THROW(shader.registerUniformVariable("test shader color", "color"));
}

TEST_F(ShaderSuite, RegisterUniformVariableNotExistShouldFail) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ASSERT_THROW_MESSAGE(
        shader.registerUniformVariable("test shader color", "clr"),
        std::runtime_error,
        "Uniform variable \"clr\" not found"
    );
}

TEST_F(ShaderSuite, RegisterUniformVariableTwiceShouldFail) {
    Shader shader(vertexShaderSource, fragmentShaderSource);

    shader.registerUniformVariable("test shader color", "color");
    ASSERT_THROW_MESSAGE(
        shader.registerUniformVariable("test shader color", "color"),
        std::runtime_error,
        "Uniform variable \"test shader color\" already registered"
    );
}

TEST_F(ShaderSuite, SetIntUniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader int", "test_shader_int");

    ASSERT_NO_THROW(shader.setIntUniformVariable("test shader int", 1));
    ASSERT_EQ(1, shader.getIntUniformVariable("test shader int"));
}

TEST_F(ShaderSuite, SetFloatUniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader float", "test_shader_float");

    ASSERT_NO_THROW(shader.setFloatUniformVariable("test shader float", 1.2f));
    ASSERT_EQ(1.2f, shader.getFloatUniformVariable("test shader float"));
}

TEST_F(ShaderSuite, SetVec2UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader vec2", "test_shader_vec2");

    vec2 value(1.0f, 4.0f);
    ASSERT_NO_THROW(shader.setVec2UniformVariable("test shader vec2", value));
    ASSERT_EQ(value, shader.getVec2UniformVariable("test shader vec2"));
}

TEST_F(ShaderSuite, SetVec3UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader vec3", "test_shader_vec3");

    vec3 value(1.0f, 4.0f, 5.0f);
    ASSERT_NO_THROW(shader.setVec3UniformVariable("test shader vec3", value));
    ASSERT_EQ(value, shader.getVec3UniformVariable("test shader vec3"));
}

TEST_F(ShaderSuite, SetVec4UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader vec4", "test_shader_vec4");

    vec4 value(1.0f, 4.0f, 5.0f, 2.0f);
    ASSERT_NO_THROW(shader.setVec4UniformVariable("test shader vec4", value));
    ASSERT_EQ(value, shader.getVec4UniformVariable("test shader vec4"));
}

TEST_F(ShaderSuite, SetMat2UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat2", "test_shader_mat2");

    mat2 value(1.0f, 2.0f, 3.0f, 4.0f);
    ASSERT_NO_THROW(shader.setMat2UniformVariable("test shader mat2", value));
    ASSERT_EQ(value, shader.getMat2UniformVariable("test shader mat2"));
}

TEST_F(ShaderSuite, SetMat3UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat3", "test_shader_mat3");

    mat3 value(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f);
    ASSERT_NO_THROW(shader.setMat3UniformVariable("test shader mat3", value));
    ASSERT_EQ(value, shader.getMat3UniformVariable("test shader mat3"));
}

TEST_F(ShaderSuite, SetMat4UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat4", "test_shader_mat4");

    mat4 value(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f);
    ASSERT_NO_THROW(shader.setMat4UniformVariable("test shader mat4", value));
    ASSERT_EQ(value, shader.getMat4UniformVariable("test shader mat4"));
}

TEST_F(ShaderSuite, SetMat2x3UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat2x3", "test_shader_mat2x3");

    mat2x3 value(
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f);
    ASSERT_NO_THROW(shader.setMat2x3UniformVariable("test shader mat2x3", value));
    ASSERT_EQ(value, shader.getMat2x3UniformVariable("test shader mat2x3"));
}

TEST_F(ShaderSuite, SetMat3x2UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat3x2", "test_shader_mat3x2");

    mat3x2 value(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f);
    ASSERT_NO_THROW(shader.setMat3x2UniformVariable("test shader mat3x2", value));
    ASSERT_EQ(value, shader.getMat3x2UniformVariable("test shader mat3x2"));
}

TEST_F(ShaderSuite, SetMat2x4UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat2x4", "test_shader_mat2x4");

    mat2x4 value(
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f,
        7.0f, 8.0f);
    ASSERT_NO_THROW(shader.setMat2x4UniformVariable("test shader mat2x4", value));
    ASSERT_EQ(value, shader.getMat2x4UniformVariable("test shader mat2x4"));
}

TEST_F(ShaderSuite, SetMat4x2UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat4x2", "test_shader_mat4x2");

    mat4x2 value(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f);
    ASSERT_NO_THROW(shader.setMat4x2UniformVariable("test shader mat4x2", value));
    ASSERT_EQ(value, shader.getMat4x2UniformVariable("test shader mat4x2"));
}

TEST_F(ShaderSuite, SetMat3x4UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat3x4", "test_shader_mat3x4");

    mat3x4 value(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f,
        10.0f, 11.0f, 12.0f);
    ASSERT_NO_THROW(shader.setMat3x4UniformVariable("test shader mat3x4", value));
    ASSERT_EQ(value, shader.getMat3x4UniformVariable("test shader mat3x4"));
}

TEST_F(ShaderSuite, SetMat4x3UniformVariable) {
    Shader shader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    shader.registerUniformVariable("test shader mat4x3", "test_shader_mat4x3");

    mat4x3 value(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f);
    ASSERT_NO_THROW(shader.setMat4x3UniformVariable("test shader mat4x3", value));
    ASSERT_EQ(value, shader.getMat4x3UniformVariable("test shader mat4x3"));
}