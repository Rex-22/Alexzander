#pragma once

#include "Renderer2D.h"
#include "al/graphics/renderables/Renderable2D.h"
#include "al/graphics/buffers/IndexBuffer.h"

#include "al/graphics/Font.h"
#include "al/graphics/FontManager.h"

#include "al/Common.h"
#include "al/Types.h"


namespace al { namespace graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3

	class AL_API BatchRenderer2D : public Renderer2D
	{
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;
		VertexData* m_Buffer;

		std::vector<GLuint> m_TextureSlots;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void Begin() override;
		void Submit(const Renderable2D* renderable) override;
		void DrawString(const String& text, float x, float y, Font* font) override;
		void DrawString(const String& text, glm::vec2 position, Font* font);
		void End() override;
		void Flush() override;
	private:
		void Init();
	};

} }