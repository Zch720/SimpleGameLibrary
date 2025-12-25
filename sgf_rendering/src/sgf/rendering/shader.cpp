#include "../../../include/sgf/rendering/shader.h"
#include <stdexcept>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

const std::string ShaderTag::TypeName = "Shader";
const std::string Shader::TypeName = "Shader";

Shader::Shader(const Id & id, const Construct & constructParameter) {
    this->id = id;

    uint32_t vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShaderHandle, constructParameter.vertexShaderSource.c_str());
    uint32_t fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShaderHandle, constructParameter.fragmentShaderSource.c_str());

    programHandle = glCreateProgram();
    linkProgram(programHandle, vertexShaderHandle, fragmentShaderHandle);
    glDeleteShader(vertexShaderHandle);
    glDeleteShader(fragmentShaderHandle);

    registerDefaultUniformVariable();
}

Shader::~Shader() {
    glDeleteProgram(programHandle);
}

void Shader::use() {
    glUseProgram(programHandle);
}

void Shader::registerUniformVariable(const std::string & identifyName, const std::string & uniformName) {
    if (uniformLocations.find(identifyName) != uniformLocations.end()) {
        throw std::runtime_error("Uniform variable \"" + identifyName + "\" already registered");
    }

    int location = glGetUniformLocation(programHandle, uniformName.c_str());
    if (location == -1) {
        throw std::runtime_error("Uniform variable \"" + uniformName + "\" not found");
    }
    uniformLocations[identifyName] = location;
}

bool Shader::hasUniformVariable(const std::string & identifyName) {
    return uniformLocations.find(identifyName) != uniformLocations.end();
}

void Shader::setIntUniformVariable(const std::string & identifyName, int value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniform1i(uniformLocations[identifyName], value);
}

int Shader::getIntUniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    int value;
    glGetUniformiv(programHandle, uniformLocations[identifyName], &value);
    return value;
}

void Shader::setFloatUniformVariable(const std::string & identifyName, float value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniform1f(uniformLocations[identifyName], value);
}

float Shader::getFloatUniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value;
    glGetUniformfv(programHandle, uniformLocations[identifyName], &value);
    return value;
}

void Shader::setVec2UniformVariable(const std::string & identifyName, glm::vec2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniform2fv(uniformLocations[identifyName], 1, glm::value_ptr(value));
}

glm::vec2 Shader::getVec2UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[2];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_vec2(value);
}

void Shader::setVec3UniformVariable(const std::string & identifyName, glm::vec3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniform3fv(uniformLocations[identifyName], 1, glm::value_ptr(value));
}

glm::vec3 Shader::getVec3UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[3];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_vec3(value);
}

void Shader::setVec4UniformVariable(const std::string & identifyName, glm::vec4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniform4f(uniformLocations[identifyName], value.x, value.y, value.z, value.w);
}

glm::vec4 Shader::getVec4UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[4];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_vec4(value);
}

void Shader::setMat2UniformVariable(const std::string & identifyName, glm::mat2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix2fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat2 Shader::getMat2UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[4];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat2(value);
}

void Shader::setMat3UniformVariable(const std::string & identifyName, glm::mat3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix3fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat3 Shader::getMat3UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[9];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat3(value);
}

void Shader::setMat4UniformVariable(const std::string & identifyName, glm::mat4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix4fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat4 Shader::getMat4UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[16];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat4(value);
}

void Shader::setMat2x3UniformVariable(const std::string & identifyName, glm::mat2x3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix2x3fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat2x3 Shader::getMat2x3UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[6];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat2x3(value);
}

void Shader::setMat3x2UniformVariable(const std::string & identifyName, glm::mat3x2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix3x2fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat3x2 Shader::getMat3x2UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[6];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat3x2(value);
}

void Shader::setMat2x4UniformVariable(const std::string & identifyName, glm::mat2x4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix2x4fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat2x4 Shader::getMat2x4UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[8];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat2x4(value);
}

void Shader::setMat4x2UniformVariable(const std::string & identifyName, glm::mat4x2 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix4x2fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat4x2 Shader::getMat4x2UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[8];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat4x2(value);
}

void Shader::setMat3x4UniformVariable(const std::string & identifyName, glm::mat3x4 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix3x4fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat3x4 Shader::getMat3x4UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[12];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
    return glm::make_mat3x4(value);
}

void Shader::setMat4x3UniformVariable(const std::string & identifyName, glm::mat4x3 value) {
    checkUniformVariableExist(identifyName);
    glUseProgram(programHandle);
    glUniformMatrix4x3fv(uniformLocations[identifyName], 1, GL_FALSE, glm::value_ptr(value));
}

glm::mat4x3 Shader::getMat4x3UniformVariable(const std::string & identifyName) {
    checkUniformVariableExist(identifyName);
    float value[12];
    glGetUniformfv(programHandle, uniformLocations[identifyName], value);
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

void Shader::linkProgram(uint32_t programHandle, uint32_t vertexShaderHandle, uint32_t fragmentShaderHandle) {
    glAttachShader(programHandle, vertexShaderHandle);
    glAttachShader(programHandle, fragmentShaderHandle);
    glLinkProgram(programHandle);
    if (!isProgramLinkSuccess(programHandle)) {
        throw std::runtime_error("Link shader failed, cause: " + getProgramLinkErrors(programHandle));
    }

    glDetachShader(programHandle, vertexShaderHandle);
    glDetachShader(programHandle, fragmentShaderHandle);
}

bool Shader::isProgramLinkSuccess(uint32_t programHandle) {
    int success;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
    return success == GL_TRUE;
}

std::string Shader::getProgramLinkErrors(uint32_t programHandle) {
    int logLength;
    glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLength);
    char * log = new char[logLength];
    glGetProgramInfoLog(programHandle, logLength, nullptr, log);
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

    glGetProgramiv(programHandle, GL_ACTIVE_UNIFORMS, &count);

    for (int i = 0; i < count; i++) {
        glGetActiveUniform(programHandle, i, bufSize, &length, &size, &type, name);
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

void Shader::checkUniformVariableExist(const std::string & identifyName) {
    if (uniformLocations.find(identifyName) == uniformLocations.end()) {
        throw std::runtime_error("Uniform variable \"" + identifyName + "\" not registered");
    }
}