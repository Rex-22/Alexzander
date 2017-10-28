#pragma once

#include <deque>
#include "Renderer2D.h"
#include "../renderables/BasicSprite.h"

#include "al/Common.h"

namespace al { namespace graphics {

	class AL_API BasicRenderer2D : public Renderer2D
	{
	private:
		std::deque<const BasicSprite*> m_RenderQueue;
	public:
		void Submit(const Renderable2D* renderable) override;
		void Flush() override;
	};

} }