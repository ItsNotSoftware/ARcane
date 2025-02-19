#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <functional>
#include <cstdint>
#include <exception>

#include "ARcane/Log.hpp"

#define ARC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ARcane {

using KeyCode = int;

// Creating an alias for smart pointers for future migration to custom, socope/ref count system.
template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T>
using Ref = std::shared_ptr<T>;

}  // namespace ARcane