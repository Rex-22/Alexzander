#pragma once

#include "Renderable2D.h"

#include "al/Common.h"

#include "gl/gl.h"

namespace al { namespace graphics {

	class AL_API BasicSprite : public Renderable2D
	{
	private:
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Shader& m_Shader;
	public:
		BasicSprite(float x, float y, float width, float height, const glm::vec4& color, Shader& shader);
		~BasicSprite();

		inline const VertexArray* getVAO() const { return m_VertexArray; }
		inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

		inline Shader& getShader() const { return m_Shader; }
	};

} }
