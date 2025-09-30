#pragma once
#include <cstdint>
#include <type_traits>
#include <variant>

#include "internal_arithmetic_type.h"

namespace varia::internal_type {
    class Num;

    template<typename T>
    concept NumAlternative = std::same_as<Int, T> || std::same_as<Float, T>;

    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T> || std::same_as<Num, T>;

    template<typename T>
    concept ArithmeticNotBool = Arithmetic<T> && !std::same_as<Bool, T>;

    template<typename T>
    concept IntegralOrBool = std::integral<T> || std::same_as<Bool, T>;

    class Num {
    public:
        Num() = default;

        explicit Num(const std::integral auto value) : mValue{static_cast<Int>(value)} {}

        explicit Num(const std::floating_point auto value) : mValue{static_cast<Float>(value)} {}

        constexpr Num& operator=(const NumAlternative auto value) {
            mValue = value;
            return *this;
        }

        template<NumAlternative T>
        [[nodiscard]] constexpr bool is_alternative() const noexcept {
            return std::holds_alternative<T>(mValue);
        }

        template<NumAlternative T, NumAlternative FallbackT = std::conditional_t<std::same_as<T, Int>, Float, Int>>
        [[nodiscard]] T as_alternative() const noexcept {
            if (is_alternative<T>()) {
                return std::get<T>(mValue);
            }

            return static_cast<T>(std::get<FallbackT>(mValue));
        }

        template<Arithmetic T>
        explicit operator T() const {
            return static_cast<T>(as_alternative<std::conditional_t<IntegralOrBool<T>, Int, Float>>());
        }

        Num operator+(const NumAlternative auto value) {
            return as_alternative<decltype(value)>() + value;
        }

    private:
        std::variant<Int, Float> mValue; // Eventually include BigInt and LongDouble
    };
}
