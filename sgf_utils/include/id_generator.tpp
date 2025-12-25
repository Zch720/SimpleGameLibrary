#include "id_generator.h"

template <typename TId>
bool IdGenerator<TId>::isValid(const TId & id) const {
    return id.getId() != 0 && id.getId() <= generations.size() && id.getGen() == generations[id.getId() - 1];
}

template <typename TId>
TId IdGenerator<TId>::getNewId() {
    if (freeIds.empty()) {
        generations.push_back(1);
        return TId(generations.size(), 1);
    } else {
        uint32_t id = freeIds.front();
        freeIds.pop();
        return TId(id, generations[id - 1]);
    }
}

template <typename TId>
void IdGenerator<TId>::removeId(const TId & id) {
    freeIds.push(id.getId());
    generations[id.getId() - 1]++;
}
