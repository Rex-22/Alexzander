#pragma once
#include "glm/glm.hpp"

namespace al { namespace graphics {

	class Camera
	{
	private:
		glm::mat4 m_ProjectionMatrix;
	public:
		Camera(const glm::mat4& projectionMatrix);

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
	};

} }
