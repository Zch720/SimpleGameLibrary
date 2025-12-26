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
        RenderContext();

        Manager<Shader> ShaderManager;
        Manager<Texture2D> Texture2DManager;
        Manager<Mesh> MeshManager;
        Manager<Material> MaterialManager;

        void initialize();
        void destroyAllResources();

        uint32_t getClearFrameBufferBits() const;

    #ifdef SGF_RENDERING_UNSAFE
        template <typename Fn>
        void unsafeExecute(Fn&& fn) {
            UnsafeGLContext glContext(*this);
            fn(glContext);
        }

        void addClearFrameBufferBit(uint32_t bit) {
            clearFrameBufferBits |= bit;
        }
    #endif

    private:
        uint32_t clearFrameBufferBits;
    };
}
