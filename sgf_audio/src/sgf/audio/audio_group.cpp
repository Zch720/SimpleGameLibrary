#include "../../../include/sgf/audio/audio_group.h"

namespace sgf_core {
    AudioSourceId AudioGroup::createSource(const AudioSource::Construct & constructParameter) {
        return sourceManager.create(constructParameter);
    }

    AudioSource & AudioGroup::getSourceRef(const AudioSourceId & id) {
        return sourceManager.getRef(id);
    }

    void AudioGroup::setGain(float gain) {
        sourceManager.setAllSourceGain(gain);
    }

    void AudioGroup::setPitch(float pitch) {
        sourceManager.setAllSourcePitch(pitch);
    }
}
