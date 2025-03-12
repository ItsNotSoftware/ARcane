#include "ARcane/Core/Log.hpp"

namespace ARcane {

// Define the static loggers
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init() {
    // Set the pattern for the loggers
    spdlog::set_pattern("%^[%T] %n: %v%$");

    // Create the loggers and set their level to trace
    s_CoreLogger = spdlog::stdout_color_mt("ARcane");
    s_CoreLogger->set_level(spdlog::level::trace);
    s_ClientLogger = spdlog::stdout_color_mt("App");
    s_ClientLogger->set_level(spdlog::level::trace);
}

}  // namespace ARcane