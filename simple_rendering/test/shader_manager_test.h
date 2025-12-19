#include <gtest/gtest.h>
#include "./test_env.h"
#include "../include/window_manager.h"
#include "../include/shader_manager.h"

class ShaderManagerSuite : public testing::Test {
protected:
    void SetUp() override {
        WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    }

    void TearDown() override {
        ShaderManager::Instance().destroyShaders();
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

TEST_F(ShaderManagerSuite, Breath) {
    ShaderManager::Instance();
}

TEST_F(ShaderManagerSuite, CreateShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSource);

    ASSERT_TRUE(ShaderManager::Instance().hasShader("test"));
}

TEST_F(ShaderManagerSuite, UseShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSource);

    ShaderManager::Instance().useShader("test");
}

TEST_F(ShaderManagerSuite, DefaultUniformVariableRegister) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ASSERT_TRUE(ShaderManager::Instance().isShaderHasUniformVariable("test", "color"));
    ASSERT_TRUE(ShaderManager::Instance().isShaderHasUniformVariable("test", "test_shader_int"));
}

TEST_F(ShaderManagerSuite, RegisterUniformVariable) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader int", "test_shader_int");
    ASSERT_TRUE(ShaderManager::Instance().isShaderHasUniformVariable("test", "test shader int"));
}

TEST_F(ShaderManagerSuite, SetIntUniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader int", "test_shader_int");

    ShaderManager::Instance().setShaderIntUniformVariable("test", "test shader int", 1);
    ASSERT_EQ(1, ShaderManager::Instance().getShaderIntUniformVariable("test", "test shader int"));
}

TEST_F(ShaderManagerSuite, SetFloatUniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader float", "test_shader_float");

    ShaderManager::Instance().setShaderFloatUniformVariable("test", "test shader float", 1.0f);
    ASSERT_EQ(1.0f, ShaderManager::Instance().getShaderFloatUniformVariable("test", "test shader float"));
}

TEST_F(ShaderManagerSuite, SetVec2UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader vec2", "test_shader_vec2");

    ShaderManager::Instance().setShaderVec2UniformVariable("test", "test shader vec2", glm::vec2(1.0f, 2.0f));
    ASSERT_EQ(glm::vec2(1.0f, 2.0f), ShaderManager::Instance().getShaderVec2UniformVariable("test", "test shader vec2"));
}

