#pragma once

#include "Renderable2D.h"

#include "al/Common.h"

namespace al { namespace graphics {

	class AL_API Sprite : public Renderable2D
	{
	private:

	public:
		Sprite(float x, float y, float width, float height, const glm::vec4& color);
		Sprite(float x, float y, float width, float height, Texture* texture);
	};

} }
