#include "../../../include/sgf/rendering/material.h"
#include <stdexcept>
#include <sgf/utils/logger/log.h>
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

    UniformId Material::registerUniform(const RenderContext & context, const std::string & name, UniformSource sourceType) {
        if (!context.ShaderManager.getRef(shaderId).hasUniformVariable(name)) {
            SGF_LOG_ERROR("Try to register not exist uniform, register failed.");
            throw std::runtime_error("Uniform variable \"" + name + "\" not exist");
        }
        
        UniformId uniformId(id, uniformIds.size() + 1);
        uniformIds[name] = uniformId;
        uniformSourceTypes[uniformId] = sourceType;
        return uniformId;
    }

    void Material::bind(const RenderContext & context) const {
        context.ShaderManager.getRef(shaderId).use();
        if (useTexture) {
            context.Texture2DManager.getRef(textureId).bind();
        }
    }

    void Material::applyPerObject(const RenderContext & context, const Renderable & renderable) const {
        Shader & shader = context.ShaderManager.getRef(shaderId);

        for (const auto & [name, uniformId]: uniformIds) {
            UniformSource sourceType = uniformSourceTypes.at(uniformId);
            if (sourceType == UniformSource::TRANSFORM_MATRIX) {
                shader.setMat4UniformVariable(name, renderable.getTransformationMatrix());
            } else if (sourceType == UniformSource::RENDERABLE_COLOR) {
                shader.setVec4UniformVariable(name, renderable.getColor());
            } else if (sourceType == UniformSource::CAMERA_VIEW) {
                shader.setMat4UniformVariable(name, context.Camera().getViewMatrix());
            } else if (sourceType == UniformSource::CAMERA_PROJECTION) {
                shader.setMat4UniformVariable(name, context.Camera().getProjectionMatrix());
            } else if (sourceType == UniformSource::CUSTOM) {
                if (renderable.getUniformProvider().hasProvider(uniformId)) {
                    shader.setUniformVariable(name, renderable.getUniformProvider().getProvider(uniformId)());
                } else if (context.UniformProvider().hasProvider(uniformId)) {
                    shader.setUniformVariable(name, context.UniformProvider().getProvider(uniformId)());
                } else {
                    SGF_LOG_WARN("Could not found provider for uniform with name {}. Shader with id {}. Renderable with id {}.", name, shader.getId().toString(), renderable.getId().toString());
                }
            }
        }
    }
}
