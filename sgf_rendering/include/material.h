#pragma once

#include "./render_context.h"
#include "./shader_id.h"
#include "./texture_2d.h"

class Renderable;

class Material {
public:
    Material(ShaderId shaderId);
    Material(ShaderId shaderId, Texture2D * texture);

    void bind(const RenderContext & context) const;
    void applyPerObject(const RenderContext & context, const Renderable & renderable) const;

private:
    bool useTexture = false;

    Texture2D * texture;
    ShaderId shaderId;
};
