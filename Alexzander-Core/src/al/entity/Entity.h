#pragma once

#include "al/al.h"
#include "al/Common.h"
#include "al/graphics/renderables/Sprite.h"
#include "al/entity/component/Component.h"
#include "glm/glm.hpp"

namespace al { namespace entity {
	
	class AL_API Entity
	{
	protected:
		std::unordered_map<component::ComponentType*, component::Component*> m_Components;
	public:
		Entity();
		Entity(graphics::Sprite* sprite, const glm::mat4& transform = glm::mat4(1.0f));

		void AddComponent(component::Component* component);

		template <typename T>
		const T* GetComponent() const
		{
			return GetComponentInternal<T>();
		}

		template <typename T>
		T* GetComponent()
		{
			return (T*)GetComponentInternal<T>();
		}
	private:
		template <typename T>
		const T* GetComponentInternal() const
		{
			component::ComponentType* type = T::GetStaticType();
			auto it = m_Components.find(type);
			if (it == m_Components.end())
				return nullptr;
			return (T*)it->second;
		}
	};
} }
