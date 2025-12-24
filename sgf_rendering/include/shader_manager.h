#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <glm/matrix.hpp>
#include "./shader_id.h"

class Shader;

class ShaderManager {
public:
    static ShaderManager & Instance();

    ShaderId createShader(const std::string & vertexShaderSource, const std::string & fragmentShaderSource);
    bool hasShader(const ShaderId & id);
    void destroyShaders();

    void useShader(const ShaderId & id);

    void registerShaderUniformVariable(const ShaderId & id, const std::string & identifyName, const std::string & uniformName);
    bool isShaderHasUniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderIntUniformVariable(const ShaderId & id, const std::string & identifyName, int value);
    void setAllShadersIntUniformVariable(const std::string & identifyName, int value);
    int getShaderIntUniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderFloatUniformVariable(const ShaderId & id, const std::string & identifyName, float value);
    void setAllShadersFloatUniformVariable(const std::string & identifyName, float value);
    float getShaderFloatUniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderVec2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::vec2 value);
    void setAllShadersVec2UniformVariable(const std::string & identifyName, glm::vec2 value);
    glm::vec2 getShaderVec2UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderVec3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::vec3 value);
    void setAllShadersVec3UniformVariable(const std::string & identifyName, glm::vec3 value);
    glm::vec3 getShaderVec3UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderVec4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::vec4 value);
    void setAllShadersVec4UniformVariable(const std::string & identifyName, glm::vec4 value);
    glm::vec4 getShaderVec4UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat2 value);
    void setAllShadersMat2UniformVariable(const std::string & identifyName, glm::mat2 value);
    glm::mat2 getShaderMat2UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat3 value);
    void setAllShadersMat3UniformVariable(const std::string & identifyName, glm::mat3 value);
    glm::mat3 getShaderMat3UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat4 value);
    void setAllShadersMat4UniformVariable(const std::string & identifyName, glm::mat4 value);
    glm::mat4 getShaderMat4UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat2x3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat2x3 value);
    void setAllShadersMat2x3UniformVariable(const std::string & identifyName, glm::mat2x3 value);
    glm::mat2x3 getShaderMat2x3UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat3x2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat3x2 value);
    void setAllShadersMat3x2UniformVariable(const std::string & identifyName, glm::mat3x2 value);
    glm::mat3x2 getShaderMat3x2UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat2x4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat2x4 value);
    void setAllShadersMat2x4UniformVariable(const std::string & identifyName, glm::mat2x4 value);
    glm::mat2x4 getShaderMat2x4UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat4x2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat4x2 value);
    void setAllShadersMat4x2UniformVariable(const std::string & identifyName, glm::mat4x2 value);
    glm::mat4x2 getShaderMat4x2UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat3x4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat3x4 value);
    void setAllShadersMat3x4UniformVariable(const std::string & identifyName, glm::mat3x4 value);
    glm::mat3x4 getShaderMat3x4UniformVariable(const ShaderId & id, const std::string & identifyName);
    void setShaderMat4x3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat4x3 value);
    void setAllShadersMat4x3UniformVariable(const std::string & identifyName, glm::mat4x3 value);
    glm::mat4x3 getShaderMat4x3UniformVariable(const ShaderId & id, const std::string & identifyName);

protected:
    ShaderManager();
    ~ShaderManager();

private:
    static ShaderManager instance;

    std::unordered_map<ShaderId, Shader *> shaders;

    void checkShaderExist(const ShaderId & id);
};
