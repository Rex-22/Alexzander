#include "al/al.h"
#include "WindowEvent.h"

namespace al { namespace events {

	ResizeWindowEvent::ResizeWindowEvent(uint width, uint height)
		: Event(ResizeWindowEvent::GetStaticType()), m_Size(glm::tvec2<uint>(width, height))
	{
	}

} }