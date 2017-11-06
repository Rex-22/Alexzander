#pragma once

#include "al/al.h"
#include "Component.h"
#include "al/graphics/renderables/Sprite.h"

namespace al { namespace entity { namespace component {
	
	class AL_API SpriteComponent : public Component
	{
	private:
		graphics::Sprite m_Sprite;
	public :
		SpriteComponent(graphics::Sprite sprite);

		static ComponentType* GetStaticType()
		{
			static ComponentType type({ "Sprite" });
			return &type;
		}

		inline virtual ComponentType* GetType() const override { return GetStaticType(); }

		inline const graphics::Sprite* GetSprite() const { return &m_Sprite; }
		inline void SetSprite(const graphics::Sprite* sprite) { m_Sprite = *sprite; }
	};

} } }
