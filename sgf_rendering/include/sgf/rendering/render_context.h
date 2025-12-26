#pragma once

#include <functional>
#include <sgf/utils/manager.h>
#include "./material.h"
#include "./mesh.h"
#include "./shader.h"
#include "./texture_2d.h"

#ifdef SGF_RENDERING_UNSAFE
#include "./unsafe_gl_context.h"
#endif

namespace sgf_core {
    class RenderContext {
    public:
        Manager<Shader> ShaderManager;
        Manager<Texture2D> Texture2DManager;
        Manager<Mesh> MeshManager;
        Manager<Material> MaterialManager;

        void destroyAllResources();

    #ifdef SGF_RENDERING_UNSAFE
        template <typename Fn>
        void unsafeExecute(Fn&& fn) {
            UnsafeGLContext glContext(*this);
            fn(glContext);
        }
    #endif
    };
}
