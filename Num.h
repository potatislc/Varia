#pragma once
#include <type_traits>
#include <variant>
#include <cmath>

#include "internal_type_hirearchy.h"

namespace varia::internal_type {
    class Num;

    template<typename T>
    concept NumAlternative = std::same_as<Int, T> || std::same_as<Float, T>;

    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T> || std::same_as<Num, T>;

    template<typename T>
    concept NonArithmeticPrimitive = std::is_base_of_v<PrimitiveObject, T> && !Arithmetic<T>;

    template<typename T>
    concept ArithmeticNotBool = Arithmetic<T> && !std::same_as<Bool, T>;

    template<typename T>
    concept ArithmeticNotNum = Arithmetic<T> && !std::same_as<Num, T>;

    template<typename T>
    concept IntegralOrBool = std::integral<T> || std::same_as<Bool, T>;

    class Num : PrimitiveObject {
    public:
        enum class Type : uint8_t {
            Int,
            Float
        };

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
        [[nodiscard]] constexpr T as_alternative() const noexcept {
            if (is_alternative<T>()) {
                return std::get<T>(mValue);
            }

            return static_cast<T>(std::get<FallbackT>(mValue));
        }

        template<ArithmeticNotNum T>
        constexpr explicit operator T() const {
            return static_cast<T>(as_alternative<std::conditional_t<IntegralOrBool<T>, Int, Float>>());
        }

        // Binary operators

        Num operator+(const Num& other) const {
            if (is_alternative<Int>()) {
                return Num{as_alternative<Int>() + other.as_alternative<Int>()};
            }

            return Num{as_alternative<Float>() + other.as_alternative<Float>()};
        }

        Num operator+(const NumAlternative auto value) const {
            return as_alternative<decltype(value)>() + value;
        }

        Num operator%(const Int value) const {
            return Num{as_alternative<Int>() % value};
        }

        // Creates random ambiguous constructor error for var<internal_type::Bool>?!
        /*Num operator%(const Float value) const {
            return Num{std::fmod(as_alternative<Float>(), value)};
        }*/

    private:
        std::variant<Int, Float> mValue; // Eventually include BigInt and LongDouble
    };
}
