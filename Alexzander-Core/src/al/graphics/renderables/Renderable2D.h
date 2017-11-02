#pragma once

#include "al/graphics/buffers/buffer.h"
#include "al/graphics/buffers/IndexBuffer.h"
#include "al/graphics/buffers/VertexArray.h"

#include "al/graphics/renderer/Renderer2D.h"
#include "al/graphics/Shader.h"
#include "Texture.h"
#include "al/Common.h"

#include "glm/glm.hpp"

namespace al { namespace graphics {

	struct AL_API VertexData
	{
		glm::vec3 vertex;
		// maths::vec4 color;
		glm::vec2 uv;
		GLfloat tid;
		uint color;
	};

	class AL_API Renderable2D
	{
	protected:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		std::vector<glm::vec2> m_UV;
		glm::vec4 m_Color;
		Texture* m_Texture;
	protected :
		Renderable2D()
	{ SetUVDefaults(); }
	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
		{ SetUVDefaults(); }

		Renderable2D(glm::vec3 position, glm::vec2 size, Texture* texture)
			: m_Position(position), m_Size(size), m_Color({1.0f, 1.0f, 1.0f, 1.0f}), m_Texture(texture) 
		{
			SetUVDefaults();
		}

		virtual ~Renderable2D() { }

		virtual void Submit(Renderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const std::vector<glm::vec2>& getUV() const { return m_UV; }
		inline const glm::vec2& getSize() const { return m_Size; }
		inline const glm::vec4& getColor() const { return m_Color; }

		inline const uint GetTID() const
		{
			return m_Texture == nullptr ? 0 : m_Texture->GetID();
		}
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