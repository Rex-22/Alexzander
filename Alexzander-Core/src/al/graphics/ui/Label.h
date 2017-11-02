#pragma once

#include "al/graphics/renderables/Renderable2D.h"

#include "al/Common.h"
#include "al/Types.h"

#include <glm/glm.hpp>

namespace al { namespace graphics {

	class AL_API Label : public Renderable2D
	{
	private:
		String m_Text;
	public:
		Label(const String& text, const glm::vec2 position);
		Label(const String& text, const glm::vec2 position, const glm::vec4& colour);
		Label(const String& text, float x, float y, const glm::vec4& colour);
		Label(const String& text, float x, float y);
		~Label();

		inline void SetText(const String& text) { this->m_Text = text; }

		void Submit(Renderer2D* renderable) const override;
	};

} }

