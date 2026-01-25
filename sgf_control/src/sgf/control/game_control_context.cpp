#include "../../../include/sgf/control/game_control_context.h"

namespace sgf_core {
    GameControlContext::GameControlContext(RenderContext & renderContext, PlatformContext & platformContext):
        gameLoop(renderContext, platformContext)
    {
    }

    sgf_core::GameLoop & GameControlContext::GameLoop() {
        return gameLoop;
    }
}
