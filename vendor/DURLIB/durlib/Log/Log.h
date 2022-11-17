#pragma once

#include "durlib/Core/_CORE.h"
#include "spdlog/spdlog.h"

namespace DURLIB
{
    class Log
    {
    public:
        static void Init();

        inline static REF<spdlog::logger> &GetClientLogger() { return ClientLogger; }
        inline static REF<spdlog::logger> &GetDebugLogger() { return DebugLogger; }

    private:
        static REF<spdlog::logger> ClientLogger;
        static REF<spdlog::logger> DebugLogger;
    };
}

// CLIENT SIDE LOGS
#define CLI_ERROR(...) ::DURLIB::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLI_WARN(...) ::DURLIB::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLI_INFO(...) ::DURLIB::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLI_TRACE(...) ::DURLIB::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLI_FATAL(...) ::DURLIB::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CLI_BUG(...) ::DURLIB::Log::GetClientLogger()->debug(__VA_ARGS__)
// DEBUG/COMPILATION LOGGER
#ifdef DURLIB_ENABLE_DEBUG_LOG
    #define DEBUG_ERROR(...) ::DURLIB::Log::GetDebugLogger()->error(__VA_ARGS__)
    #define DEBUG_WARN(...) ::DURLIB::Log::GetDebugLogger()->warn(__VA_ARGS__)
    #define DEBUG_INFO(...) ::DURLIB::Log::GetDebugLogger()->info(__VA_ARGS__)
    #define DEBUG_TRACE(...) ::DURLIB::Log::GetDebugLogger()->trace(__VA_ARGS__)
    #define DEBUG_FATAL(...) ::DURLIB::Log::GetDebugLogger()->critical(__VA_ARGS__)
    #define DEBUG_BUG(...) ::DURLIB::Log::GetDebugLogger()->debug(__VA_ARGS__)
#else
    #define DEBUG_ERROR(...)
    #define DEBUG_WARN(...)
    #define DEBUG_INFO(...)
    #define DEBUG_TRACE(...)
    #define DEBUG_FATAL(...)
    #define DEBUG_BUG(...)
#endif