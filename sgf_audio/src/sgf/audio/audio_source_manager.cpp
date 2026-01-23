#include "../../../include/sgf/audio/audio_source_manager.h"

namespace sgf_core {
    void AudioSourceManager::setAllSourceGain(float gain) {
        foreach([gain](auto &, AudioSource & source) {
            source.setGain(gain);
        });
    }

    void AudioSourceManager::setAllSourcePitch(float pitch) {
        foreach([pitch](auto &, AudioSource & source) {
            source.setPitch(pitch);
        });
    }
}
