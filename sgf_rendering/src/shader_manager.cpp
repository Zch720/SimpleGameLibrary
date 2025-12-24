#include "../include/shader.h"
#include "../include/shader_manager.h"

ShaderManager ShaderManager::instance;

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
    destroyShaders();
}

ShaderManager & ShaderManager::Instance() {
    return instance;
}

ShaderId ShaderManager::createShader(const std::string & vertexShaderSource, const std::string & fragmentShaderSource) {
    Shader * shader = new Shader(vertexShaderSource, fragmentShaderSource);
    shaders.insert(std::make_pair(shader->getId(), shader));
    return shader->getId();
}

bool ShaderManager::hasShader(const ShaderId & id) {
    if (ShaderIdGenerator::Instance().isIdValid(id)) {
        return shaders.find(id) != shaders.end();
    }
    return false;
}

void ShaderManager::useShader(const ShaderId & id) {
    checkShaderExist(id);
    shaders[id]->use();
}

void ShaderManager::destroyShaders() {
    for (auto shader : shaders) {
        delete shader.second;
    }
    shaders.clear();
}

void ShaderManager::registerShaderUniformVariable(const ShaderId & id, const std::string & identifyName, const std::string & uniformName) {
    checkShaderExist(id);
    shaders[id]->registerUniformVariable(identifyName, uniformName);
}

bool ShaderManager::isShaderHasUniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->hasUniformVariable(identifyName);
}

void ShaderManager::setShaderIntUniformVariable(const ShaderId & id, const std::string & identifyName, int value) {
    checkShaderExist(id);
    shaders[id]->setIntUniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersIntUniformVariable(const std::string & identifyName, int value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setIntUniformVariable(identifyName, value);
        }
    }
}

int ShaderManager::getShaderIntUniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getIntUniformVariable(identifyName);
}

void ShaderManager::setShaderFloatUniformVariable(const ShaderId & id, const std::string & identifyName, float value) {
    checkShaderExist(id);
    shaders[id]->setFloatUniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersFloatUniformVariable(const std::string & identifyName, float value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setFloatUniformVariable(identifyName, value);
        }
    }
}

float ShaderManager::getShaderFloatUniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getFloatUniformVariable(identifyName);
}

void ShaderManager::setShaderVec2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::vec2 value) {
    checkShaderExist(id);
    shaders[id]->setVec2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec2UniformVariable(const std::string & identifyName, glm::vec2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setVec2UniformVariable(identifyName, value);
        }
    }
}

glm::vec2 ShaderManager::getShaderVec2UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getVec2UniformVariable(identifyName);
}

void ShaderManager::setShaderVec3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::vec3 value) {
    checkShaderExist(id);
    shaders[id]->setVec3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec3UniformVariable(const std::string & identifyName, glm::vec3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setVec3UniformVariable(identifyName, value);
        }
    }
}

glm::vec3 ShaderManager::getShaderVec3UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getVec3UniformVariable(identifyName);
}

void ShaderManager::setShaderVec4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::vec4 value) {
    checkShaderExist(id);
    shaders[id]->setVec4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec4UniformVariable(const std::string & identifyName, glm::vec4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setVec4UniformVariable(identifyName, value);
        }
    }
}

glm::vec4 ShaderManager::getShaderVec4UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getVec4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat2 value) {
    checkShaderExist(id);
    shaders[id]->setMat2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2UniformVariable(const std::string & identifyName, glm::mat2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat2UniformVariable(identifyName, value);
        }
    }
}

glm::mat2 ShaderManager::getShaderMat2UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat3 value) {
    checkShaderExist(id);
    shaders[id]->setMat3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3UniformVariable(const std::string & identifyName, glm::mat3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat3UniformVariable(identifyName, value);
        }
    }
}

glm::mat3 ShaderManager::getShaderMat3UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat3UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat4 value) {
    checkShaderExist(id);
    shaders[id]->setMat4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4UniformVariable(const std::string & identifyName, glm::mat4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat4UniformVariable(identifyName, value);
        }
    }
}

glm::mat4 ShaderManager::getShaderMat4UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2x3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat2x3 value) {
    checkShaderExist(id);
    shaders[id]->setMat2x3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2x3UniformVariable(const std::string & identifyName, glm::mat2x3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat2x3UniformVariable(identifyName, value);
        }
    }
}

glm::mat2x3 ShaderManager::getShaderMat2x3UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat2x3UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3x2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat3x2 value) {
    checkShaderExist(id);
    shaders[id]->setMat3x2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3x2UniformVariable(const std::string & identifyName, glm::mat3x2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat3x2UniformVariable(identifyName, value);
        }
    }
}

glm::mat3x2 ShaderManager::getShaderMat3x2UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat3x2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2x4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat2x4 value) {
    checkShaderExist(id);
    shaders[id]->setMat2x4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2x4UniformVariable(const std::string & identifyName, glm::mat2x4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat2x4UniformVariable(identifyName, value);
        }
    }
}

glm::mat2x4 ShaderManager::getShaderMat2x4UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat2x4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4x2UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat4x2 value) {
    checkShaderExist(id);
    shaders[id]->setMat4x2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4x2UniformVariable(const std::string & identifyName, glm::mat4x2 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat4x2UniformVariable(identifyName, value);
        }
    }
}

glm::mat4x2 ShaderManager::getShaderMat4x2UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat4x2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3x4UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat3x4 value) {
    checkShaderExist(id);
    shaders[id]->setMat3x4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3x4UniformVariable(const std::string & identifyName, glm::mat3x4 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat3x4UniformVariable(identifyName, value);
        }
    }
}

glm::mat3x4 ShaderManager::getShaderMat3x4UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat3x4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4x3UniformVariable(const ShaderId & id, const std::string & identifyName, glm::mat4x3 value) {
    checkShaderExist(id);
    shaders[id]->setMat4x3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4x3UniformVariable(const std::string & identifyName, glm::mat4x3 value) {
    for (auto shader : shaders) {
        if (shader.second->hasUniformVariable(identifyName)) {
            shader.second->setMat4x3UniformVariable(identifyName, value);
        }
    }
}

glm::mat4x3 ShaderManager::getShaderMat4x3UniformVariable(const ShaderId & id, const std::string & identifyName) {
    checkShaderExist(id);
    return shaders[id]->getMat4x3UniformVariable(identifyName);
}

void ShaderManager::checkShaderExist(const ShaderId & id) {
    if (!hasShader(id)) {
        throw std::runtime_error("Cannot check uniform variable to shader that not exist");
    }
}