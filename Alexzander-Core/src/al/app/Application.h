#pragma once

#include "al/Common.h"

#include "al/graphics/Window.h"

namespace al { namespace app {
	
	class AL_API Application
	{
	public:
		virtual void Init() = 0;
		virtual void OnUpdate(float delta) const = 0;
		virtual void OnRender() const = 0;
	};

} }