TEST_F(ShaderManagerSuite, SetVec3UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader vec3", "test_shader_vec3");

    ShaderManager::Instance().setShaderVec3UniformVariable("test", "test shader vec3", glm::vec3(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(glm::vec3(1.0f, 2.0f, 3.0f), ShaderManager::Instance().getShaderVec3UniformVariable("test", "test shader vec3"));
}

TEST_F(ShaderManagerSuite, SetVec4UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader vec4", "test_shader_vec4");

    ShaderManager::Instance().setShaderVec4UniformVariable("test", "test shader vec4", glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
    ASSERT_EQ(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), ShaderManager::Instance().getShaderVec4UniformVariable("test", "test shader vec4"));
}

TEST_F(ShaderManagerSuite, SetMat2UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat2", "test_shader_mat2");

    ShaderManager::Instance().setShaderMat2UniformVariable("test", "test shader mat2", glm::mat2(1.0f));
    ASSERT_EQ(glm::mat2(1.0f), ShaderManager::Instance().getShaderMat2UniformVariable("test", "test shader mat2"));
}

TEST_F(ShaderManagerSuite, SetMat3UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat3", "test_shader_mat3");

    ShaderManager::Instance().setShaderMat3UniformVariable("test", "test shader mat3", glm::mat3(1.0f));
    ASSERT_EQ(glm::mat3(1.0f), ShaderManager::Instance().getShaderMat3UniformVariable("test", "test shader mat3"));
}

TEST_F(ShaderManagerSuite, SetMat4UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat4", "test_shader_mat4");

    ShaderManager::Instance().setShaderMat4UniformVariable("test", "test shader mat4", glm::mat4(1.0f));
    ASSERT_EQ(glm::mat4(1.0f), ShaderManager::Instance().getShaderMat4UniformVariable("test", "test shader mat4"));
}

TEST_F(ShaderManagerSuite, SetMat2x3UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat2x3", "test_shader_mat2x3");

    ShaderManager::Instance().setShaderMat2x3UniformVariable("test", "test shader mat2x3", glm::mat2x3(1.0f));
    ASSERT_EQ(glm::mat2x3(1.0f), ShaderManager::Instance().getShaderMat2x3UniformVariable("test", "test shader mat2x3"));
}

TEST_F(ShaderManagerSuite, SetMat3x2UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat3x2", "test_shader_mat3x2");

    ShaderManager::Instance().setShaderMat3x2UniformVariable("test", "test shader mat3x2", glm::mat3x2(1.0f));
    ASSERT_EQ(glm::mat3x2(1.0f), ShaderManager::Instance().getShaderMat3x2UniformVariable("test", "test shader mat3x2"));
}

TEST_F(ShaderManagerSuite, SetMat2x4UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat2x4", "test_shader_mat2x4");

    ShaderManager::Instance().setShaderMat2x4UniformVariable("test", "test shader mat2x4", glm::mat2x4(1.0f));
    ASSERT_EQ(glm::mat2x4(1.0f), ShaderManager::Instance().getShaderMat2x4UniformVariable("test", "test shader mat2x4"));
}

TEST_F(ShaderManagerSuite, SetMat4x2UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat4x2", "test_shader_mat4x2");

    ShaderManager::Instance().setShaderMat4x2UniformVariable("test", "test shader mat4x2", glm::mat4x2(1.0f));
    ASSERT_EQ(glm::mat4x2(1.0f), ShaderManager::Instance().getShaderMat4x2UniformVariable("test", "test shader mat4x2"));
}

TEST_F(ShaderManagerSuite, SetMat3x4UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat3x4", "test_shader_mat3x4");

    ShaderManager::Instance().setShaderMat3x4UniformVariable("test", "test shader mat3x4", glm::mat3x4(1.0f));
    ASSERT_EQ(glm::mat3x4(1.0f), ShaderManager::Instance().getShaderMat3x4UniformVariable("test", "test shader mat3x4"));
}

TEST_F(ShaderManagerSuite, SetMat4x3UniformVariableForShader) {
    ShaderManager::Instance().createShader("test", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test", "test shader mat4x3", "test_shader_mat4x3");

    ShaderManager::Instance().setShaderMat4x3UniformVariable("test", "test shader mat4x3", glm::mat4x3(1.0f));
    ASSERT_EQ(glm::mat4x3(1.0f), ShaderManager::Instance().getShaderMat4x3UniformVariable("test", "test shader mat4x3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderIntUniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader int", "test_shader_int");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader int", "test_shader_int");

    ShaderManager::Instance().setAllShadersIntUniformVariable("test shader int", 1);
    ASSERT_EQ(1, ShaderManager::Instance().getShaderIntUniformVariable("test1", "test shader int"));
    ASSERT_EQ(1, ShaderManager::Instance().getShaderIntUniformVariable("test2", "test shader int"));
}

TEST_F(ShaderManagerSuite, SetAllShaderFloatUniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader float", "test_shader_float");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader float", "test_shader_float");

    ShaderManager::Instance().setAllShadersFloatUniformVariable("test shader float", 1.0f);
    ASSERT_EQ(1.0f, ShaderManager::Instance().getShaderFloatUniformVariable("test1", "test shader float"));
    ASSERT_EQ(1.0f, ShaderManager::Instance().getShaderFloatUniformVariable("test2", "test shader float"));
}

TEST_F(ShaderManagerSuite, SetAllShaderVec2UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader vec2", "test_shader_vec2");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader vec2", "test_shader_vec2");

    ShaderManager::Instance().setAllShadersVec2UniformVariable("test shader vec2", glm::vec2(1.0f, 2.0f));
    ASSERT_EQ(glm::vec2(1.0f, 2.0f), ShaderManager::Instance().getShaderVec2UniformVariable("test1", "test shader vec2"));
    ASSERT_EQ(glm::vec2(1.0f, 2.0f), ShaderManager::Instance().getShaderVec2UniformVariable("test2", "test shader vec2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderVec3UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader vec3", "test_shader_vec3");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader vec3", "test_shader_vec3");

    ShaderManager::Instance().setAllShadersVec3UniformVariable("test shader vec3", glm::vec3(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(glm::vec3(1.0f, 2.0f, 3.0f), ShaderManager::Instance().getShaderVec3UniformVariable("test1", "test shader vec3"));
    ASSERT_EQ(glm::vec3(1.0f, 2.0f, 3.0f), ShaderManager::Instance().getShaderVec3UniformVariable("test2", "test shader vec3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderVec4UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader vec4", "test_shader_vec4");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader vec4", "test_shader_vec4");

    ShaderManager::Instance().setAllShadersVec4UniformVariable("test shader vec4", glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
    ASSERT_EQ(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), ShaderManager::Instance().getShaderVec4UniformVariable("test1", "test shader vec4"));
    ASSERT_EQ(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), ShaderManager::Instance().getShaderVec4UniformVariable("test2", "test shader vec4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat2UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat2", "test_shader_mat2");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat2", "test_shader_mat2");

    ShaderManager::Instance().setAllShadersMat2UniformVariable("test shader mat2", glm::mat2(1.0f));
    ASSERT_EQ(glm::mat2(1.0f), ShaderManager::Instance().getShaderMat2UniformVariable("test1", "test shader mat2"));
    ASSERT_EQ(glm::mat2(1.0f), ShaderManager::Instance().getShaderMat2UniformVariable("test2", "test shader mat2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat3UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat3", "test_shader_mat3");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat3", "test_shader_mat3");

    ShaderManager::Instance().setAllShadersMat3UniformVariable("test shader mat3", glm::mat3(1.0f));
    ASSERT_EQ(glm::mat3(1.0f), ShaderManager::Instance().getShaderMat3UniformVariable("test1", "test shader mat3"));
    ASSERT_EQ(glm::mat3(1.0f), ShaderManager::Instance().getShaderMat3UniformVariable("test2", "test shader mat3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat4UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat4", "test_shader_mat4");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat4", "test_shader_mat4");

    ShaderManager::Instance().setAllShadersMat4UniformVariable("test shader mat4", glm::mat4(1.0f));
    ASSERT_EQ(glm::mat4(1.0f), ShaderManager::Instance().getShaderMat4UniformVariable("test1", "test shader mat4"));
    ASSERT_EQ(glm::mat4(1.0f), ShaderManager::Instance().getShaderMat4UniformVariable("test2", "test shader mat4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat2x3UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat2x3", "test_shader_mat2x3");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat2x3", "test_shader_mat2x3");

    ShaderManager::Instance().setAllShadersMat2x3UniformVariable("test shader mat2x3", glm::mat2x3(1.0f));
    ASSERT_EQ(glm::mat2x3(1.0f), ShaderManager::Instance().getShaderMat2x3UniformVariable("test1", "test shader mat2x3"));
    ASSERT_EQ(glm::mat2x3(1.0f), ShaderManager::Instance().getShaderMat2x3UniformVariable("test2", "test shader mat2x3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat3x2UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat3x2", "test_shader_mat3x2");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat3x2", "test_shader_mat3x2");

    ShaderManager::Instance().setAllShadersMat3x2UniformVariable("test shader mat3x2", glm::mat3x2(1.0f));
    ASSERT_EQ(glm::mat3x2(1.0f), ShaderManager::Instance().getShaderMat3x2UniformVariable("test1", "test shader mat3x2"));
    ASSERT_EQ(glm::mat3x2(1.0f), ShaderManager::Instance().getShaderMat3x2UniformVariable("test2", "test shader mat3x2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat2x4UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat2x4", "test_shader_mat2x4");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat2x4", "test_shader_mat2x4");

    ShaderManager::Instance().setAllShadersMat2x4UniformVariable("test shader mat2x4", glm::mat2x4(1.0f));
    ASSERT_EQ(glm::mat2x4(1.0f), ShaderManager::Instance().getShaderMat2x4UniformVariable("test1", "test shader mat2x4"));
    ASSERT_EQ(glm::mat2x4(1.0f), ShaderManager::Instance().getShaderMat2x4UniformVariable("test2", "test shader mat2x4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat4x2UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat4x2", "test_shader_mat4x2");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat4x2", "test_shader_mat4x2");

    ShaderManager::Instance().setAllShadersMat4x2UniformVariable("test shader mat4x2", glm::mat4x2(1.0f));
    ASSERT_EQ(glm::mat4x2(1.0f), ShaderManager::Instance().getShaderMat4x2UniformVariable("test1", "test shader mat4x2"));
    ASSERT_EQ(glm::mat4x2(1.0f), ShaderManager::Instance().getShaderMat4x2UniformVariable("test2", "test shader mat4x2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat3x4UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat3x4", "test_shader_mat3x4");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat3x4", "test_shader_mat3x4");

    ShaderManager::Instance().setAllShadersMat3x4UniformVariable("test shader mat3x4", glm::mat3x4(1.0f));
    ASSERT_EQ(glm::mat3x4(1.0f), ShaderManager::Instance().getShaderMat3x4UniformVariable("test1", "test shader mat3x4"));
    ASSERT_EQ(glm::mat3x4(1.0f), ShaderManager::Instance().getShaderMat3x4UniformVariable("test2", "test shader mat3x4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat4x3UniformVariable) {
    ShaderManager::Instance().createShader("test1", vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().createShader("test2", vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable("test1", "test shader mat4x3", "test_shader_mat4x3");
    ShaderManager::Instance().registerShaderUniformVariable("test2", "test shader mat4x3", "test_shader_mat4x3");

    ShaderManager::Instance().setAllShadersMat4x3UniformVariable("test shader mat4x3", glm::mat4x3(1.0f));
    ASSERT_EQ(glm::mat4x3(1.0f), ShaderManager::Instance().getShaderMat4x3UniformVariable("test1", "test shader mat4x3"));
    ASSERT_EQ(glm::mat4x3(1.0f), ShaderManager::Instance().getShaderMat4x3UniformVariable("test2", "test shader mat4x3"));
}