#pragma once

#include <stdint.h>
#include "../window_id.h"

class Window;

class RenderableId {
public:
    friend Window;

    RenderableId();

    WindowId getWindowId() const;
    uint64_t getId() const;
    uint64_t getGen() const;

    friend bool operator==(const RenderableId & left, const RenderableId & right);
    friend bool operator!=(const RenderableId & left, const RenderableId & right);

private:
    RenderableId(WindowId windowId, uint64_t id, uint64_t gen);

    WindowId windowId;
    uint64_t id;
    uint64_t gen;
};
