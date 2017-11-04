#include "BasicSprite.h"

namespace al { namespace graphics {

	BasicSprite::BasicSprite(float x, float y, float width, float height, const glm::vec4& color, Shader& shader)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), new Texture("Default", "test.png")), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();
		GLfloat vertices[] =
		{
			0, 0, 0,
			0, height, 0,
			width, height, 0,
			width, 0, 0
		};

		GLfloat colors[] =
		{
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 2);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indices, 6);
	}


	BasicSprite::BasicSprite(float x, float y, float width, float height, uint color, Shader& shader)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), color), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();
		GLfloat vertices[] =
		{
			0, 0, 0,
			0, height, 0,
			width, height, 0,
			width, 0, 0
		};

		GLfloat colors[] =
		{
			GetColor(), 
			GetColor(), 
			GetColor(), 
			GetColor()
		};

		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 2);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indices, 6);
	}

	BasicSprite::BasicSprite(float x, float y, float width, float height, Texture& texture, Shader& shader) 
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), 0xffff00ff), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();
		GLfloat vertices[] =
		{
			0, 0, 0,
			0, height, 0,
			width, height, 0,
			width, 0, 0
		};

		GLfloat colors[] =
		{
			GetColor(),
			GetColor(),
			GetColor(),
			GetColor()
		};

		GLfloat uvs[] =
		{
			-1.0f, -1.0f,
			-1.0f,  1.0f,
			 1.0f,  1.0f,
			 1.0f, -1.0f
		};

		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(uvs, 2 * 4, 2), 1);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 2);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indices, 6);
	}

	BasicSprite::~BasicSprite()
	{
		delete m_VertexArray;
		delete m_IndexBuffer;
	}


} }