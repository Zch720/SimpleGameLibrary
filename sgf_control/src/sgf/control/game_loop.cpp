#include "../../../include/sgf/control/game_loop.h"

namespace sgf_core {
    GameLoop::GameLoop(RenderContext & renderContext, PlatformContext & platformContext):
        renderContext(renderContext),
        platformContext(platformContext),
        running(false),
        currentPhase(FramePhase::BeginFrame),
        gameTime(30, 500)
    {
    }

    const GameTime & GameLoop::Time() const {
        return gameTime;
    }

    bool GameLoop::isRunning() const {
        return running;
    }

    FramePhase GameLoop::getCurrentPhase() const {
        return currentPhase;
    }

    void GameLoop::run() {
        running = true;

        while (running) {
            beginFrame();

            if (platformContext.Window().isClose()) {
                running = false;
                break;
            }

            update();
            if (!running) break;

            render();

            gameTime.sleep();

            endFrame();
        }
    }

    void GameLoop::stop() {
        running = false;
        currentPhase = FramePhase::BeginFrame;
    }

    void GameLoop::addUpdateFunction(const UpdateFunc & func) {
        updates.push_back(func);
    }

    void GameLoop::addRenderFunction(const RenderFunc & func) {
        renders.push_back(func);
    }

    void GameLoop::beginFrame() {
        platformContext.Runtime().onFrameBegin();
        gameTime.beginFrame();
    }

    void GameLoop::update() {
        for (const auto & func : updates) {
            func();
        }
    }

    void GameLoop::render() {
        for (const auto & func : renders) {
            func(renderContext);
        }
    }

    void GameLoop::endFrame() {
        platformContext.Runtime().onFrameEnd();
    }
}
