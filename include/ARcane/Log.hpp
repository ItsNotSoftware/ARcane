#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ARcane {

class Log {
   public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

   private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace ARcane

// Core log macros
#define ARC_CORE_TRACE(...) ::ARcane::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ARC_CORE_INFO(...) ::ARcane::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ARC_CORE_WARN(...) ::ARcane::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ARC_CORE_ERROR(...) ::ARcane::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ARC_CORE_FATAL(...) ::ARcane::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define ARC_TRACE(...) ::ARcane::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ARC_INFO(...) ::ARcane::Log::GetClientLogger()->info(__VA_ARGS__)
#define ARC_WARN(...) ::ARcane::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_ERROR(...) ::ARcane::Log::GetClientLogger()->error(__VA_ARGS__)
#define ARC_FATAL(...) ::ARcane::Log::GetClientLogger()->fatal(__VA_ARGS__)
