#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace DURLIB
{
    REF<spdlog::logger> Log::ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        ClientLogger = spdlog::stdout_color_mt("CLI");
        ClientLogger->set_level(spdlog::level::trace);

        CLI_WARN("CLIENT LOG INITIALIZED.");
    }
}