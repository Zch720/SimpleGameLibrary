#pragma once

#include <memory>
#include <queue>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "./id_generator.h"
#include "./exceptions/resource_not_found.h"

template <typename T>
class Manager {
using TId = typename T::Id;
using Construct = typename T::Construct;

public:
    bool isExist(const TId & id) const;

    T& getRef(const TId & id) const;

    TId create(const Construct & constructParameter);
    void remove(const TId & id);
    void destroyAll();

private:
    std::unordered_map<TId, std::unique_ptr<T>> items;
    IdGenerator<TId> idGenerator;
};

#include "./manager.tpp"
