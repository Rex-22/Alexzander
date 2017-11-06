#pragma once

#include "al/graphics/buffers/buffer.h"
#include "al/graphics/buffers/IndexBuffer.h"
#include "al/graphics/buffers/VertexArray.h"

#include "al/graphics/renderer/IRenderer.h"
#include "al/graphics/Shader.h"
#include "al/graphics/Texture.h"
#include "al/Common.h"

#include "glm/glm.hpp"
#include "IRenderable.h"

namespace al { namespace graphics {

	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec2 uv;
		GLfloat tid;
		uint color;
	};

	class AL_API Renderable2D : public Renderable
	{
	protected :
		Renderable2D()
	{ SetUVDefaults(); }
	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, uint colour)
			: Renderable(position, size, colour)
		{ SetUVDefaults(); }

		Renderable2D(glm::vec3 position, glm::vec2 size, Texture* texture)
			: Renderable(position, size, texture)
		{ SetUVDefaults(); }

		virtual ~Renderable2D() { }
		
	private:
		inline void SetUVDefaults()
		{
			m_UV.push_back(glm::vec2(0, 0));
			m_UV.push_back(glm::vec2(0, 1));
			m_UV.push_back(glm::vec2(1, 1));
			m_UV.push_back(glm::vec2(1, 0));
		}
	};

} }
