#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "internal_arithmetic_type.h"

namespace varia::internal_type {
    using String = std::string;
    
    template<typename T>
    using Array = std::vector<T>;
    template<typename K, typename V>
    using Map = std::unordered_map<K, V>;
    template<typename T>
    using Set = std::unordered_set<T>;
}
