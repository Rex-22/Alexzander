#pragma once

#include "al/graphics/renderables/Renderable2D.h"

#include "al/graphics/Font.h"

#include "al/Common.h"
#include "al/Types.h"

#include <glm/glm.hpp>

namespace al { namespace graphics {

	class AL_API Label : public Renderable2D
	{
	private:
		String m_Text;
		Font *m_Font;
	public:
		Label(const String& text, const glm::vec2 position, Font* font);

		Label(const String& text, float x, float y, Font* font);
		~Label();

		inline void SetText(const String& text) { this->m_Text = text; }

		void Submit(Renderer* renderable) const override;
	};

} }

