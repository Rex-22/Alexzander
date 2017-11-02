#pragma once

#include "al/Common.h"

#include "al/graphics/Window.h"

namespace al { namespace app {
	
	class AL_API Application
	{
	protected:
		int m_Frames = 0;
	public:
		virtual void Init() = 0;
		virtual void OnUpdate(float delta) = 0;
		virtual void OnRender() const = 0;

		inline void SetFrames(int frames) { this->m_Frames = frames; }
	};

} }
