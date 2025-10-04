#pragma once
#include <type_traits>
#include "internal_type.h"

namespace varia::internal_type {
    struct IncompatibleType{}; // Cannot construct a var with this T
    struct CopiedType {};
    struct ImmutableRefType {};
    struct [[maybe_unused]] MutableRefType {};

    template<typename T>
    concept Copied = std::is_fundamental_v<T> || std::is_base_of_v<CopiedType, T>;

    template<typename T>
    concept ImmutableRef = std::same_as<String, T> || std::is_base_of_v<ImmutableRefType, T>;

    template<typename T>
    concept MutableRef = (!Copied<T> && !ImmutableRef<T>) || std::is_base_of_v<MutableRefType, T>;

    template<typename T>
    concept Referenced = ImmutableRef<T> || MutableRef<T>;

    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T> || std::same_as<Num, T> || std::same_as<Bool, T>;

    template<typename T>
    concept NonArithmeticCopied = std::is_base_of_v<CopiedType, T> && !Arithmetic<T>;

    template<typename T>
    concept ArithmeticNotBool = Arithmetic<T> && !std::same_as<Bool, T>;

    template<typename T>
    concept ArithmeticNotNum = std::is_arithmetic_v<T>;

    template<typename T>
    concept IntegralOrBool = std::integral<T> || std::same_as<Bool, T>;
}

