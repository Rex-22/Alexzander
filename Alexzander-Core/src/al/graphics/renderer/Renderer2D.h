#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "../Renderable2D.h"

namespace al { namespace graphics {

	class AL_API Renderer2D
	{
	protected:
		std::vector<glm::mat4> m_TransformationStack;

		const glm::mat4* m_LastMatrix;
	protected:
		Renderer2D()
		{
			m_TransformationStack.push_back(glm::mat4(1.0f));
			m_LastMatrix = &m_TransformationStack.back();
		}
	public:
		void push(glm::mat4 matrix, bool override = false)
		{
			if (override)
				m_TransformationStack.push_back(matrix);
			else 
				m_TransformationStack.push_back(*m_LastMatrix * matrix);

			m_LastMatrix = &m_TransformationStack.back();
		}

		void pop()
		{
			if (m_TransformationStack.size() > 1)
			{
				m_TransformationStack.pop_back();
				m_LastMatrix = &m_TransformationStack.back();
			}
		}

		virtual void Begin() {}
		virtual void Submit(const Renderable2D* renderable) = 0;
		virtual void End() {}
		virtual void Flush() = 0;
	};

} }