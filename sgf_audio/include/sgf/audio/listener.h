#pragma once

#include "./utils/vector3.h"

namespace sgf_core {
    class Listener {
    public:
        void setGain(float gain);
        void setPosition(const Vector3 & position);
        void setVelocity(const Vector3 & velocity);
        void setOrientation(const Vector3 & forward, const Vector3 & up);
    };
}
