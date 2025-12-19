#include "../include/window_id.h"

WindowId::WindowId(): id(0), gen(0) {
}

WindowId::WindowId(uint64_t id, uint64_t gen): id(id), gen(gen) {
}

uint64_t WindowId::getId() const {
    return id;
}

uint64_t WindowId::getGen() const {
    return gen;
}

bool operator==(const WindowId & left, const WindowId & right) {
    return left.id == right.id && left.gen == right.gen;
}

bool operator!=(const WindowId & left, const WindowId & right) {
    return left.id != right.id || left.gen != right.gen;
}
