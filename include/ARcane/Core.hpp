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
#include "ARcane/Events/Event.hpp"

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

typedef int KeyCode;
