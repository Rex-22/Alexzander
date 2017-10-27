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