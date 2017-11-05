#pragma once

#include "al/graphics/Font.h"

#include "al/Common.h"
#include "al/Types.h"
#include <vector>

namespace al { namespace graphics {

	class AL_API FontManager
	{
	private:
		static std::vector<Font*> m_FontStack;
	public:
		FontManager(Font* font);
		
		static void Add(Font* font);

		static Font* Get(const String& name);
		static void Clean();
	};

} }

