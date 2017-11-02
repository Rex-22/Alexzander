#include "Label.h"

namespace al { namespace graphics {
	
	Label::Label(const String& text, const glm::vec2 position, const glm::vec4& colour)
		:Renderable2D({position.x, position.y, 1.0f}, {1.0f, 1.0f}, colour), m_Text(text)
	{
	}

	Label::Label(const String& text, const glm::vec2 position)
		: Label(text, position, {1.0f, 1.0f, 1.0f, 1.0f})
	{
	}

	Label::Label(const String& text, float x, float y, const glm::vec4& colour)
		: Label(text, {x, y}, colour)
	{
	}
	
	Label::Label(const String& text, float x, float y)
		: Label(text, {x, y})
	{
	}

	Label::~Label()
	{
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawString(m_Text, m_Position.x, m_Position.y, m_Color);
	}

} }
