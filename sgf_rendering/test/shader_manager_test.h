#include <gtest/gtest.h>
#include "./test_env.h"
#include "./utils.h"
#include "../include/shader_manager.h"

class ShaderManagerSuite : public testing::Test {
protected:
    void SetUp() override {
        sgf_test::createOpenGLContext();
    }

    void TearDown() override {
        ShaderManager::Instance().destroyShaders();
        
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

TEST_F(ShaderManagerSuite, Breath) {
    ShaderManager::Instance();
}

TEST_F(ShaderManagerSuite, CreateShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSource);

    ASSERT_TRUE(ShaderManager::Instance().hasShader(id));
}

TEST_F(ShaderManagerSuite, UseShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSource);

    ShaderManager::Instance().useShader(id);
}

TEST_F(ShaderManagerSuite, DefaultUniformVariableRegister) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ASSERT_TRUE(ShaderManager::Instance().isShaderHasUniformVariable(id, "color"));
    ASSERT_TRUE(ShaderManager::Instance().isShaderHasUniformVariable(id, "test_shader_int"));
}

TEST_F(ShaderManagerSuite, RegisterUniformVariable) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader int", "test_shader_int");
    ASSERT_TRUE(ShaderManager::Instance().isShaderHasUniformVariable(id, "test shader int"));
}

TEST_F(ShaderManagerSuite, SetIntUniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader int", "test_shader_int");

    ShaderManager::Instance().setShaderIntUniformVariable(id, "test shader int", 1);
    ASSERT_EQ(1, ShaderManager::Instance().getShaderIntUniformVariable(id, "test shader int"));
}

TEST_F(ShaderManagerSuite, SetFloatUniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader float", "test_shader_float");

    ShaderManager::Instance().setShaderFloatUniformVariable(id, "test shader float", 1.0f);
    ASSERT_EQ(1.0f, ShaderManager::Instance().getShaderFloatUniformVariable(id, "test shader float"));
}

TEST_F(ShaderManagerSuite, SetVec2UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader vec2", "test_shader_vec2");

    ShaderManager::Instance().setShaderVec2UniformVariable(id, "test shader vec2", glm::vec2(1.0f, 2.0f));
    ASSERT_EQ(glm::vec2(1.0f, 2.0f), ShaderManager::Instance().getShaderVec2UniformVariable(id, "test shader vec2"));
}

