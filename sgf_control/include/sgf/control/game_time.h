#pragma once

#include <chrono>

namespace sgf_core {
    class GameLoop;

    class GameTime {
    private:
        using Clock = std::chrono::steady_clock;
        using Duration = Clock::duration;

    public:
        using TimeStamp = std::chrono::time_point<Clock, Duration>;

        double getDeltaTime() const;
        uint64_t getFrameIndex() const;

        TimeStamp currentTime() const;

    private:
        friend GameLoop;

        GameTime(uint32_t fps, double allowFpsPacingLag);

        const uint32_t fps;
        const Duration allowFpsPacingLag;

        double deltaTime;
        uint64_t frameIndex;

        TimeStamp startTime;
        TimeStamp lastFrameBegin;

        const Duration frameDuration;

        void beginFrame();
        void sleep();
        bool lagCheck(const TimeStamp & sleepUntil);
        void lagCorrection(TimeStamp & sleepUntil);
    };
}
