#include "al/al.h"

#ifdef AL_PLATFORM_GLFW

#ifdef AL_PLATFORM_WINDOWS
	#error Multiple platforms spesified
#endif

#include "al/utils/Log.h"
#include "al/utils/Colorize.h"

namespace al { namespace internal {

	void PlatformLogMessage(uint level, const char* message)
	{
		switch (level)
		{
			case ALEX_LOG_LEVEL_ERROR:
			{
				std::cout << color::rize(message, "Red") << std::endl;
			}
			case ALEX_LOG_LEVEL_FATAL:
			{
				std::cout << color::rize(message, "Default", "Red") << std::endl;
			}
			case ALEX_LOG_LEVEL_WARN:
			{
				std::cout << color::rize(message, "Yello") << std::endl;
			}
			case ALEX_LOG_LEVEL_INFO:
			{
				std::cout << color::rize(message, "Default") << std::endl;
			}	
		}
	}

} }

#endif