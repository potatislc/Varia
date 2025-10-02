#pragma once
#include <type_traits>
#include "internal_type.h"
#include "Num.h"

namespace varia::internal_type {
    struct CopiedType {};
    struct ImmutableRefType {};
    struct [[maybe_unused]] MutableRefType {};

    struct None : CopiedType {};

    template<typename T>
    concept Copied = std::is_fundamental_v<T> || std::is_base_of_v<CopiedType, T>;

    template<typename T>
    concept ImmutableRef = std::same_as<String, T> || std::is_base_of_v<ImmutableRefType, T>;

    template<typename T>
    concept MutableRef = (!Copied<T> && !ImmutableRef<T>) || std::is_base_of_v<MutableRefType, T>;

    template<typename T>
    concept Referenced = ImmutableRef<T> || MutableRef<T>;
}

