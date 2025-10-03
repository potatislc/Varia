#pragma once
#include <iostream>

struct VariaConfig {
    [[nodiscard]] const VariaConfig& enable_boolalpha() const {
        std::cout << std::boolalpha;
        return *this;
    }
};
