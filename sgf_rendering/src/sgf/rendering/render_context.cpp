#include "../../../include/sgf/rendering/render_context.h"

namespace sgf_core {
    void RenderContext::destroyAllResources() {
        ShaderManager.destroyAll();
        Texture2DManager.destroyAll();
        MeshManager.destroyAll();
        MaterialManager.destroyAll();
    }
}
