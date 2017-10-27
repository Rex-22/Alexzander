#pragma once

#include "gl/gl.h"

#include "al/Common.h"

namespace al { namespace graphics {

	class AL_API IndexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_Count;
	public:
		IndexBuffer(GLushort* data, GLsizei count);
		IndexBuffer(GLuint* data, GLsizei count);
		~IndexBuffer();
		void bind() const;
		void unbind() const;

		inline GLuint getCount() const { return m_Count; }
	};

} }