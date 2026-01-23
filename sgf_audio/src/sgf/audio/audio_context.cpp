#include "../../../include/sgf/audio/audio_context.h"
#include "sgf/audio/listener.h"
#include <AL/alc.h>
#include <memory>
#include <sgf/utils/exceptions/initialization_failed.h>
#include <sgf/utils/exceptions/resource_not_found.h>
#include <sgf/utils/logger/log.h>

namespace sgf_core {
    struct AudioContext::ContextImpl {
        ALCdevice * device = nullptr;
        ALCcontext * context = nullptr;
    };

    AudioContext::AudioContext() {
        impl = std::make_unique<ContextImpl>();
        impl->device = alcOpenDevice(nullptr);
        if (!impl->device) {
            SGF_LOG_ERROR("[sgf_audio] Failed to open default audio device.");
            throw InitializationFailed("Failed to open default audio device.");
        }

        impl->context = alcCreateContext(impl->device, nullptr);
        if (!impl->context || !alcMakeContextCurrent(impl->context)) {
            SGF_LOG_ERROR("[sgf_audio] Failed create or enable OpenAL context.");
            throw InitializationFailed("Failed create or enable OpenAL context.");
        }
    }

    AudioContext::~AudioContext() {
        if (impl->context) {
            alcDestroyContext(impl->context);
        }
        if (impl->device) {
            alcCloseDevice(impl->device);
        }
    }

    sgf_core::Listener & AudioContext::Listener() {
        return listener;
    }

    sgf_core::AudioDataManager & AudioContext::AudioDataManager() {
        return audioDataManager;
    }

    AudioGroup & AudioContext::createGroup(const std::string & name) {
        groups.insert({ name, std::make_unique<AudioGroup>() });
        return *groups[name];
    }

    AudioGroup & AudioContext::getGroupRef(const std::string & name) {
        if (groups.find(name) == groups.end()) {
            SGF_LOG_WARN("Try to get AudioGroup with name '{}', but not found", name);
            throw ResourceNotFound("Try to get AudioGroup with name '" + name + "', but not found");
        }
        return *groups[name];
    }

    AudioData & AudioContext::resolve(const AudioDataId & id) {
        return audioDataManager.getRef(id);
    }
}
