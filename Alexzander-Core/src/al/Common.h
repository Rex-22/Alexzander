#pragma once

#ifdef AL_PLATFORM_WINDOWS
#ifdef AL_CORE_DLL
#define AL_API __declspec(dllexport)
#else
#define AL_API __declspec(dllimport)
#endif
#else
#define AL_API
#endif

#define BIT(x) (1 << x)

#define METHOD_1(x) std::bind(x, this, std::placeholders::_1)
#define METHOD_2(x) std::bind(x, this, std::placeholders::_2)
#define METHOD_3(x) std::bind(x, this, std::placeholders::_3)

#define METHOD(x) METHOD_1(x)