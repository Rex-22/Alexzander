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
		String m_Name;
		String m_FontName;
		int m_FontSize;
		uint m_Colour;

		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
	public:
		Font(const String& name, const String& fontFile, int size, const uint colour);
		Font(const String& name, const String& fontFile, int size, glm::vec4 colour);
		~Font();

		int GetID() const;
		inline const String& GetName() { return m_Name; }
		inline const String& GetFontName() { return m_FontName; }
		inline ftgl::texture_font_t* GetFont() const { return m_FTFont; }
		inline const uint const GetColour() const { return m_Colour; }

		inline void SetColour(uint colour) { m_Colour = colour; }
		inline void SetColour(glm::vec4 colour) {
			int r = colour.x * 255.0f;
			int g = colour.y * 255.0f;
			int b = colour.z * 255.0f;
			int a = colour.w * 255.0f;

			m_Colour = a << 24 | b << 16 | g << 8 | r;
		}
	};

} }

