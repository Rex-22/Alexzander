#pragma once

#include "../renderer/Renderer2D.h"
#include "../Renderable2D.h"

#include "al/Common.h"

namespace al { namespace graphics {
	
	class AL_API Layer2D
	{
	protected:
		
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;

		glm::mat4 m_ProjectionMatrix;
	protected :
		Layer2D(Renderer2D* renderer, Shader* shader, glm::mat4 projection);
	public :
		virtual ~Layer2D();

		inline virtual void Add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Render();
	};

} }
