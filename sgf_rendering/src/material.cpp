#include "../include/material.h"
#include "../include/renderable.h"

Material::Material(ShaderId shaderId): shaderId(shaderId) {
}

Material::Material(ShaderId shaderId, Texture2D * texture): shaderId(shaderId), texture(texture), useTexture(true) {
}

void Material::bind(const RenderContext & context) const {
    context.ShaderManager.getRef(shaderId).use();
    if (useTexture) {
        texture->bind();
    }
}

void Material::applyPerObject(const RenderContext & context, const Renderable & renderable) const {
    Shader & shader = context.ShaderManager.getRef(shaderId);
    shader.setVec4UniformVariable("color", renderable.getColor());
    shader.setMat4UniformVariable("transform", renderable.getTransformationMatrix());
}
