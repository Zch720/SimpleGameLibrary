#include "../../../include/sgf/rendering/render_context.h"
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
}
