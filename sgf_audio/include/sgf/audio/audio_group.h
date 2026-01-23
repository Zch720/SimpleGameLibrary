#pragma once

#include "./audio_source_manager.h"

namespace sgf_core {
    class AudioGroup {
    public:
        AudioSourceId createSource(const AudioSource::Construct & constructParameter);
        AudioSource & getSourceRef(const AudioSourceId & id);

        void setGain(float gain);
        void setPitch(float pitch);

    private:
        AudioSourceManager sourceManager;
    };
}
