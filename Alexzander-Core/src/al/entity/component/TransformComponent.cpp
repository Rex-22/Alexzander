#include "al/al.h"
#include "TransformComponent.h"

namespace al { namespace entity { namespace component {
	
	TransformComponent::TransformComponent(glm::mat4 transform)
		: m_Transformation(transform)
	{
	}


} } }