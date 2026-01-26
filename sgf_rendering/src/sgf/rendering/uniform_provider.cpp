#include "../../../include/sgf/rendering/uniform_provider.h"

namespace sgf_core {
    bool UniformProvider::hasProvider(const UniformId & id) const {
        return providers.find(id) != providers.end();
    }

    void UniformProvider::setProviderFunc(const UniformId & id, const ProviderFunc & func) {
        providers[id] = func;
    }

    const UniformProvider::ProviderFunc & UniformProvider::getProvider(const UniformId & id) const {
        return providers.at(id);
    }
}
