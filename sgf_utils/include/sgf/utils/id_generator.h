#pragma once

#include <queue>
#include <vector>
#include "./resource_id.h"

namespace sgf_core {
    template <typename TId>
    class IdGenerator {
        public:
            bool isValid(const TId & id) const;

            TId getNewId();
            void removeId(const TId & id);

        private:
            std::vector<uint32_t> generations;
            std::queue<uint32_t> freeIds;
    };
}

#include "./id_generator.tpp"
