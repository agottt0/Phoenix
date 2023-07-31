#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Phoenix
{
    class PHOENIX_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define PN_CORE_ERROR(...)   ::Phoenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PN_CORE_WARN(...)    ::Phoenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PN_CORE_INFO(...)    ::Phoenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PN_CORE_TRACE(...)   ::Phoenix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PN_CORE_FATAL(...)   ::Phoenix::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define PN_ERROR(...)        ::Phoenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PN_WARN(...)         ::Phoenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PN_INFO(...)         ::Phoenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PN_TRACE(...)        ::Phoenix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PN_FATAL(...)        ::Phoenix::Log::GetCoreLogger()->fatal(__VA_ARGS__)