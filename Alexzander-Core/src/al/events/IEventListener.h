#pragma once

#include "Event.h"

namespace al { namespace events {
	
	class AL_API IEventListener
	{
	public:
		virtual bool OnEvent(Event& event) = 0;
	};

} }