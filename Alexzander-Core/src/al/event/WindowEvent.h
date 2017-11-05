#pragma once

#include "Event.h"
#include "glm/glm.hpp"

namespace al { namespace events {

	class AL_API ResizeWindowEvent : public Event
	{
	protected:
		glm::tvec2<uint> m_Size;
	public:
		ResizeWindowEvent(uint width, uint height);

		inline const glm::tvec2<uint>& GetSize() const { return m_Size; }
		inline const uint GetWidth() const { return m_Size.x; }
		inline const uint GetHeight() const { return m_Size.y; }
	public:
		inline static Type GetStaticType() { return Event::Type::WINDOW_RESIZE; }
	};

} }
