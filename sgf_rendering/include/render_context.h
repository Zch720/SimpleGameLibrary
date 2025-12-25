#pragma once

#include <manager.h>
#include "./shader.h"

class RenderContext {
public:
    Manager<Shader> ShaderManager;
};