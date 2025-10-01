#pragma once

#include <memory>
#include <type_traits>
#include <concepts>
#include <iostream>

#include "Num.h"

namespace varia {
    template<typename T>
    concept VarConstraint = !std::same_as<void, T> && std::same_as<T, std::decay_t<T>>;

    template<typename T>
    concept StringConstructible = std::is_constructible_v<std::string, T>;

    template<VarConstraint T>
    class var;

    // Typedefs for a simple subset of relevant types. Used for user declared functions with vars as parameters
    using Void = void; // Conform with varia naming convention (maybe used as function return type)
    using Bool = var<internal_type::Bool>;
    using Int = var<internal_type::Int>;
    using Float = var<internal_type::Float>;
    using Num = var<internal_type::Num>;
    using String = var<internal_type::String>;

    template<typename T>
    using Array = var<internal_type::Array<T>>;
    template<typename K, typename V>
    using Map = var<internal_type::Map<K, V>>;
    template<typename T>
    using Set = var<internal_type::Set<T>>;

    template<VarConstraint T>
    class var {
        using ValueType = T;

        class PrimitiveContainer {
        public:
            explicit PrimitiveContainer(const T& value) : mValue{value} {}

            [[nodiscard]] const T& operator*() const {
                return mValue;
            }

            [[nodiscard]] T& operator*() {
                return mValue;
            }

        private:
            T mValue{};
        };

        using Storage = std::conditional_t<internal_type::Primitive<T>, PrimitiveContainer, std::shared_ptr<T>>;

    public:
        // Intentionally Implicit

        var(const T& value) requires (!internal_type::ArithmeticNotBool<T> && !StringConstructible<T>): mValue{make(value)} {}

        template<internal_type::ArithmeticNotBool U>
        var(const U value) : mValue{internal_type::Num{value}} {}

        template<StringConstructible U>
        var(const U& value) : mValue{make(value)} {}

        template<internal_type::Arithmetic U>
        operator U() const {
            return static_cast<U>(*mValue);
        }

        operator T() const {
            return *mValue;
        }

        const T* operator->() const {
            return &*mValue;
        }

        T* operator->() {
            return &*mValue;
        }

        // Special overloads

        friend String operator+(const String& lhs, const String& rhs);
        friend Num operator+(Num lhs, Num rhs);

    private:
        auto make(const T& value) const {
            if constexpr (internal_type::Primitive<T>) {
                return value;
            } else {
                return std::make_shared<T>(value);
            }
        }

        Storage mValue{};
    };

    // Deduction guides

    template<internal_type::ArithmeticNotBool T>
    var(T) -> var<internal_type::Num>;

    template<StringConstructible T>
    var(T) -> var<internal_type::String>;

    // Special overloads

    inline Num operator+(const Num lhs, const Num rhs) {
        return *lhs.mValue + *rhs.mValue;
    }

    inline String operator+(const String& lhs, const String& rhs) {
        return *lhs.mValue + *rhs.mValue;
    }

    // Sicko Mode Zone

    template<typename T>
    concept func = std::is_constructible_v<var<T>> || std::same_as<void, T>;

    template<typename T>
    concept param = std::same_as<typename var<T>::ValueType, T>;

#define varia_func func auto
}