TEST_F(ShaderManagerSuite, SetVec3UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader vec3", "test_shader_vec3");

    ShaderManager::Instance().setShaderVec3UniformVariable(id, "test shader vec3", glm::vec3(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(glm::vec3(1.0f, 2.0f, 3.0f), ShaderManager::Instance().getShaderVec3UniformVariable(id, "test shader vec3"));
}

TEST_F(ShaderManagerSuite, SetVec4UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader vec4", "test_shader_vec4");

    ShaderManager::Instance().setShaderVec4UniformVariable(id, "test shader vec4", glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
    ASSERT_EQ(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), ShaderManager::Instance().getShaderVec4UniformVariable(id, "test shader vec4"));
}

TEST_F(ShaderManagerSuite, SetMat2UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat2", "test_shader_mat2");

    ShaderManager::Instance().setShaderMat2UniformVariable(id, "test shader mat2", glm::mat2(1.0f));
    ASSERT_EQ(glm::mat2(1.0f), ShaderManager::Instance().getShaderMat2UniformVariable(id, "test shader mat2"));
}

TEST_F(ShaderManagerSuite, SetMat3UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat3", "test_shader_mat3");

    ShaderManager::Instance().setShaderMat3UniformVariable(id, "test shader mat3", glm::mat3(1.0f));
    ASSERT_EQ(glm::mat3(1.0f), ShaderManager::Instance().getShaderMat3UniformVariable(id, "test shader mat3"));
}

TEST_F(ShaderManagerSuite, SetMat4UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat4", "test_shader_mat4");

    ShaderManager::Instance().setShaderMat4UniformVariable(id, "test shader mat4", glm::mat4(1.0f));
    ASSERT_EQ(glm::mat4(1.0f), ShaderManager::Instance().getShaderMat4UniformVariable(id, "test shader mat4"));
}

TEST_F(ShaderManagerSuite, SetMat2x3UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat2x3", "test_shader_mat2x3");

    ShaderManager::Instance().setShaderMat2x3UniformVariable(id, "test shader mat2x3", glm::mat2x3(1.0f));
    ASSERT_EQ(glm::mat2x3(1.0f), ShaderManager::Instance().getShaderMat2x3UniformVariable(id, "test shader mat2x3"));
}

TEST_F(ShaderManagerSuite, SetMat3x2UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat3x2", "test_shader_mat3x2");

    ShaderManager::Instance().setShaderMat3x2UniformVariable(id, "test shader mat3x2", glm::mat3x2(1.0f));
    ASSERT_EQ(glm::mat3x2(1.0f), ShaderManager::Instance().getShaderMat3x2UniformVariable(id, "test shader mat3x2"));
}

TEST_F(ShaderManagerSuite, SetMat2x4UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat2x4", "test_shader_mat2x4");

    ShaderManager::Instance().setShaderMat2x4UniformVariable(id, "test shader mat2x4", glm::mat2x4(1.0f));
    ASSERT_EQ(glm::mat2x4(1.0f), ShaderManager::Instance().getShaderMat2x4UniformVariable(id, "test shader mat2x4"));
}

TEST_F(ShaderManagerSuite, SetMat4x2UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat4x2", "test_shader_mat4x2");

    ShaderManager::Instance().setShaderMat4x2UniformVariable(id, "test shader mat4x2", glm::mat4x2(1.0f));
    ASSERT_EQ(glm::mat4x2(1.0f), ShaderManager::Instance().getShaderMat4x2UniformVariable(id, "test shader mat4x2"));
}

TEST_F(ShaderManagerSuite, SetMat3x4UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat3x4", "test_shader_mat3x4");

    ShaderManager::Instance().setShaderMat3x4UniformVariable(id, "test shader mat3x4", glm::mat3x4(1.0f));
    ASSERT_EQ(glm::mat3x4(1.0f), ShaderManager::Instance().getShaderMat3x4UniformVariable(id, "test shader mat3x4"));
}

TEST_F(ShaderManagerSuite, SetMat4x3UniformVariableForShader) {
    ShaderId id = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id, "test shader mat4x3", "test_shader_mat4x3");

    ShaderManager::Instance().setShaderMat4x3UniformVariable(id, "test shader mat4x3", glm::mat4x3(1.0f));
    ASSERT_EQ(glm::mat4x3(1.0f), ShaderManager::Instance().getShaderMat4x3UniformVariable(id, "test shader mat4x3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderIntUniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader int", "test_shader_int");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader int", "test_shader_int");

    ShaderManager::Instance().setAllShadersIntUniformVariable("test shader int", 1);
    ASSERT_EQ(1, ShaderManager::Instance().getShaderIntUniformVariable(id1, "test shader int"));
    ASSERT_EQ(1, ShaderManager::Instance().getShaderIntUniformVariable(id2, "test shader int"));
}

TEST_F(ShaderManagerSuite, SetAllShaderFloatUniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader float", "test_shader_float");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader float", "test_shader_float");

    ShaderManager::Instance().setAllShadersFloatUniformVariable("test shader float", 1.0f);
    ASSERT_EQ(1.0f, ShaderManager::Instance().getShaderFloatUniformVariable(id1, "test shader float"));
    ASSERT_EQ(1.0f, ShaderManager::Instance().getShaderFloatUniformVariable(id2, "test shader float"));
}

TEST_F(ShaderManagerSuite, SetAllShaderVec2UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader vec2", "test_shader_vec2");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader vec2", "test_shader_vec2");

    ShaderManager::Instance().setAllShadersVec2UniformVariable("test shader vec2", glm::vec2(1.0f, 2.0f));
    ASSERT_EQ(glm::vec2(1.0f, 2.0f), ShaderManager::Instance().getShaderVec2UniformVariable(id1, "test shader vec2"));
    ASSERT_EQ(glm::vec2(1.0f, 2.0f), ShaderManager::Instance().getShaderVec2UniformVariable(id2, "test shader vec2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderVec3UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader vec3", "test_shader_vec3");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader vec3", "test_shader_vec3");

    ShaderManager::Instance().setAllShadersVec3UniformVariable("test shader vec3", glm::vec3(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(glm::vec3(1.0f, 2.0f, 3.0f), ShaderManager::Instance().getShaderVec3UniformVariable(id1, "test shader vec3"));
    ASSERT_EQ(glm::vec3(1.0f, 2.0f, 3.0f), ShaderManager::Instance().getShaderVec3UniformVariable(id2, "test shader vec3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderVec4UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader vec4", "test_shader_vec4");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader vec4", "test_shader_vec4");

    ShaderManager::Instance().setAllShadersVec4UniformVariable("test shader vec4", glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
    ASSERT_EQ(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), ShaderManager::Instance().getShaderVec4UniformVariable(id1, "test shader vec4"));
    ASSERT_EQ(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), ShaderManager::Instance().getShaderVec4UniformVariable(id2, "test shader vec4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat2UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat2", "test_shader_mat2");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat2", "test_shader_mat2");

    ShaderManager::Instance().setAllShadersMat2UniformVariable("test shader mat2", glm::mat2(1.0f));
    ASSERT_EQ(glm::mat2(1.0f), ShaderManager::Instance().getShaderMat2UniformVariable(id1, "test shader mat2"));
    ASSERT_EQ(glm::mat2(1.0f), ShaderManager::Instance().getShaderMat2UniformVariable(id2, "test shader mat2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat3UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat3", "test_shader_mat3");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat3", "test_shader_mat3");

    ShaderManager::Instance().setAllShadersMat3UniformVariable("test shader mat3", glm::mat3(1.0f));
    ASSERT_EQ(glm::mat3(1.0f), ShaderManager::Instance().getShaderMat3UniformVariable(id1, "test shader mat3"));
    ASSERT_EQ(glm::mat3(1.0f), ShaderManager::Instance().getShaderMat3UniformVariable(id2, "test shader mat3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat4UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat4", "test_shader_mat4");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat4", "test_shader_mat4");

    ShaderManager::Instance().setAllShadersMat4UniformVariable("test shader mat4", glm::mat4(1.0f));
    ASSERT_EQ(glm::mat4(1.0f), ShaderManager::Instance().getShaderMat4UniformVariable(id1, "test shader mat4"));
    ASSERT_EQ(glm::mat4(1.0f), ShaderManager::Instance().getShaderMat4UniformVariable(id2, "test shader mat4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat2x3UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat2x3", "test_shader_mat2x3");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat2x3", "test_shader_mat2x3");

    ShaderManager::Instance().setAllShadersMat2x3UniformVariable("test shader mat2x3", glm::mat2x3(1.0f));
    ASSERT_EQ(glm::mat2x3(1.0f), ShaderManager::Instance().getShaderMat2x3UniformVariable(id1, "test shader mat2x3"));
    ASSERT_EQ(glm::mat2x3(1.0f), ShaderManager::Instance().getShaderMat2x3UniformVariable(id2, "test shader mat2x3"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat3x2UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat3x2", "test_shader_mat3x2");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat3x2", "test_shader_mat3x2");

    ShaderManager::Instance().setAllShadersMat3x2UniformVariable("test shader mat3x2", glm::mat3x2(1.0f));
    ASSERT_EQ(glm::mat3x2(1.0f), ShaderManager::Instance().getShaderMat3x2UniformVariable(id1, "test shader mat3x2"));
    ASSERT_EQ(glm::mat3x2(1.0f), ShaderManager::Instance().getShaderMat3x2UniformVariable(id2, "test shader mat3x2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat2x4UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat2x4", "test_shader_mat2x4");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat2x4", "test_shader_mat2x4");

    ShaderManager::Instance().setAllShadersMat2x4UniformVariable("test shader mat2x4", glm::mat2x4(1.0f));
    ASSERT_EQ(glm::mat2x4(1.0f), ShaderManager::Instance().getShaderMat2x4UniformVariable(id1, "test shader mat2x4"));
    ASSERT_EQ(glm::mat2x4(1.0f), ShaderManager::Instance().getShaderMat2x4UniformVariable(id2, "test shader mat2x4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat4x2UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat4x2", "test_shader_mat4x2");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat4x2", "test_shader_mat4x2");

    ShaderManager::Instance().setAllShadersMat4x2UniformVariable("test shader mat4x2", glm::mat4x2(1.0f));
    ASSERT_EQ(glm::mat4x2(1.0f), ShaderManager::Instance().getShaderMat4x2UniformVariable(id1, "test shader mat4x2"));
    ASSERT_EQ(glm::mat4x2(1.0f), ShaderManager::Instance().getShaderMat4x2UniformVariable(id2, "test shader mat4x2"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat3x4UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat3x4", "test_shader_mat3x4");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat3x4", "test_shader_mat3x4");

    ShaderManager::Instance().setAllShadersMat3x4UniformVariable("test shader mat3x4", glm::mat3x4(1.0f));
    ASSERT_EQ(glm::mat3x4(1.0f), ShaderManager::Instance().getShaderMat3x4UniformVariable(id1, "test shader mat3x4"));
    ASSERT_EQ(glm::mat3x4(1.0f), ShaderManager::Instance().getShaderMat3x4UniformVariable(id2, "test shader mat3x4"));
}

TEST_F(ShaderManagerSuite, SetAllShaderMat4x3UniformVariable) {
    ShaderId id1 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);
    ShaderId id2 = ShaderManager::Instance().createShader(vertexShaderSource, fragmentShaderSourceForUniformTest);

    ShaderManager::Instance().registerShaderUniformVariable(id1, "test shader mat4x3", "test_shader_mat4x3");
    ShaderManager::Instance().registerShaderUniformVariable(id2, "test shader mat4x3", "test_shader_mat4x3");

    ShaderManager::Instance().setAllShadersMat4x3UniformVariable("test shader mat4x3", glm::mat4x3(1.0f));
    ASSERT_EQ(glm::mat4x3(1.0f), ShaderManager::Instance().getShaderMat4x3UniformVariable(id1, "test shader mat4x3"));
    ASSERT_EQ(glm::mat4x3(1.0f), ShaderManager::Instance().getShaderMat4x3UniformVariable(id2, "test shader mat4x3"));
}