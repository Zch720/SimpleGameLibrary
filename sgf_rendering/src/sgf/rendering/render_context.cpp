#include "../../../include/sgf/rendering/render_context.h"
#include "sgf/rendering/uniform_provider.h"
#include <glad/gl.h>

namespace sgf_core {
    RenderContext::RenderContext(): clearFrameBufferBits(0) {
    }

    void RenderContext::initialize() {
        glEnable(GL_DEPTH_TEST);

        clearFrameBufferBits |= GL_DEPTH_BUFFER_BIT;
    }

    void RenderContext::destroyAllResources() {
        ShaderManager.destroyAll();
        Texture2DManager.destroyAll();
        MeshManager.destroyAll();
        MaterialManager.destroyAll();
    }

    uint32_t RenderContext::getClearFrameBufferBits() const {
        return clearFrameBufferBits;
    }

    sgf_core::UniformProvider & RenderContext::UniformProvider() {
        return uniformProvider;
    }

    const sgf_core::UniformProvider & RenderContext::UniformProvider() const {
        return uniformProvider;
    }
}
