#include "Label.h"

#include "al/graphics/FontManager.h"

namespace al { namespace graphics {
	
	Label::Label(const String& text, const glm::vec2 position, Font* font)
		: Renderable2D(glm::vec3(position, 1.0f), {1.0f, 1.0f}, font->GetColour()), m_Text(text), m_Font(FontManager::Get(font->GetName()))
	{
	}
	
	Label::Label(const String& text, float x, float y, Font* font)
		: Label(text, {x, y}, font)
	{
	}

	Label::~Label()
	{
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawString(m_Text, m_Position.x, m_Position.y, m_Font);
	}

} }
