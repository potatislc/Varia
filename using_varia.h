#pragma once
#include "var.h"
#include "VariaConfig.h"

namespace varia {
    inline const VariaConfig defaultConfig{VariaConfig{}.enable_boolalpha()};
}

using namespace std::string_literals;
using namespace varia;