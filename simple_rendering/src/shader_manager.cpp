#include "../include/shader.h"
#include "../include/shader_manager.h"

ShaderManager ShaderManager::instance;

ShaderManager::ShaderManager() {
    shaders = {};
}

ShaderManager::~ShaderManager() {
    destroyShaders();
}

ShaderManager & ShaderManager::Instance() {
    return instance;
}

void ShaderManager::createShader(std::string identifyName, std::string vertexShaderSource, std::string fragmentShaderSource) {
    Shader * shader = new Shader(vertexShaderSource, fragmentShaderSource);
    shaders[identifyName] = shader;
}

bool ShaderManager::hasShader(std::string identifyName) {
    return shaders.find(identifyName) != shaders.end();
}

void ShaderManager::useShader(std::string identifyName) {
    checkShaderExist(identifyName);
    shaders[identifyName]->use();
}

void ShaderManager::destroyShaders() {
    for (auto shader : shaders) {
        delete shader.second;
    }
    shaders.clear();
}

void ShaderManager::registerShaderUniformVariable(std::string shaderIdentifyName, std::string identifyName, std::string uniformName) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->registerUniformVariable(identifyName, uniformName);
}

bool ShaderManager::isShaderHasUniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->hasUniformVariable(identifyName);
}

void ShaderManager::setShaderIntUniformVariable(std::string shaderIdentifyName, std::string identifyName, int value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setIntUniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersIntUniformVariable(std::string identifyName, int value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setIntUniformVariable(identifyName, value);
    }
}

int ShaderManager::getShaderIntUniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getIntUniformVariable(identifyName);
}

void ShaderManager::setShaderFloatUniformVariable(std::string shaderIdentifyName, std::string identifyName, float value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setFloatUniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersFloatUniformVariable(std::string identifyName, float value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setFloatUniformVariable(identifyName, value);
    }
}

float ShaderManager::getShaderFloatUniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getFloatUniformVariable(identifyName);
}

void ShaderManager::setShaderVec2UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::vec2 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setVec2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec2UniformVariable(std::string identifyName, glm::vec2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setVec2UniformVariable(identifyName, value);
    }
}

glm::vec2 ShaderManager::getShaderVec2UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getVec2UniformVariable(identifyName);
}

void ShaderManager::setShaderVec3UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::vec3 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setVec3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec3UniformVariable(std::string identifyName, glm::vec3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setVec3UniformVariable(identifyName, value);
    }
}

glm::vec3 ShaderManager::getShaderVec3UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getVec3UniformVariable(identifyName);
}

void ShaderManager::setShaderVec4UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::vec4 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setVec4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec4UniformVariable(std::string identifyName, glm::vec4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setVec4UniformVariable(identifyName, value);
    }
}

glm::vec4 ShaderManager::getShaderVec4UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getVec4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat2 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2UniformVariable(std::string identifyName, glm::mat2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat2UniformVariable(identifyName, value);
    }
}

glm::mat2 ShaderManager::getShaderMat2UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat3 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3UniformVariable(std::string identifyName, glm::mat3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat3UniformVariable(identifyName, value);
    }
}

glm::mat3 ShaderManager::getShaderMat3UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat3UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat4 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4UniformVariable(std::string identifyName, glm::mat4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat4UniformVariable(identifyName, value);
    }
}

glm::mat4 ShaderManager::getShaderMat4UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2x3UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat2x3 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat2x3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2x3UniformVariable(std::string identifyName, glm::mat2x3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat2x3UniformVariable(identifyName, value);
    }
}

glm::mat2x3 ShaderManager::getShaderMat2x3UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat2x3UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3x2UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat3x2 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat3x2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3x2UniformVariable(std::string identifyName, glm::mat3x2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat3x2UniformVariable(identifyName, value);
    }
}

glm::mat3x2 ShaderManager::getShaderMat3x2UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat3x2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2x4UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat2x4 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat2x4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2x4UniformVariable(std::string identifyName, glm::mat2x4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat2x4UniformVariable(identifyName, value);
    }
}

glm::mat2x4 ShaderManager::getShaderMat2x4UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat2x4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4x2UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat4x2 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat4x2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4x2UniformVariable(std::string identifyName, glm::mat4x2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat4x2UniformVariable(identifyName, value);
    }
}

glm::mat4x2 ShaderManager::getShaderMat4x2UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat4x2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3x4UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat3x4 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat3x4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3x4UniformVariable(std::string identifyName, glm::mat3x4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat3x4UniformVariable(identifyName, value);
    }
}

glm::mat3x4 ShaderManager::getShaderMat3x4UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat3x4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4x3UniformVariable(std::string shaderIdentifyName, std::string identifyName, glm::mat4x3 value) {
    checkShaderExist(shaderIdentifyName);
    shaders[shaderIdentifyName]->setMat4x3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4x3UniformVariable(std::string identifyName, glm::mat4x3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName))
            shader.second->setMat4x3UniformVariable(identifyName, value);
    }
}

glm::mat4x3 ShaderManager::getShaderMat4x3UniformVariable(std::string shaderIdentifyName, std::string identifyName) {
    checkShaderExist(shaderIdentifyName);
    return shaders[shaderIdentifyName]->getMat4x3UniformVariable(identifyName);
}

void ShaderManager::checkShaderExist(std::string shaderIdentifyName) {
    if (!hasShader(shaderIdentifyName)) {
        throw std::runtime_error("Cannot check uniform variable to shader that not exist");
    }
}