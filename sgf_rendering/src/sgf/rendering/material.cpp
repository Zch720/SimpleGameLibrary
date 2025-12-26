#include "../../../include/sgf/rendering/material.h"
#include "../../../include/sgf/rendering/render_context.h"
#include "../../../include/sgf/rendering/renderable.h"

namespace sgf_core {
    const std::string MaterialTag::TypeName = "Material";
    const std::string Material::TypeName = "Material";

    Material::Material(const Id & id, const Construct & constructParameter):
        useTexture(constructParameter.useTexture),
        shaderId(constructParameter.shaderId),
        textureId(constructParameter.textureId) {
    }

    void Material::bind(const RenderContext & context) const {
        context.ShaderManager.getRef(shaderId).use();
        if (useTexture) {
            context.Texture2DManager.getRef(textureId).bind();
        }
    }

    void Material::applyPerObject(const RenderContext & context, const Renderable & renderable) const {
        Shader & shader = context.ShaderManager.getRef(shaderId);
        shader.setVec4UniformVariable("color", renderable.getColor());
        shader.setMat4UniformVariable("transform", renderable.getTransformationMatrix());
    }
}
