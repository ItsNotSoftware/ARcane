#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ARcane {

/**
 * @class Log
 * @brief Handles logging functionality for the engine.
 *
 * This class initializes and manages two separate loggers:
 * - A core logger for engine-related logs.
 * - A client logger for user-defined application logs.
 *
 * Uses spdlog for efficient, high-performance logging.
 */
class Log {
   public:
    /**
     * @brief Initializes the logging system.
     *
     * This function sets up the core and client loggers with colored output.
     */
    static void Init();

    /**
     * @brief Retrieves the core logger.
     *
     * @return A shared pointer to the core logger.
     */
    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

    /**
     * @brief Retrieves the client logger.
     *
     * @return A shared pointer to the client logger.
     */
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

   private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace ARcane

// ----------------------------
// Log Macros
// ----------------------------

// Core logging macros
#define ARC_CORE_TRACE(...) ::ARcane::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ARC_CORE_INFO(...) ::ARcane::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ARC_CORE_WARN(...) ::ARcane::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ARC_CORE_ERROR(...) ::ARcane::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ARC_CORE_FATAL(...) ::ARcane::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define ARC_TRACE(...) ::ARcane::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ARC_INFO(...) ::ARcane::Log::GetClientLogger()->info(__VA_ARGS__)
#define ARC_WARN(...) ::ARcane::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_ERROR(...) ::ARcane::Log::GetClientLogger()->error(__VA_ARGS__)
#define ARC_FATAL(...) ::ARcane::Log::GetClientLogger()->critical(__VA_ARGS__)

// Core assertion macro
#define ARC_CORE_ASSERT(x, ...)                                   \
    {                                                             \
        if (!(x)) {                                               \
            ARC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            throw std::runtime_error("Assertion Failed");         \
        }                                                         \
    }

// Client assertion macro
#define ARC_ASSERT(x, ...)                                   \
    {                                                        \
        if (!(x)) {                                          \
            ARC_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            throw std::runtime_error("Assertion Failed");    \
        }                                                    \
    }

/*
    ============================
    *Example Usage:
    ============================


    ARcane::Log::Init();

    ...

    ARC_WARN("This is a warning message");
    ARC_ERROR("Something went wrong: {0}", 404);
    ARC_INFO("X: {0}, Y: {1}", x, y);

    ARC_ASSERT(x == y, "X must be equal to Y");

    ============================
*/