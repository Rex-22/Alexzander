#include "Font.h"

#include <freetype-gl/freetype-gl.h>

namespace al { namespace graphics {
	
	Font::Font(const String& name, const String& fontFile, int size, const uint colour)
		:m_Name(name), m_FontName(fontFile), m_FontSize(size), m_Colour(colour)
	{
		m_FTAtlas = texture_atlas_new(512, 512, 2);
		m_FTFont = texture_font_new_from_file(m_FTAtlas, size, m_FontName.c_str());
	}

	Font::Font(const String& name, const String& fontFile, int size, glm::vec4 colour) 
		:m_Name(name), m_FontName(name), m_FontSize(size)
	{
		SetColour(colour);
	}

	Font::~Font()
	{
	}

	int Font::GetID() const
	{
		return m_FTAtlas->id;
	}

} }
