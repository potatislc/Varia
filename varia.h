#pragma once

#include <memory>
#include <type_traits>
#include <concepts>

#include "Num.h"

namespace varia {
    template<typename T>
    concept VarConstraint = !std::same_as<void, T> && std::same_as<T, std::decay_t<T>>;

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
        // Exclude bools from this?
        static constexpr bool is_arithmetic{internal_type::Arithmetic<T>};

        static constexpr bool is_primitive{internal_type::Primitive<T> /* include math vectors here some day? */};

        // var<internal_type::String> has special overloads
        static constexpr bool is_string{std::same_as<T, internal_type::String>};

        using Storage = std::conditional_t<is_primitive, T, std::shared_ptr<T>>;

    public:
        using ValueType = T;

        var() requires is_primitive = default;

        var(const internal_type::Bool value) requires std::same_as<internal_type::Bool, T> : mValue{value} {}

        template<internal_type::ArithmeticNotBool U>
        var(const U value) : mValue{value} {}

        var(const internal_type::NonArithmeticPrimitive auto value) : mValue{value} {}

        var() requires (!is_primitive) : mValue{std::make_shared<T>()} {}

        var(const T& t) requires (!is_primitive) : mValue{std::make_shared<T>(t)} {}

        var(T&& t) requires (!is_primitive) : mValue{std::make_shared<T>(std::move(t))} {}

        // Forwarding constructor for types convertible to T
        template<typename U>
        requires (!internal_type::Primitive<T> && std::constructible_from<T, U&&>)
        var(U&& u) : mValue{std::make_shared<T>(std::forward<U>(u))} {}

        T* operator->() {
            return &get();
        }

        const T* operator->() const {
            return &get();
        }

        // Too permissive? Even implicitly downcasts during braced initialization
        template<internal_type::ArithmeticNotNum U>
        operator U() const requires internal_type::Arithmetic<T> {
            return static_cast<U>(mValue);
        }

        operator T() const {
            return get();
        }

        operator const std::string&() const requires is_string {
            return get();
        }

        friend Num operator+(const Num& lhs, const Num& rhs);

        friend String operator+(const String& lhs, const String& rhs);
        friend String& operator+=(String& lhs, const String& rhs);
    private:
        [[nodiscard]] T& get() {
            if constexpr (is_primitive) {
                return mValue;
            }

            return *mValue;
        }

        [[nodiscard]] const T& get() const requires (is_primitive){
            return mValue;
        }

        [[nodiscard]] const T& get() const requires (!is_primitive){
            return *mValue;
        }

        Storage mValue{};
    };

    // Deduction guides

    template<typename T>
    var(T) -> var<std::decay_t<T>>;

    var(internal_type::ArithmeticNotBool auto) -> var<internal_type::Num>;

    // var(internal_type::Num) -> var<internal_type::Num>;

    template <std::size_t N>
    var(const char(&)[N]) -> var<internal_type::String>;
    var(const char*) -> var<internal_type::String>;
    var(std::string_view) -> var<internal_type::String>;

    inline Num operator+(const Num& lhs, const Num& rhs) {
        return lhs.get() + rhs.get();
    }

    inline String operator+(const String& lhs, const String& rhs) {
        return lhs.get() + rhs.get();
    }

    inline String& operator+=(String& lhs, const String& rhs) {
        lhs.get() += rhs.get();
        return lhs;
    }

    template<typename T>
    concept func = std::is_constructible_v<var<T>> || std::same_as<void, T>;

    template<typename T>
    concept param = std::same_as<typename var<T>::ValueType, T>;

#define varia_func func auto
}
