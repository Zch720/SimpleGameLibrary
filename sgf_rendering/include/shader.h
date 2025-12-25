#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/matrix.hpp>
#include <resource.h>
#include "./shader_id.h"

class Shader: public Resource<Shader, ShaderId> {
public:
    struct Construct {
        std::string vertexShaderSource;
        std::string fragmentShaderSource;
    };

    Shader(const Id & id, const Construct & constructParameter);
    ~Shader();

    void use();

    void registerUniformVariable(const std::string & identifyName, const std::string & uniformName);
    bool hasUniformVariable(const std::string & identifyName);
    void setIntUniformVariable(const std::string & identifyName, int value);
    int getIntUniformVariable(const std::string & identifyName);
    void setFloatUniformVariable(const std::string & identifyName, float value);
    float getFloatUniformVariable(const std::string & identifyName);
    void setVec2UniformVariable(const std::string & identifyName, glm::vec2 value);
    glm::vec2 getVec2UniformVariable(const std::string & identifyName);
    void setVec3UniformVariable(const std::string & identifyName, glm::vec3 value);
    glm::vec3 getVec3UniformVariable(const std::string & identifyName);
    void setVec4UniformVariable(const std::string & identifyName, glm::vec4 value);
    glm::vec4 getVec4UniformVariable(const std::string & identifyName);
    void setMat2UniformVariable(const std::string & identifyName, glm::mat2 value);
    glm::mat2 getMat2UniformVariable(const std::string & identifyName);
    void setMat3UniformVariable(const std::string & identifyName, glm::mat3 value);
    glm::mat3 getMat3UniformVariable(const std::string & identifyName);
    void setMat4UniformVariable(const std::string & identifyName, glm::mat4 value);
    glm::mat4 getMat4UniformVariable(const std::string & identifyName);
    void setMat2x3UniformVariable(const std::string & identifyName, glm::mat2x3 value);
    glm::mat2x3 getMat2x3UniformVariable(const std::string & identifyName);
    void setMat3x2UniformVariable(const std::string & identifyName, glm::mat3x2 value);
    glm::mat3x2 getMat3x2UniformVariable(const std::string & identifyName);
    void setMat2x4UniformVariable(const std::string & identifyName, glm::mat2x4 value);
    glm::mat2x4 getMat2x4UniformVariable(const std::string & identifyName);
    void setMat4x2UniformVariable(const std::string & identifyName, glm::mat4x2 value);
    glm::mat4x2 getMat4x2UniformVariable(const std::string & identifyName);
    void setMat3x4UniformVariable(const std::string & identifyName, glm::mat3x4 value);
    glm::mat3x4 getMat3x4UniformVariable(const std::string & identifyName);
    void setMat4x3UniformVariable(const std::string & identifyName, glm::mat4x3 value);
    glm::mat4x3 getMat4x3UniformVariable(const std::string & identifyName);

private:
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
    void checkUniformVariableExist(const std::string & identifyName);
};

#include "./shader.tpp"
