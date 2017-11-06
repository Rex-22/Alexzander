#pragma once

#include "al/graphics/renderer/IRenderer.h"
#include "al/graphics/renderables/Renderable2D.h"

#include "al/Common.h"
#include "Layer.h"

namespace al { namespace graphics {
	
	class AL_API Layer2D : public Layer
	{
	protected:
		
		Renderer* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;

		glm::mat4 m_ProjectionMatrix;
	protected :
		Layer2D(Renderer* renderer, Shader* shader, glm::mat4 projection);
	public :
		~Layer2D();

		inline virtual void Add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void OnRender() override;
	};

} }
