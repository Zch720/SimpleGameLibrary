#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/matrix.hpp>
#include "./shader_id.h"

using namespace glm;

class Shader {
public:
    Shader(ShaderId id, std::string vertexShaderSource, std::string fragmentShaderSource);
    ~Shader();

    ShaderId getId() const;

    void use();

    void registerUniformVariable(std::string identifyName, std::string uniformName);
    bool hasUniformVariable(std::string identifyName);
    void setIntUniformVariable(std::string identifyName, int value);
    int getIntUniformVariable(std::string identifyName);
    void setFloatUniformVariable(std::string identifyName, float value);
    float getFloatUniformVariable(std::string identifyName);
    void setVec2UniformVariable(std::string identifyName, glm::vec2 value);
    glm::vec2 getVec2UniformVariable(std::string identifyName);
    void setVec3UniformVariable(std::string identifyName, glm::vec3 value);
    glm::vec3 getVec3UniformVariable(std::string identifyName);
    void setVec4UniformVariable(std::string identifyName, glm::vec4 value);
    glm::vec4 getVec4UniformVariable(std::string identifyName);
    void setMat2UniformVariable(std::string identifyName, glm::mat2 value);
    glm::mat2 getMat2UniformVariable(std::string identifyName);
    void setMat3UniformVariable(std::string identifyName, glm::mat3 value);
    glm::mat3 getMat3UniformVariable(std::string identifyName);
    void setMat4UniformVariable(std::string identifyName, glm::mat4 value);
    glm::mat4 getMat4UniformVariable(std::string identifyName);
    void setMat2x3UniformVariable(std::string identifyName, glm::mat2x3 value);
    glm::mat2x3 getMat2x3UniformVariable(std::string identifyName);
    void setMat3x2UniformVariable(std::string identifyName, glm::mat3x2 value);
    glm::mat3x2 getMat3x2UniformVariable(std::string identifyName);
    void setMat2x4UniformVariable(std::string identifyName, glm::mat2x4 value);
    glm::mat2x4 getMat2x4UniformVariable(std::string identifyName);
    void setMat4x2UniformVariable(std::string identifyName, glm::mat4x2 value);
    glm::mat4x2 getMat4x2UniformVariable(std::string identifyName);
    void setMat3x4UniformVariable(std::string identifyName, glm::mat3x4 value);
    glm::mat3x4 getMat3x4UniformVariable(std::string identifyName);
    void setMat4x3UniformVariable(std::string identifyName, glm::mat4x3 value);
    glm::mat4x3 getMat4x3UniformVariable(std::string identifyName);

private:
    ShaderId id;

    uint32_t programId;
    std::unordered_map<std::string, uint32_t> uniformLocations;

    void compileShader(uint32_t shaderId, const char * source);
    bool isShaderCompileSuccess(uint32_t shaderId);
    std::string getShaderCompileErrors(uint32_t shaderId);
    
    void linkProgram(uint32_t programId, uint32_t vertexShaderId, uint32_t fragmentShaderId);
    bool isProgramLinkSuccess(uint32_t programId);
    std::string getProgramLinkErrors(uint32_t programId);

    std::vector<std::string> getAllUniformVariableName();
    void registerDefaultUniformVariable();
    void checkUniformVariableExist(std::string identifyName);
};