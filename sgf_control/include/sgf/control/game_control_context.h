#pragma once

#include <sgf/platform/platform_context.h>
#include <sgf/rendering/render_context.h>
#include "./game_loop.h"

namespace sgf_core {
    class GameControlContext {
    public:
        GameControlContext(RenderContext & renderContext, PlatformContext & platformContext);

        sgf_core::GameLoop & GameLoop();

    private:
        sgf_core::GameLoop gameLoop;
    };
}
