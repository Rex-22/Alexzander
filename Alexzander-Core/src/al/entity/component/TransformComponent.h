#pragma once

#include "al/al.h"
#include "Component.h"
#include "glm/glm.hpp"

namespace al { namespace entity { namespace component {
	
	class AL_API TransformComponent : public Component
	{
	private:
		glm::mat4 m_Transformation;
	public :
		TransformComponent(glm::mat4 transform);

		static ComponentType* GetStaticType()
		{
			static ComponentType type({ "Transform" });
			return &type;
		}

		inline virtual ComponentType* GetType() const override { return GetStaticType(); }

		inline const glm::mat4& GetTransform() const { return m_Transformation; }
		inline void SetTransform(const glm::mat4* transform) { m_Transformation = *transform; }
	};

} } }