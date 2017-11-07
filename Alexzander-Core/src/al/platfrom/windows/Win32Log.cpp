#include "al/al.h"

#ifdef AL_PLATFORM_WINDOWS

#ifdef AL_PLATFORM_GLFW
	#error Multiple platforms spesified
#endif

#include <Windows.h>
#include "al/utils/Log.h"

namespace al { namespace internal {

	void PlatformLogMessage(uint level, const char* message)
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

} }

#endif