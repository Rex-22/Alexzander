#include "al/al.h"
#include "SpriteComponent.h"

namespace al { namespace entity { namespace component {
	
	SpriteComponent::SpriteComponent(graphics::Sprite* sprite)
		: m_Sprite(sprite)
	{
	}

} } }
