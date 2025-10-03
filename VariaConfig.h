#pragma once
#include <iostream>

namespace varia {
    struct VariaConfig : internal_type::IncompatibleType {
        [[nodiscard]] const VariaConfig& enable_boolalpha() const {
            std::cout << std::boolalpha;
            return *this;
        }
    };
}
