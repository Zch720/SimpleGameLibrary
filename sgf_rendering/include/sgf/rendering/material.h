#pragma once

#include <unordered_map>
#include <sgf/utils/resource.h>
#include "./material_id.h"
#include "./shader_id.h"
#include "./texture_2d_id.h"
#include "./uniform.h"
#include "./uniform_id.h"

namespace sgf_core {
    class RenderContext;
    class Renderable;

    class Material: public Resource<Material, MaterialId> {
    public:
        static const std::string TypeName;
        struct Construct {
            bool useTexture;
            ShaderId shaderId;
            Texture2DId textureId;
        };
        
        Material(const Id & id, const Construct & constructParameter);

        UniformId registerUniform(const RenderContext & context, const std::string & name, UniformSource sourceType);

        void bind(const RenderContext & context) const;
        void applyPerObject(const RenderContext & context, const Renderable & renderable) const;

    private:
        bool useTexture;

        Texture2DId textureId;
        ShaderId shaderId;

        std::unordered_map<std::string, UniformId> uniformIds;
        std::unordered_map<UniformId, UniformSource> uniformSourceTypes;
    };
}
