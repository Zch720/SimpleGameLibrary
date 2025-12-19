#pragma once

#include <stdint.h>

class WindowManager;

class WindowId {
public:
    friend WindowManager;

    WindowId();

    uint64_t getId() const;
    uint64_t getGen() const;

    friend bool operator==(WindowId left, WindowId right);
    friend bool operator!=(WindowId left, WindowId right);

private:
    WindowId(uint64_t id, uint64_t gen);

    uint64_t id;
    uint64_t gen;
};