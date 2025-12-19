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

ShaderId ShaderManager::createShader(std::string vertexShaderSource, std::string fragmentShaderSource) {
    ShaderId id = ShaderId(shaders.size() + 1);
    Shader * shader = new Shader(id, vertexShaderSource, fragmentShaderSource);
    shaders.push_back(shader);
    return id;
}

bool ShaderManager::hasShader(ShaderId id) {
    return id.getId() != 0 && id.getId() <= shaders.size();
}

void ShaderManager::useShader(ShaderId id) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->use();
}

void ShaderManager::destroyShaders() {
    for (Shader * shader : shaders) {
        delete shader;
    }
    shaders.clear();
}

void ShaderManager::registerShaderUniformVariable(ShaderId id, std::string identifyName, std::string uniformName) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->registerUniformVariable(identifyName, uniformName);
}

bool ShaderManager::isShaderHasUniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->hasUniformVariable(identifyName);
}

void ShaderManager::setShaderIntUniformVariable(ShaderId id, std::string identifyName, int value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setIntUniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersIntUniformVariable(std::string identifyName, int value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setIntUniformVariable(identifyName, value);
        }
    }
}

int ShaderManager::getShaderIntUniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getIntUniformVariable(identifyName);
}

void ShaderManager::setShaderFloatUniformVariable(ShaderId id, std::string identifyName, float value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setFloatUniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersFloatUniformVariable(std::string identifyName, float value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setFloatUniformVariable(identifyName, value);
        }
    }
}

float ShaderManager::getShaderFloatUniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getFloatUniformVariable(identifyName);
}

void ShaderManager::setShaderVec2UniformVariable(ShaderId id, std::string identifyName, glm::vec2 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setVec2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec2UniformVariable(std::string identifyName, glm::vec2 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setVec2UniformVariable(identifyName, value);
        }
    }
}

glm::vec2 ShaderManager::getShaderVec2UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getVec2UniformVariable(identifyName);
}

void ShaderManager::setShaderVec3UniformVariable(ShaderId id, std::string identifyName, glm::vec3 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setVec3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec3UniformVariable(std::string identifyName, glm::vec3 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setVec3UniformVariable(identifyName, value);
        }
    }
}

glm::vec3 ShaderManager::getShaderVec3UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getVec3UniformVariable(identifyName);
}

void ShaderManager::setShaderVec4UniformVariable(ShaderId id, std::string identifyName, glm::vec4 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setVec4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersVec4UniformVariable(std::string identifyName, glm::vec4 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setVec4UniformVariable(identifyName, value);
        }
    }
}

glm::vec4 ShaderManager::getShaderVec4UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getVec4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2UniformVariable(ShaderId id, std::string identifyName, glm::mat2 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2UniformVariable(std::string identifyName, glm::mat2 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat2UniformVariable(identifyName, value);
        }
    }
}

glm::mat2 ShaderManager::getShaderMat2UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3UniformVariable(ShaderId id, std::string identifyName, glm::mat3 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3UniformVariable(std::string identifyName, glm::mat3 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat3UniformVariable(identifyName, value);
        }
    }
}

glm::mat3 ShaderManager::getShaderMat3UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat3UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4UniformVariable(ShaderId id, std::string identifyName, glm::mat4 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4UniformVariable(std::string identifyName, glm::mat4 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat4UniformVariable(identifyName, value);
        }
    }
}

glm::mat4 ShaderManager::getShaderMat4UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2x3UniformVariable(ShaderId id, std::string identifyName, glm::mat2x3 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat2x3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2x3UniformVariable(std::string identifyName, glm::mat2x3 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat2x3UniformVariable(identifyName, value);
        }
    }
}

glm::mat2x3 ShaderManager::getShaderMat2x3UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat2x3UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3x2UniformVariable(ShaderId id, std::string identifyName, glm::mat3x2 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat3x2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3x2UniformVariable(std::string identifyName, glm::mat3x2 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat3x2UniformVariable(identifyName, value);
        }
    }
}

glm::mat3x2 ShaderManager::getShaderMat3x2UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat3x2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat2x4UniformVariable(ShaderId id, std::string identifyName, glm::mat2x4 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat2x4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat2x4UniformVariable(std::string identifyName, glm::mat2x4 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat2x4UniformVariable(identifyName, value);
        }
    }
}

glm::mat2x4 ShaderManager::getShaderMat2x4UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat2x4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4x2UniformVariable(ShaderId id, std::string identifyName, glm::mat4x2 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat4x2UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4x2UniformVariable(std::string identifyName, glm::mat4x2 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat4x2UniformVariable(identifyName, value);
        }
    }
}

glm::mat4x2 ShaderManager::getShaderMat4x2UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat4x2UniformVariable(identifyName);
}

void ShaderManager::setShaderMat3x4UniformVariable(ShaderId id, std::string identifyName, glm::mat3x4 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat3x4UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat3x4UniformVariable(std::string identifyName, glm::mat3x4 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat3x4UniformVariable(identifyName, value);
        }
    }
}

glm::mat3x4 ShaderManager::getShaderMat3x4UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat3x4UniformVariable(identifyName);
}

void ShaderManager::setShaderMat4x3UniformVariable(ShaderId id, std::string identifyName, glm::mat4x3 value) {
    checkShaderExist(id);
    shaders[id.getId() - 1]->setMat4x3UniformVariable(identifyName, value);
}

void ShaderManager::setAllShadersMat4x3UniformVariable(std::string identifyName, glm::mat4x3 value) {
    for (Shader * shader : shaders) {
        if (shader->hasUniformVariable(identifyName)) {
            shader->setMat4x3UniformVariable(identifyName, value);
        }
    }
}

glm::mat4x3 ShaderManager::getShaderMat4x3UniformVariable(ShaderId id, std::string identifyName) {
    checkShaderExist(id);
    return shaders[id.getId() - 1]->getMat4x3UniformVariable(identifyName);
}

void ShaderManager::checkShaderExist(ShaderId id) {
    if (!hasShader(id)) {
        throw std::runtime_error("Cannot check uniform variable to shader that not exist");
    }
}