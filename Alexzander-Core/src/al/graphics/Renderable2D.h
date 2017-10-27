#pragma once

#include "Buffers/Buffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexArray.h"

#include "Shader.h"

#include "glm/glm.hpp"

#include "al/Common.h"

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
	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: m_Position(position), m_Size(size), m_Color(color)
		{ }

		virtual ~Renderable2D() { }

		inline const glm::vec3& getPosition() const { return m_Position; }
		inline const glm::vec2& getSize() const { return m_Size; }
		inline const glm::vec4& getColor() const { return m_Color; }
	};

} }