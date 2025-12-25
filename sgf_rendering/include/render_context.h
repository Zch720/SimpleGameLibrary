#pragma once

#include <manager.h>
#include "./material.h"
#include "./mesh.h"
#include "./shader.h"
#include "./texture_2d.h"

class RenderContext {
public:
    Manager<Shader> ShaderManager;
    Manager<Texture2D> Texture2DManager;
    Manager<Mesh> MeshManager;
    Manager<Material> MaterialManager;

    void destroyAllResources();
};
