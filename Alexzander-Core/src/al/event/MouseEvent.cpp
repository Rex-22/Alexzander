#include "al/al.h"
#include "MouseEvent.h"

namespace al { namespace events {

	MouseButtonEvent::MouseButtonEvent(int32 button, float x, float y, Type type)
		: Event(type), m_Button(button), m_Position(glm::vec2(x, y))
	{
	}

	MousePressedEvent::MousePressedEvent(int32 button, float x, float y)
		: MouseButtonEvent(button, x, y, MousePressedEvent::GetStaticType())
	{
	}

	String MousePressedEvent::ToString() const
	{
		char buffer[256];
		sprintf(buffer, "MouseReleasedEvent: (%d, %f, %f)", GetButton(), GetX(), GetY());
		return String(buffer);
	}

	MouseReleasedEvent::MouseReleasedEvent(int32 button, float x, float y)
		: MouseButtonEvent(button, x, y, MouseReleasedEvent::GetStaticType())
	{
	}

	MouseMovedEvent::MouseMovedEvent(float x, float y, bool dragged)
		: Event(MouseMovedEvent::GetStaticType()), m_Position(glm::vec2(x, y)), m_Dragged(dragged)
	{
	}

} }