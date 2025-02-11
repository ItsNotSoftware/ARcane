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

<<<<<<< HEAD
<<<<<<< Updated upstream
#define BIT(x) (1 << x)
=======
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

typedef int KeyCode;
>>>>>>> Stashed changes
=======
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
>>>>>>> 4ca001afdc0a19a36da49aef12fc4fbc3ba23c36
