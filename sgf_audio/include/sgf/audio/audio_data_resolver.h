#pragma once

#include "./audio_data.h"

namespace sgf_core {
    class AudioDataResolver {
    public:
        virtual AudioData & resolve(const AudioDataId & id) = 0;
    };
}
