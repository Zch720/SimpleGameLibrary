#pragma once

#include "../shader_id.h"
#include "./texture_2d.h"

class Renderable;

class Material {
public:
    Material(ShaderId shaderId);
    Material(ShaderId shaderId, Texture2D * texture);

    void bind() const;
    void applyPerObject(const Renderable & renderable) const;

private:
    bool useTexture = false;

    Texture2D * texture;
    ShaderId shaderId;
};
