#include "Layer2D.h"
#include "glm/gtc/matrix_transform.hpp"

namespace al { namespace graphics {
	
	Layer2D::Layer2D(Renderer2D* renderer, Shader* shader, glm::mat4 projection)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projection)
	{
		m_Shader->Enable();
		m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->Disable();	
	}

	Layer2D::~Layer2D()
	{
		//delete m_Shader;
		delete m_Renderer;

		for (int i = 0; i < m_Renderables.size(); ++i)
			delete m_Renderables[i];
	}

	void Layer2D::Render()
	{
		m_Shader->Enable();
		
		m_Renderer->Begin();
		for (const Renderable2D* renderable: m_Renderables)
			m_Renderer->Submit(renderable);
		m_Renderer->End();
		m_Renderer->Flush();
	}


} }
