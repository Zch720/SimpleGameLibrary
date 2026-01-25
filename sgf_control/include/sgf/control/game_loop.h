#pragma once

#include <functional>
#include <vector>
#include <sgf/platform/platform_context.h>
#include <sgf/rendering/render_context.h>
#include "./game_frame_phase.h"
#include "./game_time.h"

namespace sgf_core {
    class GameControlContext;

    class GameLoop {
    public:
        using UpdateFunc = std::function<void()>;
        using RenderFunc = std::function<void(const RenderContext &)>;

        const GameTime & Time() const;

        bool isRunning() const;
        FramePhase getCurrentPhase() const;

        void run();
        void stop();

        void addUpdateFunction(const UpdateFunc & func);
        void addRenderFunction(const RenderFunc & func);

    private:
        friend GameControlContext;

        GameLoop(RenderContext & renderContext, PlatformContext & platformContext);

        RenderContext & renderContext;
        PlatformContext & platformContext;

        bool running;
        FramePhase currentPhase;

        std::vector<UpdateFunc> updates;
        std::vector<RenderFunc> renders;

        GameTime gameTime;

        void beginFrame();
        void update();
        void render();
        void endFrame();
    };
}
