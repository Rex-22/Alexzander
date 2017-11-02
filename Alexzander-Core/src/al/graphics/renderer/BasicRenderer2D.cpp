#include "BasicRenderer2D.h"
#include "al/graphics/renderables/Renderable2D.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

namespace al { namespace graphics {

	void BasicRenderer2D::Submit(const Renderable2D* renderable)
	{
		glEnable(GL_TEXTURE_2D);
		m_RenderQueue.push_back((BasicSprite*) renderable);
	}

	void BasicRenderer2D::Flush()
	{
		while (!m_RenderQueue.empty())
		{
			const BasicSprite* sprite = m_RenderQueue.front();
			sprite->getVAO()->bind();
			sprite->getIBO()->bind();

			sprite->GetTexture().Bind();
			sprite->getShader().SetUniformMat4("ml_matrix", glm::translate(glm::mat4(1.0f), sprite->GetPosition()) * *m_LastMatrix);
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			sprite->getIBO()->unbind();
			sprite->getVAO()->unbind();

			m_RenderQueue.pop_front();
		}
	}


} }
