#include "../../../include/sgf/rendering/render_context.h"

void RenderContext::destroyAllResources() {
    ShaderManager.destroyAll();
    Texture2DManager.destroyAll();
    MeshManager.destroyAll();
    MaterialManager.destroyAll();
}
