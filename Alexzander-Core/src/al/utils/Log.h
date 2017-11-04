#pragma once

#include "al/Common.h"
#include "al/Types.h"

#include "glm/glm.hpp"
#include "al/String.h"
#include <windows.h>

#define ALEX_LOG_LEVEL_FATAL 0
#define ALEX_LOG_LEVEL_ERROR 1
#define ALEX_LOG_LEVEL_WARN  2
#define ALEX_LOG_LEVEL_INFO  3

#ifdef MOUSE_MOVED
#undef MOUSE_MOVED // Defined in wincon.h
#endif

namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)");
	}
}

namespace al { namespace internal {

		static char to_string_buffer[1024 * 10];
		static char sprintf_buffer[1024 * 10];

		AL_API void PlatformLogMessage(uint level, const char* message)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (level)
			{
			case ALEX_LOG_LEVEL_FATAL:
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case ALEX_LOG_LEVEL_ERROR:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case ALEX_LOG_LEVEL_WARN:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
			printf("%s", message);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

		template <typename T>
		static const char* to_string(const T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <>
		static const char* to_string<char>(const char& t)
		{
			return &t;
		}

		template <>
		static const char* to_string<char*>(char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t)
		{
			return (const char*)t;
		}

		template <>
		static const char* to_string<wchar_t*>(wchar_t* const& t)
		{
			wcstombs(sprintf_buffer, t, 1024 * 10);
			return sprintf_buffer;
		}

		template <>
		static const char* to_string<const wchar_t*>(const wchar_t* const& t)
		{
			wcstombs(sprintf_buffer, t, 1024 * 10);
			return sprintf_buffer;
		}

		template <>
		static const char* to_string<const char*>(const char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<String>(const String& t)
		{
			return t.c_str();
		}

		template <>
		static const char* to_string<bool>(const bool& t)
		{
			return t ? "true" : "false";
		}

		template <>
		static const char* to_string<glm::vec2>(const glm::vec2& t)
		{
			// TODO: sprintf
			String string = String("vec2: (") + StringFormat::ToString(t.x) + ", " + StringFormat::ToString(t.y) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <>
		static const char* to_string<glm::vec3>(const glm::vec3& t)
		{
			// TODO: sprintf
			String string = String("vec3: (") + StringFormat::ToString(t.x) + ", " + StringFormat::ToString(t.y) + ", " + StringFormat::ToString(t.z) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

//		template <>
//		static const char* to_string<math::Rectangle>(const math::Rectangle& r)
//		{
//			sprintf(sprintf_buffer, "Rectangle: (%f, %f, %f, %f)", r.x, r.y, r.width, r.height);
//			char* result = new char[strlen(sprintf_buffer)];
//			strcpy(result, &sprintf_buffer[0]);
//			return result;
//		}

		template <typename T>
		static String format_iterators(T& begin, T& end)
		{
			String result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = StringFormat::ToString(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template<typename X, typename Y>
		static const char* to_string(const std::pair<typename X, typename Y>& v)
		{
			sprintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, int32& position, First&& first)
		{
			const char* formatted = internal::to_string<First>(first);
			int32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int32& position, First&& first, Args&&... args)
		{
			const char* formatted = internal::to_string<First>(first);
			int32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
				print_log_internal(buffer, position, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log_message(int32 level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			int32 position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline)
				buffer[position++] = '\n';

			buffer[position] = 0;

			PlatformLogMessage(level, buffer);
		}
} }

// Windows (wingdi.h) defines AL_ERROR
#ifdef AL_ERROR
#undef AL_ERROR
#endif

#ifndef ALEX_LOG_LEVEL
#define ALEX_LOG_LEVEL ALEX_LOG_LEVEL_INFO
#endif

#if ALEX_LOG_LEVEL >= ALEX_LOG_LEVEL_FATAL
#define AL_FATAL(...)  internal::log_message(ALEX_LOG_LEVEL_FATAL, true, "ALEX:    ", __VA_ARGS__)
#define _AL_FATAL(...) internal::log_message(ALEX_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define AL_FATAL(...)
#define _AL_FATAL(...)
#endif

#if ALEX_LOG_LEVEL >= ALEX_LOG_LEVEL_ERROR
#define AL_ERROR(...)  internal::log_message(ALEX_LOG_LEVEL_ERROR, true, "ALEX:    ", __VA_ARGS__)
#define _AL_ERROR(...) internal::log_message(ALEX_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define AL_ERROR(...)
#define _AL_ERROR(...)
#endif

#if ALEX_LOG_LEVEL >= ALEX_LOG_LEVEL_WARN
#define AL_WARN(...)  internal::log_message(ALEX_LOG_LEVEL_WARN, true, "ALEX:    ", __VA_ARGS__)
#define _AL_WARN(...) internal::log_message(ALEX_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
#define AL_WARN(...)
#define _AL_WARN(...)
#endif

#if ALEX_LOG_LEVEL >= ALEX_LOG_LEVEL_INFO
#define AL_INFO(...)  internal::log_message(ALEX_LOG_LEVEL_INFO, true, "ALEX:    ", __VA_ARGS__)
#define _AL_INFO(...) internal::log_message(ALEX_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define AL_INFO(...)
#define _AL_INFO(...)
#endif

#if ALEX_LOG_LEVEL >= ALEX_LOG_DEBUG
#define AL_DEBUG(...)  internal::log_message(ALEX_LOG_LEVEL_INFO, true, "[DEBUG] ALEX:    ", __VA_ARGS__)
#define _AL_DEBUG(...) internal::log_message(ALEX_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define AL_INFO(...)
#define _AL_INFO(...)
#endif

#ifdef AL_DEBUG
#define AL_ASSERT(x, ...) \
		if (!(x)) {\
			AL_FATAL("*************************"); \
			AL_FATAL("    ASSERTION FAILED!    "); \
			AL_FATAL("*************************"); \
			AL_FATAL(__FILE__, ": ", __LINE__); \
			AL_FATAL("Condition: ", #x); \
			AL_FATAL(__VA_ARGS__); \
			__debugbreak(); \
		}
#else
#define AL_ASSERT(x, ...)
#endif