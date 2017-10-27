#pragma once

#include <glm/glm.hpp>

#include "glm/glm.hpp"
#include "../Renderable2D.h"

namespace al { namespace graphics {

	class AL_API Renderer2D
	{
	public:
		virtual void Begin() {}
		virtual void Submit(const Renderable2D* renderable) = 0;
		virtual void End() {}
		virtual void Flush() = 0;
	};

} }