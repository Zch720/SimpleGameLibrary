#include "../../include/renderable/renderable_id.h"

RenderableId::RenderableId(): id(0), gen(0) {
}

RenderableId::RenderableId(WindowId windowId, uint64_t id, uint64_t gen): windowId(windowId), id(id), gen(gen) {
}

WindowId RenderableId::getWindowId() const {
    return windowId;
}

uint64_t RenderableId::getId() const {
    return id;
}

uint64_t RenderableId::getGen() const {
    return gen;
}

bool operator==(const RenderableId & left, const RenderableId & right) {
    return left.windowId == right.windowId && left.id == right.id && left.gen == right.gen;
}

bool operator!=(const RenderableId & left, const RenderableId & right) {
    return left.windowId != right.windowId || left.id != right.id || left.gen != right.gen;
}
