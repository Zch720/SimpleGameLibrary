#include "./manager.h"
#include <utility>

namespace sgf_core {
    template <typename T>
    bool Manager<T>::isExist(const TId & id) const {
        if (!idGenerator.isValid(id)) return false;
        return items.find(id) != items.end();
    }

    template <typename T>
    T& Manager<T>::getRef(const TId & id) const {
        if (!isExist(id)) throw ResourceNotFound("Try to get " + T::getTypeName() + " with id " + id.toString() + " from manager, but not found");
        return *(items.find(id)->second.get());
    }

    template <typename T>
    typename T::Id Manager<T>::create(const Construct & constructParameter) {
        TId id = idGenerator.getNewId();
        items.insert({ id, std::make_unique<T>(id, constructParameter) });
        return id;
    }

    template <typename T>
    void Manager<T>::remove(const TId & id) {
        if (!isExist(id)) throw ResourceNotFound("Try to remove " + T::getTypeName() + " with id " + id.toString() + " in manager, but not found");
        items.erase(id);
    }

    template <typename T>
    void Manager<T>::destroyAll() {
        items.clear();
    }
}
