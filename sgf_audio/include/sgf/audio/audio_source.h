#pragma once

#include <cstdint>
#include <sgf/utils/resource.h>
#include "./audio_data_id.h"
#include "./audio_data_resolver.h"
#include "./audio_source_id.h"
#include "./utils/vector3.h"

namespace sgf_core {
    class AudioSource: public Resource<AudioSource, AudioSourceId> {
    public:
        static const std::string TypeName;
        struct Construct {
            AudioDataId id;
            AudioDataResolver & resolver;
        };

        class DistanceAttenuationHandler {
        public:
            void setReferenceDistance(float distance);
            void setMaxDistance(float distance);
            void setRolloffFactor(float factor);

        private:
            friend AudioSource;

            DistanceAttenuationHandler(AudioSource & instance);

            AudioSource & instance;
        };

        AudioSource(const Id & id, const Construct & construct);
        ~AudioSource();

        DistanceAttenuationHandler & DistanceAttenuation();

        bool isPlaying() const;

        void setAudioDataId(const AudioDataId & dataId);

        void setLooping(bool looping);

        void setGain(float gain);
        void setPitch(float pitch);
        
        void setRelative(bool relative);
        void setPosition(const Vector3 & position);
        void setVelocity(const Vector3 & velocity);

        void play();
        void pause();
        void stop();

    private:
        uint32_t sourceId;

        AudioDataResolver & dataResolver;

        AudioDataId dataId;
        DistanceAttenuationHandler distanceAttenuation; 
    };
}
