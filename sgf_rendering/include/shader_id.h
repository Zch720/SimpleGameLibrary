#pragma once

#include <stdint.h>
#include <vector>
#include <queue>

class Shader;
class ShaderIdGenerator;

class ShaderId {
public:
    ShaderId();

    uint32_t getId() const;
    uint32_t getGen() const;

    friend bool operator==(const ShaderId & left, const ShaderId & right);
    friend bool operator!=(const ShaderId & left, const ShaderId & right);

private:
    friend ShaderIdGenerator;

    ShaderId(uint32_t id, uint32_t gen);

    uint32_t id;
    uint32_t gen;
};

class ShaderIdGenerator {
public:
    static ShaderIdGenerator& Instance();

    bool isIdValid(const ShaderId & id) const;

protected:
    ShaderIdGenerator();
    ~ShaderIdGenerator();

private:
    friend Shader;

    static ShaderIdGenerator instance;

    ShaderId getNewId();
    void freeId(const ShaderId & id);

    std::vector<uint64_t> generations;
    std::queue<uint64_t> freeIds;
};

#include "./shader_id.tpp"
