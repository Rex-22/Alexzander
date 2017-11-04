#pragma once

#include "al/graphics/buffers/buffer.h"
#include "al/graphics/buffers/IndexBuffer.h"
#include "al/graphics/buffers/VertexArray.h"

#include "al/graphics/renderer/Renderer2D.h"
#include "al/graphics/Shader.h"
#include "al/graphics/Texture.h"
#include "al/Common.h"

#include "glm/glm.hpp"

namespace al { namespace graphics {

	struct VertexData
	{
		glm::vec3 vertex;
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
		uint m_Color;
		Texture* m_Texture;
	protected :
		Renderable2D()
	{ SetUVDefaults(); }
	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, uint color)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
		{ SetUVDefaults(); }

		Renderable2D(glm::vec3 position, glm::vec2 size, Texture* texture)
			: m_Position(position), m_Size(size), m_Color(0xffffffff), m_Texture(texture) 
		{ SetUVDefaults(); }

		virtual ~Renderable2D() { }

		virtual void Submit(Renderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		void setColor(uint color) { m_Color = color; }
		void setColor(const glm::vec4& color)
		{
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;
		
			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const std::vector<glm::vec2>& GetUV() const { return m_UV; }
		inline const glm::vec2& GetSize() const { return m_Size; }
		inline const uint GetColor() const { return m_Color; }
		inline const Texture& GetTexture() const { return *m_Texture; }

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