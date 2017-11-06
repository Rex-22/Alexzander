#pragma once

#include "al/Common.h"

namespace al { namespace graphics {
	
	class AL_API Renderable
	{
	protected:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		std::vector<glm::vec2> m_UV;
		uint m_Colour;
		Texture* m_Texture;
	public :
		Renderable() = default;

		Renderable(glm::vec3 position, glm::vec2 size, uint colour)
		: m_Position(position), m_Size(size), m_Colour(colour), m_Texture(nullptr){}

		Renderable(glm::vec3 position, glm::vec2 size, Texture* texture)
		: m_Position(position), m_Size(size), m_Colour(0xffffffff), m_Texture(texture){}

		virtual void Submit(Renderer* renderer) const
		{
			renderer->Submit(this);
		}

		void SetColor(uint color) { m_Colour = color; }
		void SetColor(const glm::vec4& color)
		{
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			m_Colour = a << 24 | b << 16 | g << 8 | r;
		}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline virtual const std::vector<glm::vec2>& GetUV() const { return m_UV; }
		inline virtual const glm::vec2& GetSize() const { return m_Size; }
		inline virtual const uint GetColour() const { return m_Colour; }
		inline virtual const Texture& GetTexture() const { return *m_Texture; }

		inline const uint GetTID() const
		{
			return m_Texture == nullptr ? 0 : m_Texture->GetID();
		}
	};

} }