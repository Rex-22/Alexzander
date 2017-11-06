#include "Entity.h"
#include "al/entity/component/Components.h"
namespace al { namespace entity {
	
	using namespace component;

	Entity::Entity()
	{
	}

	Entity::Entity(graphics::Sprite* sprite, const glm::mat4& transform)
	{
		AddComponent(new SpriteComponent(sprite));
		AddComponent(new TransformComponent(transform));
	}

	void Entity::AddComponent(component::Component* component)
	{
		AL_ASSERT(component->GetType());
		m_Components[component->GetType()] = component;
	}

} }
