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

    private:
        static REF<spdlog::logger> ClientLogger;
    };
}

// CLIENT SIDE LOGS
#define CLI_ERROR(...) ::DURLIB::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLI_WARN(...) ::DURLIB::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLI_INFO(...) ::DURLIB::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLI_TRACE(...) ::DURLIB::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLI_FATAL(...) ::DURLIB::Log::GetClientLogger()->fatal(__VA_ARGS__)