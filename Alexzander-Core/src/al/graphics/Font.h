#pragma once

#include "al/Common.h"
#include "al/Types.h"

#include "glm/glm.hpp"

namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace al { namespace graphics {

	class AL_API Font
	{
	private :
		String m_FontName;
		int m_FontSize;
		glm::vec4 m_Colour;

		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
	public:
		Font(const String& name, int size, const glm::vec4& colour);
		~Font();

		int GetID() const;
		inline const String& GetName() { return m_FontName; }
		inline ftgl::texture_font_t* GetFont() const { return m_FTFont; }
		inline const glm::vec4& const GetColour() const { return m_Colour; }
	};

} }

