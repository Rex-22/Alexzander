#include "al/al.h"
#include "Camera.h"

namespace al { namespace graphics {
	
	Camera::Camera(const glm::mat4& projectionMatrix)
		:m_ProjectionMatrix(projectionMatrix)
	{
		
	}

} }
