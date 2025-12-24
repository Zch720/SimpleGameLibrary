#include "../include/shader_id.h"

ShaderId::ShaderId(): id(0), gen(0) {
}

ShaderId::ShaderId(uint32_t id, uint32_t gen): id(id), gen(gen) {
}

uint32_t ShaderId::getId() const {
    return id;
}

uint32_t ShaderId::getGen() const {
    return gen;
}

bool operator==(const ShaderId & left, const ShaderId & right) {
    return left.id == right.id && left.gen == right.gen;
}

bool operator!=(const ShaderId & left, const ShaderId & right) {
    return left.id != right.id || left.gen != right.gen;
}


ShaderIdGenerator ShaderIdGenerator::instance;

ShaderIdGenerator::ShaderIdGenerator() {
}

ShaderIdGenerator::~ShaderIdGenerator() {
}

ShaderIdGenerator& ShaderIdGenerator::Instance() {
    return instance;
}

bool ShaderIdGenerator::isIdValid(const ShaderId & id) const {
    return id.getId() != 0 && id.getId() <= generations.size() && id.getGen() == generations[id.getId() - 1];
}

ShaderId ShaderIdGenerator::getNewId() {
    if (freeIds.empty()) {
        generations.push_back(1);
        return ShaderId(generations.size(), 1);
    } else {
        uint64_t id = freeIds.front();
        freeIds.pop();
        return ShaderId(id, generations[id - 1]);
    }
}

void ShaderIdGenerator::freeId(const ShaderId & id) {
    generations[id.getId() - 1]++;
    freeIds.push(id.getId());
}
