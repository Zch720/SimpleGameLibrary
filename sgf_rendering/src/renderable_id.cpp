#include "../include/renderable_id.h"

RenderableId::RenderableId(): id(0), gen(0) {
}

RenderableId::RenderableId(uint32_t id, uint32_t gen): id(id), gen(gen) {
}

uint32_t RenderableId::getId() const {
    return id;
}

uint32_t RenderableId::getGen() const {
    return gen;
}

bool operator==(const RenderableId & left, const RenderableId & right) {
    return left.id == right.id && left.gen == right.gen;
}

bool operator!=(const RenderableId & left, const RenderableId & right) {
    return left.id != right.id || left.gen != right.gen;
}


RenderableIdGenerator RenderableIdGenerator::instance;

RenderableIdGenerator::RenderableIdGenerator() {
}

RenderableIdGenerator::~RenderableIdGenerator() {
}

RenderableIdGenerator& RenderableIdGenerator::Instance() {
    return instance;
}

bool RenderableIdGenerator::isIdValid(const RenderableId & id) const {
    return id.getId() != 0 && id.getId() <= generations.size() && id.getGen() == generations[id.getId() - 1];
}

RenderableId RenderableIdGenerator::getNewId() {
    if (freeIds.empty()) {
        generations.push_back(1);
        return RenderableId(generations.size(), 1);
    } else {
        uint64_t id = freeIds.front();
        freeIds.pop();
        return RenderableId(id, generations[id - 1]);
    }
}

void RenderableIdGenerator::freeId(const RenderableId & id) {
    generations[id.getId() - 1]++;
    freeIds.push(id.getId());
}
