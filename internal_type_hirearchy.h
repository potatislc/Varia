#pragma once
#include <type_traits>
#include "internal_type.h"

namespace varia::internal_type {
    // Primitive: std::is_arithmetic<T> || std::same_as<internal_type::Num, T>
    // PrimitiveRefObject: internal_type::String
    // RefObject: Allt annat
    struct PrimitiveObject {}; // Copied
    struct PrimitiveRefObject {}; // Immutable ref
    struct RefObject {}; // Ref

    template<typename T>
    concept Primitive = std::is_arithmetic_v<T> || std::is_base_of_v<PrimitiveObject, T>;

    template<typename T>
    concept NonArithmeticPrimitive = std::is_base_of_v<PrimitiveObject, T>;

    template<typename T>
    concept PrimitiveRef = std::same_as<String, T> || std::is_base_of_v<PrimitiveRefObject, T>;
}

