#pragma once

#ifdef PHOENIX_PLATFORM_WINDOWS
    #ifdef PHOENIX_BUILD_DLL
        #define PHOENIX_API __declspec(dllexport)
    #else
        #define PHOENIX_API __declspec(dllimport)
    #endif
#else
    #error Phoenix only support Windows!
#endif

#ifdef PN_ENABLE_ASSERTS
    #define PN_ASSERT(x, ...) { if(!(x)) { PN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define PN_CORE_ASSERT(x, ...) { if(!(x)) { PN_CORE_ERROR("Assertion Failed: {0}", __VA_AGRS__);__debugbreak(); } }
#else
    #define PN_ASSERT(x, ...)
    #define PN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)