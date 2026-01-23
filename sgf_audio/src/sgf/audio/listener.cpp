#include "../../../include/sgf/audio/listener.h"
#include <AL/al.h>

namespace sgf_core {
    void Listener::setGain(float gain) {
        alListenerf(AL_GAIN, gain);
    }

    void Listener::setPosition(const Vector3 & position) {
        alListener3f(AL_POSITION, position.x, position.y, position.z);
    }

    void Listener::setVelocity(const Vector3 & velocity) {
        alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    }

    void Listener::setOrientation(const Vector3 & forward, const Vector3 & up) {
        float vals[6] = { forward.x, forward.y, forward.z, up.x, up.y, up.z };
        alListenerfv(AL_ORIENTATION, vals);
    }
}
