#pragma once

#include <vector>
#include "gl/gl.h"

#include "Buffer.h"

#include "al/Common.h"

namespace al { namespace graphics {

	class AL_API VertexArray
	{
	private:
		GLuint m_ArrayID;
		std::vector<Buffer*> m_Buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};

} }