#include "../include/material.h"
#include "../include/shader_manager.h"
#include "../include/renderable.h"

Material::Material(ShaderId shaderId): shaderId(shaderId) {
}

Material::Material(ShaderId shaderId, Texture2D * texture): shaderId(shaderId), texture(texture), useTexture(true) {
}

void Material::bind() const {
    ShaderManager::Instance().useShader(shaderId);
    if (useTexture) {
        texture->bind();
    }
}

void Material::applyPerObject(const Renderable & renderable) const {
    ShaderManager::Instance().setShaderVec4UniformVariable(shaderId, "color", renderable.getColor());
    ShaderManager::Instance().setShaderMat4UniformVariable(shaderId, "transform", renderable.getTransformationMatrix());
}
