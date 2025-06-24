#pragma once

#include <string>
#include <vector>
#include <glm/matrix.hpp>
#include "./shader_id.h"

class Shader;

class ShaderManager {
public:
    static ShaderManager & Instance();

    ShaderId createShader(std::string vertexShaderSource, std::string fragmentShaderSource);
    bool hasShader(ShaderId id);
    void destroyShaders();

    void useShader(ShaderId id);

    void registerShaderUniformVariable(ShaderId id, std::string identifyName, std::string uniformName);
    bool isShaderHasUniformVariable(ShaderId id, std::string identifyName);
    void setShaderIntUniformVariable(ShaderId id, std::string identifyName, int value);
    void setAllShadersIntUniformVariable(std::string identifyName, int value);
    int getShaderIntUniformVariable(ShaderId id, std::string identifyName);
    void setShaderFloatUniformVariable(ShaderId id, std::string identifyName, float value);
    void setAllShadersFloatUniformVariable(std::string identifyName, float value);
    float getShaderFloatUniformVariable(ShaderId id, std::string identifyName);
    void setShaderVec2UniformVariable(ShaderId id, std::string identifyName, glm::vec2 value);
    void setAllShadersVec2UniformVariable(std::string identifyName, glm::vec2 value);
    glm::vec2 getShaderVec2UniformVariable(ShaderId id, std::string identifyName);
    void setShaderVec3UniformVariable(ShaderId id, std::string identifyName, glm::vec3 value);
    void setAllShadersVec3UniformVariable(std::string identifyName, glm::vec3 value);
    glm::vec3 getShaderVec3UniformVariable(ShaderId id, std::string identifyName);
    void setShaderVec4UniformVariable(ShaderId id, std::string identifyName, glm::vec4 value);
    void setAllShadersVec4UniformVariable(std::string identifyName, glm::vec4 value);
    glm::vec4 getShaderVec4UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat2UniformVariable(ShaderId id, std::string identifyName, glm::mat2 value);
    void setAllShadersMat2UniformVariable(std::string identifyName, glm::mat2 value);
    glm::mat2 getShaderMat2UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat3UniformVariable(ShaderId id, std::string identifyName, glm::mat3 value);
    void setAllShadersMat3UniformVariable(std::string identifyName, glm::mat3 value);
    glm::mat3 getShaderMat3UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat4UniformVariable(ShaderId id, std::string identifyName, glm::mat4 value);
    void setAllShadersMat4UniformVariable(std::string identifyName, glm::mat4 value);
    glm::mat4 getShaderMat4UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat2x3UniformVariable(ShaderId id, std::string identifyName, glm::mat2x3 value);
    void setAllShadersMat2x3UniformVariable(std::string identifyName, glm::mat2x3 value);
    glm::mat2x3 getShaderMat2x3UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat3x2UniformVariable(ShaderId id, std::string identifyName, glm::mat3x2 value);
    void setAllShadersMat3x2UniformVariable(std::string identifyName, glm::mat3x2 value);
    glm::mat3x2 getShaderMat3x2UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat2x4UniformVariable(ShaderId id, std::string identifyName, glm::mat2x4 value);
    void setAllShadersMat2x4UniformVariable(std::string identifyName, glm::mat2x4 value);
    glm::mat2x4 getShaderMat2x4UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat4x2UniformVariable(ShaderId id, std::string identifyName, glm::mat4x2 value);
    void setAllShadersMat4x2UniformVariable(std::string identifyName, glm::mat4x2 value);
    glm::mat4x2 getShaderMat4x2UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat3x4UniformVariable(ShaderId id, std::string identifyName, glm::mat3x4 value);
    void setAllShadersMat3x4UniformVariable(std::string identifyName, glm::mat3x4 value);
    glm::mat3x4 getShaderMat3x4UniformVariable(ShaderId id, std::string identifyName);
    void setShaderMat4x3UniformVariable(ShaderId id, std::string identifyName, glm::mat4x3 value);
    void setAllShadersMat4x3UniformVariable(std::string identifyName, glm::mat4x3 value);
    glm::mat4x3 getShaderMat4x3UniformVariable(ShaderId id, std::string identifyName);

protected:
    ShaderManager();
    ~ShaderManager();

private:
    static ShaderManager instance;

    std::vector<Shader *> shaders;

    void checkShaderExist(ShaderId id);
};