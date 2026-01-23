#pragma once

#include <sgf/utils/manager.h>
#include "./audio_source.h"

namespace sgf_core {
    class AudioSourceManager: public Manager<AudioSource> {
    public:
        void setAllSourceGain(float gain);
        void setAllSourcePitch(float pitch);
    };
}
