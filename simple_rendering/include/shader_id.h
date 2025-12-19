#pragma once

#include <stdint.h>

class ShaderManager;

class ShaderId {
public:
    friend ShaderManager;

    ShaderId();

    uint64_t getId() const;

    friend bool operator==(const ShaderId & left, const ShaderId & right);
    friend bool operator!=(const ShaderId & left, const ShaderId & right);

private:
    ShaderId(uint64_t id);

    uint64_t id;
};