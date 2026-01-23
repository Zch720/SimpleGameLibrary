#pragma once

#include <cstdint>
#include <vector>
#include <sgf/utils/resource.h>
#include "./audio_data_id.h"

namespace sgf_core {
    class AudioSource;

    class AudioData: public Resource<AudioData, AudioDataId> {
    public:
        static const std::string TypeName;
        struct Construct {
            std::vector<uint8_t> pcmData;
            int32_t format = 0;
            int32_t sampleRate = 0;

            uint16_t numChannels = 0;
            uint16_t bitsPreSample = 0;
        };

        AudioData(const Id & id, const Construct & constructParameter);
        ~AudioData();

    private:
        friend AudioSource;

        uint32_t bufferId;

        std::vector<uint8_t> pcmData;
        int32_t format; // TODO: use enum
        int32_t sampleRate;

        uint16_t numChannels;
        uint16_t bitsPreSample;

        bool isValid() const;
    };
}
