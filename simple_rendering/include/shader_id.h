#pragma once

#include <stdint.h>

class ShaderManager;

class ShaderId {
public:
    friend ShaderManager;

    ShaderId();

    uint64_t getId() const;

private:
    ShaderId(uint64_t id);

    uint64_t id;
};