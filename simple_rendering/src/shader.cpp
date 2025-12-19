#include <stdexcept>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "../include/shader.h"

Shader::Shader(ShaderId id, std::string vertexShaderSource, std::string fragmentShaderSource): id(id) {
    uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShaderId, vertexShaderSource.c_str());
    uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShaderId, fragmentShaderSource.c_str());

    programId = glCreateProgram();
    linkProgram(programId, vertexShaderId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    registerDefaultUniformVariable();
}

Shader::~Shader() {
    glDeleteProgram(programId);
}

ShaderId Shader::getId() const {
    return id;
}

void Shader::use() {
    glUseProgram(programId);
}

void Shader::registerUniformVariable(std::string identifyName, std::string uniformName) {
    if (uniformLocations.find(identifyName) != uniformLocations.end()) {
        throw std::runtime_error("Uniform variable \"" + identifyName + "\" already registered");
    }

    int location = glGetUniformLocation(programId, uniformName.c_str());
    if (location == -1) {
        throw std::runtime_error("Uniform variable \"" + uniformName + "\" not found");
    }
    uniformLocations[identifyName] = location;
}

bool Shader::hasUniformVariable(std::string identifyName) {
    return uniformLocations.find(identifyName) != uniformLocations.end();
}

void Shader::setIntUniformVariable(std::string identifyName, int value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniform1i(uniformLocations[identifyName], value);
}

int Shader::getIntUniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    int value;
    glGetUniformiv(programId, uniformLocations[identifyName], &value);
    return value;
}

void Shader::setFloatUniformVariable(std::string identifyName, float value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniform1f(uniformLocations[identifyName], value);
}

float Shader::getFloatUniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value;
    glGetUniformfv(programId, uniformLocations[identifyName], &value);
    return value;
}

void Shader::setVec2UniformVariable(std::string identifyName, glm::vec2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniform2fv(uniformLocations[identifyName], 1, glm::value_ptr(value));
}

glm::vec2 Shader::getVec2UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[2];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_vec2(value);
}

void Shader::setVec3UniformVariable(std::string identifyName, glm::vec3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniform3fv(uniformLocations[identifyName], 1, glm::value_ptr(value));
}

glm::vec3 Shader::getVec3UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[3];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_vec3(value);
}

void Shader::setVec4UniformVariable(std::string identifyName, glm::vec4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniform4f(uniformLocations[identifyName], value.x, value.y, value.z, value.w);
}

glm::vec4 Shader::getVec4UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[4];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_vec4(value);
}

void Shader::setMat2UniformVariable(std::string identifyName, glm::mat2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix2fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat2 Shader::getMat2UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[4];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat2(value);
}

void Shader::setMat3UniformVariable(std::string identifyName, glm::mat3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix3fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat3 Shader::getMat3UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[9];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat3(value);
}

void Shader::setMat4UniformVariable(std::string identifyName, glm::mat4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix4fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat4 Shader::getMat4UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[16];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat4(value);
}

void Shader::setMat2x3UniformVariable(std::string identifyName, glm::mat2x3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix2x3fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat2x3 Shader::getMat2x3UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[6];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat2x3(value);
}

void Shader::setMat3x2UniformVariable(std::string identifyName, glm::mat3x2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix3x2fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat3x2 Shader::getMat3x2UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[6];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat3x2(value);
}

void Shader::setMat2x4UniformVariable(std::string identifyName, glm::mat2x4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix2x4fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat2x4 Shader::getMat2x4UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[8];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat2x4(value);
}

void Shader::setMat4x2UniformVariable(std::string identifyName, glm::mat4x2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix4x2fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat4x2 Shader::getMat4x2UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[8];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat4x2(value);
}

void Shader::setMat3x4UniformVariable(std::string identifyName, glm::mat3x4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix3x4fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat3x4 Shader::getMat3x4UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[12];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat3x4(value);
}

void Shader::setMat4x3UniformVariable(std::string identifyName, glm::mat4x3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programId);
    glUniformMatrix4x3fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat4x3 Shader::getMat4x3UniformVariable(std::string identifyName) {
    checkUniformVariableExist(identifyName);
    float value[12];
    glGetUniformfv(programId, uniformLocations[identifyName], value);
    return glm::make_mat4x3(value);
}

void Shader::compileShader(uint32_t shaderId, const char * source) {
    glShaderSource(shaderId, 1, &source, nullptr);
    glCompileShader(shaderId);
    if (!isShaderCompileSuccess(shaderId)) {
        throw std::runtime_error("Compile shader failed, cause: " + getShaderCompileErrors(shaderId));
    }
}

bool Shader::isShaderCompileSuccess(uint32_t shaderId) {
    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    return success == GL_TRUE;
}

std::string Shader::getShaderCompileErrors(uint32_t shaderId) {
    int logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    char * log = new char[logLength];
    glGetShaderInfoLog(shaderId, logLength, nullptr, log);
    std::string logString(log);
    delete[] log;
    return logString;
}

void Shader::linkProgram(uint32_t programId, uint32_t vertexShaderId, uint32_t fragmentShaderId) {
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);
    if (!isProgramLinkSuccess(programId)) {
        throw std::runtime_error("Link shader failed, cause: " + getProgramLinkErrors(programId));
    }

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
}

bool Shader::isProgramLinkSuccess(uint32_t programId) {
    int success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    return success == GL_TRUE;
}

std::string Shader::getProgramLinkErrors(uint32_t programId) {
    int logLength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
    char * log = new char[logLength];
    glGetProgramInfoLog(programId, logLength, nullptr, log);
    std::string logString(log);
    delete[] log;
    return logString;
}

std::vector<std::string> Shader::getAllUniformVariableName() {
    std::vector<std::string> uniformNames = {};

    int count;

    int size;
    unsigned int type;

    const int bufSize = 64;
    char name[bufSize];
    int length;

    glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &count);

    for (int i = 0; i < count; i++) {
        glGetActiveUniform(programId, i, bufSize, &length, &size, &type, name);
        uniformNames.push_back(name);
    }

    return uniformNames;
}

void Shader::registerDefaultUniformVariable() {
    std::vector<std::string> uniformNames = getAllUniformVariableName();
    for (std::string uniformName : uniformNames) {
        registerUniformVariable(uniformName, uniformName);
    }
}

void Shader::checkUniformVariableExist(std::string identifyName) {
    if (uniformLocations.find(identifyName) == uniformLocations.end()) {
        throw std::runtime_error("Uniform variable \"" + identifyName + "\" not registered");
    }
}