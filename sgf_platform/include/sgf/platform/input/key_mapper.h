#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include "./key.h"

namespace sgf_core {
    class KeyMapper {
    public:
        static Key toSGFKey(int32_t key);
        static int32_t toGLFWKey(Key key);
        static std::string toName(Key key);

        static MouseKey toSGFMouseKey(int32_t key);
        static int32_t toGLFWMouseKey(MouseKey key);
        static std::string toName(MouseKey key);
    
    private:
        static std::unordered_map<int32_t, Key> toSGFMap;
        static std::unordered_map<Key, int32_t> toGLFWMap;
        static std::unordered_map<Key, std::string> toNameMap;

        static std::unordered_map<int32_t, MouseKey> toSGFMouseMap;
        static std::unordered_map<MouseKey, int32_t> toGLFWMouseMap;
        static std::unordered_map<MouseKey, std::string> toNameMouseMap;
    };
}
