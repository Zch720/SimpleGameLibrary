#pragma once

#include <functional>
#include <unordered_map>
#include "./uniform.h"
#include "./uniform_id.h"

namespace sgf_core {
    class UniformProvider {
    public:
        using ProviderFunc = std::function<UniformType()>;

        bool hasProvider(const UniformId & id) const;

        void setProviderFunc(const UniformId & id, const ProviderFunc & func);
        const ProviderFunc & getProvider(const UniformId & id) const;

    private:
        std::unordered_map<UniformId, ProviderFunc> providers;
    };
}
