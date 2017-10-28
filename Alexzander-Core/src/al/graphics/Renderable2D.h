#pragma once

#include "buffers/buffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexArray.h"

#include "renderer/Renderer2D.h"
#include "Shader.h"

#include "al/Common.h"

#include "glm/glm.hpp"

namespace al { namespace graphics {

	struct AL_API VertexData
	{
		glm::vec3 vertex;
		// maths::vec4 color;
		unsigned int color;
	};

	class AL_API Renderable2D
	{
	protected:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;
	protected :
		Renderable2D(){}
	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: m_Position(position), m_Size(size), m_Color(color)
		{ }

		virtual ~Renderable2D() { }

		virtual void Submit(Renderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		inline const glm::vec3& getPosition() const { return m_Position; }
		inline const glm::vec2& getSize() const { return m_Size; }
		inline const glm::vec4& getColor() const { return m_Color; }
	};

} }