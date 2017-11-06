#include "al/al.h"
#include "Group.h"
#include "al/graphics/renderer/IRenderer.h"

namespace al { namespace graphics {
	
	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{
	}

	Group::~Group()
	{
		for (Renderable2D* renderable: m_Renderables)
			delete renderable;
	}

	void Group::Add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Group::Submit(Renderer* renderer) const
	{
		renderer->push(m_TransformationMatrix);

		for (const Renderable2D* renderable : m_Renderables)
			renderable->Submit(renderer);

		renderer->pop();
	}

} }
