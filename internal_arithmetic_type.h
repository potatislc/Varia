#pragma once
#include <cstdint>

namespace varia::internal_type {
    using Bool = bool;
    // Default to 64bit counterparts to conform with Python and lua
    using Int = int64_t;
    using Float = double;
    class Num;
}
