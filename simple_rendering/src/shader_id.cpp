#include "../include/shader_id.h"

ShaderId::ShaderId() {
    this->id = 0;
}

ShaderId::ShaderId(uint64_t id) {
    this->id = id;
}

uint64_t ShaderId::getId() const {
    return id;
}

bool operator==(const ShaderId & left, const ShaderId & right) {
    return left.id == right.id;
}

bool operator!=(const ShaderId & left, const ShaderId & right) {
    return left.id == right.id;
}
