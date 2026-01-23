#include "../../../include/sgf/audio/audio_source.h"
#include "sgf/audio/audio_source_id.h"
#include <AL/al.h>
#include <sgf/utils/exceptions/initialization_failed.h>
#include <sgf/utils/exceptions/invalid_state.h>
#include <sgf/utils/logger/log.h>
#include <string>

namespace sgf_core {
    const std::string AudioSourceTag::TypeName = "AudioSource";
    const std::string AudioSource::TypeName = "AudioSource";

    AudioSource::AudioSource(const Id & id, const Construct & constructParameter):
        dataId(constructParameter.id),
        dataResolver(constructParameter.resolver),
        distanceAttenuation(*this)
    {
        this->id = id;

        alGenSources(1, &sourceId);
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            SGF_LOG_ERROR("[sgf_audio] Failed to create OpenAL source, code: {}", error);
            throw InitializationFailed("Failed to create OpenAL source, code: " + std::to_string(error));
        }
    }

    AudioSource::~AudioSource() {
        if (sourceId != 0) {
            alDeleteSources(1, &sourceId);
        }
    }

    bool AudioSource::isPlaying() const {
        ALint state = 0;
        alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }

    void AudioSource::setAudioDataId(const AudioDataId & dataId) {
        this->dataId = dataId;

        if (isPlaying()) {
            SGF_LOG_WARN("[sgf_audio] Tried to set audio data before audio stop with id {}.", id.toString());
            throw InvalidState("Tried to set audio data before audio stop with id " + id.toString());
        }

        alSourcei(sourceId, AL_BUFFER, static_cast<ALint>(dataResolver.resolve(dataId).bufferId));
    }

    void AudioSource::setLooping(bool looping) {
        alSourcei(sourceId, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
    }

    void AudioSource::setGain(float gain) {
        alSourcef(sourceId, AL_GAIN, gain);
    }

    void AudioSource::setPitch(float pitch) {
        alSourcef(sourceId, AL_PITCH, pitch);
    }

    void AudioSource::setRelative(bool relative) {
        alSourcei(sourceId, AL_SOURCE_RELATIVE, relative ? AL_TRUE : AL_FALSE);
    }

    void AudioSource::setPosition(const Vector3 & position) {
        alSource3f(sourceId, AL_POSITION, position.x, position.y, position.z);
    }

    void AudioSource::setVelocity(const Vector3 & velocity) {
        alSource3f(sourceId, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    }

    void AudioSource::play() {
        alSourcePlay(sourceId);
    }

    void AudioSource::pause() {
        alSourcePause(sourceId);
    }

    void AudioSource::stop() {
        alSourceStop(sourceId);
    }

    void AudioSource::DistanceAttenuationHandler::setReferenceDistance(float distance) {
        alSourcei(instance.sourceId, AL_REFERENCE_DISTANCE, distance);
    }

    void AudioSource::DistanceAttenuationHandler::setMaxDistance(float distance) {
        alSourcei(instance.sourceId, AL_MAX_DISTANCE, distance);
    }

    void AudioSource::DistanceAttenuationHandler::setRolloffFactor(float factor) {
        alSourcei(instance.sourceId, AL_ROLLOFF_FACTOR, factor);
    }
}
