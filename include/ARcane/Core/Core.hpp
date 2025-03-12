#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <functional>
#include <cstdint>
#include <exception>
#include <fstream>
#include <unordered_map>

#include "ARcane/Core/Log.hpp"
#include "ARcane/Debug/Instrumentor.hpp"

#define ARC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ARcane {

using KeyCode = int;

// Creating an alias for smart pointers for future migration to custom, socope/ref count system.
template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#ifndef ASSETS_DIR
#define ASSETS_DIR "[CMAKE FAILED TO SET ASSETS_DIR]"
#endif

#define ARC_ASSET_PATH(path) (std::string(ASSETS_DIR) + std::string("/") + (path))

}  // namespace ARcane