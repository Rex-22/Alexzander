#pragma once

#include "al/Types.h"
#include "al/Common.h"

namespace al {

	class AL_API ImageUtils
	{
	public:
		static BYTE* LoadImage(const char* filename, uint* width, uint* height);
	};

}