#include "al/al.h"
#include "Sprite.h"

namespace al { namespace graphics {
	
	Sprite::Sprite(Texture* texture) 
		:Renderable2D({ 0, 0, 0 }, { texture->GetWidth(), texture->GetHeight() }, texture)
	{	}

	Sprite::Sprite(float x, float y, Texture* texture)
		: Renderable2D({ x, y, 0 }, { texture->GetWidth(), texture->GetHeight() }, texture)
	{	}

	Sprite::Sprite(float x, float y, float width, float height, const uint color)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), color)
	{	}
	
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), texture)
	{	}

} }