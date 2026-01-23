#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "./audio_data_manager.h"
#include "./audio_data_resolver.h"
#include "./audio_group.h"
#include "./listener.h"

namespace sgf_core {
    class AudioContext: public AudioDataResolver {
    public:
        AudioContext();
        ~AudioContext();

        sgf_core::Listener & Listener();
        sgf_core::AudioDataManager & AudioDataManager();

        AudioGroup & createGroup(const std::string & name);
        AudioGroup & getGroupRef(const std::string & name);

    private:
        struct ContextImpl;
        std::unique_ptr<ContextImpl> impl;

        sgf_core::Listener listener;
        sgf_core::AudioDataManager audioDataManager;
        std::unordered_map<std::string, std::unique_ptr<AudioGroup>> groups;

        AudioData & resolve(const AudioDataId & id) override;
    };
}
