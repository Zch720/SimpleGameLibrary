#include "../../../include/sgf/audio/audio_data.h"
#include <AL/al.h>
#include <sgf/utils/logger/log.h>
#include <sgf/utils/exceptions/initialization_failed.h>

namespace sgf_core {
    const std::string AudioDataTag::TypeName = "AudioData";
    const std::string AudioData::TypeName = "AudioData";

    AudioData::AudioData(const Id & id, const Construct & constructParameter):
        pcmData(constructParameter.pcmData),
        format(constructParameter.format),
        sampleRate(constructParameter.sampleRate),
        numChannels(constructParameter.numChannels),
        bitsPreSample(constructParameter.bitsPreSample)
    {
        if (!isValid()) {
            throw InitializationFailed("Audio data is valid, cannot create OpenAL buffer.");
        }

        this->id = id;

        alGenBuffers(1, &bufferId);
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            SGF_LOG_ERROR("[sgf_audio] Failed to create OpenAL buffer, code: {}", error);
            throw InitializationFailed("Failed to create OpenAL buffer, code: " + std::to_string(error));
        }

        alBufferData(bufferId, format, pcmData.data(), static_cast<ALsizei>(pcmData.size()), sampleRate);
        error = alGetError();
        if (error != AL_NO_ERROR) {
            SGF_LOG_ERROR("[sgf_audio] Failed to setting OpenAL buffer data, code: {}", error);
            throw InitializationFailed("Failed to setting OpenAL buffer data, code: " + std::to_string(error));
        }
    }

    AudioData::~AudioData() {
        if (bufferId != 0) {
            alDeleteBuffers(1, &bufferId);
        }
    }

    bool AudioData::isValid() const {
        if (pcmData.empty()) {
            SGF_LOG_ERROR("[sgf_audio] Audio data is valid, pcm data is empty.");
            return false;
        }
        if (format == 0) {
            SGF_LOG_ERROR("[sgf_audio] Audio data is valid, format not set.");
            return false;
        }
        if (sampleRate == 0) {
            SGF_LOG_ERROR("[sgf_audio] Audio data is valid, sample rate not set.");
            return false;
        }
        return true;
    }
}
