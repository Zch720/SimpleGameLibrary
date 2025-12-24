#pragma once

#include <stdint.h>
#include <vector>
#include <queue>

class Renderable;
class RenderableIdGenerator;

class RenderableId {
public:
    RenderableId();

    uint32_t getId() const;
    uint32_t getGen() const;

    friend bool operator==(const RenderableId & left, const RenderableId & right);
    friend bool operator!=(const RenderableId & left, const RenderableId & right);

private:
    friend RenderableIdGenerator;

    RenderableId(uint32_t id, uint32_t gen);

    uint32_t id;
    uint32_t gen;
};

class RenderableIdGenerator {
public:
    static RenderableIdGenerator& Instance();

    bool isIdValid(const RenderableId & id) const;

protected:
    RenderableIdGenerator();
    ~RenderableIdGenerator();

private:
    friend Renderable;

    static RenderableIdGenerator instance;

    RenderableId getNewId();
    void freeId(const RenderableId & id);

    std::vector<uint64_t> generations;
    std::queue<uint64_t> freeIds;
};

#include "./renderable_id.tpp"
