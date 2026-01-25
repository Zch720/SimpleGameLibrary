#include "../../../include/sgf/control/game_time.h"
#include <chrono>
#include <thread>

namespace sgf_core {
    GameTime::GameTime(uint32_t fps, double allowFpsPacingLag):
        fps(fps),
        allowFpsPacingLag((long long)(allowFpsPacingLag * 1e9)),
        frameIndex(0),
        deltaTime(0),
        frameDuration((long long)(1e9 / fps))
    {
    }
    
    double GameTime::getDeltaTime() const {
        return deltaTime;
    }

    uint64_t GameTime::getFrameIndex() const {
        return frameIndex;
    }

    GameTime::TimeStamp GameTime::currentTime() const {
        return std::chrono::steady_clock::now();
    }
    
    void GameTime::beginFrame() {
        TimeStamp current = currentTime();
        if (frameIndex == 0) {
            startTime = current;
        } else {
            deltaTime = std::chrono::duration<double>(current - lastFrameBegin).count();
        }

        lastFrameBegin = current;
        frameIndex++;
    }

    void GameTime::sleep() {
        TimeStamp until = startTime + frameDuration * frameIndex;

        if (lagCheck(until)) {
            lagCorrection(until);
        }

        std::this_thread::sleep_until(until);
    }

    bool GameTime::lagCheck(const TimeStamp & sleepUntil) {
        TimeStamp current = currentTime();
        return current > sleepUntil && current - sleepUntil > allowFpsPacingLag;
    }

    void GameTime::lagCorrection(TimeStamp & sleepUntil) {
        TimeStamp current = currentTime();
        startTime += current - sleepUntil;
        sleepUntil = current;
    }
}
