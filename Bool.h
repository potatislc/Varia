#pragma once

#include "None.h"
#include "Num.h"

namespace varia::internal_type {
    class Bool : CopiedType {
    public:
        enum class State {
            False,
            True,
            None
        };

        Bool() = default;
        explicit Bool(const bool value) : mValue{value} {}
        explicit Bool(const ArithmeticNotBool auto& value) : mValue{static_cast<bool>(value)} {}

        Bool& operator=(const bool b) {
            mValue = static_cast<State>(b);
            return *this;
        }

        template<Arithmetic T>
        explicit operator T() const {
            return static_cast<T>(mValue);
        }

    private:
        State mValue{State::None};
    };
}
